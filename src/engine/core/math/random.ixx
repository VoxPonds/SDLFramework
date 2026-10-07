module;
#include <random>

export module engine.core.random;


export namespace engine::core
{
    class Random
    {
        private:
            std::mt19937 random_engine_;

        public:
            Random();

            template<std::integral T>
            auto nextInt(T min, std::type_identity_t<T> max) -> T;

            template<std::floating_point T>
            auto nextFloat(T min, std::type_identity_t<T> max) -> T;

            std::mt19937& rng() noexcept;
    };
}

namespace engine::core
{
    Random::Random() :
        random_engine_{std::random_device{}()}
    {
    }

    std::mt19937& Random::rng() noexcept
    {
        return random_engine_;
    }

    template<std::integral T>
    auto Random::nextInt(const T min, const std::type_identity_t<T> max) -> T
    {
        return std::uniform_int_distribution<T>{min, max}(random_engine_);
    }

    template<std::floating_point T>
    auto Random::nextFloat(const T min, const std::type_identity_t<T> max) -> T
    {
        return std::uniform_real_distribution<T>{min, max}(random_engine_);
    }

}

