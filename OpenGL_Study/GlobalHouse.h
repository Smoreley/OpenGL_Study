#pragma once

// Window
static GLint RES_MULTI = 1;
static GLint WINDOW_WIDTH = 1280, WINDOW_HEIGHT = 720;
static const char *WINDOW_TITLE = "Study in the Blue";
static int monitor_res_width, monitor_res_height;

// FrameRate
const int SCREEN_FPS = 30;
const float SCREEN_TICKS_PER_FRAME = 1.0f / SCREEN_FPS;


// Rendering Stuff
static const GLfloat clear_color[] = { 0.0, 0.0, 0.1, 1.0 };
static const GLfloat one = 1.0f;