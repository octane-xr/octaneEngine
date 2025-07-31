#pragma once
#include "Common/Event.h"

namespace Octane
{
    //Window Events
    struct WindowMaximizeEvent {};

    struct WindowIconifyEvent {};

    struct WindowRestoreEvent {};

    struct WindowCloseEvent {};

    struct WindowResizeEvent
    {
        WindowResizeEvent(int32_t w, int32_t h):
        Width(w), Height(h) {}
        int32_t Height = 0;
        int32_t Width = 0;
    };

    //Key Events
}