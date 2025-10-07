#pragma once
#include "Common/Core.h"

namespace octane
{
    struct FrameBuffer
    {
        OCTANE_INLINE FrameBuffer(int32_t width, int32_t height): m_Width(width), m_Height(height)
        {
            glGenFramebuffers(1, &m_BufferID);
            glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

            CrateColorAttachment();
            CreateRenderBuffer();
        };


        private:
            uint32_t m_BufferID = 0u;
            uint32_t m_Render = 0u;
            uint32_t m_Color = 0u;
            int32_t m_Height = 0;
            int32_t m_Width = 0;
    };
}