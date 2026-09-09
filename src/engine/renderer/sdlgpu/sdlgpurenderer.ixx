module;

export module engine.render.sdlgpurenderer;

import engine.platform.sdlptr;
import engine.render.rendererbackend;
import engine.render.framerecorder;
import engine.render.framedata;
import engine.render.camera;
import engine.resource.resourcemanager;
import std;

export namespace engine::render
{
    class SdlGpuRenderer
    {
        private:
            platform::SdlGpuDeviceObPtr sdl_gpu_ptr;
            resource::ResourceManager& resource_manager_borrowed;

        public:
            SdlGpuRenderer(platform::SdlGpuDeviceObPtr renderer, resource::ResourceManager& manager);
            void beginFrame();

            void clear();

            void endFrame();

            std::expected<void, RendererError> execute(const RenderCommand3D &render_command_3d);

            std::expected<void, RendererError> execute(const Camera &camera,const RenderCommand2D &render_command_2d);

            void present();

            std::expected<void, RendererError>
            render(const FrameData &data);
    };

    SdlGpuRenderer::SdlGpuRenderer(platform::SdlGpuDeviceObPtr renderer, resource::ResourceManager& manager):
        sdl_gpu_ptr(renderer),
        resource_manager_borrowed(manager)
    {
    }

    void SdlGpuRenderer::beginFrame()
    {
    }

    void SdlGpuRenderer::clear()
    {
    }

    void SdlGpuRenderer::endFrame()
    {
    }

    std::expected<void, RendererError> SdlGpuRenderer::execute(const RenderCommand3D &render_command_3d)
    {
        return {};
    }

    std::expected<void, RendererError> SdlGpuRenderer::execute(const Camera &camera, const RenderCommand2D &render_command_2d)
    {
        return{};
    }

    void SdlGpuRenderer::present()
    {
    }

    std::expected<void, RendererError> SdlGpuRenderer::render(const FrameData &data)
    {
        return {};
    }
}
