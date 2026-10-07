module;
#include <glm/vec2.hpp>
#include <glm/matrix.hpp>

export module engine.render.camera;
import engine.core.math;
import std;

export namespace engine::render
{
	enum class EProjectionType : uint8_t
	{
		PERSPECTIVE,
		ORTHOGRAPHY,
	};
	struct Camera2D 
	{
		math::Vector2 position{0.0,0.0};
		math::Vector2 viewport_size{0.0,0.0};
		float rotation{};
		float zoom{ 1.0f };

		math::Vector2 worldToScreen(math::Vector2 world_pos, math::Vector2 scroll_factor = { 1.0f, 1.0f }) const
		{
			return world_pos - position * scroll_factor;
		}
		math::Vector2 screenToWorld(math::Vector2 screen_pos) const
		{
			return screen_pos + position;
		}
		void follow(math::Vector2 target)
		{
			position = target - viewport_size * 0.5f;

			//clampPosition();
		}
	};

	struct Camera3D 
	{
		math::Vector3 position{};
		math::Quaternion orientation{};
		EProjectionType projection{};
		float vertical_fov_radians{};
		float orthographic_height{};
		float near_clip{};
		float far_clip{};
		math::Vector2 viewport_size{};

		math::Matrix4 viewMatrix() const
		{
			const math::Matrix4 rotation = math::castMat4(orientation);
			const math::Matrix4 translation = math::translate(math::Matrix4(1.0f), position);

			return math::inverse(translation * rotation);
		}

		glm::mat4 projectionMatrix() const
		{
			const float aspect = viewport_size.x / viewport_size.y;
			switch (projection)
			{
				case EProjectionType::PERSPECTIVE:
					return math::perspective(
						vertical_fov_radians,
						aspect,
						near_clip,
						far_clip
					);
				case EProjectionType::ORTHOGRAPHY:
				{
					const float half_height = orthographic_height * 0.5f;
					const float half_width = half_height * aspect;
					return math::ortho(
						-half_width,
						 half_width,
						-half_height,
						 half_height,
						near_clip,
						far_clip
					);
				}
			}

			return math::Matrix4(1.0f);
		}
		math::Matrix4 viewProjectionMatrix() const
		{
			return projectionMatrix() * viewMatrix();
		}
	};

	using Camera = std::variant<Camera2D, Camera3D>;
}
