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

    public:
    template <typename Layer> 
    OCTANE_INLINE void DetachLayer()
    {
        OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
        m_Context->Dispatcher.PostTask([this]
        {
            m_Context->Layers.erase(std::remove_if(m_Context->Layers.begin(),
                m_Context->Layers.end(), [this] (auto& layer)
                {
                    if(layer->m_LayerId == TypeID<Layer>())
                    {
                        m_Context->Dispatcher.EraseListener(layer->m_LayerId);
                        OCTANE_DELETE(layer);
                        return true;
                    }
                    return false;
                }),
            m_Context->Layers.end());
        });
    }

    };
    
    
}
