#ifndef AGENT_H__
#define AGENT_H__
#include "Vec3.h"
#include "World.h"
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

/// @class Agent a pure virtual base class for our Agent
/// factory.
class Agent
{
public:
  /// @brief ctor, this will auto increment the static id
  /// would be better to use a pool at some stage
  Agent(){ m_id=s_id++;}
  /// @brief dtor not used
  virtual ~Agent() {}
  /// @brief a simple init method to set the base values
  /// not used that often
  /// @param[in] _p the position
  /// @param[in] _d the direction
  virtual void init(const Vec3 &_p, const Vec3 &_d) = 0;
  /// @brief this method updates the Agent
  virtual void update() = 0;
  /// @brief render the agent
  virtual void render(const glm::mat4 &_project, GLuint _MVPID,GLuint _colourID) const = 0;
  /// @brief accessor for pos
  /// @returns m_pos
  Vec3 pos() const {return m_pos;}
  /// @brief accessor for dir
  /// @returns m_dir
  Vec3 dir() const {return m_dir;}
  /// @brief accessor for id
  /// @returns m_id
  int id() const {return m_id; }
  ///@brief mutator for pos
  /// @param[in] _p value to set m_pos;
  void setPos(const Vec3 &_p){m_pos=_p;}
  ///@brief mutator for dir
  /// @param[in] _d value to set m_dir;
  void setDir(const Vec3 &_d){m_dir=_d;}
  ///@brief set a pointer to the world for the agent
  /// this is the agents only access point for other agents
  /// @param[in] _w pointer to the world
  void setWorld(const World *_w){m_world=_w;}

protected :
  /// @brief  all agents have a position
  Vec3 m_pos;
  /// @brief  all agents have a direction
  Vec3 m_dir;
  /// @brief  we need to know about the world
  const World *m_world;
  /// @brief id for the agent this is allocated at
  /// construction as an increment to the s_id
  /// we use this to avoid self checks when doing the
  /// world collisions
  int m_id;
  /// @brief static initialiser count for the id
  static int s_id;

};


#endif
