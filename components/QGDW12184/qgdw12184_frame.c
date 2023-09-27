#include "qgdw12184_frame.h"

void qgdw12184_frame_set_sensor_id(uint8_t *frame,size_t frame_len,qgdw12184_frame_sensor_id_t *sensor_id)
{
    if(frame==NULL || frame_len <= 6 || sensor_id == NULL)
    {
        return;
    }

    {
        //厂商ID
        frame[0]=((sensor_id->manufacturer_id >> 8)&0xFF);
        frame[1]=((sensor_id->manufacturer_id)&0xFF);
    }
    {
        //版本及序列号
        frame[2]=((sensor_id->version_and_serialnumber >> 24)&0xFF);
        frame[3]=((sensor_id->version_and_serialnumber >> 16)&0xFF);
        frame[4]=((sensor_id->version_and_serialnumber >> 8)&0xFF);
        frame[5]=((sensor_id->version_and_serialnumber)&0xFF);
    }
}

void qgdw12184_frame_get_sensor_id(uint8_t *frame,size_t frame_len,qgdw12184_frame_sensor_id_t *sensor_id)
{
    if(frame==NULL || frame_len <= 6 || sensor_id == NULL)
    {
        return;
    }

    {
        //厂商ID
        sensor_id->manufacturer_id=frame[0];
        sensor_id->manufacturer_id<<=8;
        sensor_id->manufacturer_id+=frame[1];
    }
    {
        //版本及序列号
        sensor_id->version_and_serialnumber=frame[2];
        sensor_id->version_and_serialnumber<<=8;
        sensor_id->version_and_serialnumber+=frame[3];
        sensor_id->version_and_serialnumber<<=8;
        sensor_id->version_and_serialnumber+=frame[4];
        sensor_id->version_and_serialnumber<<=8;
        sensor_id->version_and_serialnumber+=frame[5];
    }
}

const char * qgdw12184_frame_packet_header_frag_ind_str(qgdw12184_frame_packet_header_frag_ind_t frag_ind)
{
    switch(frag_ind)
    {
    case QGDW12184_FRAME_PACKET_HEADER_FRAG_IND_NO_FRAGMENT:
        return "No Fragment";
    default:
        return "Fragment";
    }
}

const char *qgdw12184_frame_packet_header_packet_type_str(qgdw12184_frame_packet_header_packet_type_t packet_type)
{
    switch(packet_type)
    {
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA:
        return "Monitor Data";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP:
        return "Monitor Data Resp";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA:
        return "Alarm Data";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP:
        return "Alarm Data Resp";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL:
        return "Control";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP:
        return "Control Resp";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK:
        return "Fragment Ack";
    case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_RESERVED:
        return "Reserved";
    }
}

void qgdw12184_frame_set_packet_header(uint8_t *frame,size_t frame_len,qgdw12184_frame_packet_header_t *packet_header)
{
    if(frame==NULL || frame_len <= 7 || packet_header == NULL)
    {
        return;
    }

    frame[6]=packet_header->packet_header;
}
void qgdw12184_frame_get_packet_header(uint8_t *frame,size_t frame_len,qgdw12184_frame_packet_header_t *packet_header)
{
    if(frame==NULL || frame_len <= 7 || packet_header == NULL)
    {
        return;
    }

    packet_header->packet_header=frame[6];
}

uint16_t qgdw12184_frame_data_type_to_uint(qgdw12184_frame_data_type_t *data_type)
{
    if(data_type==NULL)
    {
        return 0;
    }
    return data_type->data_type;
}

void qgdw12184_frame_data_type_from_uint(qgdw12184_frame_data_type_t *data_type,uint16_t data_type_u)
{
    if(data_type!=NULL)
    {
        data_type->data_type=data_type_u;
    }
}

void qgdw12184_frame_set_data_header(uint8_t *data,size_t data_len,qgdw12184_frame_data_header_t *data_header)
{
    if(data==NULL || data_len <2 || data_header==NULL)
    {
        return;
    }
    data[0]=(data_header->data_header &0xFF);
    data[1]=((data_header->data_header >> 8)&0xFF);
}

void qgdw12184_frame_get_data_header(uint8_t *data,size_t data_len,qgdw12184_frame_data_header_t *data_header)
{
    if(data==NULL || data_len <2 || data_header==NULL)
    {
        return;
    }
    data_header->data_header=data[1];
    data_header->data_header<<=8;
    data_header->data_header+=data[0];
}

