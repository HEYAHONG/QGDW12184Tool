
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#ifndef __QGDW12184_CRC_H__
#define __QGDW12184_CRC_H__

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


/** \brief QGDW12184 CRC-16计算
 *
 * \param buff uint8_t* 待计算的缓冲
 * \param buff_len size_t 待计算的缓冲长度
 * \return uint16_t CRC-16结果
 *
 */
uint16_t qgdw12184_crc_claculate(uint8_t *buff,size_t buff_len);

/** \brief QGDW12184 帧校验
 *
 * \param frame uint8_t* 待校验的帧(需大于2字节)
 * \param frame_len size_t 待校验的帧长度(需大于2字节)
 * \return bool 是否校验成功
 *
 */
bool qgdw12184_crc_check(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 添加帧校验
 *
 * \param frame uint8_t* 待添加校验的帧(需大于2字节,含校验所需字节)
 * \param frame_len size_t 待添加校验的帧长度(需大于2字节,含校验所需字节)
 *
 */
void qgdw12184_crc_append(uint8_t *frame,size_t frame_len);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __QGDW12184_CRC_H__
