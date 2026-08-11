export module engine.resource.sdlresourcemanager:fontmanager;


export namespace engine::resource
{
	class FontManager final
	{
		public:
			FontManager() = default;
			~FontManager() = default;
			FontManager(const FontManager&) = delete;
			FontManager& operator=(const FontManager&) = delete;
			FontManager(FontManager&&) = delete;
			FontManager& operator=(FontManager&&) = delete;
	};
}
