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
			inline static std::uint64_t start_counter_;
			inline static std::uint64_t last_counter_;

			inline static double delta_time_;
			inline static double total_time_;
			inline static double time_scale_;

			inline static std::uint16_t target_fps_;
			inline static std::optional<double> target_frame_time_;

	    public:
			Timer()
			{
				start_counter_ = SDL_GetTicksNS();
				if (last_counter_ == 0)
				{
					last_counter_ = start_counter_;
					delta_time_ = 0.0;
					setTargetFPS(144);
					return;
				}
			};
	        static void beginFrame();
	        static void endFrame();

			static double deltaTime();
	        /*
	        double unscaledDeltaTime() const;
	        double totalTime() const;
	        */

	        static void setTimeScale(double scale);
	        /*double getTimeScale() const;*/

	        static void setTargetFPS(int fps);
    		static std::uint16_t getTargetFPS();
	        static void limitFrameRate();

			Timer(const Timer&) = delete;
			Timer& operator=(const Timer&) = delete;
			Timer(Timer&&) = delete;
			Timer& operator=(Timer&&) = delete;

    };

}
void engine::core::Timer::beginFrame()
{
	start_counter_ = SDL_GetTicksNS();

	delta_time_ = (start_counter_ - last_counter_) / 1'000'000'000.0;
	SDL_Log("Delta Time: %f", delta_time_);
	last_counter_ = start_counter_;
}

void engine::core::Timer::endFrame()
{
	limitFrameRate();
}

double engine::core::Timer::deltaTime()
{
	return delta_time_;
}

void engine::core::Timer::setTimeScale(double scale)
{
	time_scale_ = std::max(0.0,scale);
}

void engine::core::Timer::setTargetFPS(const int fps)
{
	target_fps_ = std::max(0, fps);

	target_frame_time_ =
		target_fps_ > 0
		? std::make_optional(1.0f / target_fps_)
		: std::nullopt;
}

std::uint16_t engine::core::Timer::getTargetFPS()
{
	return target_fps_;
}


void engine::core::Timer::limitFrameRate()
{
	if (!target_frame_time_) return;

	const auto current = SDL_GetTicksNS();

	const auto frame_time = current - start_counter_ ;

	if (const std::uint64_t remaining = *target_frame_time_ * 1'000'000'000 - frame_time; remaining > 0.0)
	{
		SDL_DelayNS(remaining);
	}
}
