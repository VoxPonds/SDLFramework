module;

export module engine.core.appcontext;

import engine.resource.resourcemanager;
import engine.render.framerecorder;
import engine.platform.inputsystem;

export namespace engine::core
{
    struct AppContext
    {
        platform::InputSystem<>& input_system;
        render::FrameRecorder& recorder;
        resource::ResourceManager& manager;
    };
}
