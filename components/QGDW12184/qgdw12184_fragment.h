#ifndef QGDW12184_FRAGMENT_H
#define QGDW12184_FRAGMENT_H

#include "qgdw12184_frame.h"
#include "qgdw12184_sysapi.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct qgdw12184_fragment_fragment_info qgdw12184_fragment_fragment_info_t;/**< 分片结构体 */

/** \brief QGDW12184 新建qgdw12184_fragment_fragment_info_t结构体
 *
 * \return qgdw12184_fragment_fragment_info_t* qgdw12184_fragment_fragment_info_t结构体，失败返回NULL
 *
 */
qgdw12184_fragment_fragment_info_t *qgdw12184_fragment_fragment_info_new();


/** \brief QGDW12184 删除qgdw12184_fragment_fragment_info_t结构体
 *
 * \param info qgdw12184_fragment_fragment_info_t* qgdw12184_fragment_fragment_info_t结构体
 *
 */
void qgdw12184_fragment_fragment_info_delete(qgdw12184_fragment_fragment_info_t *info);



/** \brief QGDW12184 设置帧(未分片)数据
 *
 * \param info qgdw12184_fragment_fragment_info_t* qgdw12184_fragment_fragment_info_t结构体
 * \param frame uint8_t* 帧(未分片)起始地址
 * \param frame_len size_t 帧(未分片)长度
 * \param sseq uint8_t  业务数据单元序号,从一开始连续取值
 * \return bool 是否成功,失败返回false
 *
 */
bool qgdw12184_fragment_fragment_set_frame(qgdw12184_fragment_fragment_info_t *info,uint8_t *frame,size_t frame_len,uint8_t sseq);

/** \brief QGDW12184 帧分片回调，注意，分片操作一般会调用多次。
 *
 * \param usr void* 用户参数
 * \param pseq uint8_t 协议数据单元序号
 * \param frame uint8_t* 帧(分片后)起始地址
 * \param frame_len size_t 帧(分片后)长度
 *
 */
typedef void (*qgdw12184_fragment_fragment_callback_t)(void *usr,uint8_t pseq,uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 是否能分片
 *
 * \param info qgdw12184_fragment_fragment_info_t* qgdw12184_fragment_fragment_info_t结构体
 * \param frag_len size_t 分片大小（主要指除开传感器id、参量个数、分片指示、报文类型、CRC校验的部分），当分片超过(1400-9)字节时按(1400-9)字节计算。
 * \return bool 是否能分片
 *
 */
bool qgdw12184_fragment_can_fragment(qgdw12184_fragment_fragment_info_t *info,size_t frag_len);

/** \brief QGDW12184 帧分片
 *
 * \param info qgdw12184_fragment_fragment_info_t* qgdw12184_fragment_fragment_info_t结构体
 * \param frag_len size_t 分片大小（主要指除开传感器id、参量个数、分片指示、报文类型、CRC校验的部分），当分片超过(1400-9)字节时按(1400-9)字节计算。
 * \param priority 优先级
 * \param on_fragment qgdw12184_fragment_fragment_callback_t 帧分片回调
 * \param usr void* 用户参数
 * \return bool 是否分片完成
 *
 */
bool qgdw12184_fragment_do_fragment(qgdw12184_fragment_fragment_info_t *info,size_t frag_len,uint8_t priority,qgdw12184_fragment_fragment_callback_t on_fragment,void *usr);


typedef struct qgdw12184_fragment_defragment_info qgdw12184_fragment_defragment_info_t;/**< 重组结构体 */

/** \brief QGDW12184 新建qgdw12184_fragment_defragment_info_t结构体
 *
 * \return qgdw12184_fragment_defragment_info_t* qgdw12184_fragment_defragment_info_t结构体
 *
 */
qgdw12184_fragment_defragment_info_t *qgdw12184_fragment_defragment_info_new();

/** \brief QGDW12184 删除qgdw12184_fragment_defragment_info_t结构体
 *
 * \param info qgdw12184_fragment_defragment_info_t* qgdw12184_fragment_defragment_info_t结构体
 *
 */
void qgdw12184_fragment_defragment_info_delete(qgdw12184_fragment_defragment_info_t* info);

/** \brief QGDW12184 添加帧(已分片)数据，需要多次调用直到所有分片均添加完成
 *
 * \param info qgdw12184_fragment_defragment_info_t* qgdw12184_fragment_defragment_info_t结构体
 * \param frame uint8_t* 帧(已分片)起始地址
 * \param frame_len size_t 帧(已分片)长度
 * \return bool 是否添加成功，注意:后续添加的帧数据必须与第一次添加的帧数据属于同一个传感器的同一SSEQ的帧
 *
 */
bool qgdw12184_fragment_defragment_add_frame(qgdw12184_fragment_defragment_info_t* info,uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 帧重组回调，注意，重组操作一般只调用一次。
 *
 * \param usr void* 用户参数
 * \param sseq uint8_t 业务数据单元序号
 * \param frame uint8_t* 帧(重组后)起始地址
 * \param frame_len size_t 帧(重组后)长度
 *
 */
typedef void (*qgdw12184_fragment_defragment_callback_t)(void *usr,uint8_t sseq,uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 是否能重组
 *
 * \param info qgdw12184_fragment_defragment_info_t* qgdw12184_fragment_defragment_info_t结构体
 * \return bool 是否能重组
 *
 */
bool qgdw12184_fragment_can_defragment(qgdw12184_fragment_defragment_info_t *info);

/** \brief QGDW12184 帧重组
 *
 * \param info qgdw12184_fragment_defragment_info_t* qgdw12184_fragment_defragment_info_t结构体
 * \param on_fragment qgdw12184_fragment_defragment_callback_t 帧重组回调
 * \param usr void* 用户参数
 * \return bool 是否重组完成
 *
 */
bool qgdw12184_fragment_do_defragment(qgdw12184_fragment_defragment_info_t *info,qgdw12184_fragment_defragment_callback_t on_defragment,void *usr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // QGDW12184_FRAGMENT_H
