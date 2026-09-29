module;

export module engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.render.camera;
import engine.render.rendertypes;
import engine.utilities;
import engine.core.math;
import std;

export namespace engine::render
{
    template<typename Derived>
    class RendererBackend
    {
        protected:
            Derived& derived()
            {
                return static_cast<Derived&>(*this);
            }

        public:
            auto render(const FrameData& data) -> std::expected<void, ERendererError>
            {
                auto& self = derived();

                self.beginFrame();
                self.clear();
                self.execute(data);
                self.present();
                self.endFrame();
                return {};
            }
    };

    class IRendererBackend
    {
	    public:
	        virtual ~IRendererBackend() = default;
            virtual std::expected<void, ERendererError> render(const FrameData& data) = 0;

	        virtual void beginFrame() = 0;
	        virtual void clear() = 0;
            //virtual std::expected<void, RendererError> execute(const RenderCommand2D& render_command_2d) = 0;
            virtual std::expected<void, ERendererError> execute(const RenderCommand3D& render_command_3d);
            virtual std::expected<void, ERendererError> execute(const Camera& camera, const RenderCommand2D& render_command_2d)= 0;
            
            
	        virtual void present() = 0;
            virtual void endFrame() = 0;
    };


    std::expected<void, ERendererError> IRendererBackend::execute(const RenderCommand3D& render_command_3d)
    {
        return std::unexpected(ERendererError::UNSUPPORTED_COMMAND);
    }

    using RenderObPtr = utilities::ObPtr<IRendererBackend>;
}
