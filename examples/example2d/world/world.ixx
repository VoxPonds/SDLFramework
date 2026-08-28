module;

export module example.world;

import engine.core.math;
import engine.renderer.renderer;
import engine.renderer.sprite;
import engine.renderer.spriterenderer;
import engine.resource.resourcemanager;
import engine.resource.sdlresourcecache;
import engine.utilities;
import std;
import engine.resource.resourcehandle;


export namespace example::world
{
	struct GameWorld
	{
		private:
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
			engine::renderer::Sprite sprite_;
			engine::core::Transform2D transform_;
			engine::renderer::SpriteRenderer sprite_renderer_;
			

		public:
			GameWorld(
					engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed,
					engine::renderer::RenderObPtr renderer_borrowed
			);

			void update();
			std::expected<engine::resource::TextureHandle, engine::resource::ResourceError> loadResource();
			std::expected<void, engine::renderer::RendererError> draw();
	};

	GameWorld::GameWorld(
			engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed,
			engine::renderer::RenderObPtr renderer_borrowed
		)
		:	resource_manager_borrowed_(resource_manager_borrowed),
			sprite_{},
			transform_{},
			sprite_renderer_(renderer_borrowed)
	{

	}

	void GameWorld::update()
	{
	}

	auto GameWorld::loadResource()->std::expected<engine::resource::TextureHandle, engine::resource::ResourceError>
	{
		auto result =
			resource_manager_borrowed_->getTextureManager()->loadTexture({
				"/assets/test.png"
			});
		if (!result)
		{
			return std::unexpected(result.error());
		}
		sprite_.setTextureHandle(result.value());
		return std::expected<engine::resource::TextureHandle, engine::resource::ResourceError>(std::in_place);
	}

	auto GameWorld::draw()->std::expected<void, engine::renderer::RendererError>
	{
		return sprite_renderer_.drawSprite(sprite_, transform_, engine::renderer::FlipMode::FLIP_NONE);
	}
}
