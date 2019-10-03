#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iostream>
#include "AgentFactory.h"
#include "FlockAgent.h"
#include "World.h"
#include "Command.h"
#include "glFunctions.h"
#include "Util.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


Command *alignment ;
Command *cohesion;
Command *separation;
Command *globalAim;
World world;
GLuint vertexBuffer;
GLuint shaderID;
GLuint colourUniform;
GLuint MVP;
// Include the Emscripten library only if targetting WebAssembly
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#define GL_FRAGMENT_PRECISION_HIGH 1
glm::mat4 project;


#include <GLFW/glfw3.h>

GLFWwindow* window;

// Handle GLFW Errors
static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

// Handle key presses
static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  std::cout<<"key "<<key<<'\n';

}

static void force_exit() {
  emscripten_force_exit(EXIT_FAILURE);
}

// Generate the frame data.
static void generate_frame() 
{
  // Clear the window with the background color
glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniformMatrix4fv(MVP,1,GL_FALSE,glm::value_ptr(project));

  glDrawArrays(GL_TRIANGLES, 0, 3);

  for(size_t i=0; i<world.numAgents(); ++i)
  {
    world.m_agents[i]->update();
  }
  for(size_t i=0; i<world.numAgents(); ++i)
  {
    world.m_agents[i]->render(project,MVP,colourUniform);
  }

//  std::cout<<"render \n";
  // Flip the double buffer
  glfwSwapBuffers(window);
  // Handle any events
  glfwPollEvents();
}

void loadBufferData()
{

  float m_size=3.0f;
    float vertexData[9] = {0, -m_size*2,0.0f,-m_size, m_size*2,0.0f,m_size, m_size*2,0.0f};
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertexData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(float) , (const GLvoid *)0);

}




int main()
{
  // Setup the Error handler
  glfwSetErrorCallback(error_callback);

  // Start GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Error: GLFW Initialization failed.");
    force_exit();
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create the display window
  window = glfwCreateWindow(800, 600, "Demo", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error: GLFW Window Creation Failed");
    glfwTerminate();
    force_exit();
  }

  // check command line arguments and set default if not passed
  int numAgents=400;
 // register the two different create methods to our factory
  AgentFactory::registerAgent("flock", FlockAgent::create);
  // now we are going to create some command for the flock agent
  //these will need to be added to the Agents once created
 alignment = new AlignmentCommand;
 cohesion= new CohesionCommand;
  separation= new SeparationCommand;
  globalAim= new GlobalAimCommand;
  // seed rng (can use a set seed for repeatable flocks)
  //srand(time(NULL));
  // create the world using a set size for easy experimentation
  const static int wsize=200;
    // register the two different create methods to our factory
  AgentFactory::registerAgent("flock", FlockAgent::create);

  world.set(-wsize,wsize,-wsize,wsize);
  // for speed going to resize the std::vector to the
  // size of the agent we want.
  world.m_agents.resize(numAgents);
  world.m_globalAim.set(randf(-wsize,wsize),randf(-wsize,wsize),0);
  globalAim->m_active=false;

// define this so I can easly switch between the two different
// demos, set to 1 for Flock 0 for simple
  // add the agents
  for(size_t i=0; i<world.numAgents(); ++i)
  {
    world.m_agents[i]=AgentFactory::createAgent("flock");
    ///  use a dynamic cast here so we can access the concrete
    /// type methods (Agent doesn't have all of them)
    FlockAgent *a=dynamic_cast<FlockAgent*>(world.m_agents[i]);
    if(a)
    {
      /// set the world
      a->setWorld(&world);
      /// add the commands (comment out to see individual effects)
      a->addCommand(alignment);
      a->addCommand(cohesion);
      a->addCommand(separation);
      a->setSize(2);
      // need to set random pos if using global aim else
      // flock centers on this
      a->addCommand(globalAim);
    }
  }


  // Setup the Key Press handler


  glfwSetKeyCallback(window, key_callback);
  // Select the window as the drawing destination
  glfwMakeContextCurrent(window);




  loadBufferData();
  shaderID=createShader();
  glUseProgram(shaderID);
  colourUniform=glGetUniformLocation(shaderID,"colour");
  MVP=glGetUniformLocation(shaderID,"MVP");
  std::cout<<"MVP "<<MVP<<'\n';
  glUniform3f(colourUniform,1.0f,0.0f,1.0f);
  project=glm::ortho(world.m_left,world.m_right,world.m_bottom,world.m_top,-1.0f,1.0f);
  std::cout << glm::to_string(project) << '\n';





  // Run the loop correctly for the target environment
//#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(generate_frame, 0, false);
//#else
//  // Display the window until ESC is pressed
//  while (!glfwWindowShouldClose(window)) {
      
//    generate_frame();
//  }
  // Clean up
}
