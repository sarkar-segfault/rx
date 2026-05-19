#ifndef RX_INTERNAL_RESULT_H
#define RX_INTERNAL_RESULT_H

#include "Rx/Result.h" // IWYU pragma: export

#define RX_PASS                                                                \
  (RxResult){.type = RX_RESULT_PASS,                                           \
             .msg = "(Rx) the operation completed successfully"}

#define RX_NOT_CONF                                                            \
  (RxResult){.type = RX_RESULT_NOT_CONF,                                       \
             .msg = "(Rx) the specified feature was not configured"}

#define RX_BAD_ALLOC                                                           \
  (RxResult){.type = RX_RESULT_BAD_ALLOC,                                      \
             .msg = "(Rx) failed to allocate memory for usage"}

#define RX_WGPU_FAIL(txt, len)                                                 \
  (RxResult) { .type = RX_RESULT_WGPU_FAIL, .msg = txt, .length = len }

#endif
