#include "Application.hpp"

namespace Uz
{
    Application::Application()
    {
        CreateInstance();
        CreateDevice();
    }

    Application::~Application()
    {
        vkDestroyDevice(m_Device, nullptr);
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

    void Application::CreateDevice()
    {
        uint32_t physical_device_count = 0;
        vkEnumeratePhysicalDevices(m_Instance, &physical_device_count, nullptr);

        if (!physical_device_count)
        {
            throw std::runtime_error("Failed to find any physical devices with Vulkan support.");
        }

        VkPhysicalDevice physical_devices[physical_device_count];
        vkEnumeratePhysicalDevices(m_Instance, &physical_device_count, physical_devices);

        std::cout << '\n';
        for (uint32_t i = 0; i < physical_device_count; ++i)
        {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(physical_devices[i], &properties);

            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(physical_devices[i], &features);

            VkPhysicalDeviceMemoryProperties memory_properties;
            vkGetPhysicalDeviceMemoryProperties(physical_devices[i], &memory_properties);

            uint32_t queue_family_count = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(physical_devices[i], &queue_family_count, nullptr);

            VkQueueFamilyProperties queue_family_properties[queue_family_count];
            vkGetPhysicalDeviceQueueFamilyProperties(physical_devices[i], &queue_family_count, queue_family_properties);

            std::cout << "[UZVARIUM] Found physical device: " << properties.deviceName << '\n';
            std::cout << "[UZVARIUM]   API version:          " << properties.apiVersion << '\n';
            std::cout << "[UZVARIUM]   Driver version:       " << properties.driverVersion << '\n';
            std::cout << "[UZVARIUM]   Geometry shader:      " << features.geometryShader << '\n';
            std::cout << "[UZVARIUM]   Tesselation shader:   " << features.tessellationShader << '\n';
            std::cout << "[UZVARIUM]   Queue families count: " << queue_family_count << '\n';
            std::cout << "[UZVARIUM]     Index\t Count\t VK_QUEUE_GRAPHICS_BIT\n";
            for (uint32_t j = 0; j < queue_family_count; ++j)
            {
                std::cout << "[UZVARIUM]     " << j << "\t " << queue_family_properties[j].queueCount << "\t " << (queue_family_properties[j].queueFlags & VK_QUEUE_GRAPHICS_BIT) << '\n';
            }
            std::cout << '\n';
        }

        constexpr float queue_priorities[] = {1.0f};

        std::array<VkDeviceQueueCreateInfo, 1> queue_create_infos{};
        queue_create_infos[0].sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_create_infos[0].queueFamilyIndex = 0;
        queue_create_infos[0].queueCount       = 1;
        queue_create_infos[0].pQueuePriorities = queue_priorities;

        VkPhysicalDeviceFeatures features{};
        features.geometryShader     = VK_TRUE;
        features.tessellationShader = VK_TRUE;

        VkDeviceCreateInfo create_info{};
        create_info.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount    = queue_create_infos.size();
        create_info.pQueueCreateInfos       = queue_create_infos.data();
        create_info.enabledExtensionCount   = 0;
        create_info.ppEnabledExtensionNames = nullptr;
        create_info.pEnabledFeatures        = &features;

        if (vkCreateDevice(physical_devices[0], &create_info, nullptr, &m_Device) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create VkDevice.");
        }

        std::cout << "[UZVARIUM] VkDevice: " << m_Device << '\n';
    }
}
