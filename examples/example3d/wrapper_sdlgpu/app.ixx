module;

export module example3d.wrappersdlgpu;
import engine.core.runtime;
import engine.core.eventtype;
import engine.core.appconfig;
import engine.render.framerecorder;
import engine.resource.resourcemanager;
import engine.render.apprenderer;
import engine.utilities;

export
{
    struct WrapperSdlGpuTest
    {
    private:
        engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
        engine::render::AppRenderer app_renderer_;


    public:
        WrapperSdlGpuTest(
                engine::resource::ResourceManager& resource_manager_borrowed,
                engine::render::FrameRecorder& recorder
        );
        static consteval auto appConfig() -> engine::core::AppConfig;
        void init();
        void processEvent(const engine::core::Event& event);
        void update();
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
    resource_manager_borrowed_(resource_manager_borrowed),
    app_renderer_(recorder)
{

}

void WrapperSdlGpuTest::init()
{

}

void WrapperSdlGpuTest::processEvent(const engine::core::Event &event)
{
}

void WrapperSdlGpuTest::update()
{
}

void WrapperSdlGpuTest::draw()
{
}
