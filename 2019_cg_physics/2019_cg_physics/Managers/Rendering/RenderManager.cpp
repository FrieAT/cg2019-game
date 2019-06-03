#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderManager.hpp"
#include "WindowManager.hpp"
#include "ObjectManager.hpp"
#include "IDrawing.hpp"
#include "IPosition.hpp"
#include "IShader.hpp"
#include "ITexture.hpp"

RenderManager::RenderManager(const Game &engine)
: AbstractManager(engine)
, _currentCamera(nullptr)
{
    
}

void RenderManager::Initialize()
{
    auto objectManager = this->GetEngine().GetManager<ObjectManager>();
    
    /*
    auto cameras = objectManager->GetObjectsByName("Camera");
    
    auto cameraIt = cameras.begin();
    while(cameraIt != cameras.end())
    {
        if(!(*cameraIt)->IsActive()) {
            continue;
        }
        
        auto cameraPosition = dynamic_cast<IPosition*>((*cameraIt)->GetComponent(EComponentType::Position));
        auto cameraView = dynamic_cast<IView*>((*cameraIt)->GetComponent(EComponentType::View));
        if(cameraPosition != nullptr && cameraView != nullptr) {

            // Set the current Camera to render.
            _currentCamera = cameraView;
            
 
        }
        

        
        cameraIt++;
    }
    */
    
    auto objects = objectManager->GetObjectsByName("Opaque");
    auto it = objects.begin();
    while(it != objects.end())
    {
        if(!(*it)->IsActive()) {
            it++;
            continue;
        }
        
        auto shader = dynamic_cast<IShader*>((*it)->GetComponent(EComponentType::Shader));
        if(shader != nullptr) {
            GLuint shaderProgram;
            const std::string shaderId = shader->GetShaderId();
            auto shaderIt = _shaderPrograms.find(shaderId);
            if(shaderIt != _shaderPrograms.end()) {
                shaderProgram = (*shaderIt).second;
            } else {
                shaderProgram = glCreateProgram();
                for ( int i = 0; i < (int)EShaderType::MaxItem; i++ )
                {
                    EShaderType shaderType = static_cast<EShaderType>(i);
                    const char* shaderSource = shader->GetShaderSource(shaderType);
                    if(shaderSource != nullptr) {
                        GLuint glShader = glCreateShader(getShaderIdByType(shaderType));
                        glShaderSource(glShader, 1, &shaderSource, NULL);
                        glCompileShader(glShader);
                        
                        /* check whether the shader compiled without an error */
                        if (!checkShaderCompileStatus(glShader)) {
                            fprintf(stderr, "Shader did not compile\n"); // Output name of shader.
                            exit(EXIT_FAILURE);
                        }
                        
                        glAttachShader(shaderProgram, glShader);
                    }
                }
                
                glBindFragDataLocation(shaderProgram, 0, "outColor");
                glLinkProgram(shaderProgram);
                
                /* check whether the shader program linked without an error */
                if (!checkShaderProgramLinkStatus(shaderProgram)) {
                    fprintf(stderr, "Shader did not link\n");
                    exit(EXIT_FAILURE);
                }
                
                _shaderPrograms.insert(std::pair<const std::string, unsigned int>(shaderId, shaderProgram));
            }
            
            //Update attribute ids
            for(int i = 0; i < (int)EShaderAttrib::MaxItem; i++) {
                const char* attribStr = IShader::AttribStr((EShaderAttrib)i);
                int attribute = glGetAttribLocation(shaderProgram, attribStr);
                if(attribute != -1) {
                    shader->AddAttrib((EShaderAttrib)i, attribute);
                }
            }
            
            //Update uniform ids
            for(int i = 0; i < (int)EShaderUniform::MaxItem; i++) {
                const char* uniformStr = IShader::UniformStr((EShaderUniform)i);
                int uniforme = glGetUniformLocation(shaderProgram, uniformStr);
                if(uniforme != -1) {
                    shader->AddUniform((EShaderUniform)i, uniforme);
                }
            }
            
            shader->SetShaderProgram(shaderProgram);
        }
        it++;
    }
}

