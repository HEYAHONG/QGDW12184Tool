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
    QGDW12184_PACKET_HEADER_PACKET_TYPE_RESERVED=7,/**< 保留 */

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

typedef union
{
    uint16_t data_type;
    struct
    {
        uint16_t data_type_code:11;/**<  编码*/
        uint16_t data_type_char:3;/**< 特征 */
    };

} qgdw12184_frame_data_type_t; /**< 参量类型 */

/** \brief QGDW12184 参量类型转Uint
 *
 * \param data_type qgdw12184_frame_data_type_t* 参量类型
 * \return uint16 Uint类型参量类型
 *
 */
uint16_t qgdw12184_frame_data_type_to_uint(qgdw12184_frame_data_type_t *data_type);


/** \brief QGDW12184 Uint转参量类型
 *
 * \param data_type qgdw12184_frame_data_type_t* 参量类型
 * \param data_type_u uint16_t Uint类型参量类型
 *
 */
void qgdw12184_frame_data_type_from_uint(qgdw12184_frame_data_type_t *data_type,uint16_t data_type_u);

typedef union
{
    uint16_t data_header;
    struct
    {
        uint16_t data_length_flag:2;/**< 数据长度，0=4字节，其余数据表示后接几个字节作为数据长度 */
        uint16_t data_type:14;/**< 参量类型(Uint类型) */
    };
} qgdw12184_frame_data_header_t;/**< (单个）参量头 */

/** \brief QGDW12184 设置参量头到(单个)参量数据
 *
 * \param data uint8_t* (单个)参量数据起始地址
 * \param data_len size_t (单个)参量数据长度（可大不可小）
 * \param data_header qgdw12184_frame_data_header_t* (单个）参量头
 *
 */
void qgdw12184_frame_set_data_header(uint8_t *data,size_t data_len,qgdw12184_frame_data_header_t *data_header);

/** \brief QGDW12184 从(单个)参量数据获取参量头
 *
 * \param data uint8_t* (单个)参量数据起始地址
 * \param data_len size_t (单个)参量数据长度（可大不可小）
 * \param data_header qgdw12184_frame_data_header_t* (单个）参量头
 *
 */
void qgdw12184_frame_get_data_header(uint8_t *data,size_t data_len,qgdw12184_frame_data_header_t *data_header);

/** \brief QGDW12184 获取(单个)参量占用空间
 *
 * \param data uint8_t* (单个)参量数据起始地址
 * \param data_len size_t (单个)参量数据长度（可大不可小）
 * \return size_t (单个)参量占用空间(包括参量头、参量数据长度，参量数据内容)，失败返回0
 *
 */
size_t qgdw12184_frame_get_data_capacity(uint8_t *data,size_t data_len);

/** \brief QGDW12184 获取(单个)参量内容长度
 *
 * \param data uint8_t* (单个)参量数据起始地址
 * \param data_len size_t (单个)参量数据长度（可大不可小）
 * \return size_t (单个)参量内容长度
 *
 */
size_t qgdw12184_frame_get_data_content_length(uint8_t *data,size_t data_len);

/** \brief  QGDW12184 获取(单个)参量内容指针
 *
 * \param data uint8_t* (单个)参量数据起始地址
 * \param data_len size_t (单个)参量数据长度（可大不可小）
 * \return uint8_t* (单个)参量内容指针,失败返回NULL
 *
 */
uint8_t * qgdw12184_frame_get_data_content_ptr(uint8_t *data,size_t data_len);


/** \brief  QGDW12184 监测报文参量回调
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param index size_t 参量引索，从0开始
 * \param data_header const qgdw12184_frame_data_header_t* 参量头
 * \param data_content const uint8_t* 参量内容
 * \param data_content_length size_t 参量内容长度
 *
 */
typedef void (*qgdw12184_frame_monitor_data_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,size_t index,const qgdw12184_frame_data_header_t *data_header,const uint8_t *data_content,size_t data_content_length);


/** \brief QGDW12184 监测报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_monitor qgdw12184_frame_monitor_data_callback_t 监测报文参量回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_monitor_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_monitor_data_callback_t on_monitor,void *usr);

typedef enum
{
    QGDW12184_FRAME_MONITOR_RESP_STATUS_SUCCESS=0xFF,/**< 发送成功 */
    QGDW12184_FRAME_MONITOR_RESP_STATUS_FAILURE=0x0 /**< 发送失败 */
} qgdw12184_frame_monitor_resp_status_t;/**< 监测响应报文响应状态 */

/** \brief  QGDW12184 监测响应报文响应状态回调
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param status  qgdw12184_frame_monitor_resp_status_t 响应状态
 *
 */
typedef void (*qgdw12184_frame_monitor_resp_status_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_monitor_resp_status_t status);


/** \brief QGDW12184 监测响应报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_monitor_resp qgdw12184_frame_monitor_resp_status_callback_t 监测响应报文响应状态回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_monitor_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_monitor_resp_status_callback_t on_monitor_resp,void *usr);


/** \brief  QGDW12184 告警报文参量回调
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param index size_t 参量引索，从0开始
 * \param data_header const qgdw12184_frame_data_header_t* 参量头
 * \param data_content const uint8_t* 参量内容
 * \param data_content_length size_t 参量内容长度
 *
 */
typedef void (*qgdw12184_frame_alarm_data_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,size_t index,const qgdw12184_frame_data_header_t *data_header,const uint8_t *data_content,size_t data_content_length);


/** \brief QGDW12184 告警报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_alarm qgdw12184_frame_alarm_data_callback_t 告警报文参量回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_alarm_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_alarm_data_callback_t on_alarm,void *usr);

typedef enum
{
    QGDW12184_FRAME_ALARM_RESP_STATUS_SUCCESS=0xFF,/**< 发送成功 */
    QGDW12184_FRAME_ALARM_RESP_STATUS_FAILURE=0x0 /**< 发送失败 */
} qgdw12184_frame_alarm_resp_status_t;/**< 告警响应报文响应状态 */

/** \brief  QGDW12184 告警响应报文响应状态回调
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param status  qgdw12184_frame_alarm_resp_status_t 响应状态
 *
 */
typedef void (*qgdw12184_frame_alarm_resp_status_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_alarm_resp_status_t status);


/** \brief QGDW12184 告警响应报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_alarm_resp qgdw12184_frame_alarm_resp_status_callback_t 告警响应报文响应状态回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_alarm_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_alarm_resp_status_callback_t on_alarm_resp,void *usr);



#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __QGDW12184_FRAME_H__
