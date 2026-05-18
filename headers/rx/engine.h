#ifndef RX_ENGINE_H
#define RX_ENGINE_H

#include "result.h"
#include "private.h"

typedef struct RxEngine RxEngine;

RX_EXPORT RxResult rxEngineCreate(RxEngine **engine, void *display);

RX_EXPORT RxResult rxEngineDelete(RxEngine **engine);

#endif
