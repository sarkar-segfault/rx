#include <stdio.h>
#include <stdlib.h>

#include "Rx/DeviceSpec.h" // IWYU pragma: associated

void *RxHandleSpec_Make(void *data, size_t size) {
  void *out = malloc(size);
#ifndef NDEBUG
  fprintf(stderr, "Allocated %zu bytes to %p\n", size, out);
#endif
  return out;
}

void RxHandleSpec_Drop(void *data, void *ptr) {
  free(ptr);
#ifndef NDEBUG
  fprintf(stderr, "Freed bytes from %p\n", ptr);
#endif
}
