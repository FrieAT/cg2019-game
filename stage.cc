/* standard includes */
#include<stdio.h>
#include<stdlib.h>

/* We use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* SOIL is used for loading (texture) images */
//#include <SOIL.h>
/* GLFW is used for creating and manipulating graphics windows */
#include<GLFW/glfw3.h>
/* GLNM is used for handling vector and matrix math */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLSL(src) "#version 330 core\n" #src
#define GLM_FORCE_RADIANS

const GLfloat SPEED = 0.01f;
const GLfloat STAGE_AREA_LENGTH_HALF = 2.0f;
const GLfloat STAGE_AREA_WIDTH_HALF = 1.0f;

int dir = -1;

/*                                                                           */
/* GLFW callback functions for event handling                                */
/*                                                                           */
static void errorCallback(int error, const char* description)
{
   fprintf(stderr, "GLFW error %d: %s\n", error, description);
}


static void keyCallback(GLFWwindow* myWindow, int key, int scanCode,
                         int action, int mod)
{
   if (((key == GLFW_KEY_ESCAPE) || (key == GLFW_KEY_Q))  &&
       (action == GLFW_PRESS)) {
      /* close window upon hitting the escape key or Q/q */
      glfwSetWindowShouldClose(myWindow, GL_TRUE);
	} else if ((key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS)) {
		dir = 0;
	} else if ((key == GLFW_KEY_LEFT) && (action == GLFW_PRESS)) {
		dir = 1;
	} else if ((key == GLFW_KEY_DOWN) && (action == GLFW_PRESS)) {
		dir = 2;
	} else if ((key == GLFW_KEY_UP) && (action == GLFW_PRESS)) {
		dir = 3;
	} else if ((key == GLFW_KEY_RIGHT) && (action == GLFW_RELEASE)) {
		dir = -1;
	} else if ((key == GLFW_KEY_LEFT) && (action == GLFW_RELEASE)) {
		dir = -1;
	} else if ((key == GLFW_KEY_DOWN) && (action == GLFW_RELEASE)) {
		dir = -1;
	} else if ((key == GLFW_KEY_UP) && (action == GLFW_RELEASE)) {
		dir = -1;
	}
}


bool checkShaderCompileStatus(GLuint shaderID)
{
   GLint status;
   glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
   if(status == GL_FALSE) {
      GLint length;
      glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
      GLchar* log = new char[length + 1];
      glGetShaderInfoLog(shaderID, length, &length, &log[0]);
      fprintf(stderr, "%s", log);
      return false;
   }
   return true;
}


bool checkShaderProgramLinkStatus(GLuint programID)
{
   GLint status;
   glGetProgramiv(programID, GL_LINK_STATUS, &status);
   if(status == GL_FALSE) {
      GLint length;
      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
      GLchar* log = new char[length + 1];
      glGetProgramInfoLog(programID, length, &length, &log[0]);
      fprintf(stderr, "%s", log);
      return false;
   }
   return true;
}


