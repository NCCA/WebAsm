#ifdef EMSCRIPTEN
#   include <GLES2/gl2.h>
#   include "emscripten.h"
#else
// OSX only - change on other platforms
#   include <OpenGL/gl3.h>
#endif

#include <string>
#include <iostream>

void printInfoLog(const GLuint &_obj  )
{
  GLint infologLength = 0;
  GLint charsWritten  = 0;

  glGetShaderiv(_obj, GL_INFO_LOG_LENGTH,&infologLength);
  std::cerr<<"info log length "<<infologLength<<"\n";
  if(infologLength > 0)
  {
    std::unique_ptr<char []>infoLog( new char[infologLength]);
    glGetShaderInfoLog(_obj, infologLength, &charsWritten, infoLog.get());

    std::cerr<<infoLog.get()<<'\n';
    glGetShaderiv(_obj, GL_COMPILE_STATUS,&infologLength);
    if( infologLength == GL_FALSE)
    {
      std::cerr<<"Shader compile failed or had warnings \n";
      exit(EXIT_FAILURE);
    }
  }

}


GLuint createShader()
{
 // here we create a program
 auto shaderID=glCreateProgram();
 // some raw data for our vertex shader
 const std::string vertex =
 R"(#version 300 es
 precision highp float;

layout(location=0) in vec3  inPosition;
uniform vec3 position;
uniform mat4 MVP;
void main()
{

 vec4 pos=MVP*vec4(inPosition,1);
 gl_Position = pos;
}
)";
  // create a Vertex shader object
  GLuint vertexID=glCreateShader(GL_VERTEX_SHADER);
  // attatch the shader source we need to convert to GL format
  const char* source=vertex.c_str();
  glShaderSource(vertexID,1,&source,NULL);
  // now compile the shader
  glCompileShader(vertexID);
  std::cerr<<"compiling vertex shader\n";
  printInfoLog(vertexID);
  // some source for our fragment shader
  const std::string fragment =
  R"(#version 300 es
  precision highp float;
  layout(location=0) out vec4 fragColour;
uniform vec3 colour;

void main()
{
fragColour = vec4(colour,1.0);
}
  )";
// now create a fragment shader
  GLuint fragmentID=glCreateShader(GL_FRAGMENT_SHADER);
  // attatch the shader source
  source=fragment.c_str();
  glShaderSource(fragmentID,1,&source,NULL);
  // compile the shader
  std::cerr<<"compiling frag shader shader\n";
  glCompileShader(fragmentID);
  printInfoLog(fragmentID);
  // now attach to the program object
  glAttachShader(shaderID,vertexID);
  glAttachShader(shaderID,fragmentID);

  // link the program
  glLinkProgram(shaderID);
  // and enable it for use
  glUseProgram(shaderID);
  // now tidy up the shaders as we don't need them
  glDeleteShader(vertexID);
  glDeleteShader(fragmentID);
  return  shaderID;
}
