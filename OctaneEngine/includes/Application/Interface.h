#pragma once
#include "Context.h"

namespace Octane
{
    struct AppInterface
    {
        OCTANE_INLINE virtual ~AppInterface() = default;


    protected:
        OCTANE_INLINE virtual void OnUpdate() {}
        OCTANE_INLINE virtual void OnStart() {}

    private:
        friend struct Application;
        AppContext* m_Context;
        uint32_t m_LayerId;

    };
}
