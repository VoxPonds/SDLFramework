module;

export module example2d.imgae;

import engine.core.math;
import engine.core.timer;
import engine.render.sprite;
import engine.render.apprenderer;
import engine.render.framerecorder;
import engine.resource.resourcemanager;
import engine.resource.resourcehandle;
import engine.render.camera;
import engine.utilities;
import std;

export
{
	struct GameApp
	{
		private:
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
			engine::render::Sprite sprite_;
			math::Transform2D transform_;
			engine::render::AppRenderer app_renderer_;
			engine::render::Camera2D camera;

		public:
			GameApp(
					engine::resource::ResourceManager& resource_manager_borrowed,
					engine::render::FrameRecorder& recorder
			);

			void init();
			void update(engine::core::Timer::DeltaTimeType dt);
			void draw();

		private:
			std::expected<engine::resource::ImageHandle, engine::resource::EResourceError> loadResource();
	};

}
GameApp::GameApp(
	engine::resource::ResourceManager& resource_manager_borrowed,
	engine::render::FrameRecorder& recorder
):	resource_manager_borrowed_(resource_manager_borrowed),
	sprite_{},
	transform_{},
	app_renderer_(recorder)
{

}

void GameApp::init()
{
	if (!loadResource()) return;
}

void GameApp::update(engine::core::Timer::DeltaTimeType dt)
{
	//camera.follow(engine::core::Vector2{ 0.0, 0.0 });
	camera.position.x += 5.0f * dt;
	camera.position.y += 5.0f * dt;
}

void GameApp::draw()
{
	app_renderer_.setActiveCamera(camera);
	auto result = app_renderer_.drawSprite(sprite_, transform_, engine::render::FlipMode::FLIP_NONE);
	if (!result)
	{
		std::println("DrawSprite failed");
	}
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