size_t qgdw12184_frame_get_data_capacity(uint8_t *data,size_t data_len)
{
    size_t ret=0;
    if(data==NULL || data_len <2)
    {
        return 0;
    }
    qgdw12184_frame_data_header_t header= {0};
    qgdw12184_frame_get_data_header(data,data_len,&header);
    if(header.data_length_flag==0)
    {
        size_t data_content_length=qgdw12184_frame_get_data_content_length(data,data_len);
        //头+4字节数据
        ret=sizeof(header)+data_content_length;
    }
    else
    {
        size_t data_content_length=qgdw12184_frame_get_data_content_length(data,data_len);
        //头+数据长度+数据内容长度
        ret=sizeof(header)+header.data_length_flag+data_content_length;
    }

    if(ret>data_len)
    {
        return 0;
    }
    else
    {
        return ret;
    }
}

size_t qgdw12184_frame_get_data_content_length(uint8_t *data,size_t data_len)
{
    size_t ret=0;
    if(data==NULL || data_len <2)
    {
        return 0;
    }
    qgdw12184_frame_data_header_t header= {0};
    qgdw12184_frame_get_data_header(data,data_len,&header);
    switch(header.data_length_flag)
    {
    case 1:
    {
        if(data_len>=sizeof(header)+1)
        {
            ret=data[sizeof(header)];
        }
    }
    break;
    case 2:
    {
        if(data_len>=sizeof(header)+2)
        {
            ret=data[sizeof(header)+1];
            ret<<=8;
            ret+=data[sizeof(header)];
        }
    }
    break;
    case 3:
    {
        if(data_len>=sizeof(header)+3)
        {
            ret=data[sizeof(header)+2];
            ret<<=8;
            ret+=data[sizeof(header)+1];
            ret<<=8;
            ret+=data[sizeof(header)];
        }
    }
    break;
    default:
    {
        //默认4字节数据
        ret=4;
    }
    break;
    }
    return ret;
}

uint8_t * qgdw12184_frame_get_data_content_ptr(uint8_t *data,size_t data_len)
{
    if(data==NULL || data_len <2)
    {
        return NULL;
    }

    size_t data_capacity=qgdw12184_frame_get_data_capacity(data,data_len);
    size_t data_content_length=qgdw12184_frame_get_data_content_length(data,data_len);

    if(data_capacity > data_content_length && data_capacity!=0 && data_content_length!=0)
    {
        return &data[data_capacity-data_content_length];
    }

    return NULL;
}

void qgdw12184_frame_monitor_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_monitor_data_callback_t on_monitor,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_monitor==NULL)
    {
        return;
    }

    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==1)
    {
        //分片报文不处理
        return;
    }
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA)
    {
        uint8_t *data_start=&frame[7];
        size_t data_len=frame_len-9;
        for(size_t i=0; i<packet_header.data_len; i++)
        {
            size_t data_capacity=qgdw12184_frame_get_data_capacity(data_start,data_len);
            size_t data_content_length=qgdw12184_frame_get_data_content_length(data_start,data_len);
            uint8_t *data_content_ptr=qgdw12184_frame_get_data_content_ptr(data_start,data_len);
            qgdw12184_frame_data_header_t data_header;
            qgdw12184_frame_get_data_header(data_start,data_len,&data_header);
            if(data_capacity!=0 && data_content_ptr!=NULL && data_content_length > 0)
            {
                on_monitor(usr,&sensor_id,&packet_header,i,&data_header,data_content_ptr,data_content_length);
            }
            else
            {
                break;
            }
            if(data_capacity <= data_len)
            {
                data_len-=data_capacity;
                data_start+=data_capacity;
            }
        }
    }
}

void qgdw12184_frame_monitor_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_monitor_resp_status_callback_t on_monitor_resp,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_monitor_resp==NULL)
    {
        return;
    }

    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==1)
    {
        //分片报文不处理
        return;
    }
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP)
    {
        uint8_t status=frame[7];
        if(status==QGDW12184_FRAME_MONITOR_RESP_STATUS_SUCCESS)
        {
            on_monitor_resp(usr,&sensor_id,&packet_header,QGDW12184_FRAME_MONITOR_RESP_STATUS_SUCCESS);
        }
        if(status==QGDW12184_FRAME_MONITOR_RESP_STATUS_FAILURE)
        {
            on_monitor_resp(usr,&sensor_id,&packet_header,QGDW12184_FRAME_MONITOR_RESP_STATUS_FAILURE);
        }
    }
}

