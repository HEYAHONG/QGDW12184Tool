#ifndef QGDW12184_SYSAPI_H
#define QGDW12184_SYSAPI_H

#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/** \brief QGDW12184 内存分配
 *
 * \param n_bytes size_t 待分配的内存大小
 * \return void* 指针
 *
 */
void * qgdw12184_sysapi_malloc(size_t n_bytes);

/** \brief QGDW12184 内存分配钩子，当此钩子不为NULL优先调用钩子
 *
 * \param n_bytes size_t 待分配的内存大小
 * \return void* 指针
 *
 */
extern void * (*qgdw12184_sysapi_malloc_hook)(size_t n_bytes);


/** \brief QGDW12184 内存释放
 *
 * \param ptr void* 指针
 *
 */
void qgdw12184_sysapi_free(void *ptr);


/** \brief QGDW12184 内存释放钩子，当此钩子不为NULL优先调用钩子
 *
 * \param ptr void* 指针
 *
 */
extern void (*qgdw12184_sysapi_free_hook)(void *ptr);

/** \brief QGDW12184 让出时间片，协议中使用此函数表示空闲（协议不使用CPU）
 *
 * \return int 成功返回0，失败返回非0
 *
 */
int qgdw12184_sysapi_yield();

/** \brief QGDW12184 让出时间片钩子,当此钩子不为NULL优先调用钩子
 *
 * \return int 成功返回0，失败返回非0
 *
 */
extern int (*qgdw12184_sysapi_yield_hook)();



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // QGDW12184_SYSAPI_H
