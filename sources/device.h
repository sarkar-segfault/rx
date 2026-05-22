#ifndef RX_INTERNAL_DEVICE_H
#define RX_INTERNAL_DEVICE_H

#include <webgpu/webgpu.h>

#include "rx/device_spec.h"

struct RxDevice {
  WGPUInstance inst;
  WGPUAdapter adapt;
  WGPUDevice device;
  RxDeviceSpec spec;
  char label[28];
};

#endif
