module;
#if defined GLM_FORCE_LEFT_HANDED && defined GLM_FORCE_DEPTH_ZERO_TO_ONE
#elif
    #error "Framework need defined macro GLM_FORCE_LEFT_HANDED and GLM_FORCE_DEPTH_ZERO_TO_ONE before"
#endif
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
/*Coordinate system: Left-handed
Up: +Y
Right: +X
Forward: +Z
Rotation unit: radians
Depth: [0, 1]*/
export module engine.core.math;

export namespace engine::core::math
{
    using Vector2 = glm::vec2;
    using IntVector2 = glm::ivec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Matrix3 = glm::mat3;
    using Matrix4 = glm::mat4;
    using Quaternion = glm::quat;
    Matrix4 (&castMat4)(const Quaternion&) = glm::mat4_cast;
    using glm::translate;
    using glm::inverse;
    using glm::perspective;
    using glm::ortho;

    struct BaseRect
    {
        Vector2 position{};
        Vector2 size{};
    };

    struct BaseColor
    {
        float r{};
        float g{};
        float b{};
        float a{1.0f};
    };

    struct Transform2D
    {
        Vector2 position{};
        float rotation{};
        Vector2 scale{ 1.0f, 1.0f };
    };

    struct Transform3D
    {
        Vector3 position{};
        Quaternion rotation{};
        Vector3 scale{ 1.0f, 1.0f, 1.0f };
    };

}

export namespace core = engine::core::math;
export namespace math = engine::core::math;
