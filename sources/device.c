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

  if (spec.create)
    *device = spec.create(spec.userdata, sizeof(RxDevice));
  else
    *device = malloc(sizeof(struct RxDevice));

  if (!*device)
    return RX_BAD_ALLOC;

  (*device)->spec = spec;
  RxResult r = RX_PASS;

  const WGPUInstanceDescriptor id = WGPU_INSTANCE_DESCRIPTOR_INIT;
  (*device)->inst = wgpuCreateInstance(&id);
  if (!(*device)->inst) {
    r = RX_WGPU_FAIL("failed to create instance");
    goto wgpuFail;
  }

  return r;

wgpuFail:
  rxDeviceDelete(device);
  return r;
}

RxDeviceSpec rxDeviceGetSpec(const RxDevice *device) {
  assert(device);
  return device->spec;
}

RxResult rxDeviceDelete(RxDevice **device) {
  assert(device && *device);

  if ((*device)->inst)
    wgpuInstanceRelease((*device)->inst);

  if ((*device)->spec.delete)
    (*device)->spec.delete((*device)->spec.userdata, *device);
  else
    free(*device);

  *device = NULL;
  return RX_PASS;
}
