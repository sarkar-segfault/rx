#include <stddef.h>

#include "Rx/Rx.h"
#include "Vx/Vx.h"

int main(void) {
  VxHandle *handle = NULL;
  VxHandle_Create(&handle, VxHandleSpec_Default);

  VxWindow *window = NULL;
  VxWindow_Create(&window, handle, VxWindowSpec_Default);

  VxEvent event;

  RxDevice *device = NULL;
  RxDevice_Create(&device, RxDeviceSpec_Default);

  while (VxWindow_IsOpen(window)) {
    VxWindow_PollEvents(window);

    while (VxWindow_PopEvent(window, &event)) {
      if (event.type == VxEvent_Close) {
        VxWindow_Close(window);
        goto terminate;
      }
    }
  }

terminate:
  RxDevice_Delete(&device);

  VxWindow_Delete(&window);
  VxHandle_Delete(&handle);
  return 0;
}
