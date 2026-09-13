module;

export module engine.render.rendercontext;
import engine.render.framerecorder;
import engine.utilities;

export namespace engine::render
{
	struct RenderContext
	{
		private:
			utilities::ObPtr<FrameRecorder> frame_recorder;

		public:
			RenderContext() = default;
			utilities::ObPtr<FrameRecorder> frameRecorder() noexcept;
	};
}
