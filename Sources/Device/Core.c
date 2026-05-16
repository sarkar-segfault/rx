#include <assert.h>
#include <vulkan/vulkan.h>

#include "../Result.h"
#include "Extra.h"
#include "Rx/Device.h" // IWYU pragma: associated
#include "Rx/Result.h"

struct RxDevice {
  VkInstance instance;
  RxDeviceSpec spec;
};

RxResult RxDevice_Create(RxDevice **device, const RxDeviceSpec spec) {
  assert(device);

  *device = spec.make(spec.data, sizeof(RxDevice));
  if (!*device)
    return RxResult_AllocFail;

  (*device)->spec = spec;

  VkApplicationInfo appinfo = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = spec.name ? spec.name : "Rx",
      .applicationVersion = VK_MAKE_VERSION(spec.major, spec.minor, spec.micro),
      .pEngineName = "Rx",
      .engineVersion =
          VK_MAKE_VERSION(Rx_VersionMajor, Rx_VersionMinor, Rx_VersionMicro),
      .apiVersion = VK_API_VERSION_1_0,
  };

  const char *extensions[] = {"VK_KHR_surface",
#ifdef _WIN32
                              "VK_KHR_win32_surface"
#endif
  };

  VkInstanceCreateInfo instinfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appinfo,
      .ppEnabledExtensionNames = extensions,
      .enabledExtensionCount = sizeof(extensions) / sizeof(extensions[0]),
  };

  if (RxDevice_ValidationSupported(spec).type == RxResultType_Pass) {
    const char *layers[] = {"VK_LAYER_KHRONOS_validation"};
    instinfo.enabledLayerCount = sizeof(layers) / sizeof(layers[0]);
    instinfo.ppEnabledLayerNames = layers;
  }

  VkResult result = vkCreateInstance(&instinfo, NULL, &(*device)->instance);
  if (result != VK_SUCCESS) {
    RxDevice_Delete(device);
    return RxResult_VulkanFail(result);
  }

  return RxResult_Pass;
}

RxDeviceSpec RxDevice_GetSpec(const RxDevice *device) {
  assert(device);

  return device->spec;
}

RxResult RxDevice_Delete(RxDevice **device) {
  assert(device && *device);
  RxResult s = RxResult_Pass;

  vkDestroyInstance((*device)->instance, NULL);

  (*device)->spec.drop((*device)->spec.data, *device);
  *device = NULL;

  return s;
}
