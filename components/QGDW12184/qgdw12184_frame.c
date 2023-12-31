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

uint16_t qgdw12184_frame_get_sensor_id_manufacturer_id(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_sensor_id_t sensor_id= {0};
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    return sensor_id.manufacturer_id;
}

uint32_t qgdw12184_frame_get_sensor_id_serial_number(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_sensor_id_t sensor_id= {0};
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    return sensor_id.serial_number;
}

uint32_t qgdw12184_frame_get_sensor_id_version_number(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_sensor_id_t sensor_id= {0};
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    return sensor_id.version_number;
}

uint32_t qgdw12184_frame_get_sensor_id_version_letter(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_sensor_id_t sensor_id= {0};
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    return sensor_id.version_letter;
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

uint8_t qgdw12184_frame_get_packet_header_packet_type(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_packet_header_t packet_header= {0};
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    return packet_header.packet_type;
}

uint8_t qgdw12184_frame_get_packet_header_frag_ind(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_packet_header_t packet_header= {0};
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    return packet_header.frag_ind;
}

uint8_t qgdw12184_frame_get_packet_header_data_len(uint8_t *frame,size_t frame_len)
{
    qgdw12184_frame_packet_header_t packet_header= {0};
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    return packet_header.data_len;
}

uint8_t * qgdw12184_frame_get_packet_data_ptr(uint8_t *frame,size_t frame_len)
{
    if(frame!=NULL && frame_len > 9)
    {
        return &frame[7];
    }
    else
    {
        return NULL;
    }
}

size_t  qgdw12184_frame_get_packet_data_len(uint8_t *frame,size_t frame_len)
{
    if(frame!=NULL && frame_len > 9)
    {
        return frame_len-9;
    }
    else
    {
        return 0;
    }
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

uint16_t qgdw12184_frame_get_data_header_data_length_flag(uint8_t *data,size_t data_len)
{
    qgdw12184_frame_data_header_t data_header= {0};
    qgdw12184_frame_get_data_header(data,data_len,&data_header);
    return data_header.data_length_flag;
}

uint16_t qgdw12184_frame_get_data_header_data_type(uint8_t *data,size_t data_len)
{
    qgdw12184_frame_data_header_t data_header= {0};
    qgdw12184_frame_get_data_header(data,data_len,&data_header);
    return data_header.data_type;
}

uint16_t qgdw12184_frame_get_data_length_flag_from_data_content_length(size_t data_length)
{
    if(data_length==4)
    {
        //默认4字节
        return 0;
    }

    if(data_length < 0x100)
    {
        return 1;
    }

    if(data_length < 0x10000)
    {
        return 2;
    }

    //最大3字节(超过3字节也按3字节计算)
    return 3;
}

size_t qgdw12184_frame_get_data_capacity_from_data_content_length(size_t data_length)
{
    return sizeof(qgdw12184_frame_data_header_t)+qgdw12184_frame_get_data_length_flag_from_data_content_length(data_length)+data_length;
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

uint8_t qgdw12184_frame_get_control_header_request_set_flag(uint8_t *data,size_t data_len)
{
    qgdw12184_frame_control_header_t control_header= {0};
    qgdw12184_frame_get_control_header(data,data_len,&control_header);
    return control_header.request_set_flag;
}

uint8_t qgdw12184_frame_get_control_header_ctrl_type(uint8_t *data,size_t data_len)
{
    qgdw12184_frame_control_header_t control_header= {0};
    qgdw12184_frame_get_control_header(data,data_len,&control_header);
    return control_header.ctrl_type;
}

void qgdw12184_frame_control_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_control_data_content_callback_t on_data_content,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_data_content==NULL)
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
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL)
    {
        on_data_content(usr,&sensor_id,&packet_header,&frame[7],frame_len-9);
    }
}

void qgdw12184_frame_control_resp_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_control_resp_data_content_callback_t on_data_content,void *usr)
{
    if(frame==NULL || frame_len < 9 || on_data_content==NULL)
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
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP)
    {
        on_data_content(usr,&sensor_id,&packet_header,&frame[7],frame_len-9);
    }
}

const char * qgdw12184_frame_fragment_header_priority_str(qgdw12184_frame_fragment_header_priority_t priority)
{
    switch(priority)
    {
    case QGDW12184_FRAME_FRAGMENT_HEADER_PRIORITY_LOW:
        return "Low";
    default:
        return "High";
    }
}

