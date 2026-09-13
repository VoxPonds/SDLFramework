module;

export module example2d.snakeapp;

import engine.core.eventtype;
import engine.render.framerecorder;
import engine.render.apprenderer;
import engine.resource.resourcemanager;
import engine.platform.inputsystem;
import engine.platform.inputcode;
import engine.utilities;
import std;

export
{
    enum class SnakeAction : std::uint8_t
    {
        ACTION_UP,
        ACTION_LEFT,
        ACTION_DOWN,
        ACTION_RIGHT,
        ACTION_COUNT
    };

    enum class InputContextType : std::uint8_t {
        GAMEPLAY,
        MENU,
        PAUSE,
        CONTEXT_COUNT
    };

    struct SnakeApp
    {
        using SnakeInputMapping = engine::platform::InputMappingList<SnakeAction>;
        using SnakeInputSystem = engine::platform::InputSystem<SnakeAction>;
        private:
            engine::utilities::ObPtr<engine::resource::ResourceManager> resource_manager_borrowed_;
            engine::render::AppRenderer app_renderer_;
            SnakeInputMapping input_mapping;
            SnakeInputSystem input_system_;

        public:

            SnakeApp(engine::resource::ResourceManager& resource_manager_borrowed, engine::render::FrameRecorder& recorder);
            void init();
            void beginFrame();
            void processEvent(const engine::core::Event& event);
            void update();
            void draw();
            void endFrame();

    };
}

static SnakeApp::SnakeInputMapping mappingConfig()
{
    using namespace engine::platform;
    using namespace engine::platform::input;
    return SnakeApp::SnakeInputMapping {
        { SnakeAction::ACTION_UP, {
            { {pressed(EInputCode::KEY_W)}, {pressed(EInputCode::KEY_UP)} }, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_LEFT,{
            {{pressed(EInputCode::KEY_A)}, pressed(EInputCode::KEY_LEFT)}, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_DOWN, {
            {{pressed(EInputCode::KEY_S)}, pressed(EInputCode::KEY_DOWN)}, MODE_TOGGLE}
        },
        { SnakeAction::ACTION_RIGHT, {
            {{pressed(EInputCode::KEY_D)}, pressed(EInputCode::KEY_RIGHT)}, MODE_TOGGLE}
        },
    };
}

SnakeApp::SnakeApp(engine::resource::ResourceManager& resource_manager_borrowed, engine::render::FrameRecorder& recorder):
    resource_manager_borrowed_(resource_manager_borrowed),
    app_renderer_(recorder),
    input_mapping(mappingConfig()),
    input_system_(input_mapping)
{
}

void SnakeApp::init()
{
}

void SnakeApp::beginFrame()
{
}

void SnakeApp::processEvent(const engine::core::Event& event)
{
    input_system_.processEvent(event);
}

void SnakeApp::update()
{
    if (input_system_.getActionEvent(SnakeAction::ACTION_UP))
        std::println("SnakeApp::update(): SnakeAction::ACTION_UP");
    if (input_system_.getActionEvent(SnakeAction::ACTION_LEFT))
        std::println("SnakeApp::update(): SnakeAction::ACTION_LEFT");
    if (input_system_.getActionEvent(SnakeAction::ACTION_DOWN))
        std::println("SnakeApp::update(): SnakeAction::ACTION_DOWN");
    if (input_system_.getActionEvent(SnakeAction::ACTION_RIGHT))
        std::println("SnakeApp::update(): SnakeAction::ACTION_RIGHT");

    input_system_.reset();
}
void SnakeApp::draw()
{
}

void SnakeApp::endFrame()
{
}








