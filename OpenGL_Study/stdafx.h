#pragma once
// Only Include files that rarely if ever change

/* Include Standard Library Files */
#include <iostream>
#include <vector>

/* File Creation stuff */
#include <fstream>

/* Time */
#include <chrono>
#include <ctime>

/* Include glew (helps in loading openGL and gives us access to higher versions) */
#define GLEW_STATIC
#include <GL/glew.h>

/* Include GLFW (window context creation) */
#include <GLFW/glfw3.h>

/* Include GLM (OpenGL Mathematics) */
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* TypeDefs for some math variables */
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat4x4 mat4;
//typedef glm::ivec3 ivec3;
typedef glm::ivec4 ivec4;


/* Include GLI (Image Loading) */
#include <gli/gli.hpp>

/* My global stuff */
// Window
static GLint RES_MULTI = 1;
//static GLint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
static GLint WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;
static const char *WINDOW_TITLE = "Study in the Blue";
static int monitor_res_width, monitor_res_height;

// FrameRate
const int SCREEN_FPS = 30;
const float SCREEN_TICKS_PER_FRAME = 1.0f / SCREEN_FPS;

// Rendering Stuff
static const GLfloat clear_color[] = { 0.0, 0.1, 0.2, 1.0 };
static const GLfloat one = 1.0f;