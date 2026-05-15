#ifndef Rx__DeviceH
#define Rx__DeviceH

#include <stdbool.h>
#include <stdint.h>

#include "Result.h"
#include "_Expose.h"

typedef struct RxDevice RxDevice;

typedef struct RxDeviceSpec {
  const char *name;
  uint8_t major, minor, micro;
} RxDeviceSpec;

#define RxDeviceSpec_Default ((RxDeviceSpec){0})

Rx__Expose RxResult RxDevice_Create(RxDevice **device, const RxDeviceSpec spec);

Rx__Expose RxDeviceSpec RxDevice_GetSpec(const RxDevice *device);

Rx__Expose RxResult RxDevice_Delete(RxDevice **device);

#endif
