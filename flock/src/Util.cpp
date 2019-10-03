#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

float randf(float _min, float _max)
{
  std::random_device rd;
  std::default_random_engine gen(rd());
  //std::uniform_real_distribution<> dis(_min, _max);
  std::normal_distribution<float> dis(_min, _max);
  //std::lognormal_distribution<float> dis(_min, _max);
  //std::student_t_distribution<float> dis( _max);
 // std::chi_squared_distribution<float>dis( _max);
 // std::extreme_value_distribution<float>dis(_max);
   //std::gamma_distribution<float>dis(_min,_max);
   //std::cauchy_distribution<float>dis(_min,_max);

  return dis(gen);
}

float radians(const float _deg )
{
  return (_deg/180.0f) * M_PI;
}

//----------------------------------------------------------------------------------------------------------------------
float degrees( const float _rad   )
{
  return (_rad / M_PI) * 180.0f;
}

