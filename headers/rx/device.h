#ifndef RX_DEVICE_H
#define RX_DEVICE_H

#include <stdbool.h>
#include <stdint.h>

#include "device_spec.h"
#include "result.h"
#include "private.h"

typedef struct RxDevice RxDevice;

RX_EXPORT RxResult rxDeviceCreate(RxDevice **device, const RxDeviceSpec spec);

RX_EXPORT RxDeviceSpec rxDeviceGetSpec(const RxDevice *device);

RX_EXPORT RxResult rxDeviceDelete(RxDevice **device);

#endif
