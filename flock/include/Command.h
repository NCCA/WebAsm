// based on discussions here
// http://gameprogrammingpatterns.com/command.html
#ifndef COMMAND_H__
#define COMMAND_H__
// need to pre-declare this but not include else
// we get a cyclic include error.
class FlockAgent;

/// @class Command, abstract command class to wrap up
/// a series of method calls
class Command
{
public:
 /// @brief ctor
 Command():m_active(true){}
 /// @brief dtor
 virtual ~Command() {}
 /// @brief this is the command to execute the concrete class
 /// will wrap up a call to a method from the agent.
 virtual void execute(FlockAgent& _agent) = 0;
 bool m_active;
};

/// @brief Alignement command will wrap the FlockAgent
/// allignment method call
class AlignmentCommand :public Command
{
  public:
  virtual void execute(FlockAgent& _agent);
};

/// @brief Separation command will wrap the FlockAgent
/// seperation method call
class SeparationCommand :public Command
{
  public:
  virtual void execute(FlockAgent& _agent);
};

/// @brief Cohesion command will wrap the FlockAgent
/// Cohesion method call

class CohesionCommand :public Command
{
  public:
  virtual void execute(FlockAgent& _agent);
};

class GlobalAimCommand :public Command
{
  public:
  virtual void execute(FlockAgent& _agent);
};
#endif
