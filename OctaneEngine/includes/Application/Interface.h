#pragma once
#include "Context.h"

namespace Octane
{
    struct AppInterface
    {
        OCTANE_INLINE virtual ~AppInterface() = default;
        
        // attach event callback
        template <typename Event, typename Callback>
        OCTANE_INLINE void AttachCallback(Callback&& callback) 
        { 
            m_Context->Dispatcher.AttachCallback<Event>(std::move(callback), m_LayerID); 
        } 

        // post event
        template <typename Event, typename... Args>
        OCTANE_INLINE void PostEvent(Args&&...args) 
        { 
            m_Context->Dispatcher.PostEvent<Event>(std::forward<Args>(args)...); 
        }

        // post task event
        template <typename Task>
        OCTANE_INLINE void PostTask(Task&& task) 
        { 
            m_Context->Dispatcher.PostTask(std::move(task)); 
        } 

        // detach callback
        template <typename Event> 
        OCTANE_INLINE void DetachCallback() 
        { 
            m_Context->Dispatcher.DetachCallback<Event>(m_LayerID); 
        } 

        // ++

        // attach layer
        template<typename Layer, typename... Args> 
        OCTANE_INLINE Layer* AttachLayer(Args&&... args) 
        {
            // check layer's type compliance 
            OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);

            // check if layer allready exist
            if(GetLayer<Layer>() != nullptr)
            {
                OCTANE_ERROR("Layer allready attached!");
                return nullptr;
            }

            // create layer and add to collection
            auto layer = new Layer(std::forward<Args>(args)...);
            m_Context->Layers.push_back(layer);
            layer->m_LayerID = TypeID<Layer>();
            layer->m_Context = m_Context;
            layer->OnStart();   
            return layer;         
        }

        // detach layer
        template<typename Layer> 
        OCTANE_INLINE void DetachLayer()
        {   
            OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);
            m_Context->Dispatcher.PostTask([this] 
            {
                m_Context->Layers.erase(std::remove_if(m_Context->Layers.begin(), 
                m_Context->Layers.end(), [this] (auto& layer) 
                {
                    if(layer->m_LayerID == TypeID<Layer>())
                    {                
                        m_Context->Dispatcher.EraseListener(layer->m_LayerID);
                        OCTANE_DELETE(layer);
                        return true;
                    }
                    return false;
                }), 
                m_Context->Layers.end());   
            });     
        }

        // retreive layer
        template<typename Layer> 
        OCTANE_INLINE Layer* GetLayer() 
        { 
            OCTANE_STATIC_ASSERT(std::is_base_of<AppInterface, Layer>::value);

            auto itr = std::find_if(m_Context->Layers.begin(), 
            m_Context->Layers.end(), [this] (auto layer) 
            {
                return (layer->m_LayerID == TypeID<Layer>());                   
            });    

            if(itr != m_Context->Layers.end())
            {
                return static_cast<Layer*>(*itr);
            }
            return nullptr;
        }

    protected:
        OCTANE_INLINE virtual void OnUpdate() {}
        OCTANE_INLINE virtual void OnStart() {}

    private:
        friend struct Application;
        AppContext* m_Context;
        uint32_t m_LayerID;
    };
}