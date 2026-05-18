/*
  Private macros to export symbols constituting the library's public API, and to
  annonate nullability.

  These macros control cross-platform symbol visibility in shared libraries, C
  linkage, and pointer annotations.
*/

// IWYU pragma: private
// IWYU pragma: no_include

#ifndef RX_PRIVATE_H
#define RX_PRIVATE_H

/*
  Controls symbol export/import for shared libraries.
*/
#ifdef RX_SHARED
  #ifdef _WIN32
    #ifdef RX_BUILD
      #define RX_EXPOSE __declspec(dllexport)
    #else
      #define RX_EXPOSE __declspec(dllimport)
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
*/
#define RX_EXPORT RX_EXTERN RX_EXPOSE

/*
  Marks a pointer that can be `NULL`.
*/
#define RX_NULLABLE

/*
  Marks a pointer that cannot be `NULL`.
*/
#define RX_NOTNULL

#endif
