#ifndef RX_INTERNAL_RESULT_H
#define RX_INTERNAL_RESULT_H

#include "Rx/Result.h" // IWYU pragma: export

#define RX_PASS                                                                \
  (RxResult) {                                                                 \
    .type = RX_RESULT_PASS,                                                    \
    .msg = "(rx) the operation completed successfully",                        \
  }

#define RX_NOT_CONF                                                            \
  (RxResult) {                                                                 \
    .type = RX_RESULT_NOT_CONF,                                                \
    .msg = "(rx) the specified feature was not configured",                    \
  }

#define RX_BAD_ALLOC                                                           \
  (RxResult) {                                                                 \
    .type = RX_RESULT_BAD_ALLOC,                                               \
    .msg = "(rx) failed to allocate memory for usage",                         \
  }

#define RX_WGPU_FAIL_INSTANCE                                                  \
  (RxResult) {                                                                 \
    .type = RX_RESULT_WGPU_FAIL, .msg = "failed to create instance",           \
  }

#define RX_WGPU_FAIL_ADAPTER                                                   \
  (RxResult) {                                                                 \
    .type = RX_RESULT_WGPU_FAIL, .msg = "failed to request adapter",           \
  }

#define RX_WGPU_FAIL_DEVICE                                                    \
  (RxResult) { .type = RX_RESULT_WGPU_FAIL, .msg = "failed to request device", }

#endif
