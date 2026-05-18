#ifndef RX_DEVICE_SPEC_H
#define RX_DEVICE_SPEC_H

#include <stdint.h>

typedef void *(*RxHandleSpecMake)(void *data, const size_t size);

typedef void (*RxHandleSpecDrop)(void *data, void *ptr);

typedef struct RxDeviceSpec {
  const char *name;
  uint8_t major, minor, micro;

  void *data;
  RxHandleSpecMake make;
  RxHandleSpecDrop drop;
} RxDeviceSpec;

#define RX_DEVICE_SPEC_DEFAULT ((RxDeviceSpec){0})

#endif
