module;
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_timer.h"

export module engine.core.timer;

import std.compat;

export namespace engine::core
{
    class Timer final
    {
	private:
		std::uint64_t start_counter_{};
		std::uint64_t last_counter_{};

		double delta_time_{};
		double total_time_{};
		double time_scale_{1.0};

		std::uint16_t target_fps_{};
		std::optional<double> target_frame_time_{};

	    public:
			Timer()
			{
				setTargetFPS(60);
			};
	        void beginFrame();
	        void endFrame();

	        double deltaTime() const;
	        double unscaledDeltaTime() const;
	        double totalTime() const;

	        void setTimeScale(double scale);
	        double getTimeScale() const;

	        void setTargetFPS(int fps);
	        int getTargetFPS() const;
	        void limitFrameRate();

			Timer(const Timer&) = delete;
			Timer& operator=(const Timer&) = delete;
			Timer(Timer&&) = delete;
			Timer& operator=(Timer&&) = delete;

    };

}
void engine::core::Timer::beginFrame()
{
	start_counter_ = SDL_GetTicksNS();
	delta_time_ = start_counter_ - last_counter_;
	SDL_Log("Delta Time: %f", delta_time_);
	last_counter_ = start_counter_;
}

void engine::core::Timer::setTimeScale(double scale)
{
	time_scale_ = std::max(0.0,scale);
}

void engine::core::Timer::setTargetFPS(int fps)
{
	target_fps_ = std::max(0, fps);

	target_frame_time_ =
		target_fps_ > 0
		? std::make_optional(1.0f / target_fps_)
		: std::nullopt;
}
