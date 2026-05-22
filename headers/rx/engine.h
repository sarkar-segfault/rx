#ifndef RX_ENGINE_H
#define RX_ENGINE_H

#include "private.h"
#include "result.h"
#include "device.h"

typedef struct RxEngine RxEngine;

RX_EXPORT RxResult rxEngineCreate(RX_NOTNULL RxEngine **engine,
                                  RX_NOTNULL RxDevice *device,
                                  RX_NOTNULL void *native);

RX_EXPORT RxResult rxEngineDelete(RX_NOTNULL RxEngine **engine);

#endif
