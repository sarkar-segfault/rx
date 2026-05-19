#include "rx/device.h"

#include <assert.h>
#include <stdlib.h>
#include <webgpu/webgpu.h>

#include "result.h"

struct RxDevice {
  WGPUInstance inst;
  WGPUAdapter adapt;
  RxDeviceSpec spec;
};

typedef struct RxCallbackInfo {
  WGPUStringView sv;
  bool done;
} RxCallbackInfo;

void rxRequestAdapter(WGPURequestAdapterStatus status, WGPUAdapter adapter,
                      WGPUStringView message, void *adapt_, void *rai_) {
  WGPUAdapter *adapt = (WGPUAdapter *)adapt_;
  RxCallbackInfo *rai = (RxCallbackInfo *)rai_;

  if (status != WGPURequestAdapterStatus_Success)
    rai->sv = message;
  else
    *adapt = adapter;

  rai->done = true;
}

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
    r = RX_WGPU_FAIL("failed to create instance", 0);
    goto wgpuFail;
  }

  WGPURequestAdapterOptions rao = {
      .powerPreference = spec.highPower ? WGPUPowerPreference_HighPerformance
                                        : WGPUPowerPreference_LowPower,
      .featureLevel = spec.compatibilityMode ? WGPUFeatureLevel_Compatibility
                                             : WGPUFeatureLevel_Core,
      .forceFallbackAdapter = spec.softwareRendering,
  };

  RxCallbackInfo rai = {0};

  WGPURequestAdapterCallbackInfo raci = {
      .mode = WGPUCallbackMode_AllowProcessEvents,
      .callback = rxRequestAdapter,
      .userdata1 = &(*device)->adapt,
      .userdata2 = &rai,
  };

  wgpuInstanceRequestAdapter((*device)->inst, &rao, raci);

  while (!rai.done)
    wgpuInstanceProcessEvents((*device)->inst);

  if (!(*device)->adapt) {
    r = RX_WGPU_FAIL(rai.sv.data, rai.sv.length);
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

  if ((*device)->adapt)
    wgpuAdapterRelease((*device)->adapt);

  if ((*device)->spec.delete)
    (*device)->spec.delete((*device)->spec.userdata, *device);
  else
    free(*device);

  *device = NULL;
  return RX_PASS;
}
