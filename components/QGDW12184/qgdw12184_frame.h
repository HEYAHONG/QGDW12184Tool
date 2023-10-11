#ifndef __QGDW12184_FRAME_H__
#define __QGDW12184_FRAME_H__

#include "qgdw12184_crc.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

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

/** \brief QGDW12184 获取传感器id的厂商ID
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint16_t 厂商ID
 *
 */
uint16_t qgdw12184_frame_get_sensor_id_manufacturer_id(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取传感器id的序列号
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint32_t 序列号
 *
 */
uint32_t qgdw12184_frame_get_sensor_id_serial_number(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取传感器id的版本号
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint32_t 版本号
 *
 */
uint32_t qgdw12184_frame_get_sensor_id_version_number(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取传感器id的版本标签
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint32_t 版本标签
 *
 */
uint32_t qgdw12184_frame_get_sensor_id_version_letter(uint8_t *frame,size_t frame_len);

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
    QGDW12184_FRAME_PACKET_HEADER_FRAG_IND_NO_FRAGMENT=0, /**< 未分片 */
    QGDW12184_FRAME_PACKET_HEADER_FRAG_IND_FRAGMENT=1 /**<  分片 */
} qgdw12184_frame_packet_header_frag_ind_t; /**< 数据包头分片指示 */

/** \brief QGDW12184 数据包头分片指示字符串
 *
 * \param frag_ind qgdw12184_frame_packet_header_frag_ind_t  数据包头分片指示
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_packet_header_frag_ind_str(qgdw12184_frame_packet_header_frag_ind_t frag_ind);

typedef enum
{
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA=0,/**< 监测数据报文 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP=1,/**< 监测数据报文响应 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA=2,/**< 告警数据报文 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP=3,/**< 告警数据报文响应 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL=4,/**< 控制报文 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP=5,/**< 控制报文响应 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK=6,/**< 分片应答报文 */
    QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_RESERVED=7,/**< 保留 */

} qgdw12184_frame_packet_header_packet_type_t;/**< 数据包头报文类型 */

/** \brief QGDW12184 数据包头报文类型字符串
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

/** \brief QGDW12184 获取数据包头的报文类型
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint8_t 报文类型
 *
 */
uint8_t qgdw12184_frame_get_packet_header_packet_type(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取数据包头的分片指示
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint8_t 分片指示
 *
 */
uint8_t qgdw12184_frame_get_packet_header_frag_ind(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取数据包头的参量个数
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint8_t 参量个数
 *
 */
uint8_t qgdw12184_frame_get_packet_header_data_len(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取数据包数据(即数据包头之后CRC之前的部分)
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return uint8_t* 获取数据包数据
 *
 */
uint8_t * qgdw12184_frame_get_packet_data_ptr(uint8_t *frame,size_t frame_len);

/** \brief QGDW12184 获取数据包数据(即数据包头之后CRC之前的部分)长度
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \return size_t 数据包数据(即数据包头之后CRC之前的部分)长度
 *
 */
size_t  qgdw12184_frame_get_packet_data_len(uint8_t *frame,size_t frame_len);

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

typedef union
{
    uint8_t control_header;
    struct
    {
        uint8_t request_set_flag:1; /**< 参数配置类型，0： 查询； 1： 设置 */
        uint8_t ctrl_type:7; /**<  控制报文类型 */
    };
} qgdw12184_frame_control_header_t;/**< 控制报文头 */

typedef enum
{
    QGDW12184_FRAME_CONTROL_HEADER_REQUEST_SET_FLAG_REQUSET=0,/**< 查询 */
    QGDW12184_FRAME_CONTROL_HEADER_REQUEST_SET_FLAG_SET=1,/**< 设置 */
} qgdw12184_frame_control_header_request_set_flag_t;/**< 控制报文头参数配置类型 */

/** \brief QGDW12184 控制报文头参数配置类型字符串
 *
 * \param flag qgdw12184_frame_control_header_request_set_flag_t 控制报文头参数配置类型
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_control_header_request_set_flag_str(qgdw12184_frame_control_header_request_set_flag_t flag);

typedef enum
{
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_GENERIC=1,/**< 传感器通用参数查询/设置 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_MONITOR=2,/**< 传感器监测数据查询报文 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_ALARM=3,/**< 传感器告警参数查询/设置 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_TIME=4,/**< 传感器时间参数查询/设置 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_SENSOR_ID=5,/**< 传感器ID查询/设置 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_RESET=6,/**< 传感器复位设置 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_TIME_REQUEST=7,/**< 传感器请求校时 */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_PROTOCOL_RESERVED_BEGIN=8, /**< 协议扩展预留字段（起始） */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_PROTOCOL_RESERVED_END=99, /**< 协议扩展预留字段（结束） */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_VENDOR_RESERVED_BEGIN=100,/**< 厂商自定义预留字段(起始) */
    QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_VENDOR_RESERVED_END=127, /**< 厂商自定义预留字段(结束) */

} qgdw12184_frame_control_header_ctrl_type_t; /**< 控制报文头控制报文类型 */


/** \brief QGDW12184 控制报文头控制报文类型字符串
 *
 * \param ctrl_type uint8_t 控制报文头控制报文类型
 * \return const char* 字符串
 *
 */
const char *qgdw12184_frame_control_header_ctrl_type_str(uint8_t ctrl_type);


/** \brief QGDW12184 设置控制报文头
 *
 * \param data uint8_t* 控制帧数据（不含传感器地址与包头）起始
 * \param data_len size_t 控制帧数据（不含传感器地址与包头）长度
 * \param control_header qgdw12184_frame_control_header_t* 控制报文头
 *
 */
void qgdw12184_frame_set_control_header(uint8_t *data,size_t data_len,qgdw12184_frame_control_header_t *control_header);

/** \brief QGDW12184 获取控制报文头
 *
 * \param data uint8_t* 控制帧数据（不含传感器地址与包头）起始
 * \param data_len size_t 控制帧数据（不含传感器地址与包头）长度
 * \param control_header qgdw12184_frame_control_header_t*控制报文头
 *
 */
void qgdw12184_frame_get_control_header(uint8_t *data,size_t data_len,qgdw12184_frame_control_header_t *control_header);

/** \brief QGDW12184 获取控制报文头的参数配置类型
 *
 * \param data uint8_t* 控制帧数据（不含传感器地址与包头）起始
 * \param data_len size_t 控制帧数据（不含传感器地址与包头）长度
 * \return uint8_t 参数配置类型
 *
 */
uint8_t qgdw12184_frame_get_control_header_request_set_flag(uint8_t *data,size_t data_len);

/** \brief QGDW12184 获取控制报文头的控制报文类型
 *
 * \param data uint8_t* 控制帧数据（不含传感器地址与包头）起始
 * \param data_len size_t 控制帧数据（不含传感器地址与包头）长度
 * \return uint8_t 控制报文类型
 *
 */
uint8_t qgdw12184_frame_get_control_header_ctrl_type(uint8_t *data,size_t data_len);


/** \brief  QGDW12184 控制报文数据回调
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param data uint8_t* 控制帧数据（不含传感器地址与包头）起始
 * \param data_len size_t 控制帧数据（不含传感器地址与包头）长度
 *
 */
typedef void (*qgdw12184_frame_control_data_content_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,uint8_t *data,size_t data_len);


/** \brief QGDW12184 控制报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_data_content qgdw12184_frame_control_data_content_callback_t 控制报文数据回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_control_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_control_data_content_callback_t on_data_content,void *usr);


typedef qgdw12184_frame_control_data_content_callback_t qgdw12184_frame_control_resp_data_content_callback_t;/**< 控制响应报文数据回调 */


/** \brief QGDW12184 控制响应报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_data_content qgdw12184_frame_control_resp_data_content_callback_t 控制报文数据回调
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_control_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_control_resp_data_content_callback_t on_data_content,void *usr);

typedef union
{
    uint16_t fragment_header;
    struct
    {
        uint16_t pseq:7;/**< 协议数据单元序号 */
        uint16_t priority:1;/**< 协议数据单元优先级 */
        uint16_t sseq:6;/**< 业务数据单元序号 */
        uint16_t flag:2;/**< 分片属性 */
    };
} qgdw12184_frame_fragment_header_t;/**< 分片报文头 */

typedef enum
{
    QGDW12184_FRAME_FRAGMENT_HEADER_PRIORITY_LOW=0,/**< 低优先级 */
    QGDW12184_FRAME_FRAGMENT_HEADER_PRIORITY_HIGH=1/**< 高优先级 */
} qgdw12184_frame_fragment_header_priority_t;/**< 分片报文头优先级 */


/** \brief QGDW12184 分片报文头优先级字符串
 *
 * \param priority qgdw12184_frame_fragment_header_priority_t 分片报文头优先级
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_fragment_header_priority_str(qgdw12184_frame_fragment_header_priority_t priority);

typedef enum
{
    QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_AG_UNFRAG=0,/**< 没有进行分片 */
    QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_START=1,/**< 第一个分片 */
    QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_NEXT=2,/**< 后续还有分片 */
    QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_STOP=3/**< 最后一个分片 */
} qgdw12184_frame_fragment_header_flag_t; /**< 分片报文头分片属性 */

