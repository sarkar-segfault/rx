#ifndef Rx__InternalResultH
#define Rx__InternalResultH

#include "Rx/Result.h" // IWYU pragma: export

#define RxResult_Pass                                                          \
  (RxResult){.type = RxResultType_Pass,                                        \
             .msg = "(Rx) the operation completed successfully"}

#define RxResult_NotConf                                                       \
  (RxResult){.type = RxResultType_NotConf,                                     \
             .msg = "(Rx) the specified feature was not configured"}

#define RxResult_AllocFail                                                     \
  (RxResult){.type = RxResultType_AllocFail,                                   \
             .msg = "(Rx) failed to allocate memory for usage"}

#define RxResult_GlFail                                                        \
  (RxResult){.type = RxResultType_GlFail,                                      \
             .msg = "(Rx) encountered opengl failure"}

#endif
