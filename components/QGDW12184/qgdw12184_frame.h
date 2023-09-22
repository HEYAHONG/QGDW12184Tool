#ifndef __QGDW12184_FRAME_H__
#define __QGDW12184_FRAME_H__

#include "qgdw12184_crc.h"
#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


typedef struct
{
    uint16_t manufacturer_id;/**< 厂商ID */
    union
    {
        uint32_t version_and_serialnumber;
        struct
        {
            uint32_t serial_number:21;/**< 序列号 */
            uint32_t version_number:6;/**< 版本号 */
            uint32_t version_letter:5;/**< 版本标签,1=a */
        };
    };

} qgdw12184_frame_sensor_id_t; /**< 传感器id，有时也称网络id*/


/** \brief QGDW12184 设置传感器id
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param sensor_id qgdw12184_frame_sensor_id_t* 传感器ID
 *
 */
void qgdw12184_frame_set_sensor_id(uint8_t *frame,size_t frame_len,qgdw12184_frame_sensor_id_t *sensor_id);

/** \brief QGDW12184 获取传感器id
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param sensor_id qgdw12184_frame_sensor_id_t* 传感器ID
 *
 */
void qgdw12184_frame_get_sensor_id(uint8_t *frame,size_t frame_len,qgdw12184_frame_sensor_id_t *sensor_id);

typedef union
{
    uint8_t packet_header;
    struct
    {
        uint8_t packet_type:3; /**< 报文类型 */
        uint8_t frag_ind:1;/**< 分片指示 */
        uint8_t data_len:4;  /**< 参量个数 */
    };
} qgdw12184_frame_packet_header_t;/**< 数据包头 */

typedef enum
{
    QGDW12184_PACKET_HEADER_FRAG_IND_NO_FRAGMENT=0, /**< 未分片 */
    QGDW12184_PACKET_HEADER_FRAG_IND_FRAGMENT=1 /**<  分片 */
} qgdw12184_frame_packet_header_frag_ind_t; /**< 数据包头分片指示 */

/** \brief 数据包头分片指示字符串
 *
 * \param frag_ind qgdw12184_frame_packet_header_frag_ind_t  数据包头分片指示
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_packet_header_frag_ind_str(qgdw12184_frame_packet_header_frag_ind_t frag_ind);

typedef enum
{
    QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA=0,/**< 监测数据报文 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP=1,/**< 监测数据报文响应 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_ALARM_DATA=2,/**< 告警数据报文 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP=3,/**< 告警数据报文响应 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_CONTROL=4,/**< 控制报文 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP=5,/**< 控制报文响应 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK=6,/**< 分片应答报文 */
    QGDW12184_PACKET_HEADER_PACKET_TYPE_RESERVED=7,/**< 告警数据报文响应 */

} qgdw12184_frame_packet_header_packet_type_t;/**< 数据包头报文类型 */

/** \brief 数据包头报文类型字符串
 *
 * \param packet_type qgdw12184_frame_packet_header_packet_type_t 数据包头报文类型
 * \return const char* 字符串
 *
 */
const char *qgdw12184_frame_packet_header_packet_type_str(qgdw12184_frame_packet_header_packet_type_t packet_type);


/** \brief QGDW12184 设置数据包头
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param packet_header qgdw12184_frame_packet_header_t* 数据包头
 *
 */
void qgdw12184_frame_set_packet_header(uint8_t *frame,size_t frame_len,qgdw12184_frame_packet_header_t *packet_header);

/** \brief QGDW12184 获取数据包头
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param packet_header qgdw12184_frame_packet_header_t* 数据包头
 *
 */
void qgdw12184_frame_get_packet_header(uint8_t *frame,size_t frame_len,qgdw12184_frame_packet_header_t *packet_header);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __QGDW12184_FRAME_H__
