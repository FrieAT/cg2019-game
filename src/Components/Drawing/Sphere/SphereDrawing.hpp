#ifndef SphereDrawing_hpp
#define SphereDrawing_hpp

#include "IDrawing.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>
#define GLSL(src) "#version 330 core\n" #src
#include <vector>

class SphereDrawing : public IDrawing
{
public:
    void Init();
    void Draw(RenderManager* renderManager);
    void initializeColorValues();
    void initializeVertices();
    void initializeParameters();
    SphereDrawing();
    void organize(GLint posAttrib, GLint normAttrib, GLint uvAttrib);
    void draw(GLdouble time, GLint colAttrib, GLint shininessAttrib);
    void update(GLdouble time);
    void update_fall_pos(GLdouble time);
    void update_fall_neg(GLdouble time);
    void deleteBufferAndArray();
    float stageWidthHalf;
    float stageLengthHalf;
   
    float getCurrentCX();
   
    ~SphereDrawing();


    
    SphereDrawing generateBall(GLint posAttrib, GLint normAttrib, GLint uvAttrib);
    void SetFreeze(bool freeze);
    bool GetFreeze() { return _freeze; }
    void SetRoad(bool road) { _road = road; }
    bool GetRoad() { return _road; }
   
    float getRadius();
    
private:
    float _radius;
    float cx;
    float cy;
    float cz;
    float dx;
    float dy;
    double birthTime;
    float speed;
    float per;
    
    static constexpr float BRIGHTNESS = 1.0; // saturation of the color
    static constexpr float PI = 3.14159265358979323846;
    static constexpr float MAX_RADIUS = 0.2;
    static constexpr float MIN_RADIUS = 0.1;
    static constexpr float MIN_AMP = 0.3f;
    static constexpr float MAX_AMP = 0.9f;
     static constexpr float MAX_AMPL = 10;
    static constexpr float BRIGHTNESS_FACTOR = 0.5; // constant to set the maximal brightness for shadows to avoid totally white shadows
    static constexpr float MAX_PER = 5.0f;
    static constexpr float MIN_PER = 3.0f;
    
    static constexpr float MAX_SPEED = 1.9f;
    static constexpr float MIN_SPEED = 0.7f;
    static constexpr float STAGE_AREA_LENGTH_HALF = 2.5;
    static constexpr float STAGE_AREA_WIDTH_HALF = 1.0;
    
    float colorValues[2]  = { 0 };
    float vtx[18*36*12+38*6] = {0};
  
    glm::mat4 anim;
    glm::mat4 animPlane;
    
    GLuint vao;
    GLuint vbo;
    GLint posAttrib;
    GLint normAttrib;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint colAttrib ;
    GLint shininessAttrib;
    GLint uniformAnim;
    GLint uniformMode;
    
  

    GLdouble time ;
    bool _freeze = true;
    bool _road = true;
    float amp;
    bool _fallState = true;
 
};
#endif /* SphereDrawing_hpp */
