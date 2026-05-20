#include "rx/device.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <webgpu/webgpu.h>

#include "result.h"

struct RxDevice {
  WGPUInstance inst;
  WGPUAdapter adapt;
  WGPUDevice device;
  RxDeviceSpec spec;
  char label[28];
};

void rxRequestAdapter(WGPURequestAdapterStatus status, WGPUAdapter adapter,
                      WGPUStringView message, void *adapt_, void *rai_);

void rxRequestDevice(WGPURequestDeviceStatus status, WGPUDevice device,
                     WGPUStringView message, void *dev_, void *rai_);

void rxHandleError(WGPUDevice const *device, WGPUErrorType type,
                   WGPUStringView message, WGPU_NULLABLE void *userdata1,
                   WGPU_NULLABLE void *userdata2);

void rxHandleDeviceLost(WGPUDevice const *device, WGPUDeviceLostReason reason,
                        WGPUStringView message, WGPU_NULLABLE void *userdata1,
                        WGPU_NULLABLE void *userdata2);

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

  const WGPUInstanceDescriptor id = {0};
  (*device)->inst = wgpuCreateInstance(&id);
  if (!(*device)->inst) {
    r = RX_WGPU_FAIL_INSTANCE;
    goto fail;
  }

  WGPURequestAdapterOptions rao = {
      .powerPreference = spec.highPower ? WGPUPowerPreference_HighPerformance
                                        : WGPUPowerPreference_LowPower,
      .featureLevel = spec.compatibilityMode ? WGPUFeatureLevel_Compatibility
                                             : WGPUFeatureLevel_Core,
      .forceFallbackAdapter = spec.softwareRendering,
  };

  bool done = false;

  WGPURequestAdapterCallbackInfo raci = {
      .mode = WGPUCallbackMode_AllowProcessEvents,
      .callback = rxRequestAdapter,
      .userdata1 = &(*device)->adapt,
      .userdata2 = &done,
  };

  wgpuInstanceRequestAdapter((*device)->inst, &rao, raci);

  while (!done)
    wgpuInstanceProcessEvents((*device)->inst);

  if (!(*device)->adapt) {
    r = RX_WGPU_FAIL_ADAPTER;
    goto fail;
  }

  snprintf((*device)->label, sizeof((*device)->label), "RxDevice %p",
           (*device));

  WGPUDeviceDescriptor dd = {
      .label = (WGPUStringView){(*device)->label, WGPU_STRLEN},
      .uncapturedErrorCallbackInfo.callback = rxHandleError,
      .deviceLostCallbackInfo.callback = rxHandleDeviceLost,
  };

  done = false;
  WGPURequestDeviceCallbackInfo rdci = {
      .mode = WGPUCallbackMode_AllowProcessEvents,
      .callback = rxRequestDevice,
      .userdata1 = &(*device)->device,
      .userdata2 = &done,
  };

  wgpuAdapterRequestDevice((*device)->adapt, &dd, rdci);
  while (!done)
    wgpuInstanceProcessEvents((*device)->inst);

  if (!(*device)->device) {
    r = RX_WGPU_FAIL_DEVICE;
    goto fail;
  }

  return r;

fail:
  rxDeviceDelete(device);
  return r;
}

RxDeviceSpec rxDeviceGetSpec(const RxDevice *device) {
  assert(device);
  return device->spec;
}

RxResult rxDeviceDelete(RxDevice **device) {
  assert(device && *device);

  if ((*device)->device)
    wgpuDeviceRelease((*device)->device);

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

void rxRequestAdapter(WGPURequestAdapterStatus status, WGPUAdapter adapter,
                      WGPUStringView message, void *adapt_, void *done_) {
  WGPUAdapter *adapt = (WGPUAdapter *)adapt_;
  bool *done = (bool *)done_;

  if (status != WGPURequestAdapterStatus_Success)
    fprintf(stderr, "(rx) failed to request wgpu adapter: %.*s\n",
            (int)message.length, message.data);
  else
    *adapt = adapter;

  *done = true;
}

void rxRequestDevice(WGPURequestDeviceStatus status, WGPUDevice device,
                     WGPUStringView message, void *dev_, void *done_) {
  WGPUDevice *dev = (WGPUDevice *)dev_;
  bool *done = (bool *)done_;

  if (status != WGPURequestDeviceStatus_Success)
    fprintf(stderr, "(rx) failed to request wgpu device: %.*s\n",
            (int)message.length, message.data);
  else
    *dev = device;

  *done = true;
}

void rxHandleError(WGPUDevice const *device, WGPUErrorType type,
                   WGPUStringView message, WGPU_NULLABLE void *userdata1,
                   WGPU_NULLABLE void *userdata2) {
  fprintf(stderr, "(rx) unhandled wgpu failure: %.*s\n", (int)message.length,
          message.data);
}

void rxHandleDeviceLost(WGPUDevice const *device, WGPUDeviceLostReason reason,
                        WGPUStringView message, WGPU_NULLABLE void *userdata1,
                        WGPU_NULLABLE void *userdata2) {
  fprintf(stderr, "(rx) lost wgpu device handle: %.*s\n", (int)message.length,
          message.data);
}
