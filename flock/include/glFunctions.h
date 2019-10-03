#ifndef GL_FUNCTIONS_H_
#define GL_FUNCTIONS_H_
#ifdef EMSCRIPTEN
#   include <GLES2/gl2.h>
#   include "emscripten.h"
#else
// OSX only - change on other platforms
#   include <OpenGL/gl3.h>
#endif

extern GLuint createShader();


#endif
