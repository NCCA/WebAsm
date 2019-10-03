#include "FlockAgent.h"
#include "Command.h"


void AlignmentCommand::execute(FlockAgent& _agent)
{
  if(m_active)
    _agent.alignment();
}

void SeparationCommand::execute(FlockAgent& _agent)
{
  if(m_active)
  _agent.separation();
}

void CohesionCommand::execute(FlockAgent& _agent)
{
  if(m_active)
  _agent.cohesion();
}

void GlobalAimCommand::execute(FlockAgent& _agent)
{
  if(m_active)
  _agent.globalAim();
}
