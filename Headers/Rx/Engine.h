#ifndef Rx_EngineH
#define Rx_EngineH

#include "Result.h"
#include "_Expose.h"

typedef struct RxEngine RxEngine;

Rx_Expose RxResult RxEngine_Create(RxEngine **engine, void *display);

Rx_Expose RxResult RxEngine_Delete(RxEngine **engine);

#endif