void qgdw12184_frame_alarm_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_alarm_data_callback_t on_alarm,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_alarm==NULL)
    {
        return;
    }

    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==1)
    {
        //分片报文不处理
        return;
    }
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA)
    {
        uint8_t *data_start=&frame[7];
        size_t data_len=frame_len-9;
        for(size_t i=0; i<packet_header.data_len; i++)
        {
            size_t data_capacity=qgdw12184_frame_get_data_capacity(data_start,data_len);
            size_t data_content_length=qgdw12184_frame_get_data_content_length(data_start,data_len);
            uint8_t *data_content_ptr=qgdw12184_frame_get_data_content_ptr(data_start,data_len);
            qgdw12184_frame_data_header_t data_header;
            qgdw12184_frame_get_data_header(data_start,data_len,&data_header);
            if(data_capacity!=0 && data_content_ptr!=NULL && data_content_length > 0)
            {
                on_alarm(usr,&sensor_id,&packet_header,i,&data_header,data_content_ptr,data_content_length);
            }
            else
            {
                break;
            }
            if(data_capacity <= data_len)
            {
                data_len-=data_capacity;
                data_start+=data_capacity;
            }
        }
    }
}

void qgdw12184_frame_alarm_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_alarm_resp_status_callback_t on_alarm_resp,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_alarm_resp==NULL)
    {
        return;
    }

    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==1)
    {
        //分片报文不处理
        return;
    }
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP)
    {
        uint8_t status=frame[7];
        if(status==QGDW12184_FRAME_ALARM_RESP_STATUS_SUCCESS)
        {
            on_alarm_resp(usr,&sensor_id,&packet_header,QGDW12184_FRAME_ALARM_RESP_STATUS_SUCCESS);
        }
        if(status==QGDW12184_FRAME_ALARM_RESP_STATUS_FAILURE)
        {
            on_alarm_resp(usr,&sensor_id,&packet_header,QGDW12184_FRAME_ALARM_RESP_STATUS_FAILURE);
        }
    }
}

const char * qgdw12184_frame_control_header_request_set_flag_str(qgdw12184_frame_control_header_request_set_flag_t flag)
{
    switch(flag)
    {
    case QGDW12184_FRAME_CONTROL_HEADER_REQUEST_SET_FLAG_REQUSET:
    {
        return "Request";
    }
    default:
    {
        return "Set";
    }
    }
}

const char *qgdw12184_frame_control_header_ctrl_type_str(uint8_t ctrl_type)
{
    if(ctrl_type!=0 && ctrl_type <= 127)
    {
        if(ctrl_type>=QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_PROTOCOL_RESERVED_BEGIN && ctrl_type <= QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_PROTOCOL_RESERVED_END)
        {
            return "Protocol Reserved";
        }
        if(ctrl_type>=QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_VENDOR_RESERVED_BEGIN && ctrl_type <= QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_VENDOR_RESERVED_END)
        {
            return "Vendor Reserved";
        }
        switch(ctrl_type)
        {
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_GENERIC:
            return "Generic";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_MONITOR:
            return "Monitor";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_ALARM:
            return "Alarm";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_TIME:
            return "Time";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_SENSOR_ID:
            return "Sensor Id";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_RESET:
            return "Reset";
        case QGDW12184_FRAME_CONTROL_HEADER_CTRL_TYPE_TIME_REQUEST:
            return "Time Request";
        default:
            break;
        }
    }
    return "Invalid";
}

void qgdw12184_frame_set_control_header(uint8_t *data,size_t data_len,qgdw12184_frame_control_header_t *control_header)
{
    if(data==NULL || data_len == 0 || control_header==NULL)
    {
        return;
    }
    data[0]=control_header->control_header;
}

void qgdw12184_frame_get_control_header(uint8_t *data,size_t data_len,qgdw12184_frame_control_header_t *control_header)
{
    if(data==NULL || data_len == 0 || control_header==NULL)
    {
        return;
    }
    control_header->control_header=data[0];
}
