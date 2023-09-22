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
    case QGDW12184_PACKET_HEADER_FRAG_IND_NO_FRAGMENT:
        return "No Fragment";
    default:
        return "Fragment";
    }
}

const char *qgdw12184_frame_packet_header_packet_type_str(qgdw12184_frame_packet_header_packet_type_t packet_type)
{
    switch(packet_type)
    {
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA:
        return "Monitor Data";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP:
        return "Monitor Data Resp";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_ALARM_DATA:
        return "Alarm Data";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP:
        return "Alarm Data Resp";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_CONTROL:
        return "Control";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP:
        return "Control Resp";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK:
        return "Fragment Ack";
    case QGDW12184_PACKET_HEADER_PACKET_TYPE_RESERVED:
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
