#pragma once
#include "math.hpp"
#include "..\core.hpp"

namespace sdk
{
	namespace utilities
	{

		VMatrix& c_math::world_to_screen_matrix()
		{
			static uint64_t dwFunction = csgo.m_utils()->find_pattern_ida("engine.dll", "A1 ? ? ? ? 83 F8 01 7E 11 69 C8");
			static DWORD_PTR dwVMatrixPtr = *(DWORD_PTR*)(dwFunction + 0x11);

			DWORD_PTR dwVMatrix = *(DWORD_PTR*)dwVMatrixPtr;

			DWORD_PTR dwResult = dwVMatrix + 2 * 528 - 68;

			return (VMatrix&)(*(DWORD_PTR*)dwResult);
		}

		void c_math::sin_cos(float radians, float *sine, float *cosine)
		{
			*sine = sin(radians);
			*cosine = cos(radians);
		}

		void c_math::vector_angles(const vec3_t& forward, angle_t &angles)
		{
			if (forward[1] == 0.0f && forward[0] == 0.0f)
			{
				angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
				angles[1] = 0.0f;  //yaw left/right
			}
			else
			{
				angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
				angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

				if (angles[1] > 90) angles[1] -= 180;
				else if (angles[1] < 90) angles[1] += 180;
				else if (angles[1] == 90) angles[1] = 0;
			}

			angles[2] = 0.0f;
		}

		void c_math::angle_vectors(const angle_t &angles, vec3_t *forward)
		{
			float sp, sy, cp, cy;

			sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
			sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);

			forward->x = cp*cy;
			forward->y = cp*sy;
			forward->z = -sp;
		}

		void c_math::angle_vectors(const angle_t &angles, vec3_t *forward, vec3_t *right, vec3_t *up)
		{
			float sr, sp, sy, cr, cp, cy;

			sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
			sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);
			sin_cos(DEG2RAD(angles[ROLL]), &sr, &cr);

			if (forward)
			{
				forward->x = cp*cy;
				forward->y = cp*sy;
				forward->z = -sp;
			}

			if (right)
			{
				right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
				right->y = (-1 * sr*sp*sy + -1 * cr*cy);
				right->z = -1 * sr*cp;
			}

