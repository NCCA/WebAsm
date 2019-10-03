#include "Agent.h"
#include <string>
#include <map>
#include "Agent.h"
/// @class AgentFactory and extensible factory for creating agents
class AgentFactory
{
public :
  /// @brief The type for the callback that creates an Agent instance
  typedef Agent *(*createCallback)();

  ///@brief Add a new agent to the system
  /// @param[in] type the name for the Agent
  /// @param[in] createCallback is the callback that will
  /// create the agent
  static void registerAgent(const std::string &type, createCallback cb);
  /// @brief Remove an existing 3D renderer from the system
  /// @param[in] type the name to remove
  static void unregisterAgent(const std::string &type);

  ///@brief Create an instance of a named Agent
  /// @param type the name of the registered agent to create
  /// @returns a pointer to an Agent abstract class if the
  /// Agent creator callback exists else NULL
  static Agent *createAgent(const std::string &type);
private :
  /// @brief a std::map to store our Agents, note this is
  /// static so it is global this avoids the need for a
  /// singleton class which could be used instead
  static std::map<std::string, createCallback> m_agents;

};
