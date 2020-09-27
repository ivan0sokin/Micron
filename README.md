[![License](https://img.shields.io/github/license/x4kkk3r/Micron)]()

# Micron
Micron is a graphics engine which is using Vulkan. There will be no UI, only code, only hardcore.

## Build
**Static library recommended**
````sh
git clone https://github.com/x4kkk3r/Micron.git
cd Micron && mkdir build && cd build/
cmake .. && cmake --build .
````

## Example
```cpp
#include "Micron/Entrypoint.hpp"

class Sandbox : public Micron::Application
{
public:
    Sandbox() = default;
    ~Sandbox() = default;

    virtual void Initialize() noexcept override 
    {
        // If MICRON_DEBUG is not defined this message will not be shown
        MICRON_LOG_DEBUG("Sandbox initialized successfully");
    }
    
    virtual void OnUpdate(double deltaTime) noexcept override
    {}
};

static Micron::Rc<Micron::Application> applicationInstance = Micron::MakeRc<Sandbox>();

Micron::Rc<Micron::Application> Micron::Application::Instance() noexcept
{
    return applicationInstance;
}
```

## Dependecies
#### [IOMath](https://github.com/x4kkk3r/IOMath)
#### [IOWindow](https://github.com/x4kkk3r/IOWindow)
#### [SPDLog](https://github.com/gabime/spdlog)
#### [FMT](https://github.com/fmtlib/fmt)

## License
Micron is licensed under the [Apache-2.0 License](LICENSE)