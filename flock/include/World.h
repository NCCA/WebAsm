#ifndef WORLD_H__
#define WORLD_H__
#include "Vec3.h"
#include <vector>
#include <cassert>
// can't include here due to include guard but as
// we don't use any methods we can pre-declare the class
class Agent;
// this is a very simple class and makes sense to make it
// public for access (could use struct)
class World
{
public :
  /// @brief ctor
  World()=default;
  void set(float _l, float _r,float _b, float _t)
  {
    m_left=_l;
    m_right=_r;
    m_bottom=_b;
    m_top=_t;

  }
  World(float _l, float _r,float _b, float _t) :
    m_left(_l),m_right(_r),m_bottom(_b),m_top(_t)
  {
    /// note rather than using a singleton we use a
    /// static assert here to tell the programmer we
    /// can only have one world, see
    /// http://gameprogrammingpatterns.com/singleton.html
    /// for a discussion of this
    assert(!s_instantiated && "Can only be one World!");
    s_instantiated = true;
  }
  /// @brief get the number of Agents
  size_t numAgents() const {return m_agents.size();}
  /// @brief as this is expensive do it once a frame
  void calculateFlockCenter();
  /// @brief access the flock center value
  Vec3 getFlockCenter() const {return m_flockCenter;}
  /// @brief find local Agents using a simple AABB test
  /// @param _id the id of the agent tested so we don't self test
  /// @param _p the current position of the agent
  /// @param _dx the x extents of the AABB
  /// @param _dy the y extents of the AABB
  /// @param _dz the z extents of the AABB
  std::vector<Agent *> findLocalAgents(int _id,const Vec3 &_p, float _dx, float _dy, float _dz) const;
  /// @brief left extents of the world
  float  	m_left;
  /// @brief right extents of the world
  float  	m_right;
  /// @brief bottom extents of the world
  float  	m_bottom;
  /// @brief top extents of the world
  float  	m_top;
  /// @brief the gometric center of All the Agents in the world
  Vec3 m_flockCenter;
  /// @brief the list of agents
  std::vector<Agent *> m_agents;
  /// @brief flag to say if the world exists
  static bool s_instantiated;
  /// a global aim position
  Vec3 m_globalAim;
};


#endif
