#ifndef Rx_DeviceH
#define Rx_DeviceH

#include <stdbool.h>
#include <stdint.h>

#include "DeviceSpec.h"
#include "Result.h"
#include "_Expose.h"

typedef struct RxDevice RxDevice;

Rx_Expose RxResult RxDevice_Create(RxDevice **device, const RxDeviceSpec spec);

Rx_Expose RxDeviceSpec RxDevice_GetSpec(const RxDevice *device);

Rx_Expose RxResult RxDevice_Delete(RxDevice **device);

#endif
