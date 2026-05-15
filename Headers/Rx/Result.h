/*
  Simple result type for function error handling.

  This is a lightweight error handling system used across the library's API to
  indicate success or failure states.
*/

#ifndef Rx__ResultH
#define Rx__ResultH

/*
  Common status codes returned by library functions.
*/
typedef enum RxResultType {
  /* Operation completed successfully */
  RxResultType_Pass,

  /* The specified feature was not configured */
  RxResultType_NotConf,

  /* Failed to allocate memory for usage */
  RxResultType_AllocFail,

  /* Underlying Vulkan failure */
  RxResultType_VulkanFail,
} RxResultType;

/*
  Stores a result type and a human-readable string for it.
*/
typedef struct RxResult {
  RxResultType type;
  const char *msg;
} RxResult;

#endif
