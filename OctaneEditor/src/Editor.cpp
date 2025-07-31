#include <Octane.h>
using namespace Octane;

struct MyLayer : AppInterface
{
    OCTANE_INLINE void OnUpdate()
    {
        OCTANE_INFO("OnUpdate()");
    }

    OCTANE_INLINE void OnStart()
    {
        OCTANE_TRACE("OnStart()");
    }
};

int32_t main(int32_t argc, char** argv)
{
    auto app = new Application();
    app->AttachmentLayer<MyLayer>();
    app->RunContext();
    
    return 0;
}