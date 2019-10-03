#ifndef FLOCKAGENT_H__
#define FLOCKAGENT_H__
#include "Agent.h"
#include "World.h"
#include "Command.h"
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/// @class FlockAgent will create a simple Craig Reynolds style
/// flocking system see  http://www.red3d.com/cwr/boids/ for
/// more details, the basic algorithm used here is based on
/// Flocking by Daniel Shiffman which comes from the processing
/// demos https://processing.org/examples

class FlockAgent : public Agent
{
  public:
    /// @brief init the agent to default values
    void init(const Vec3 &_p, const Vec3 &_d) override;
    /// @brief this runs the commands for the agent
    void update() override;
    /// @brief render the agents
    void render(const glm::mat4 &_project, GLuint _MVP,GLuint _colourID)const override;
    /// @brief the create function is used by the
    /// factory
    static Agent *create() { return new FlockAgent; }
    /// @brief this adds a command to the command queue
    /// for the agent they are execute in order of insertion
    /// using a std::vector
    /// @param _c the command to use
    void addCommand(Command *_c){m_commands.push_back(_c);}
    /// @brief the alignment behaviour
    void alignment();
    /// @brief the separation behaviour
    void separation();
    /// @brief the cohesion behaviour
    void cohesion();
    /// @brief the cohesion behaviour
    void globalAim();
    /// @brief set the size
    void setSize(float _s){m_size=_s;}

  private :
    /// @brief ctor private so can only be created with the
    /// factory
    FlockAgent();
    /// @brief the colour of the agent for rendering
    Vec3 m_colour;
    /// @brief the alignment force to add to the position
    Vec3 m_alignment;
    /// @brief the cohesion force to add to the position
    Vec3 m_cohesion;
    /// @brief the seperation force to add to the position
    Vec3 m_seperation;
    /// @brief the agents velocity
    /// @brief the cohesion force to add to the position
    Vec3 m_globalAim;
    Vec3 m_velocity;
    /// @brief the agents acceleration
    Vec3 m_acceleration;
    // @brief the agents ID
    int m_agentID;
    ///@brief maximum steering force
    float m_maxforce;
    /// @brief maximum speed
    float m_maxspeed;
    /// @brief size for drawing / colliding
    float m_size;
    /// @brief our command queue
    std::vector<Command *>m_commands;
    std::vector<Agent *> m_local;

};

#endif
