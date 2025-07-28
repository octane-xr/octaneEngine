#pragma once
#include "Interface.h"

namespace Octane
{
    struct Application : AppInterface
    {
        OCTANE_INLINE Application()
        {
            m_LayerId = TypeID<Application>();
            m_Context = new AppContext();
        }

        OCTANE_INLINE ~Application()
        {
            OCTANE_DELETE(m_Context);
        }

        OCTANE_INLINE void RunContext()
        {
            while(true)
            {
                for(auto layer : m_Context -> Layers)
                {
                    layer->OnUpdate();
                }
            }
        }

        template<typename Layer> OCTANE_INLINE Layer* GetLayer()
        {
            OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface,Layer>::value);
            auto itr = std::find_if(m_Context->Layers.begin(),m_Context->Layers.end(),[this] (auto layer)
            {
                return (layer->m_LayerId==TypeId<Layer>());
            });

            if(itr != m_Context->Layers.end())
            {
                return static_cast<Layer*>(*itr);
            }
            return nullptr;
        }

        template<typename Layer, typename... Args> OCTANE_INLINE Layer* AttachmentLayer(Args&&... args)
        {
            //check layers type complilance
            OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface,Layer>::value);

            //check if layer already exist
            if(GetLayer<Layer>() != nullptr)
            {
                OCTANE_ERROR("Layer is already attached!!");
                return nullptr;
            }

            //create layer and add to collection
            auto layer = new Layer(std::forward<Args>(args)...);
            m_Context->Layers.push_back(layer);
            layer->m_LayerId = TypeID<Layer>();
            layer->m_Context = m_Context;
            layer->OnStart();
            return layer;

        }

    };
}
