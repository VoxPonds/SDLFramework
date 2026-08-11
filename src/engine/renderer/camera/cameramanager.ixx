module;
#include "SDL3/SDL_rect.h"
#include "glm/glm.hpp"

export module engine.renderer.cameramanager;
import std.compat;
import engine.core.math;

export namespace engine::renderer
{
	struct Camera2D {
		core::Vector2 position{};
		core::Vector2 viewport_size{};
		float rotation{};
		float zoom{ 1.0f };
	};
	struct Camera3D {
		core::Vector3 position;       // Camera position
		core::Vector3 target;         // Camera target it looks-at
		core::Vector3 up;             // Camera up vector (rotation over its axis)
		float fovy;             // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
		int projection;         // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
	};

    class Camera2DManager final
    {
	    private:
			Camera2D& camera2d_;
	        std::optional<SDL_Rect> limit_bounds_{};

	        void clampPosition();

	    public:
			explicit Camera2DManager(
				Camera2D& camera_2d
			);
	        Camera2DManager(
				Camera2D& camera_2d,
	            std::optional<SDL_Rect> limit_bounds = std::nullopt
	        );

	        void move(core::Vector2 offset);

	        void setPosition(core::Vector2 position);

	        void setViewportSize(core::Vector2 viewport_size);

			void follow(core::Vector2 target);

	        void setLimitBounds(std::optional<SDL_Rect> bounds);

			core::Vector2 worldToScreen(const core::Vector2 world_pos, core::Vector2 scroll_factor = { 1.0f, 1.0f }) const;

			core::Vector2 screenToWorld(core::Vector2 screen_pos) const;

	        const core::Vector2& getPosition() const;

	        const core::Vector2& getViewportSize() const;

	        const std::optional<SDL_Rect>& getLimitBounds() const;

			Camera2DManager(const Camera2DManager&) = default;
			Camera2DManager& operator=(const Camera2DManager&) = default;
			Camera2DManager(Camera2DManager&&) = default;
			Camera2DManager& operator=(Camera2DManager&&) = delete;
    };

    void Camera2DManager::clampPosition()
    {

    }

	Camera2DManager::Camera2DManager(Camera2D& camera_2d):
		camera2d_(camera_2d)
    {
    }
	void Camera2DManager::follow(core::Vector2 target)
	{
		camera2d_.position = target - camera2d_.viewport_size * 0.5f;

		clampPosition();
	}

	core::Vector2 Camera2DManager::worldToScreen(glm::vec2 world_pos, glm::vec2 scroll_factor) const
	{
		return world_pos - camera2d_.position * scroll_factor;
	}

	core::Vector2 Camera2DManager::screenToWorld(core::Vector2 screen_pos) const
	{
		return screen_pos + camera2d_.position;
	}
}