			if (up)
			{
				up->x = (cr*sp*cy + -sr*-sy);
				up->y = (cr*sp*sy + -sr*cy);
				up->z = cr*cp;
			}
		}

		angle_t c_math::compute_angle(const vec3_t &source, const vec3_t &destination)
		{
			angle_t angles;

			vec3_t delta = source - destination;
			angles.x = static_cast< float >(asin(delta.z / delta.Length()) * M_RADPI);
			angles.y = static_cast< float >(atan(delta.y / delta.x) * M_RADPI);
			angles.z = 0.0f;

			if (delta.x >= 0.0f)
				angles.y += 180.0f;

			return angles;
		}

		float c_math::get_fov(const angle_t& viewAngle, const angle_t& aimAngle)
		{
			vec3_t ang, aim;
			angle_vectors(viewAngle, &aim);
			angle_vectors(aimAngle, &ang);

			return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
		}

		angle_t c_math::calc_angle(vec3_t src, vec3_t dst)
		{
			angle_t angles;
			vec3_t delta = src - dst;
			vector_angles(delta, angles);
			delta.Normalized();
			return angles;
		}

		float c_math::vector_distance(vec3_t v1, vec3_t v2)
		{
			return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2) + pow(v1.z - v2.z, 2));
		}

		void c_math::angle_vectors_2d(vec3_t& vecAngles, vec3_t& vecForward)
		{
			float sp, sy, cp, cy;
			sin_cos(static_cast<float>(vecAngles[1] * (M_PI / 180.f)), &sy, &cy);
			sin_cos(static_cast<float>(vecAngles[0] * (M_PI / 180.f)), &sp, &cp);

			vecForward[0] = cp * cy;
			vecForward[1] = cp * sy;
			vecForward[2] = -sp;
		}

		void c_math::vector_angles_2d(vec3_t& vecForward, vec3_t& vecAngles)
		{
			vec3_t vecView;
			if (vecForward[1] == 0.f && vecForward[0] == 0.f)
			{
				vecView[0] = 0.f;
				vecView[1] = 0.f;
			}
			else
			{
				vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

				if (vecView[1] < 0.f)
					vecView[1] += 360.f;

				vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

				vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
			}

			vecAngles[0] = -vecView[0];
			vecAngles[1] = vecView[1];
			vecAngles[2] = 0.f;
		}

		void c_math::clamp_angles(angle_t& angles)
		{
			if (angles.x > 89.0f) angles.x = 89.0f;
			else if (angles.x < -89.0f) angles.x = -89.0f;

			if (angles.y > 180.0f) angles.y = 180.0f;
			else if (angles.y < -180.0f) angles.y = -180.0f;

			angles.z = 0;
		}


		float c_math::get_distance(const vec3_t &start, const vec3_t &end)
		{
			float distance = sqrt((start - end).Length());

			if (distance < 1.0f)
				distance = 1.0f;

			return distance;
		}

		bool c_math::sanitize_angles(angle_t &angles)
		{
			angle_t temp = angles;
			normalize_angles(temp);
			clamp_angles(temp);

			if (!isfinite(temp.x) ||
				!isfinite(temp.y) ||
				!isfinite(temp.z))
				return false;

			angles = temp;

			return true;
		}

		void c_math::normalize_angles(vec3_t& vecAngles)
		{
			for (auto i = 0; i < 3; ++i)
			{
				while (vecAngles[i] > 180.f)
					vecAngles[i] -= 360.f;

				while (vecAngles[i] < -180.f)
					vecAngles[i] += 360.f;
			}

			vecAngles[2] = 0.f;
		}

		void c_math::vector_transform(vec3_t& in1, matrix3x4_t& in2, vec3_t &out)
		{
			out.x = in1.Dot(in2.m_flMatVal[0]) + in2.m_flMatVal[0][3];
			out.y = in1.Dot(in2.m_flMatVal[1]) + in2.m_flMatVal[1][3];
			out.z = in1.Dot(in2.m_flMatVal[2]) + in2.m_flMatVal[2][3];
		}

		void c_math::vector_transform(const vec3_t& in1, const matrix3x4_t& in2, vec3_t& out)
		{
			out[0] = in1.Dot(in2[0]) + in2[0][3];
			out[1] = in1.Dot(in2[1]) + in2[1][3];
			out[2] = in1.Dot(in2[2]) + in2[2][3];
		}

		vec3_t c_math::cubic_interpolate(const vec3_t& p1, const vec3_t& p2, const vec3_t& p3, const vec3_t& p4, float t)
		{
			return p1 * (1 - t) * (1 - t) * (1 - t) +
				p2 * 3 * t * (1 - t) * (1 - t) +
				p3 * 3 * t * t * (1 - t) +
				p4 * t * t * t;
		}

		float c_math::get_delta(float hspeed, float maxspeed, float airaccelerate)
		{
			float term = (30.0f - (airaccelerate * maxspeed / 66.0f)) / hspeed;

			if (term < 1.0f && term > -1.0f) {
				return acos(term);
			}

			return 0.f;
		}

		inline float c_math::random_float(float M, float N)
		{
			return (float)(M + (rand() / (RAND_MAX / (N - M))));
		}

		bool c_math::world_to_screen(vec3_t &origin, vec3_t &screen)
		{
			if (screen_transform(origin, screen)) {
				int w, h;
				csgo.m_engine( )->get_screen_size(w, h);

				screen.x = (w / 2.0f) + (screen.x * w) / 2.0f;
				screen.y = (h / 2.0f) - (screen.y * h) / 2.0f;

				return true;
			}
			return false;
		}

		bool c_math::screen_transform(const  vec3_t &point, vec3_t &screen)
		{
			static auto& w2sMatrix = csgo.world_to_screen_matrix;

			screen.x = w2sMatrix.m[0][0] * point.x + w2sMatrix.m[0][1] * point.y + w2sMatrix.m[0][2] * point.z + w2sMatrix.m[0][3];
			screen.y = w2sMatrix.m[1][0] * point.x + w2sMatrix.m[1][1] * point.y + w2sMatrix.m[1][2] * point.z + w2sMatrix.m[1][3];
			screen.z = 0.0f;

			float w = w2sMatrix.m[3][0] * point.x + w2sMatrix.m[3][1] * point.y + w2sMatrix.m[3][2] * point.z + w2sMatrix.m[3][3];

			if (w < 0.001f) {
				screen.x *= 100000;
				screen.y *= 100000;
				return false;
			}

			screen.x /= w;
			screen.y /= w;

			return true;
		}
	}
}