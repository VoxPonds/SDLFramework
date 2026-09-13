module;

export module engine.render.sdlrenderer;

import engine.platform.sdlwindow;
import engine.platform.sdlptr;
import engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.framerecorder;
import engine.render.cameramanager;
import engine.render.framedata;
import engine.render.sdlrenderdevice;
import engine.render.sdlrendereradapter;
import engine.render.texturemanager;
import engine.render.camera;
import engine.resource.resourcemanager;
import engine.resource.resourceptr;
import engine.core.math;
import engine.utilities;
import std;

export namespace engine::render
{
	class SdlRenderer
	{
		private:
			//using SdlRendererDevicePtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
			platform::SdlRendererDeviceObPtr renderer_ptr;
			resource::ResourceManager& resource_manager_borrowed;
			TextureManager texture_manager;

		public:
			SdlRenderer(platform::SdlRendererDeviceObPtr renderer, resource::ResourceManager& manager);
			~SdlRenderer() = default;

			SdlRenderer(const SdlRenderer&) = delete;
			SdlRenderer& operator=(const SdlRenderer&) = delete;
			SdlRenderer(SdlRenderer&&) = delete;
			SdlRenderer& operator=(SdlRenderer&&) = delete;

			void renderTest()const;
			auto render(const FrameData& data)-> std::expected<void, ERendererError>;

			void drawTexture(const Camera2D& camera, const SpriteRenderCommand& command);
			void drawTexture(const SpriteRenderCommand& command);

			platform::SdlRendererDeviceObPtr getRendererPtr()const;

			//std::expected<void, RendererError> submit(const RenderCommand2D& render_command_2d) override;
			void beginFrame();
			void clear();
			auto execute(const Camera& camera, const RenderCommand2D& render_command_2d) -> std::expected<void, ERendererError>;
			void present();
			void endFrame();
			
	};


}

