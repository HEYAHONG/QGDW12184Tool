#include "qgdw12184_sysapi.h"

#ifdef WIN32
//Windows
#include "windows.h"

#ifndef USE_MALLOC
#define USE_MALLOC
#endif // USE_MALLOC

#ifndef USE_FREE
#define USE_FREE
#endif // USE_FREE

#ifndef USE_SLEEP
#define USE_SLEEP
#endif // USE_SLEEP

#endif // WIN32


#if defined(__unix__) || defined(__linux__)

#include "unistd.h"
#include "pthread.h"

#ifndef USE_MALLOC
#define USE_MALLOC
#endif // USE_MALLOC

#ifndef USE_FREE
#define USE_FREE
#endif // USE_FREE

#ifndef USE_USLEEP
#define USE_USLEEP
#endif // USE_USLEEP

#endif

void * qgdw12184_sysapi_malloc(size_t n_bytes)
{
    //调用钩子
    if(qgdw12184_sysapi_malloc_hook!=NULL)
    {
        return qgdw12184_sysapi_malloc_hook(n_bytes);
    }

    if(n_bytes==0)
    {
        return NULL;
    }
#ifdef USE_MALLOC
    return malloc(n_bytes);
#else
#warning malloc() may not be used
#endif
}

void * (*qgdw12184_sysapi_malloc_hook)(size_t n_bytes)=NULL;


void qgdw12184_sysapi_free(void *ptr)
{
    //调用钩子
    if(qgdw12184_sysapi_free_hook!=NULL)
    {
        return qgdw12184_sysapi_free_hook(ptr);
    }

    if(ptr==NULL)
    {
        return;
    }
#ifdef USE_FREE
    free(ptr);
#else
#warning free() may not be used
#endif // USE_FREE
}

void (*qgdw12184_sysapi_free_hook)(void *ptr)=NULL;

int qgdw12184_sysapi_yield()
{
    if(qgdw12184_sysapi_yield_hook!=NULL)
    {
        return qgdw12184_sysapi_yield_hook();
    }
    int ret=0;
#ifdef USE_SLEEP
    Sleep(0);
#endif // USE_SLEEP

#ifdef USE_USLEEP
    usleep(0);
#endif // USE_USLEEP
    return ret;
}

int (*qgdw12184_sysapi_yield_hook)()=NULL;
