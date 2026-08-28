module;
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

export module engine.core.math;

export namespace engine::core
{
    using Vector2 = glm::vec2;
    using IntVector2 = glm::ivec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Matrix3 = glm::mat3;
    using Matrix4 = glm::mat4;


    struct Transform2D
    {
        Vector2 position{};
        Vector2 scale{ 1.0f, 1.0f };
        double rotation{};
    };

}

