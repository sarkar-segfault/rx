#include "rx/engine.h" // IWYU pragma: associated
#include "rx/result.h"

struct RxEngine;

RxResult rxEngineCreate(RxEngine **engine, void *display);

RxResult rxEngineDelete(RxEngine **engine);
