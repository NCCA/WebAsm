#include "World.h"
#include "Agent.h"
#include <iostream>


bool World::s_instantiated = false;

// sum the agent positions and find average pos
void World::calculateFlockCenter()
{
  Vec3 total;
  for(size_t i=0; i<m_agents.size(); ++i)
  {
    total+=m_agents[i]->pos();
  }
  total/=m_agents.size();
  m_flockCenter=total;
}

std::vector<Agent *> World::findLocalAgents(int _id, const Vec3 &_p, float _dx, float _dy, float _dz) const
{
std::vector<Agent *> ret;
for(size_t i=0; i<m_agents.size(); ++i)
{
  // don't check self
  if(m_agents[i]->id() == _id)
    continue;

  Vec3 l = m_agents[i]->pos();
  // minimal AABB test
  if(
     l.m_x > _p.m_x-_dx && l.m_x < _p.m_x+_dx &&
     l.m_y > _p.m_y-_dy && l.m_y < _p.m_y+_dy &&
     l.m_z > _p.m_z-_dz && l.m_z < _p.m_z+_dz
     )
  {
    ret.push_back(m_agents[i]);
  }
}
 return ret;
}
