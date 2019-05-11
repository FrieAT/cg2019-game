#ifndef SphereDrawing_hpp
#define SphereDrawing_hpp

#include "IDrawing.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#define GLSL(src) "#version 330 core\n" #src
#include <vector>

class SphereDrawing : public IDrawing
{
public:
    void Draw();
    void initializeColorValues();
    void initializeVertices();
    void initializeParameters();
    SphereDrawing();
    void organize(GLint posAttrib, GLint normAttrib);
    void draw(GLdouble time, GLint colAttrib, GLint uniformAnim, GLint uniformMode, GLint shininessAttrib);
    void update(GLdouble time);
    bool checkFinished();
    void SetRadius(float radius);
    void SetFacets(double facets);
    void deleteBufferAndArray();
    float getCurrentCX();
    float getCurrentCY();
    float getCZ();
    float stageWidthHalf;
    float stageLengthHalf;
   
    


    
    SphereDrawing generateBall(GLint posAttrib, GLint normAttrib);
   
    float getRadius();
    
private:
    float _radius; // Radius of the sphere.
    double _facets; // Amount of faces used for sphere.
    float cx; // the original x coordinate of the ball's center
    float cy; // the original y coordinate of the ball's center
    float cz; // the z coordinate of the ball's center
    float dx; // the shift of the x coordinate
    float dy; // the shift of the y coordinate
    double birthTime;
    float speed;
    float per; // the period of the sine curve
    float amp; // the amplitude of the sine curve
    float phase; // the phase of the sine curve
    
    static constexpr float BRIGHTNESS = 0.5; // saturation of the color
    static constexpr int ACCURACY = 36; // circles are drawn as regular 36-gon
    static constexpr float PI = 3.14159265358979323846;
    static constexpr float MAX_RADIUS = 0.2;
    static constexpr float MIN_RADIUS = 0.1;
    static constexpr float MIN_AMP = 2.5;
    static constexpr float MAX_AMP = 3;
    static constexpr float BRIGHTNESS_FACTOR = 0.5; // constant to set the maximal brightness for shadows to avoid totally white shadows
    static constexpr float MAX_PHASE = PI;
    static constexpr float MAX_PER = 2;
    static constexpr float MIN_PER = 0.5;
    
    static constexpr float MAX_SPEED = 1.2;
    static constexpr float MIN_SPEED = 0.5;
    static constexpr float STAGE_AREA_LENGTH_HALF = 2.5;
    static constexpr float STAGE_AREA_WIDTH_HALF = 1.0;
    
    float colorValues[3] = { 0 };
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
    
    int ballCount;
   std::vector<SphereDrawing> ballList;
    GLdouble time ;
    
};
#endif /* SphereDrawing_hpp */
