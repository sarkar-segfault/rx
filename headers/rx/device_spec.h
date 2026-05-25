#ifndef RX_DEVICE_SPEC_H
#define RX_DEVICE_SPEC_H

#include <stdbool.h>
#include <stdint.h>

#include "private.h"

typedef RX_NULLABLE void *(*RxAllocator)(void *userdata, const size_t size);

typedef void (*RxDeallocator)(void *userdata, void *ptr);

typedef struct RxDeviceSpec {
  RX_NULLABLE void *userdata;
  RX_NULLABLE RxAllocator alloc;
  RX_NULLABLE RxDeallocator dealloc;

  bool highPower;
  bool compatibilityMode;
  bool softwareRendering;
} RxDeviceSpec;

#define RX_DEVICE_SPEC_DEFAULT                                                 \
  ((RxDeviceSpec){.highPower = true, .compatibilityMode = false})

#endif
