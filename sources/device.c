#include "rx/device.h" // IWYU pragma: associated

#include <assert.h>
#include <stdlib.h>

#include "result.h"

struct RxDevice {
  RxDeviceSpec spec;
};

RxResult rxDeviceCreate(RxDevice **device, const RxDeviceSpec spec) {
  assert(device);

  if (*device)
    *device = spec.make(spec.data, sizeof(RxDevice));
  else
    *device = malloc(sizeof(struct RxDevice));

  if (!*device)
    return RX_BAD_ALLOC;

  (*device)->spec = spec;
  return RX_PASS;
}

RxDeviceSpec rxDeviceGetSpec(const RxDevice *device) {
  assert(device);
  return device->spec;
}

RxResult rxDeviceDelete(RxDevice **device) {
  assert(device && *device);

  if ((*device)->spec.drop)
    (*device)->spec.drop((*device)->spec.data, *device);
  else
    free(*device);

  *device = NULL;

  return RX_PASS;
}
