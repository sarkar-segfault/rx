#ifndef Rx__InternalResultH
#define Rx__InternalResultH

#include <vulkan/vk_enum_string_helper.h>

#include "Rx/Result.h" // IWYU pragma: export

#define RxResult_Pass                                                          \
  (RxResult){.type = RxResultType_Pass,                                        \
             .msg = "(Rx) the operation completed successfully"}

#define RxResult_NotConf                                                       \
  (RxResult){.type = RxResultType_NotConf,                                     \
             .msg = "(Rx) the specified feature was not configured"}

#define RxResult_AllocFail                                                     \
  (RxResult){.type = RxResultType_AllocFail,                                   \
             .msg = "(Rx) failed to allocate memory for usage"}

#define RxResult_NoValidation                                                  \
  (RxResult){.type = RxResultType_VulkanFail,                                  \
             .msg = "(Rx) no validation layers are present"}

#define RxResult_VulkanFail(vk)                                                \
  (RxResult) { .type = RxResultType_VulkanFail, .msg = string_VkResult(vk) }

#endif
