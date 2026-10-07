module;

export module engine.render.mesh;

import engine.core.math;
import std;

export namespace engine::render
{
    struct VertexData
    {
        math::Vector3 position;
        math::Vector3 normal;
        math::Vector2 uv0;
        math::BaseColor color;
        math::Vector4 tangent;
    };

    struct MeshData
    {
        std::span<const VertexData> vertices;
        std::span<const std::uint32_t> indices;
    };
}