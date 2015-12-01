#pragma once

namespace Simplifications{
    struct CanRun{
        bool running = true;
        bool is_running()
        { return running; }
        void set_running(bool value)
        { running = value; }
    };
};