#ifndef __CC_COMPILER_GCC_H
#define __CC_COMPILER_GCC_H

#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#define GCC_VERSION 0
#endif

/* Are two vars/types the same type (ignoring qualitfiers)?*/
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int:(-!!(e)); }))

#define __must_be_array(a) BUILD_BUG_ON_ZERO(__same_type((a), &(a)[0]))

/* define __attribute__ ((*)) */
#if GCC_VERSION >= 30400
#undef inline
#define inline         inline __attribute__ ((always_inline))
#define __noinline      __attribute__ ((noinline))
#define __pure          __attribute__ ((pure))
#define __const         __attribute__ ((const))
#define __noreturn      __attribute__ ((noreturn))
#define __malloc        __attribute__ ((malloc))
#define __must_check    __attribute__ ((warn_unused_result))
#define __deprecated    __attribute__ ((deprecated))
#define __used          __attribute__ ((used))
#define __unused        __attribute__ ((unused))
#define __packed        __attribute__ ((packed))
#define __align(x)      __attribute__ ((aligned, (x)))
#define __align_max     __attribute__ ((aligned))
#define __init          __attribute__ ((constructor))
#define __exit          __attribute__ ((destructor))
#define likely(x)       __builtin_expect (!!(x), 1)
#define unlikely(x)     __builtin_expect (!!(x), 0)
#else
#undef inline
#define __noinline   /* no noinline           */
#define __pure       /* no pure               */
#define __const      /* no const              */
#define __noreturn   /* no noreturn           */
#define __malloc     /* no malloc             */
#define __must_check /* no warn_unused_result */
#define __deprecated /* no deprecated         */
#define __used       /* no used               */
#define __unused     /* no unused             */
#define __packed     /* no packed             */
#define __align(x)   /* no aligned            */
#define __align_max  /* no align_max          */
#define __init
#define __exit
#define likely(x)    (x)
#define unlikely(x)  (x)
#endif

#endif /* __CC_COMPILER_GCC_H */
