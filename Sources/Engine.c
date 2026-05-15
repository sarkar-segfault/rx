#include "Rx/Engine.h" // IWYU pragma: associated

#include "Rx/Result.h"

struct RxEngine;

RxResult RxEngine_Create(RxEngine **engine, void *display);

RxResult RxEngine_Delete(RxEngine **engine);
