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
		core::Vector2 position{0.0,0.0};
		core::Vector2 viewport_size{0.0,0.0};
		float rotation{};
		float zoom{ 1.0f };

		core::Vector2 worldToScreen(core::Vector2 world_pos, core::Vector2 scroll_factor = { 1.0f, 1.0f }) const
		{
			return world_pos - position * scroll_factor;
		}
		core::Vector2 screenToWorld(core::Vector2 screen_pos) const
		{
			return screen_pos + position;
		}
		void follow(core::Vector2 target)
		{
			position = target - viewport_size * 0.5f;

			//clampPosition();
		}
	};

	struct Camera3D 
	{
		core::Vector3 position{};
		core::Quaternion orientation{};
		EProjectionType projection{};
		float vertical_fov_radians{};
		float orthographic_height{};
		float near_clip{};
		float far_clip{};
		core::Vector2 viewport_size{};

		core::Matrix4 viewMatrix() const
		{
			const core::Matrix4 rotation = core::castMat4(orientation);
			const core::Matrix4 translation = core::translate(core::Matrix4(1.0f), position);

			return core::inverse(translation * rotation);
		}

		glm::mat4 projectionMatrix() const
		{
			const float aspect = viewport_size.x / viewport_size.y;
			switch (projection)
			{
				case EProjectionType::PERSPECTIVE:
					return core::perspective(
						vertical_fov_radians,
						aspect,
						near_clip,
						far_clip
					);
				case EProjectionType::ORTHOGRAPHY:
				{
					const float half_height = orthographic_height * 0.5f;
					const float half_width = half_height * aspect;
					return core::ortho(
						-half_width,
						 half_width,
						-half_height,
						 half_height,
						near_clip,
						far_clip
					);
				}
			}

			return core::Matrix4(1.0f);
		}
		core::Matrix4 viewProjectionMatrix() const
		{
			return projectionMatrix() * viewMatrix();
		}
	};

	using Camera = std::variant<Camera2D, Camera3D>;
}
