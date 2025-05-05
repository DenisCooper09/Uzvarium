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
        void CreateDevice();

    private:
        VkInstance m_Instance{};
        VkDevice   m_Device{};
    };
}
