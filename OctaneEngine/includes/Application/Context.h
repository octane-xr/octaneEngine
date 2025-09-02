#pragma once
#include "Common/Event.h"
#include "Window/Window.h"

namespace Octane
{
    //forward declaration
    struct AppInterface;

    //aplication context
    struct AppContext
    {
        OCTANE_INLINE AppContext()
        {
            Window = std::make_unique<AppWindow>(&Dispatcher,  1280, 720, "Octane Engine");
        }

        OCTANE_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                OCTANE_DELETE(layer);
            }
        }

        std::vector<AppInterface*> Layers;
        std::unique_ptr<AppWindow> Window;
        EventDispatcher Dispatcher;
    
    };
}