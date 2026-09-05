module;
#include "SDL3/SDL_rect.h"
#include "glm/vec2.hpp"

export module engine.render.cameramanager;
import engine.render.camera;
import std.compat;
import engine.core.math;

export namespace engine::render
{
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
			Camera2DManager& operator=(const Camera2DManager&) = delete;
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
}
