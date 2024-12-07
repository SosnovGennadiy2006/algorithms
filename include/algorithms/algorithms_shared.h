
#ifndef ALGORITHMS_EXPORT_H
#define ALGORITHMS_EXPORT_H

#ifdef ALGORITHMS_STATIC_DEFINE
#  define ALGORITHMS_EXPORT
#  define ALGORITHMS_NO_EXPORT
#else
#  ifndef ALGORITHMS_EXPORT
#    ifdef algorithms_EXPORTS
        /* We are building this library */
#      define ALGORITHMS_EXPORT 
#    else
        /* We are using this library */
#      define ALGORITHMS_EXPORT 
#    endif
#  endif

#  ifndef ALGORITHMS_NO_EXPORT
#    define ALGORITHMS_NO_EXPORT 
#  endif
#endif

#ifndef ALGORITHMS_DEPRECATED
#  define ALGORITHMS_DEPRECATED __declspec(deprecated)
#endif

#ifndef ALGORITHMS_DEPRECATED_EXPORT
#  define ALGORITHMS_DEPRECATED_EXPORT ALGORITHMS_EXPORT ALGORITHMS_DEPRECATED
#endif

#ifndef ALGORITHMS_DEPRECATED_NO_EXPORT
#  define ALGORITHMS_DEPRECATED_NO_EXPORT ALGORITHMS_NO_EXPORT ALGORITHMS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ALGORITHMS_NO_DEPRECATED
#    define ALGORITHMS_NO_DEPRECATED
#  endif
#endif

#endif /* ALGORITHMS_EXPORT_H */
