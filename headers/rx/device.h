#ifndef RX_DEVICE_H
#define RX_DEVICE_H

#include <stdbool.h>
#include <stdint.h>

#include "device_spec.h"
#include "private.h"
#include "result.h"

typedef struct RxDevice RxDevice;

RX_EXPORT RxResult rxDeviceCreate(RX_NOTNULL RxDevice **device,
                                  const RxDeviceSpec spec);

RX_EXPORT RxDeviceSpec rxDeviceGetSpec(RX_NOTNULL const RxDevice *device);

RX_EXPORT RxResult rxDeviceDelete(RX_NOTNULL RxDevice **device);

#endif
