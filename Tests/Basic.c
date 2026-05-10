#include <stddef.h>

#include "Rx/Rx.h"
#include "Vx/Vx.h"

int main(void) {
  RxStatus rs;

  VxHandle *handle = NULL;
  VxHandle_Create(&handle, VxHandleSpec_Default);

  VxWindow *window;
  VxWindow_Create(&window, handle, VxWindowFlag_Default);

  VxEvent event;

  RxDevice *device;
  RxStatus_Debug(rs, RxDevice_Create(&device, RxDeviceSpec_Default));

  while (VxWindow_IsOpen(window)) {
    VxWindow_PollEvents(window);

    while (VxWindow_PopEvent(window, &event) == VxStatus_Pass) {
      if (event.type == VxEventType_Close) {
        VxWindow_Close(window);
        goto terminate;
      }
    }
  }

terminate:
  RxStatus_Debug(rs, RxDevice_Delete(&device));

  VxWindow_Delete(&window);
  VxHandle_Delete(&handle);
  return 0;
}
