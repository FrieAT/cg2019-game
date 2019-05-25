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
                }
                else {
                    shaderProgram = windowManager->getDefaultShaderProgram();
                }
                glUseProgram(shaderProgram);
                
                //Camera Uniforms
                GLint uniformCam = getUniformId(shaderProgram, "cameraPosition");
                if(uniformCam != -1) {
                    auto cameraVecPosition = cameraPosition->GetPosition();
                    glUniform3f(uniformCam, cameraVecPosition.x, cameraVecPosition.y, cameraVecPosition.z);
                }
                GLint uniformView = getUniformId(shaderProgram, "view");
                if(uniformCam != -1) {
                    auto cameraMat4View = cameraView->GetView();
                    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(cameraMat4View));
                }
                GLint uniformProj = getUniformId(shaderProgram, "proj");
                if(uniformCam != -1) {
                    auto cameraMat4Projection = cameraView->GetProjection();
                    glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(cameraMat4Projection));
                }
                
                //Shader Attribs.
                //TODO: Move to IView.
                //TODO: Refactoring needed.
                posAttrib = getAttribId(shaderProgram, "positionIn");
                normAttrib = getAttribId(shaderProgram, "normalIn");
                colAttrib = getAttribId(shaderProgram, "colorVtxIn");
                shininessAttrib = getUniformId(shaderProgram, "shininess");
                
                auto drawing = dynamic_cast<IDrawing*>((*it)->GetComponent(EComponentType::Drawing));
                auto position = dynamic_cast<IPosition*>((*it)->GetComponent(EComponentType::Position));
                
                if(position != nullptr && drawing != nullptr)
                {
                    glm::mat4 anim = glm::translate(Matrix4(1.0f), position->GetPosition());
                    /* define a transformation matrix for the animation */
                    GLint uniformAnim = getUniformId(shaderProgram, UniformAnim.c_str());
                    if(uniformAnim != -1) {
                        glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));
                    }
                    
                    
                    drawing->Draw(this);
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
