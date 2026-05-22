#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "device.h" // IWYU pragma: keep
#include "result.h"
#include "rx/engine.h"
#include "rx/result.h"

struct RxEngine {
  RxDeviceSpec spec;
};

RxResult rxEngineCreate(RxEngine **engine, RxDevice *device, void *native) {
  assert(engine && device && native);

  if (device->spec.create)
    *engine =
        device->spec.create(device->spec.userdata, sizeof(struct RxEngine));
  else
    *engine = malloc(sizeof(struct RxEngine));

  if (!*engine)
    return RX_BAD_ALLOC;

  memset(*engine, 0, sizeof(struct RxEngine));

  (*engine)->spec = device->spec;
  return RX_PASS;
}

RxResult rxEngineDelete(RxEngine **engine) {
  assert(engine && *engine);

  if ((*engine)->spec.delete)
    (*engine)->spec.delete((*engine)->spec.userdata, *engine);
  else
    free(*engine);

  *engine = NULL;

  return RX_PASS;
}
