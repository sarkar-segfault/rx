#ifndef Rx__DeviceSpecH
#define Rx__DeviceSpecH

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

#define RxDeviceSpec_Default                                                   \
  ((RxDeviceSpec){.make = RxHandleSpec_Make, .drop = RxHandleSpec_Drop})

void *RxHandleSpec_Make(void *data, const size_t size);

void RxHandleSpec_Drop(void *data, void *ptr);

#endif
