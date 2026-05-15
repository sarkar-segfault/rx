#ifndef Rx__EngineH
#define Rx__EngineH

#include "Result.h"
#include "_Expose.h"

typedef struct RxEngine RxEngine;

Rx__Expose RxResult RxEngine_Create(RxEngine **engine, void *display);

Rx__Expose RxResult RxEngine_Delete(RxEngine **engine);

#endif
