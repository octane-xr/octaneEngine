#pragma once
#include "Common/Event.h"

namespace Octane
{
    //forward declaration
    struct AppInterface;

    //aplication context
    struct AppContext
    {
        OCTANE_INLINE ~AppContext()
        {
            for(auto& layer : Layers)
            {
                OCTANE_DELETE(layer);
            }
        }

        std::vector<AppInterface*> Layers;
        EventDispatcher Dispatcher;
    
    };
}