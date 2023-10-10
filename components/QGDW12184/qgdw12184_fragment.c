#include "qgdw12184_fragment.h"
#include "string.h"

struct qgdw12184_fragment_fragment_info
{
    qgdw12184_frame_sensor_id_t sensor_id;/**< 传感器id */
    qgdw12184_frame_packet_header_t packet_header; /**< 包头 */
    struct
    {
        uint8_t * data;/**< SDU数据指针 */
        size_t len;/**<  SDU数据指针长度 */
        uint8_t sseq;/**< 业务数据单元序号,从1开始连续取值 */
    } SDU;
} ;

qgdw12184_fragment_fragment_info_t *qgdw12184_fragment_fragment_info_new()
{
    qgdw12184_fragment_fragment_info_t * ret=NULL;
    ret=(qgdw12184_fragment_fragment_info_t *)qgdw12184_sysapi_malloc(sizeof(qgdw12184_fragment_fragment_info_t));
    if(ret!=NULL)
    {
        memset(ret,0,sizeof(qgdw12184_fragment_fragment_info_t));
        ret->SDU.data=NULL;
    }
    return ret;
}

void qgdw12184_fragment_fragment_info_delete(qgdw12184_fragment_fragment_info_t *info)
{
    if(info!=NULL)
    {
        if(info->SDU.data!=NULL)
        {
            qgdw12184_sysapi_free(info->SDU.data);
        }
        qgdw12184_sysapi_free(info);
    }
}

bool qgdw12184_fragment_fragment_set_frame(qgdw12184_fragment_fragment_info_t *info,uint8_t *frame,size_t frame_len,uint8_t sseq)
{
    bool ret=false;
    if(frame==NULL || frame_len < 9 || info==NULL)
    {
        return ret;
    }


    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return ret;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==1)
    {
        //分片报文不处理
        return ret;
    }

    ret=true;

    info->sensor_id=sensor_id;
    info->packet_header=packet_header;

    //删除之前的SDU数据
    if(info->SDU.data!=NULL)
    {
        qgdw12184_sysapi_free(info->SDU.data);
    }
    info->SDU.len=frame_len-9;
    if(info->SDU.len==0)
    {
        info->SDU.data=NULL;
    }
    else
    {
        info->SDU.data=(uint8_t*)qgdw12184_sysapi_malloc(info->SDU.len);
        if(info->SDU.data!=NULL)
        {
            memcpy(info->SDU.data,&frame[7],info->SDU.len);
        }
        else
        {
            ret=false;
            info->SDU.len=0;
        }
    }
    info->SDU.sseq=sseq;

    return ret;
}

bool qgdw12184_fragment_can_fragment(qgdw12184_fragment_fragment_info_t *info,size_t frag_len)
{
    bool ret=false;
    if(info==NULL || frag_len == 0 || info->SDU.data==NULL)
    {
        return ret;
    }

    if(frag_len >= (1400 - 9))
    {
        frag_len = (1400-9);
    }

    //判断分片大小与SDU大小
    if(frag_len < info->SDU.len)
    {
        ret=true;
    }
    else
    {
        ret=false;
    }

    return ret;
}

bool qgdw12184_fragment_do_fragment(qgdw12184_fragment_fragment_info_t *info,size_t frag_len,uint8_t priority,qgdw12184_fragment_fragment_callback_t on_fragment,void *usr)
{
    if(on_fragment==NULL)
    {
        return false;
    }
    if(!qgdw12184_fragment_can_fragment(info,frag_len))
    {
        return false;
    }
    if(frag_len >= (1400 - 9))
    {
        frag_len = (1400-9);
    }
    bool ret=true;
    qgdw12184_frame_sensor_id_t sensor_id=info->sensor_id;
    qgdw12184_frame_packet_header_t packet_header=info->packet_header;
    //启用分片
    packet_header.frag_ind=1;
    //剩余SDU大小
    size_t SDU_Remain_len=info->SDU.len;
    //PSEQ
    uint8_t pseq=1;
    while(SDU_Remain_len > 0)
    {
        //本次分片的数据大小
        uint16_t data_len=frag_len;
        if(data_len > SDU_Remain_len)
        {
            data_len=SDU_Remain_len;
        }

        size_t frame_len=7+4+data_len+2;
        uint8_t *frame=(uint8_t*)qgdw12184_sysapi_malloc(frame_len);
        if(frame==NULL)
        {
            ret=false;
            break;
        }
        qgdw12184_frame_set_sensor_id(frame,frame_len,&sensor_id);
        qgdw12184_frame_set_packet_header(frame,frame_len,&packet_header);
        uint8_t *data=&frame[7];
        qgdw12184_frame_fragment_header_t fragment_header={0};
        fragment_header.sseq=info->SDU.sseq;
        if(priority!=0)
        {
            fragment_header.priority=1;
        }
        else
        {
            fragment_header.priority=0;
        }
        {
            fragment_header.flag=QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_NEXT;
            if(SDU_Remain_len==info->SDU.len)
            {
                fragment_header.flag=QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_START;
            }
            if(SDU_Remain_len==data_len)
            {
                fragment_header.flag=QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_STOP;
            }
        }
        fragment_header.pseq=pseq;
        qgdw12184_frame_set_fragment_header(data,data_len,&fragment_header);

        //设置分片数据长度
        data[2]=data_len&0xFF;
        data[3]=(data_len>>8)&0xFF;

        //设置分片数据
        memcpy(&data[4],&info->SDU.data[info->SDU.len-SDU_Remain_len],data_len);

        //添加校验
        qgdw12184_crc_append(frame,frame_len);

        //调用回调
        on_fragment(usr,pseq,frame,frame_len);

        //释放数据帧
        qgdw12184_sysapi_free(frame);

        //减少已经分片的内容
        SDU_Remain_len-=data_len;
        //检查pseq
        if(pseq==127 && SDU_Remain_len > 0)
        {
            //pseq只有7位，最大值127
            ret=false;
            break;
        }
        pseq++;
    }

    return ret;
}
