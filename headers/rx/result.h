/*
  Simple result type for function error handling.

  This is a lightweight error handling system used across the library's API to
  indicate success or failure states.
*/

#ifndef RX_RESULT_H
#define RX_RESULT_H

#include "private.h"

/*
  Common status codes returned by library functions.
*/
typedef enum RxResultType {
  /* Operation completed successfully */
  RX_RESULT_PASS,

  /* The specified feature was not configured */
  RX_RESULT_NOT_CONF,

  /* Failed to allocate memory for usage */
  RX_RESULT_BAD_ALLOC,

  /* Underlying WebGPU failure */
  RX_RESULT_WGPU_FAIL,
} RxResultType;

/*
  Stores a result type and a human-readable string for it.
*/
typedef struct RxResult {
  RxResultType type;
  RX_NOTNULL const char *msg;
} RxResult;

#endif
