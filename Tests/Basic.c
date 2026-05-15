#include <stddef.h>

#include "Rx/Rx.h"
#include "Vx/Vx.h"

int main(void) {
  VxHandle *handle = NULL;
  VxHandle_Create(&handle, VxHandleSpec_Default);

  VxWindow *window;
  VxWindow_Create(&window, handle, VxWindowSpec_Default);

  VxEvent event;

  RxDevice *device;
  RxDevice_Create(&device, RxDeviceSpec_Default);

  while (VxWindow_IsOpen(window)) {
    VxWindow_PollEvents(window);

    while (VxWindow_PopEvent(window, &event)) {
      if (event.type == VxEventType_Close) {
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
