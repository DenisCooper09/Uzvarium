set(VULKAN_SDK_PATH C:/VulkanSDK/1.4.309.0)

target_include_directories(Uzvarium PRIVATE ${VULKAN_SDK_PATH}/Include)
target_link_libraries(Uzvarium PRIVATE ${VULKAN_SDK_PATH}/Lib/vulkan-1.lib)
