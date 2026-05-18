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

#ifndef RX_EXPOSE_H
#define RX_EXPOSE_H

/*
  Controls symbol export/import for shared libraries.
*/
#ifdef RX_SHARED
  #ifdef _WIN32
    #ifdef RX_BUILD
      #define RX_EXPOSE _declspec(dllexport)
    #else
      #define RX_EXPOSE _declspec(dllimport)
    #endif
  #elif defined(__GNUC__)
    #define RX_EXPOSE __attribute__((visibility("default")))
  #else
    #define RX_EXPOSE
  #endif
#else
  #define RX_EXPOSE
#endif

/*
  Prevents C++ name mangling when linking with C.
*/
#ifdef __cplusplus
  #define RX_EXTERN extern "C"
#else
  #define RX_EXTERN extern
#endif

/*
  Marks a function as part of the public C API of the library.

  Use this on all functions that must be visible outside the shared library.
*/
#define RX_EXPORT RX_EXTERN RX_EXPOSE

#endif
