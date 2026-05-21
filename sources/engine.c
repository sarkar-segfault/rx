#include "rx/engine.h"
#include "rx/result.h"

struct RxEngine;

RxResult rxEngineCreate(RxEngine **engine, void *display);

RxResult rxEngineDelete(RxEngine **engine);