/** \brief QGDW12184 分片报文头分片属性字符串
 *
 * \param flag qgdw12184_frame_fragment_header_flag_t 分片报文头分片属性
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_fragment_header_flag_str(qgdw12184_frame_fragment_header_flag_t flag);

/** \brief QGDW12184 设置分片报文头
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \param header qgdw12184_frame_fragment_header_t* 分片报文头
 *
 */
void qgdw12184_frame_set_fragment_header(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_header_t *header);

/** \brief QGDW12184 获取分片报文头
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \param header qgdw12184_frame_fragment_header_t* 分片报文头
 *
 */
void qgdw12184_frame_get_fragment_header(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_header_t *header);

/** \brief QGDW12184 获取分片报文头的协议数据单元序号
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \return uint8_t 协议数据单元序号
 *
 */
uint8_t qgdw12184_frame_get_fragment_header_pseq(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片报文头的协议数据单元优先级
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \return uint8_t 协议数据单元优先级
 *
 */
uint8_t qgdw12184_frame_get_fragment_header_priority(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片报文头的业务数据单元序号
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \return uint8_t 业务数据单元序号
 *
 */
uint8_t qgdw12184_frame_get_fragment_header_sseq(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片报文头的分片属性
 *
 * \param data uint8_t* PDU数据起始地址
 * \param data_len size_t PDU数据长度
 * \return uint8_t 分片属性
 *
 */
uint8_t qgdw12184_frame_get_fragment_header_flag(uint8_t * data,size_t data_len);

typedef union
{
    uint16_t ackdata;
    struct
    {
        uint16_t pseq:7;/**< 协议数据单元序号 */
        uint16_t priority:1;/**< 协议数据单元优先级 */
        uint16_t sseq:6;/**< 业务数据单元序号 */
        uint16_t ack:2;/**< 0=接收错误,3=接收正确,其它=保留 */
    };
} qgdw12184_frame_fragment_ack_ackdata_t;/**< 分片响应报文AckData */

typedef enum
{
    QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_PRIORITY_LOW=0,/**< 低优先级 */
    QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_PRIORITY_HIGH=1/**< 高优先级 */
} qgdw12184_frame_fragment_ack_ackdata_priority_t;/**< 分片响应报文AckData的优先级 */

/** \brief QGDW12184 分片响应报文AckData的优先级字符串
 *
 * \param priority qgdw12184_frame_fragment_ack_ackdata_priority_t 分片响应报文AckData的优先级
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_fragment_ack_ackdata_priority_str(qgdw12184_frame_fragment_ack_ackdata_priority_t priority);

typedef enum
{
    QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_ACK_ERROR=0,/**< 错误 */
    QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_ACK_OK=3 /**< 正确 */
} qgdw12184_frame_fragment_ack_ackdata_ack_t;/**< 分片响应报文AckData的Ack字段 */

/** \brief QGDW12184 分片响应报文AckData的Ack字段字符串
 *
 * \param ack qgdw12184_frame_fragment_ack_ackdata_ack_t 分片响应报文AckData的Ack字段
 * \return const char* 字符串
 *
 */
const char * qgdw12184_frame_fragment_ack_ackdata_ack_str(qgdw12184_frame_fragment_ack_ackdata_ack_t ack);

/** \brief QGDW12184 设置分片响应报文AckData
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \param ackdata qgdw12184_frame_fragment_ack_ackdata_t* 分片响应报文AckData
 *
 */
void qgdw12184_frame_set_fragment_ack_ackdata(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_ack_ackdata_t *ackdata);

/** \brief QGDW12184 获取分片响应报文AckData
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \param ackdata qgdw12184_frame_fragment_ack_ackdata_t* 分片响应报文AckData
 *
 */
void qgdw12184_frame_get_fragment_ack_ackdata(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_ack_ackdata_t *ackdata);

/** \brief QGDW12184 获取分片响应报文AckData的协议数据单元序号
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \return uint8_t 协议数据单元序号
 *
 */
uint8_t qgdw12184_frame_get_fragment_ack_ackdata_pseq(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片响应报文AckData的协议数据单元优先级
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \return uint8_t 协议数据单元优先级
 *
 */
uint8_t qgdw12184_frame_get_fragment_ack_ackdata_priority(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片响应报文AckData的业务数据单元序号
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \return uint8_t 业务数据单元序号
 *
 */
uint8_t qgdw12184_frame_get_fragment_ack_ackdata_sseq(uint8_t * data,size_t data_len);

/** \brief QGDW12184 获取分片响应报文AckData的ack
 *
 * \param data uint8_t* AckData起始地址
 * \param data_len size_t AckData长度
 * \return uint8_t ack
 *
 */
uint8_t qgdw12184_frame_get_fragment_ack_ackdata_ack(uint8_t * data,size_t data_len);

/** \brief  QGDW12184 分片响应报文AckData
 *
 * \param usr void* 用户参数(由用户自定义)
 * \param sensor_id const qgdw12184_frame_sensor_id_t* 传感器id（不可写入）
 * \param packet_header const qgdw12184_frame_packet_header_t* 数据包头(不可写入)
 * \param ackdata qgdw12184_frame_fragment_ack_ackdata_t* 分片响应报文AckData
 */
typedef void (*qgdw12184_frame_fragment_ack_ackdata_callback_t)(void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_fragment_ack_ackdata_t *ackdata);

/** \brief QGDW12184 分片响应报文(无分片)解析
 *
 * \param frame uint8_t* 帧起始地址
 * \param frame_len size_t 帧长度
 * \param on_ack_data qgdw12184_frame_fragment_ack_ackdata_callback_t 分片响应报文AckData
 * \param usr void* 用户参数(由用户自定义)
 *
 */
void qgdw12184_frame_fragment_ack_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_fragment_ack_ackdata_callback_t on_ack_data,void *usr);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __QGDW12184_FRAME_H__
