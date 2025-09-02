#include <Octane.h>
using namespace Octane;

struct MyLayer : AppInterface
{
    OCTANE_INLINE void OnStart() 
    {
        AttachCallback<MouseMotionEvent>([this] (auto e) 
        {
            OCTANE_TRACE("Mouse x:{} y:{}", e.TargetX, e.TargetY);
        });
    }
};

int32_t main(int32_t argc, char** argv) 
{
    auto app = new Application();

    app->AttachCallback<KeyPressEvent>([] (auto e) {
        OCTANE_TRACE("Key: {}", e.Key);
    });

    app->AttachmentLayer<MyLayer>();
    app->RunContext();
    return 0;
}