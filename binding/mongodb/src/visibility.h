#ifndef MONGODBL_VISIBILITY_H
#define MONGODBL_VISIBILITY_H

// Handle symbol visibility
// From: https://gcc.gnu.org/wiki/Visibility

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
  #define MONGODBL_HELPER_DLL_IMPORT __declspec(dllimport)
  #define MONGODBL_HELPER_DLL_EXPORT __declspec(dllexport)
  #define MONGODBL_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define MONGODBL_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define MONGODBL_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define MONGODBL_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MONGODBL_HELPER_DLL_IMPORT
    #define MONGODBL_HELPER_DLL_EXPORT
    #define MONGODBL_HELPER_DLL_LOCAL
  #endif
#endif

// Now we use the generic helper definitions above to define MONGODBL_API and MONGODBL_LOCAL.
// MONGODBL_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// MONGODBL_LOCAL is used for non-api symbols.

#ifdef MONGODBL_EXPORTS // defined if we are building the MONGODBL DLL (instead of using it)
#define MONGODBL_API MONGODBL_HELPER_DLL_EXPORT
#else
#define MONGODBL_API MONGODBL_HELPER_DLL_IMPORT
#endif // MONGODBL_DLL_EXPORTS
#define MONGODBL_LOCAL MONGODBL_HELPER_DLL_LOCAL
#endif
