#include "Application.hpp"

namespace Uz
{
    Application::Application()
    {
        CreateInstance();
    }

    Application::~Application()
    {
        vkDestroyInstance(m_Instance, nullptr);
    }

    void Application::CreateInstance()
    {
        VkApplicationInfo application_info{};
        application_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        application_info.pApplicationName   = "Uzvarium Engine";
        application_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        application_info.apiVersion         = VK_API_VERSION_1_3;

        VkInstanceCreateInfo create_info{};
        create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &application_info;

        if (vkCreateInstance(&create_info, nullptr, &m_Instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create VkInstance.");
        }

        std::cout << "[UZVARIUM] VkInstance: " << m_Instance << '\n';
    }
}
