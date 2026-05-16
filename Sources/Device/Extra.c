#include "Extra.h" // IWYU pragma: associated

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "../Result.h"

RxResult RxDevice_ValidationSupported(RxDeviceSpec spec) {
#ifndef NDEBUG
  uint32_t count = 0;
  VkResult result = vkEnumerateInstanceLayerProperties(&count, NULL);

  if (result != VK_SUCCESS)
    return RxResult_VulkanFail(result);

  VkLayerProperties *props =
      spec.make(spec.data, count * sizeof(VkLayerProperties));
  if (!props)
    return RxResult_AllocFail;

  result = vkEnumerateInstanceLayerProperties(&count, props);
  if (result != VK_SUCCESS)
    return RxResult_VulkanFail(result);

  for (uint32_t i = 0; i < count; i++) {
    if (!strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation")) {
      spec.drop(spec.data, props);
      return RxResult_Pass;
    }
  }

  spec.drop(spec.data, props);
#endif

  return RxResult_NoValidation;
}