void RenderManager::Loop()
{
    auto windowManager = this->GetEngine().GetManager<WindowManager>();
    auto objectManager = this->GetEngine().GetManager<ObjectManager>();
    
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    auto cameras = objectManager->GetObjectsByName("Camera");
    
    auto cameraIt = cameras.begin();
    while(cameraIt != cameras.end())
    {
        if(!(*cameraIt)->IsActive()) {
            continue;
        }
        
        auto cameraPosition = dynamic_cast<IPosition*>((*cameraIt)->GetComponent(EComponentType::Position));
        auto cameraView = dynamic_cast<IView*>((*cameraIt)->GetComponent(EComponentType::View));
        if(cameraPosition != nullptr && cameraView != nullptr) {
            
            // Set the current Camera to render.
            _currentCamera = cameraView;
            
            auto objects = objectManager->GetObjectsByName("Opaque");
            auto it = objects.begin();
            while(it != objects.end())
            {
                auto shader = dynamic_cast<IShader*>((*it)->GetComponent(EComponentType::Shader));
                GLuint shaderProgram;
                if(shader != nullptr) {
                    shaderProgram = (GLuint)shader->GetShaderProgram();
                    glUseProgram(shaderProgram);
                    
                    //Camera Uniforms
                    GLint uniformCam = shader->GetUniform(EShaderUniform::CameraPosition);
                    if(uniformCam != -1) {
                        auto cameraVecPosition = cameraPosition->GetPosition();
                        glUniform3f(uniformCam, cameraVecPosition.x, cameraVecPosition.y, cameraVecPosition.z);
                    }
                    GLint uniformView = shader->GetUniform(EShaderUniform::CameraView);
                    if(uniformCam != -1) {
                        auto cameraMat4View = cameraView->GetView();
                        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameraMat4View));
                    }
                    GLint uniformProj = shader->GetUniform(EShaderUniform::CameraProjection);
                    if(uniformCam != -1) {
                        auto cameraMat4Projection = cameraView->GetProjection();
                        glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(cameraMat4Projection));
                    }
                    
                    Matrix4 parentTransform = Matrix4(1.0f);
                    
                    updateTransformRecursive((*it), parentTransform);
                }
                it++;
            }
        }
        cameraIt++;
    }
    
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(windowManager->GetWindow());
}

GLint RenderManager::getUniformId(GLint shaderProgram, const char* uniformName)
{
    GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
    //TODO: exception handling if uniform -1
    return uniform;
}

GLint RenderManager::getAttribId(GLint shaderProgram, const char* attributeName)
{
    GLint attribute = glGetAttribLocation(shaderProgram, attributeName);
    //TODO: exception handling if attribute -1
    std::cout << "For Attribute " << attributeName << " given id is: " << attribute << std::endl;
    return attribute;
}

GLuint RenderManager::getShaderIdByType(EShaderType shaderType)
{
    switch(shaderType)
    {
        case EShaderType::VertexShader:
            return GL_VERTEX_SHADER;
        case EShaderType::FragmentShader:
            return GL_FRAGMENT_SHADER;
        default:
            return GL_INVALID_ENUM;
    }
}

bool RenderManager::checkShaderCompileStatus(GLuint shaderID)
{
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new char[length + 1];
        glGetShaderInfoLog(shaderID, length, &length, &log[0]);
        fprintf(stderr, "%s", log);
        return false;
    }
    return true;
}

bool RenderManager::checkShaderProgramLinkStatus(GLuint programID)
{
    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = new char[length + 1];
        glGetProgramInfoLog(programID, length, &length, &log[0]);
        fprintf(stderr, "%s", log);
        return false;
    }
    return true;
}

void RenderManager::updateTransformRecursive(GameObject* transform, Matrix4 parentTransform)
{
    auto shader = dynamic_cast<IShader*>(transform->GetComponent(EComponentType::Shader));
    auto drawing = dynamic_cast<IDrawing*>(transform->GetComponent(EComponentType::Drawing));
    auto position = dynamic_cast<IPosition*>(transform->GetComponent(EComponentType::Position));
    auto texture = dynamic_cast<ITexture*>(transform->GetComponent(EComponentType::Texture));
    
    if(position != nullptr) {
    
        Vector3 vecPosition = position->GetPosition();
        Vector3 vecScale = position->GetScale();
        
        Matrix4 modelRotation = position->GetRotation();
        Matrix4 modelScale = glm::scale(Matrix4(1.0f), vecScale);
        Matrix4 modelTranslation = glm::translate(Matrix4(1.0f), vecPosition);
        Matrix4 anim = parentTransform * (modelTranslation * modelScale * modelRotation);
   
        if(transform->HasChilds()) {
            parentTransform = Matrix4(1.0f);
        }
        
        parentTransform = anim;
        
        GLint enableTexture = shader->GetUniform(EShaderUniform::EnableTexture);
        if(enableTexture != -1) {
            glUniform1i(enableTexture, 0);
        }
        
        if(texture != nullptr)
        {
            texture->Texture();
        }
        
        if(drawing != nullptr)
        {
            /* define a transformation matrix for the model-matrice */
            if(shader != nullptr) {
                GLint uniformAnim = shader->GetUniform(EShaderUniform::Model);
                if(uniformAnim != -1) {
                    glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
                }
            }
            
            drawing->Draw(this);
        }
        
        if(transform->HasChilds()) {
            auto it = transform->GetChildsIterator();
            while(it != transform->GetChildsIteratorEnd()) {
                updateTransformRecursive((*it), parentTransform);
                it++;
            }
        }
    }
}
