#pragma once
#include "Common/Event.h"

namespace Octane
{
    struct GraphicsRenderer
    {
        OCTANE_INLINE GraphicsRenderer(int32_t width, int32_t height)
        {
            //initialize opengl
            if(glewInit() != GLEW_OK)
            {
                OCTANE_FATAL("failed to init glew!");
                exit(EXIT_FAILURE);
            }
            glewExperimental = GL_TRUE;
        }
    };
}