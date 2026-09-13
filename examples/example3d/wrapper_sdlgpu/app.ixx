module;

export module example3d.wrappersdlgpu;
import engine.core.runtime;
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

        void init();
        void update();
        void draw();
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

void WrapperSdlGpuTest::update()
{
}

void WrapperSdlGpuTest::draw()
{
}
