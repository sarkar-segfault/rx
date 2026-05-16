/*
  Cross-platform symbol visibility macros.

  These macros control how functions are exposed when building or using as a
  shared library (DLL / SO).

  They handle:
  - C/C++ name mangling
  - Windows DLL import/export
  - GCC/Clang visibility attributes
*/

// IWYU pragma: private
// IWYU pragma: no_include

#ifndef Rx_ExposeH
#define Rx_ExposeH

/*
  Controls symbol export/import for shared libraries.
*/
#ifdef Rx_Shared
  #ifdef _WIN32
    #ifdef Rx_Build
      #define Rx_Export _declspec(dllexport)
    #else
      #define Rx_Export _declspec(dllimport)
    #endif
  #elif defined(__GNUC__)
    #define Rx_Export __attribute__((visibility("default")))
  #else
    #define Rx_Export
  #endif
#else
  #define Rx_Export
#endif

/*
  Prevents C++ name mangling when linking with C.
*/
#ifdef __cplusplus
  #define Rx_Extern extern "C"
#else
  #define Rx_Extern extern
#endif

/*
  Marks a function as part of the public C API of the library.

  Use this on all functions that must be visible outside the shared library.
*/
#define Rx_Expose Rx_Extern Rx_Export

#endif
