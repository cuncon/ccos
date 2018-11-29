#if !defined(_CC_STDDEF_H) || defined(__need_size_t) \
    || defined(__need_boolean) || defined(__need_NULL)

#if defined(_CC_STDDEF_H) || defined(__need_NULL)
#undef NULL /* in case someone has defined it */
#define NULL ((void *)0)
#undef __need_NULL
#endif

#if defined(_CC_STDDEF_H) || defined(__need_size_t)
#ifndef _SIZE_T /* in case <sys/types.h> has defined it */
#ifndef __size_t
#define __size_t
#ifndef __SIZE_TYPE
#define __SIZE_TYPE long unsigned int
#endif
#if !defined(size_t)
typedef __SIZE_TYPE size_t;
#endif /* !defined(size_t) */
#endif /* _SIZE_T */
#endif /* __size_t */
#undef __need_size_t
#endif /* defined(_CC_STDDEF_H) || defined(__need_size_t) */

#if defined(_CC_STDDEF_H) || defined(__need_boolean)
#if !(defined(TRUE) && defined(FALSE))
#define TRUE 1
#define FALSE !TRUE
#endif
#undef __need_boolean
#endif /* defined(_CC_STDDEF_H) || defined(__need_boolean) */

#endif /* !_CC_STDDEF_H || __need_XXX was defined before */
