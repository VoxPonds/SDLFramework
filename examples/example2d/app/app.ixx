module;

export module example.world;

import engine.core.math;
import engine.render.rendererbackend;
import engine.render.sprite;
import engine.render.spriterenderer;
import engine.render.framerecorder;
import engine.resource.resourcemanager;
import engine.resource.resourcecache;
import engine.resource.resourcehandle;
import engine.utilities;
import std;



export namespace example::world
{
	struct GameApp
	{
		private:
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
			engine::render::Sprite sprite_;
			engine::core::Transform2D transform_;
			engine::render::SpriteRenderer sprite_renderer_;
			

		public:
			GameApp(
					engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed,
					engine::utilities::ObPtr<engine::render::FrameRecorder> recorder
			);

			void init();
			void update();
			auto render() -> std::expected<void, engine::render::RendererError>;

		private:
			std::expected<engine::resource::ImageHandle, engine::resource::ResourceError> loadResource();
	};

	GameApp::GameApp(
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed,
			engine::utilities::ObPtr<engine::render::FrameRecorder> recorder
		)
		:	resource_manager_borrowed_(resource_manager_borrowed),
			sprite_{},
			transform_{},
			sprite_renderer_(recorder)
	{

	}

	void GameApp::init()
	{
		if (!loadResource()) return;
	}


	void GameApp::update()
	{

	}

	auto GameApp::loadResource()->std::expected<engine::resource::ImageHandle, engine::resource::ResourceError>
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
		return std::expected<engine::resource::ImageHandle, engine::resource::ResourceError>(std::in_place);
	}

	auto GameApp::render()->std::expected<void, engine::render::RendererError>
	{
		//constexpr std::size_t command_count = 10000;

		//for (std::size_t i = 0; i < command_count; ++i)
		//{
		//	sprite_renderer_.drawSprite(sprite_, transform_, engine::render::FlipMode::FLIP_NONE);
		//}
		return sprite_renderer_.drawSprite(sprite_, transform_, engine::render::FlipMode::FLIP_NONE);
	}
}
