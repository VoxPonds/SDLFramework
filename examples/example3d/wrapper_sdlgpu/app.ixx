module;

export module example3d.wrappersdlgpu;

import engine.core.runtime;
import engine.core.eventtype;
import engine.core.appconfig;
import engine.core.timer;
import engine.core.math;
import engine.render.framerecorder;
import engine.render.apprenderer;
import engine.render.mesh;
import engine.resource.resourcemanager;
import engine.utilities;
import std;

export
{
    constinit std::array vertices{
        engine::render::VertexData{.position = { 0.0f,  -0.5f,  0.0f} },
        engine::render::VertexData{.position = { 0.5f,   0.5f,  0.0f} },
        engine::render::VertexData{.position = { -0.5f,   0.5f,  0.0f} }
    };

    struct WrapperSdlGpuTest
    {
        private:
            engine::utilities::ObPtr<engine::resource::ResourceManager> m_resource_manager_borrowed_;
            engine::render::AppRenderer m_app_renderer_;

        public:
            WrapperSdlGpuTest(
                    engine::resource::ResourceManager& resource_manager_borrowed,
                    engine::render::FrameRecorder& recorder
            );
            static consteval auto appConfig() -> engine::core::AppConfig;
            void init();
            void processEvent(const Event& event);
            void update(Timer::DeltaTimeType dt);
            void draw();
        };
}

consteval auto WrapperSdlGpuTest::appConfig() -> engine::core::AppConfig
{
    return engine::core::AppConfig{
        .window_config_ {
            .width {1280},
            .height {720},
            .title {"WrapperSdlGpuTest"},
            .flags {20},
        }
    };
}

WrapperSdlGpuTest::WrapperSdlGpuTest(engine::resource::ResourceManager& resource_manager_borrowed,
                                     engine::render::FrameRecorder& recorder):
    m_resource_manager_borrowed_(resource_manager_borrowed),
    m_app_renderer_(recorder)
{

}

void WrapperSdlGpuTest::init()
{

}

void WrapperSdlGpuTest::processEvent(const Event& event)
{
}

void WrapperSdlGpuTest::update(Timer::DeltaTimeType dt)
{
}

void WrapperSdlGpuTest::draw()
{
    auto result =
        m_app_renderer_.drawMesh(
            engine::render::MeshData{.vertices = vertices},
            math::Transform3D{}
        );
}