int main()
{
   /* window dimensions */
   const GLuint WIDTH = 800, HEIGHT = 600;

   /*                                                                        */
   /* initialization and set-up                                              */
   /*                                                                        */
   /* initialization of GLFW */
   glfwSetErrorCallback(errorCallback);
   if (glfwInit() != GLFW_TRUE) {
      fprintf(stderr, "Cannot initialize GLFW\n");
      exit(EXIT_FAILURE);
   }

   /* set some GLFW options: we require OpenGL 3.3 (or more recent) context */
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   /* create GFLW window (monitor in windowed mode), do not share resources */
   GLFWwindow* myWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Demo",
                                           NULL, NULL);
   if (myWindow == NULL) {
      fprintf(stderr, "Cannot open GLFW window\n");
      exit(EXIT_FAILURE);
   }
   glfwMakeContextCurrent(myWindow);

   /* initialization of GLEW */
   glewExperimental = GL_TRUE;
   GLenum glewStatus = glewInit();
   if (glewStatus != GLEW_OK) {
      fprintf(stderr, "Error: %s\n", glewGetErrorString(glewStatus));
      exit(EXIT_FAILURE);
   }

   if (!GLEW_VERSION_2_0) {
      fprintf(stderr, "Error: GPU does not support GLEW 2.0\n");
      exit(EXIT_FAILURE);
   }


   /* define and compile the vertex shader */
   const char* vertexShaderSource = GLSL(
      in vec3 position;
      in vec3 colorVtxIn;
      out vec3 colorVtxOut;
      uniform mat4 proj;
      uniform mat4 view;
		uniform mat4 anim;
      void main() {
         gl_Position = proj * view * anim * vec4(position, 1.0);
         colorVtxOut = colorVtxIn;
      }
   );
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   /* check whether the vertex shader compiled without an error */
   if (!checkShaderCompileStatus(vertexShader)) {
      fprintf(stderr, "Vertex shader did not compile\n");
      exit(EXIT_FAILURE);
   }

   /* define and compile the fragment shader */
   const char* fragmentShaderSource = GLSL(
      in vec3 colorVtxOut;
      out vec4 outColor;
      void main() {
         outColor = vec4(colorVtxOut, 1.0f);
      }
   );
   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   /* check whether the fragment shader compiled without an error */
   if (!checkShaderCompileStatus(fragmentShader)) {
      fprintf(stderr, "Fragment shader did not compile\n");
      exit(EXIT_FAILURE);
   }

   /* create a shader program by linking the vertex and fragment shader */
   GLuint shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glBindFragDataLocation(shaderProgram, 0, "outColor");
   glLinkProgram(shaderProgram);

   /* check whether the shader program linked without an error */
   if (!checkShaderProgramLinkStatus(shaderProgram)) {
      fprintf(stderr, "Shader did not link\n");
      exit(EXIT_FAILURE);
   }

   /* make the shader program active */
   glUseProgram(shaderProgram);

   /*                                                                        */
   /* define and allocate graphics objects and resources: quad               */
   /*                                                                        */
   GLfloat vtx[] = {
      -STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF, /* bottom */
       STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF, /* top */
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF, /* front */
       STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF, /* back */
      -STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF, /* left */
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF,
      -STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF, /* right */
       STAGE_AREA_LENGTH_HALF,-1.0f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-1.0f, STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f,-STAGE_AREA_WIDTH_HALF,
       STAGE_AREA_LENGTH_HALF,-0.96f, STAGE_AREA_WIDTH_HALF
    };

 GLfloat vtx2[] = {
      -0.2f,-0.96f,-0.2f, /* bottom */
       0.2f,-0.96f,-0.2f,
      -0.2f,-0.96f, 0.2f,
       0.2f,-0.96f,-0.2f,
       0.2f,-0.96f, 0.2f,
      -0.2f,-0.96f, 0.2f,
      -0.2f,-0.25f,-0.2f, /* top */
      -0.2f,-0.25f, 0.2f,
       0.2f,-0.25f,-0.2f,
       0.2f,-0.25f,-0.2f,
      -0.2f,-0.25f, 0.2f,
       0.2f,-0.25f, 0.2f,
      -0.2f,-0.96f, 0.2f, /* font */
       0.2f,-0.96f, 0.2f,
      -0.2f,-0.25f, 0.2f,
       0.2f,-0.96f, 0.2f,
       0.2f,-0.25f, 0.2f,
      -0.2f,-0.25f, 0.2f,
      -0.2f,-0.96f,-0.2f, /* back */
      -0.2f,-0.25f,-0.2f,
       0.2f,-0.96f,-0.2f,
       0.2f,-0.96f,-0.2f,
      -0.2f,-0.25f,-0.2f,
       0.2f,-0.25f,-0.2f,
      -0.2f,-0.96f, 0.2f, /* left */
      -0.2f,-0.25f,-0.2f,
      -0.2f,-0.96f,-0.2f,
      -0.2f,-0.96f, 0.2f,
      -0.2f,-0.25f, 0.2f,
      -0.2f,-0.25f,-0.2f,
       0.2f,-0.96f, 0.2f, /* right */
       0.2f,-0.96f,-0.2f,
       0.2f,-0.25f,-0.2f,
       0.2f,-0.96f, 0.2f,
       0.2f,-0.25f,-0.2f,
       0.2f,-0.25f, 0.2f,
    };

   /* create and bind two Vertex Array Objects */
   GLuint myVAO[2];
   glGenVertexArrays(2, &myVAO[0]);
   glBindVertexArray(myVAO[0]);

   /**********************/
   /* first VAO setup */
   /* generate and bind one Vertex Buffer Object */
   GLuint myVBO[2];
   glGenBuffers(1, &myVBO[0]);
   glBindBuffer(GL_ARRAY_BUFFER, myVBO[0]);;

   /* copy the vertex data to it */
   glBufferData(GL_ARRAY_BUFFER, sizeof(vtx), vtx, GL_STATIC_DRAW);

   /* define how the input is organized */
   const char* attributeName;
   attributeName = "position";
   GLint posAttrib = glGetAttribLocation(shaderProgram, attributeName);
   if (posAttrib == -1) {
      fprintf(stderr, "Error: could not bind attribute %s\n", attributeName);
      exit(EXIT_FAILURE);
   }
   glEnableVertexAttribArray(posAttrib);
   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                         3 * sizeof(GLfloat), 0);

	attributeName = "colorVtxIn";
   GLint colAttrib = glGetAttribLocation(shaderProgram, attributeName);
   if (colAttrib == -1) {
      fprintf(stderr, "Error: could not bind attribute %s\n", attributeName);
      exit(EXIT_FAILURE);
   }

   /* second VAO setup */
   /* generate and bind one Vertex Buffer Object */
   glBindVertexArray(myVAO[1]);
   glGenBuffers(1, &myVBO[1]);
   glBindBuffer(GL_ARRAY_BUFFER, myVBO[1]);

   /* copy the vertex data to it */
   glBufferData(GL_ARRAY_BUFFER, sizeof(vtx2), vtx2, GL_STATIC_DRAW);

   glEnableVertexAttribArray(posAttrib);
   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
                         3 * sizeof(GLfloat), 0);

   glBindVertexArray(0);

   /* define a view transformation */
   glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.0f, 3.5f),
                                glm::vec3(0.0f, 0.0f, 0.0f),
                                glm::vec3(0.0f, 1.0f, 0.0f));

   /* define a  projection transformation */
   glm::mat4 proj = glm::perspective(glm::radians(60.0f), 4.0f/3.0f, 0.1f, 10.0f);

	/* define a transformation matrix for the animation */
   glm::mat4 anim = glm::mat4(1.0f);

   /* bind uniforms and pass data to the shader program */
   const char* uniformName;
   uniformName = "view";
   GLint uniformView = glGetUniformLocation(shaderProgram, uniformName);
   if (uniformView == -1) {
      fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
      exit(EXIT_FAILURE);
   }
   glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));

   uniformName = "proj";
   GLint uniformProj = glGetUniformLocation(shaderProgram, "proj");
   if (uniformProj == -1) {
      fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
      exit(EXIT_FAILURE);
   }
   glUniformMatrix4fv(uniformProj, 1, GL_FALSE, glm::value_ptr(proj));

	uniformName = "anim";
   GLint uniformAnim = glGetUniformLocation(shaderProgram, uniformName);
   if (uniformAnim == -1) {
      fprintf(stderr, "Error: could not bind uniform %s\n", uniformName);
      exit(EXIT_FAILURE);
   }
   glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));

   /* register callback functions */
   glfwSetKeyCallback(myWindow, keyCallback);

	/* create matrix for moving player */
	glm::mat4 animPlayer = glm::mat4(1.0f);

	GLfloat curTrans [3] = { 0.0f, 0.0f, 0.0f }; // for getting correct current translation

   /*                                                                        */
   /* event-handling and rendering loop                                      */
   /*                                                                        */
   while (!glfwWindowShouldClose(myWindow)) {
      /* set the window background to black */
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      /* draw the first VAO */
      glBindVertexArray(myVAO[0]);		// select first VAO
      glVertexAttrib3f(colAttrib, 0.65f, 0.65f, 0.65f); // set constant color attribute

		/* do not translate (move) the second object */
		//anim = glm::mat4(1.0f);
		glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(anim));

      glDrawArrays(GL_TRIANGLES, 0, 36);

      /* draw the second VAO */
      glBindVertexArray(myVAO[1]);		// select second VAO
      glVertexAttrib3f(colAttrib, 1.0f, 0.0f, 0.0f); // set constant color attribute

		/* translate (move) the second object */
      if (dir == 0) {
			if ((curTrans[0] + SPEED) <= (STAGE_AREA_LENGTH_HALF - SPEED))
				curTrans[0] = curTrans[0] + SPEED;
			//dir = -1;
      } else if (dir == 1) {
			if ((curTrans[0] - SPEED) >= (-STAGE_AREA_LENGTH_HALF + SPEED))
				curTrans[0] = curTrans[0] - SPEED;
			//dir = -1;
		} else if (dir == 2) {
			if ((curTrans[2] + SPEED) <= (STAGE_AREA_WIDTH_HALF - SPEED))
				curTrans[2] = curTrans[2] + SPEED;
			//dir = -1;
		} else if (dir == 3) {
			if ((curTrans[2] - SPEED) >= (-STAGE_AREA_WIDTH_HALF + SPEED))
				curTrans[2] = curTrans[2] - SPEED;
			//dir = -1;
		}

		animPlayer = glm::translate(anim, glm::vec3(curTrans[0], curTrans[1], curTrans[2]));
		glUniformMatrix4fv(uniformAnim, 1, GL_FALSE, glm::value_ptr(animPlayer));

      glDrawArrays(GL_TRIANGLES, 0, 36);

      /* Swap buffers */
      glfwSwapBuffers(myWindow);

      /* poll events */
      glfwPollEvents();
   }

   /*                                                                        */
   /* clean-up and release resources                                         */
   /*                                                                        */

   glUseProgram(0);
   glDetachShader(shaderProgram, vertexShader);
   glDetachShader(shaderProgram, fragmentShader);
   glDeleteShader(fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteProgram(shaderProgram);

   glDeleteBuffers(2, myVBO);

   glDeleteVertexArrays(2, myVAO);


   /*                                                                        */
   /* termination of GLFW                                                    */
   /*                                                                        */
   glfwTerminate();

   exit(EXIT_SUCCESS);
}
