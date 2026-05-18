#include <stddef.h>

#include "Rx/Rx.h"
#include "vx/vx.h"

int main(void) {
  VxHandle *handle = NULL;
  vxHandleCreate(&handle, VX_HANDLE_SPEC_DEFAULT);

  VxWindow *window = NULL;
  vxWindowCreate(&window, handle, VX_WINDOW_SPEC_DEFAULT);

  VxEvent event;

  RxDevice *device = NULL;
  RxDevice_Create(&device, RxDeviceSpec_Default);

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
  RxDevice_Delete(&device);

  vxWindowDelete(&window);
  vxHandleDelete(&handle);
  return 0;
}
