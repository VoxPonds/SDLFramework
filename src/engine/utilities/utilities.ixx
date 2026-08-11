module;


export module engine.utilities;
import std.compat;



export namespace engine::utilities
{

	template<typename T>
	void hashCombine(std::size_t& seed, const T& value)
	{
		seed ^= std::hash<T>{}(value)
			+0x9e3779b9
			+ (seed << 6)
			+ (seed >> 2);
	}
	template<typename... Ts>
	std::size_t makeHash(const Ts&... values)
	{
		std::size_t seed = 0;
		(hashCombine(seed, values), ...);

		return seed;
	}


}
