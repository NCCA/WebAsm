#include "AgentFactory.h"
// QMAKE_CXXFLAGS+= -std=c++11 -stdlib=libc++
// instantiate the static variable in AgentFactory
std::map<std::string, AgentFactory::createCallback>  AgentFactory::m_agents;

void AgentFactory::registerAgent(const std::string &type,createCallback cb)
{
  m_agents[type] = cb;
}

void AgentFactory::unregisterAgent(const std::string &type)
{
  m_agents.erase(type);
}

Agent *AgentFactory::createAgent(const std::string &type)
{
  // we should always use the find method for a std::map as if we use
  // the [type] if not found a new one will be added
  std::map<std::string, createCallback>::iterator it = m_agents.find(type);
  if (it != m_agents.end())
  {
    // call the creation callback to construct this derived type
    return (it->second)();
  }
  return NULL;
}

