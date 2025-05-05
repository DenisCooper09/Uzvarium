#pragma once

#include <iostream>
#include <array>
#include <vulkan/vulkan.h>

namespace Uz
{
    class Application
    {
    public:
        Application();
        ~Application();

        void CreateInstance();

    private:
        VkInstance m_Instance{};
    };
}
