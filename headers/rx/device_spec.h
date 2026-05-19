#ifndef RX_DEVICE_SPEC_H
#define RX_DEVICE_SPEC_H

#include <stdbool.h>
#include <stdint.h>

#include "private.h"

typedef RX_NULLABLE void *(*RxHandleSpecCreate)(void *userdata,
                                                const size_t size);

typedef void (*RxHandleSpecDelete)(void *userdata, void *ptr);

typedef struct RxDeviceSpec {
  RX_NULLABLE void *userdata;
  RX_NULLABLE RxHandleSpecCreate create;
  RX_NULLABLE RxHandleSpecDelete delete;
} RxDeviceSpec;

#define RX_DEVICE_SPEC_DEFAULT ((RxDeviceSpec){0})

#endif
