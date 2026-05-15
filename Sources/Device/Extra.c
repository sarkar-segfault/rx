#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <vulkan/vulkan.h>

#include "../Result.h"
#include "Extra.h" // IWYU pragma: associated

RxResult RxDevice_ValidationSupported(void) {
#ifndef NDEBUG
  uint32_t count = 0;
  VkResult result = vkEnumerateInstanceLayerProperties(&count, NULL);

  if (result != VK_SUCCESS)
    return RxResult_VulkanFail(result);

  VkLayerProperties *props = calloc(count, sizeof(VkLayerProperties));
  if (!props)
    return RxResult_AllocFail;

  result = vkEnumerateInstanceLayerProperties(&count, props);
  if (result != VK_SUCCESS)
    return RxResult_VulkanFail(result);

  for (uint32_t i = 0; i < count; i++) {
    if (!strcmp(props[i].layerName, "VK_LAYER_KHRONOS_validation"))
      return RxResult_Pass;
  }
#endif

  return RxResult_NoValidation;
}
