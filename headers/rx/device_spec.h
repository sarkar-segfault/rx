#ifndef RX_DEVICE_SPEC_H
#define RX_DEVICE_SPEC_H

#include <stdint.h>

#include "private.h"

typedef RX_NULLABLE void *(*RxHandleSpecMake)(void *data, const size_t size);

typedef void (*RxHandleSpecDrop)(void *data, void *ptr);

typedef struct RxDeviceSpec {
  RX_NULLABLE void *data;
  RX_NULLABLE RxHandleSpecMake make;
  RX_NULLABLE RxHandleSpecDrop drop;
} RxDeviceSpec;

#define RX_DEVICE_SPEC_DEFAULT ((RxDeviceSpec){0})

#endif
