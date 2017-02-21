#pragma once

// Only Include files that rarely if ever change

/* Include Standard Library Files */
#include <iostream>
#include <vector>

/* Include glew (helps in loading openGL and gives us access to higher versions) */
#define GLEW_STATIC
#include <GL/glew.h>

/* Include GLFW (window context creation) */
#include <GLFW/glfw3.h>

/* Include GLM (OpenGL Mathematics) */
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>