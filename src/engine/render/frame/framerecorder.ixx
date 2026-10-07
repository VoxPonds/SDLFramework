module;

export module engine.render.framerecorder;

import engine.render.sprite;
import engine.render.framedata;
import engine.render.camera;
import engine.utilities;
import std;

export namespace engine::render
{
    enum class ERendererError : std::uint8_t
    {
        NONE,
    	GPU_FAILURE,
        INVALID_COMMAND,
    	INVALID_CAMERA,
        RENDER_FAILED,
        CREATE_TEXTURE_FAILED,
        UPDATE_TEXTURE_FAILED,
        UNSUPPORTED_COMMAND,
        RESOURCE_NOT_FOUND,
        BACKEND_ERROR
    };

	class FrameRecorder
	{
		private:
			FrameData frame_data_;

		public:
            void record(const RenderCommand2D& render_command_2d);
            void record(const RenderCommand3D& render_command_3d);
            void setCamera(const Camera2D& camera2d);
            void setCamera(const Camera3D& camera3d);
            const FrameData& Data()const noexcept;

            void beginFrame();
            void endFrame();
	};
}

namespace engine::render
{
	void FrameRecorder::record(const RenderCommand2D& render_command_2d)
	{
		frame_data_.add(render_command_2d);
	}

	void FrameRecorder::record(const RenderCommand3D& render_command_3d)
	{
		frame_data_.add(render_command_3d);
	}

	void FrameRecorder::setCamera(const Camera2D& camera2d)
	{
		frame_data_.camera = camera2d;
	}

	void FrameRecorder::setCamera(const Camera3D& camera3d)
	{
		frame_data_.camera = camera3d;
	}

	const FrameData& FrameRecorder::Data()const noexcept
	{
		return frame_data_;
	}

	void FrameRecorder::beginFrame()
	{
		frame_data_.clear();
	}

	void FrameRecorder::endFrame()
	{
	}
}
