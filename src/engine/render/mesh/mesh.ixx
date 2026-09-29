module;

export module engine.render.mesh;
import engine.core.math;
import std;

export namespace engine::render
{
    struct VertexData
    {
        core::Vector3 position;
        core::Vector3 normal;
        core::Vector2 uv0;
        core::BaseColor color;
        core::Vector4 tangent;
    };

    struct MeshData
    {
        std::span<const VertexData> vertices;
        std::span<const std::uint32_t> indices;
    };
}