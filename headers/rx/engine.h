#ifndef RX_ENGINE_H
#define RX_ENGINE_H

#include "private.h"
#include "result.h"

typedef struct RxEngine RxEngine;

RX_EXPORT RxResult rxEngineCreate(RX_NOTNULL RxEngine **engine,
                                  RX_NOTNULL void *display);

RX_EXPORT RxResult rxEngineDelete(RX_NOTNULL RxEngine **engine);

#endif
