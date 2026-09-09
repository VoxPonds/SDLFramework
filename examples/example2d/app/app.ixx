module;

export module example2d;

import engine.core.math;
import engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.apprenderer;
import engine.render.framerecorder;
import engine.resource.resourcemanager;
import engine.resource.resourcecache;
import engine.resource.resourcehandle;
import engine.render.camera;
import engine.utilities;
import engine.core.math;
import std;

export
{
	struct GameApp
	{
		private:
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
			engine::render::Sprite sprite_;
			engine::core::Transform2D transform_;
			engine::render::AppRenderer app_renderer_;
			engine::render::Camera2D camera;

		public:
			GameApp(
					engine::resource::ResourceManager& resource_manager_borrowed,
					engine::render::FrameRecorder& recorder
			);

			void init();
			void update();
			auto draw() -> std::expected<void, engine::render::RendererError>;

		private:
			std::expected<engine::resource::ImageHandle, engine::resource::EResourceError> loadResource();
	};

	GameApp::GameApp(
			engine::resource::ResourceManager& resource_manager_borrowed,
			engine::render::FrameRecorder& recorder
		)
		:	resource_manager_borrowed_(resource_manager_borrowed),
			sprite_{},
			transform_{},
			app_renderer_(recorder)
	{

	}

	void GameApp::init()
	{
		if (!loadResource()) return;
	}

	void GameApp::update()
	{
		//camera.follow(engine::core::Vector2{ 0.0, 0.0 });
	}

	auto GameApp::draw()->std::expected<void, engine::render::RendererError>
	{
		app_renderer_.setActiveCamera(camera);
		camera.position.x += 0.2f;
		camera.position.y += 0.2f;
		return app_renderer_.drawSprite(sprite_, transform_, engine::render::FlipMode::FLIP_NONE);
	}

	auto GameApp::loadResource()->std::expected<engine::resource::ImageHandle, engine::resource::EResourceError>
	{
		auto result =
			resource_manager_borrowed_->loadImage({
				"assets/test.png"
			});
		if (!result)
		{
			return std::unexpected(result.error());
		}
		sprite_.setImageHandle(result.value());
		return std::expected<engine::resource::ImageHandle, engine::resource::EResourceError>(std::in_place);
	}
}