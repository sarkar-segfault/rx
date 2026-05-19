#include "rx/device.h"

#include <assert.h>
#include <stdlib.h>
#include <webgpu/webgpu.h>

#include "result.h"

struct RxDevice {
  WGPUInstance inst;
  RxDeviceSpec spec;
};

RxResult rxDeviceCreate(RxDevice **device, const RxDeviceSpec spec) {
  assert(device);

  if (spec.make)
    *device = spec.make(spec.data, sizeof(RxDevice));
  else
    *device = malloc(sizeof(struct RxDevice));

  if (!*device)
    return RX_BAD_ALLOC;

  (*device)->spec = spec;

  const WGPUInstanceDescriptor id = WGPU_INSTANCE_DESCRIPTOR_INIT;
  (*device)->inst = wgpuCreateInstance(&id);
  if (!(*device)->inst)
    goto wgpu_fail;

  return RX_PASS;

wgpu_fail:
  rxDeviceDelete(device);
  return RX_WGPU_FAIL;
}

RxDeviceSpec rxDeviceGetSpec(const RxDevice *device) {
  assert(device);
  return device->spec;
}

RxResult rxDeviceDelete(RxDevice **device) {
  assert(device && *device);

  if ((*device)->inst)
    wgpuInstanceRelease((*device)->inst);

  if ((*device)->spec.drop)
    (*device)->spec.drop((*device)->spec.data, *device);
  else
    free(*device);

  *device = NULL;
  return RX_PASS;
}
