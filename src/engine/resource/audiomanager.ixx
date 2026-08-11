export module engine.resource.sdlresourcemanager:audiomanager;


export namespace engine::resource
{
	class AudioManager final
	{
		public:
			AudioManager() = default;
			~AudioManager() = default;
			AudioManager(const AudioManager&) = delete;
			AudioManager& operator=(const AudioManager&) = delete;
			AudioManager(AudioManager&&) = delete;
			AudioManager& operator=(AudioManager&&) = delete;
	};
}
