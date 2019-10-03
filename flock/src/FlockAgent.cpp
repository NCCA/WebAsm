#include "FlockAgent.h"
#ifdef __linux__
	#include <GL/gl.h>
#endif
#ifdef __APPLE__
	#include <OpenGL/gl.h>
#endif
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Util.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


const static int locality=40;
void FlockAgent::init(const Vec3 &_p, const Vec3 &_d)
{
	m_pos=_p;
	m_dir=_d;
}


FlockAgent::FlockAgent()
{
	m_pos.set(0.0,0.0,0.0);

	m_colour.set(randf(0.2f,1.0f),randf(0.2f,1.0f),randf(0.2f,1.0f));
	m_agentID=++m_id;
	m_alignment.set(0,0,0);
	m_seperation.set(0,0,0);
	m_cohesion.set(0,0,0);

	m_acceleration.set(0.0f,0.0f,0.0f);
	float angle=randf(-2*M_PI,2*M_PI);
	m_velocity.set(cos(angle), sin(angle),0.0f);
	m_maxspeed = 2.0f;
	m_maxforce = 0.03f;
	m_size=3.0f;
}



void FlockAgent::render(const glm::mat4 &_project, GLuint _MVPID,GLuint _colourID) const
{
  float theta = atan2(m_velocity.m_y,m_velocity.m_x) +radians(90);
  glUniform3f(_colourID,m_colour.m_x,m_colour.m_y,m_colour.m_z);
  auto translate=glm::translate(glm::mat4(1.0f), glm::vec3(m_pos.m_x,m_pos.m_y, m_pos.m_z));

  auto M = glm::rotate(translate, theta, glm::vec3(0.0f, 0.0f, 1.0f));
  auto MVP=_project*translate*M;
//  std::cout << glm::to_string(translate) << '\n';
//  std::cout<<"Pos "<<m_pos.m_x<<' '<<m_pos.m_y<<'\n';
  glUniformMatrix4fv(_MVPID,1,GL_FALSE,glm::value_ptr(MVP));
  glDrawArrays(GL_TRIANGLES,0,3);

  //   glPushMatrix();

//     glTranslatef(m_pos.m_x,m_pos.m_y,m_pos.m_z);
//     glRotatef(degrees(theta),0,0,1);
//     glBegin(GL_TRIANGLES);
//       glColor3f(m_colour.m_x,m_colour.m_y,m_colour.m_z);
//       glVertex3f(0, -m_size*2,0.0f);
//       glVertex3f(-m_size, m_size*2,0.0f);
//       glVertex3f(m_size, m_size*2,0.0f);
//     glEnd();
//    glPopMatrix();

}

void FlockAgent::update()
{
	m_local=m_world->findLocalAgents(m_id,m_pos,locality,locality,locality);

	// process the commands
	for(size_t i=0; i<m_commands.size(); ++i)
	{
		m_commands[i]->execute(*this);
	}
		// make seperation bigger to meet point size
		m_seperation*=m_size;
		m_acceleration+=m_seperation;
    m_acceleration+=m_alignment;
    m_acceleration+=m_cohesion;
    m_acceleration+=m_globalAim;
// can either teleport or reflect on edges change TELEPORT
#define TELEPORT 1
#if TELEPORT

		if(m_pos.m_x<=m_world->m_left)
		{
			m_pos.m_x=m_world->m_right;
		}
		else if(m_pos.m_x>=m_world->m_right)
		{
			m_pos.m_x=m_world->m_left;
		}
		if(m_pos.m_y<=m_world->m_bottom)
		{
			m_pos.m_y=m_world->m_top;
		}
		else if(m_pos.m_y>=m_world->m_top)
		{
			m_pos.m_y=m_world->m_bottom;
		}
#else
		if(m_pos.x<=m_world->m_left)
			m_velocity=m_velocity.reflect(Vec3(-1.0,0.0,0.0));
		else if(m_pos.x>=m_world->m_right)
			m_velocity=m_velocity.reflect(Vec3(1.0,0.0,0.0));
		if(m_pos.y<=m_world->m_bottom)
			m_velocity=m_velocity.reflect(Vec3(0.0,1.0,0.0));
		if(m_pos.y>=m_world->m_top)
			m_velocity=m_velocity.reflect(Vec3(0.0,-1.0,0.0));
#endif
		m_velocity+=m_acceleration;
		// Limit speed
		m_velocity.clamp(m_maxspeed);
		m_pos+=m_velocity;
		// Reset acceleration to 0 each cycle
		m_acceleration=0;

}

void FlockAgent::cohesion()
{
	m_cohesion=0.0f;
	if(m_local.size()!=0)
	{
		Vec3 sum(0,0,0);
		for(size_t i=0; i<m_local.size(); ++i)
		{
			sum+=m_local[i]->pos();
		}
		sum/=m_local.size();
		Vec3 desired = sum-m_pos;
		desired*=m_maxspeed;
		desired.clamp(m_maxforce);
		m_cohesion=desired;
	}

}
void FlockAgent::alignment()
{
	m_alignment=0;

	if(m_local.size()!=0)
	{
		Vec3 sum(0,0,0);
		for(size_t i=0; i<m_local.size(); ++i)
		{
			FlockAgent *a=dynamic_cast<FlockAgent *>(m_local[i]);
			sum+=a->m_velocity;
		}
		sum/=m_local.size();
		// Implement Reynolds: Steering = Desired - Velocity
		sum.normalize();
		sum*=m_maxspeed;
		m_alignment = sum-m_velocity;
		m_alignment.clamp(m_maxforce);
	}
}

void FlockAgent::globalAim()
{
	m_globalAim=m_world->m_globalAim-m_pos;
	m_globalAim*=m_maxspeed;
	m_globalAim.normalize();
	m_globalAim-=m_velocity;
	m_globalAim.clamp(m_maxforce);
}


void FlockAgent::separation()
{
	m_seperation=0.0;
	float desiredseparation = 25.0f;
	Vec3 steer;

	for(size_t i=0; i<m_local.size(); ++i)
	{
		Vec3 currentAgentPos=m_local[i]->pos();
		float d=(m_pos-currentAgentPos).length();
		if ((d > 0) && (d < desiredseparation))
		{
			Vec3 diff = m_pos-currentAgentPos;
			diff.normalize();
			diff/=d;        // Weight by distance
			steer+=diff;
		}
	}
	// As long as the vector is greater than 0
	if (steer.length() > 0)
	{

		// Implement Reynolds: Steering = Desired - Velocity
		steer.normalize();
		steer*=m_maxspeed;
		steer-=m_velocity;
		steer.clamp(m_maxforce);
		}
	m_seperation=steer;
}
