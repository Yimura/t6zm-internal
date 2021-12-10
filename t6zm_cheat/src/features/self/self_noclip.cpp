#include "features.hpp"
#include "util/keyboard.hpp"
#include "util/math.hpp"

namespace t6zm
{
	const float speed = .007f;

	static Vector3 last_position;

	void features::self_noclip()
	{
		if (g_settings->self.noclip)
		{
			Vector3 pos = g_pointers->m_player->m_origin;
			Vector3 vel;

			if (keyboard::key_pressed(eKey::LEFT_SHIFT))
				vel.z += speed;
			if (keyboard::key_pressed(eKey::LEFT_CONTROL))
				vel.z -= speed;
			if (keyboard::key_pressed(eKey::Z)) //Forward
				vel.x += speed;
			if (keyboard::key_pressed(eKey::S)) //Backward
				vel.x -= speed;
			if (keyboard::key_pressed(eKey::Q)) //Left
				vel.y += speed;
			if (keyboard::key_pressed(eKey::D)) //Right
				vel.y -= speed;

			Vector2 rot = g_pointers->m_player->m_view_angles;
			float yaw = (float)math::deg_to_rad(rot.y);

			Vector3 velocity;
			velocity.x = (vel.x * cos(yaw) - vel.y * sin(yaw));
			velocity.y = (vel.x * sin(yaw) + vel.y * cos(yaw));
			velocity.z = vel.z;

			g_pointers->m_player->m_origin = pos + velocity;
		}
	}
}