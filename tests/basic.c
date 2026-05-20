#include <stddef.h>

#include "rx/rx.h"
#include "vx/vx.h"

int main(void) {
  VxHandle *handle = NULL;
  vxHandleCreate(&handle, VX_HANDLE_SPEC_DEFAULT);

  RxDevice *device = NULL;
  rxDeviceCreate(&device, RX_DEVICE_SPEC_DEFAULT);

  VxWindow *window = NULL;
  vxWindowCreate(&window, handle, VX_WINDOW_SPEC_DEFAULT);

  VxEvent event;

  while (vxWindowIsOpen(window)) {
    vxWindowPollEvents(window);

    while (vxWindowPopEvent(window, &event)) {
      if (event.type == VX_EVENT_CLOSE) {
        vxWindowClose(window);
        goto terminate;
      }
    }
  }

terminate:
  rxDeviceDelete(&device);

  vxWindowDelete(&window);
  vxHandleDelete(&handle);
  return 0;
}