const char * qgdw12184_frame_fragment_header_flag_str(qgdw12184_frame_fragment_header_flag_t flag)
{
    switch(flag)
    {
    case QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_AG_UNFRAG:
        return "Unfrag";
    case QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_START:
        return "Frag_Start";
    case QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_NEXT:
        return "Frag_Next";
    case QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_STOP:
        return "Frag_Stop";
    }
}

void qgdw12184_frame_set_fragment_header(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_header_t *header)
{
    if(data==NULL || data_len < 2 || header==NULL)
    {
        return;
    }
    data[0]=header->fragment_header&0xFF;
    data[1]=(header->fragment_header>>8)&0xFF;
}

void qgdw12184_frame_get_fragment_header(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_header_t *header)
{
    if(data==NULL || data_len < 2 || header==NULL)
    {
        return;
    }
    header->fragment_header=data[1];
    header->fragment_header<<=8;
    header->fragment_header+=data[0];
}

uint8_t qgdw12184_frame_get_fragment_header_pseq(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_header_t fragment_header= {0};
    qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);
    return fragment_header.pseq;
}

uint8_t qgdw12184_frame_get_fragment_header_priority(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_header_t fragment_header= {0};
    qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);
    return fragment_header.priority;
}

uint8_t qgdw12184_frame_get_fragment_header_sseq(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_header_t fragment_header= {0};
    qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);
    return fragment_header.sseq;
}

uint8_t qgdw12184_frame_get_fragment_header_flag(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_header_t fragment_header= {0};
    qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);
    return fragment_header.flag;
}

const char * qgdw12184_frame_fragment_ack_ackdata_priority_str(qgdw12184_frame_fragment_ack_ackdata_priority_t priority)
{
    switch(priority)
    {
    case QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_PRIORITY_LOW:
        return "Low";
    default:
        return "High";
    }
}

const char * qgdw12184_frame_fragment_ack_ackdata_ack_str(qgdw12184_frame_fragment_ack_ackdata_ack_t ack)
{
    switch(ack)
    {
    case QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_ACK_ERROR:
    {
        return "Error";
    }
    case QGDW12184_FRAME_FRAGMENT_ACK_ACKDATA_ACK_OK:
    {
        return "Ok";
    }
    default:
    {
        return "Reserved";
    }
    }
}

void qgdw12184_frame_set_fragment_ack_ackdata(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_ack_ackdata_t *ackdata)
{
    if(data==NULL || data_len < 2 || ackdata == NULL)
    {
        return;
    }

    data[0]=ackdata->ackdata&0xFF;
    data[1]=(ackdata->ackdata>>8)&0xFF;
}

void qgdw12184_frame_get_fragment_ack_ackdata(uint8_t * data,size_t data_len,qgdw12184_frame_fragment_ack_ackdata_t *ackdata)
{
    if(data==NULL || data_len < 2 || ackdata == NULL)
    {
        return;
    }

    ackdata->ackdata=data[1];
    ackdata->ackdata<<=8;
    ackdata->ackdata+=data[0];
}

uint8_t qgdw12184_frame_get_fragment_ack_ackdata_pseq(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_ack_ackdata_t ackdata= {0};
    qgdw12184_frame_get_fragment_ack_ackdata(data,data_len,&ackdata);
    return ackdata.pseq;
}

uint8_t qgdw12184_frame_get_fragment_ack_ackdata_priority(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_ack_ackdata_t ackdata= {0};
    qgdw12184_frame_get_fragment_ack_ackdata(data,data_len,&ackdata);
    return ackdata.priority;
}

uint8_t qgdw12184_frame_get_fragment_ack_ackdata_sseq(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_ack_ackdata_t ackdata= {0};
    qgdw12184_frame_get_fragment_ack_ackdata(data,data_len,&ackdata);
    return ackdata.sseq;
}

uint8_t qgdw12184_frame_get_fragment_ack_ackdata_ack(uint8_t * data,size_t data_len)
{
    qgdw12184_frame_fragment_ack_ackdata_t ackdata= {0};
    qgdw12184_frame_get_fragment_ack_ackdata(data,data_len,&ackdata);
    return ackdata.ack;
}

void qgdw12184_frame_fragment_ack_no_fragment_parse(uint8_t *frame,size_t frame_len,qgdw12184_frame_fragment_ack_ackdata_callback_t on_ack_data,void *usr)
{
    if(frame==NULL || frame_len < 11 || on_ack_data==NULL)
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
    if(packet_header.packet_type==QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK)
    {
        qgdw12184_frame_fragment_ack_ackdata_t ackdata= {0};
        qgdw12184_frame_get_fragment_ack_ackdata(&frame[7],2,&ackdata);
        on_ack_data(usr,&sensor_id,&packet_header,&ackdata);
    }
}
