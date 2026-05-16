#ifndef Rx__DeviceH
#define Rx__DeviceH

#include <stdbool.h>
#include <stdint.h>

#include "DeviceSpec.h"
#include "Result.h"
#include "_Expose.h"

typedef struct RxDevice RxDevice;

Rx__Expose RxResult RxDevice_Create(RxDevice **device, const RxDeviceSpec spec);

Rx__Expose RxDeviceSpec RxDevice_GetSpec(const RxDevice *device);

Rx__Expose RxResult RxDevice_Delete(RxDevice **device);

#endif
