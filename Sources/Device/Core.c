#include <assert.h>

#include "../Result.h"
#include "Rx/Device.h" // IWYU pragma: associated
#include "Rx/Result.h"

struct RxDevice {
  RxDeviceSpec spec;
};

RxResult RxDevice_Create(RxDevice **device, const RxDeviceSpec spec) {
  assert(device);

  *device = spec.make(spec.data, sizeof(RxDevice));
  if (!*device)
    return RxResult_AllocFail;

  (*device)->spec = spec;
  return RxResult_Pass;
}

RxDeviceSpec RxDevice_GetSpec(const RxDevice *device) {
  assert(device);
  return device->spec;
}

RxResult RxDevice_Delete(RxDevice **device) {
  assert(device && *device);
  RxResult s = RxResult_Pass;

  (*device)->spec.drop((*device)->spec.data, *device);
  *device = NULL;

  return s;
}
