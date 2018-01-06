#pragma once
#include "..\sdk\angles.hpp"

namespace sdk
{
	namespace utilities
	{
		enum angle_stuff
		{
			PITCH = 0,
			YAW = 1,
			ROLL = 2
		};

		class c_math
		{
		public:
			 void sin_cos(float radians, float *sine, float *cosine);
			 void angle_vectors_2d(vec3_t& vecAngles, vec3_t& vecForward);
			 void vector_angles_2d(vec3_t& vecForward, vec3_t& vecAngles);
			 void normalize_angles(vec3_t& vecAngles);
			 void vector_angles(const vec3_t& forward, angle_t &angles);
			 void angle_vectors(const angle_t& angles, vec3_t *forward);
			 void angle_vectors(const angle_t &angles, vec3_t *forward, vec3_t *right, vec3_t *up);
			 angle_t calc_angle(vec3_t v1, vec3_t v2);
			 float get_fov(const angle_t& viewAngle, const angle_t& aimAngle);
			 float vector_distance(vec3_t v1, vec3_t v2);
			 void vector_transform(vec3_t& in1, matrix3x4_t& in2, vec3_t &out);
			 void vector_transform(const vec3_t& in1, const matrix3x4_t& in2, vec3_t& out);
			 float get_delta(float hspeed, float maxspeed, float airaccelerate);
			 vec3_t extrapolate_tick(vec3_t p0, vec3_t v0);
			 inline float random_float(float M, float N);
			 vec3_t cubic_interpolate(const vec3_t& p1, const vec3_t& p2, const vec3_t& p3, const vec3_t& p4, float t);
			 bool sanitize_angles(angle_t &angles);
			 void clamp_angles(angle_t& angles);
			 float get_distance(const vec3_t &start, const vec3_t &end);
			 angle_t compute_angle(const vec3_t &source, const vec3_t &destination);
			 bool screen_transform(const  vec3_t &point, vec3_t &screen);
			 bool world_to_screen(vec3_t &origin, vec3_t &screen);
			 VMatrix& world_to_screen_matrix();
		};
	}
}