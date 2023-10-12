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

    if(frag_len >= (1400 - 9-4))
    {
        frag_len = (1400-9-4);
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
    if(frag_len >= (1400 - 9-4))
    {
        frag_len = (1400-9-4);
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
        qgdw12184_frame_fragment_header_t fragment_header= {0};
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

typedef struct qgdw12184_fragment_pdu_list
{
    struct qgdw12184_fragment_pdu_list *next;
    qgdw12184_frame_fragment_header_t fragment_header;
    uint16_t pdu_data_len;
    uint8_t * pdu_data;

} qgdw12184_fragment_pdu_list_t;

struct qgdw12184_fragment_defragment_info
{
    qgdw12184_frame_sensor_id_t sensor_id;/**< 传感器id */
    qgdw12184_frame_packet_header_t packet_header; /**< 包头 */
    qgdw12184_fragment_pdu_list_t *list;/**< pdu列表 */
};

qgdw12184_fragment_defragment_info_t *qgdw12184_fragment_defragment_info_new()
{
    qgdw12184_fragment_defragment_info_t *ret=(qgdw12184_fragment_defragment_info_t *)qgdw12184_sysapi_malloc(sizeof(qgdw12184_fragment_defragment_info_t));

    if(ret!=NULL)
    {
        memset(ret,0,sizeof(qgdw12184_fragment_defragment_info_t));
        ret->list=NULL;
    }

    return ret;
}

void qgdw12184_fragment_defragment_info_delete(qgdw12184_fragment_defragment_info_t* info)
{
    if(info!=NULL)
    {
        qgdw12184_fragment_pdu_list_t *list=info->list;
        while(list!=NULL)
        {
            qgdw12184_fragment_pdu_list_t * next_list=list->next;
            if(list->pdu_data!=NULL)
            {
                qgdw12184_sysapi_free(list->pdu_data);
            }
            qgdw12184_sysapi_free(list);
            list=next_list;
        }
        qgdw12184_sysapi_free(info);
    }
}

bool qgdw12184_fragment_defragment_add_frame(qgdw12184_fragment_defragment_info_t* info,uint8_t *frame,size_t frame_len)
{
    if(info==NULL || frame == NULL || frame_len < 7+4+2)
    {
        return false;
    }

    bool ret=false;
    if(!qgdw12184_crc_check(frame,frame_len))
    {
        return ret;
    }

    qgdw12184_frame_sensor_id_t sensor_id;
    qgdw12184_frame_get_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_packet_header_t packet_header;
    qgdw12184_frame_get_packet_header(frame,frame_len,&packet_header);
    if(packet_header.frag_ind==0)
    {
        //未分片报文不处理
        return ret;
    }

    if(info->list==NULL)
    {
        //第一次添加
        info->sensor_id=sensor_id;
        info->packet_header=packet_header;
        uint8_t *data=&frame[7];
        size_t data_len=frame_len-(7+2);
        if(data_len < 5)
        {
            //至少需要分片头、分片长度及1字节分片数据
            return ret;
        }
        qgdw12184_frame_fragment_header_t fragment_header;
        qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);

        qgdw12184_fragment_pdu_list_t *new_pdu=(qgdw12184_fragment_pdu_list_t*)qgdw12184_sysapi_malloc(sizeof(qgdw12184_fragment_pdu_list_t));
        if(new_pdu==NULL)
        {
            return ret;
        }
        new_pdu->next=NULL;
        new_pdu->fragment_header=fragment_header;
        new_pdu->pdu_data_len=data[3];
        new_pdu->pdu_data_len<<=8;
        new_pdu->pdu_data_len+=data[2];
        if(new_pdu->pdu_data_len==0 || new_pdu->pdu_data_len < (frame_len-7-4-2))
        {
            qgdw12184_sysapi_free(new_pdu);
            return ret;
        }
        new_pdu->pdu_data=(uint8_t *)qgdw12184_sysapi_malloc(new_pdu->pdu_data_len);
        if(new_pdu->pdu_data==NULL)
        {
            qgdw12184_sysapi_free(new_pdu);
            return ret;
        }
        //复制分片数据
        memcpy(new_pdu->pdu_data,&frame[7+4],new_pdu->pdu_data_len);

        info->list=new_pdu;

    }
    else
    {
        //后续添加

        uint8_t *data=&frame[7];
        size_t data_len=frame_len-(7+2);
        if(data_len < 5)
        {
            //至少需要分片头、分片长度及1字节分片数据
            return ret;
        }
        qgdw12184_frame_fragment_header_t fragment_header;
        qgdw12184_frame_get_fragment_header(data,data_len,&fragment_header);

        if(sensor_id.manufacturer_id != info->sensor_id.manufacturer_id || sensor_id.version_and_serialnumber != info->sensor_id.version_and_serialnumber)
        {
            //不同传感器不予处理
            return ret;
        }

        if(packet_header.packet_header != info->packet_header.packet_header)
        {
            //不同包头不予处理
            return ret;
        }

        if(fragment_header.sseq != info->list->fragment_header.sseq)
        {
            //不同sseq不予处理
            return ret;
        }

        qgdw12184_fragment_pdu_list_t *new_pdu=(qgdw12184_fragment_pdu_list_t*)qgdw12184_sysapi_malloc(sizeof(qgdw12184_fragment_pdu_list_t));
        if(new_pdu==NULL)
        {
            return ret;
        }
        new_pdu->next=NULL;
        new_pdu->fragment_header=fragment_header;
        new_pdu->pdu_data_len=data[3];
        new_pdu->pdu_data_len<<=8;
        new_pdu->pdu_data_len+=data[2];
        if(new_pdu->pdu_data_len==0 || new_pdu->pdu_data_len < (frame_len-7-4-2))
        {
            qgdw12184_sysapi_free(new_pdu);
            return ret;
        }
        new_pdu->pdu_data=(uint8_t *)qgdw12184_sysapi_malloc(new_pdu->pdu_data_len);
        if(new_pdu->pdu_data==NULL)
        {
            qgdw12184_sysapi_free(new_pdu);
            return ret;
        }
        //复制分片数据
        memcpy(new_pdu->pdu_data,&frame[7+4],new_pdu->pdu_data_len);

        {
            //将pseq大的放在末尾
            qgdw12184_fragment_pdu_list_t *list_current=info->list;
            if(list_current->fragment_header.pseq > new_pdu->fragment_header.pseq)
            {
                //头的pseq大于新pdu的pseq，新pdu作为头
                new_pdu->next=list_current;
                info->list=new_pdu;
                ret=true;
                return ret;
            }

            if(list_current->fragment_header.pseq == new_pdu->fragment_header.pseq)
            {
                //丢弃相同pseq
                qgdw12184_sysapi_free(new_pdu->pdu_data);
                qgdw12184_sysapi_free(new_pdu);
                return ret;
            }

            while(list_current!=NULL)
            {
                if(list_current->fragment_header.pseq == new_pdu->fragment_header.pseq)
                {
                    //丢弃相同pseq
                    qgdw12184_sysapi_free(new_pdu->pdu_data);
                    qgdw12184_sysapi_free(new_pdu);
                    break;
                }
                if(list_current->next==NULL)
                {
                    if(list_current->fragment_header.pseq < new_pdu->fragment_header.pseq)
                    {
                        //插入末尾
                        list_current->next=new_pdu;
                        ret=true;
                    }
                    else
                    {
                        qgdw12184_sysapi_free(new_pdu->pdu_data);
                        qgdw12184_sysapi_free(new_pdu);
                    }
                    break;
                }
                else
                {
                    if(list_current->fragment_header.pseq < new_pdu->fragment_header.pseq && list_current->next->fragment_header.pseq > new_pdu->fragment_header.pseq )
                    {
                        //插入中间
                        new_pdu->next=list_current->next;
                        list_current->next=new_pdu;
                        break;
                    }

                }
                list_current=list_current->next;
            }
        }

    }

    return ret;
}

bool qgdw12184_fragment_can_defragment(qgdw12184_fragment_defragment_info_t *info)
{
    bool ret=false;
    if(info==NULL || info->list==NULL)
    {
        return ret;
    }
    qgdw12184_fragment_pdu_list_t *list_current=info->list;

    if(list_current->fragment_header.pseq!=1)
    {
        //pseq起始不为1
        return ret;
    }
    while(list_current!=NULL)
    {
        if(list_current->next==NULL)
        {
            if(list_current->fragment_header.flag!=QGDW12184_FRAME_FRAGMENT_HEADER_FLAG_FRAG_STOP)
            {
                //未结束
                break;
            }
            else
            {
                ret=true;
                break;
            }
        }
        else
        {
            if(list_current->fragment_header.pseq != (list_current->next->fragment_header.pseq-1))
            {
                //pseq不连续
                break;
            }
        }
        list_current=list_current->next;
    }
    return ret;
}

bool qgdw12184_fragment_do_defragment(qgdw12184_fragment_defragment_info_t *info,qgdw12184_fragment_defragment_callback_t on_defragment,void *usr)
{
    bool ret=false;
    if(on_defragment==NULL)
    {
        return ret;
    }

    if(!qgdw12184_fragment_can_defragment(info))
    {
        return ret;
    }

    size_t sdu_len=0;

    //统计sdu大小
    qgdw12184_fragment_pdu_list_t *list_current=info->list;
    while(list_current!=NULL)
    {
        sdu_len+=list_current->pdu_data_len;
        list_current=list_current->next;
    }
    list_current=info->list;


    size_t frame_len=sdu_len+9;
    uint8_t *frame=(uint8_t *)qgdw12184_sysapi_malloc(frame_len);
    if(frame==NULL)
    {
        return ret;
    }

    ret=true;

    qgdw12184_frame_sensor_id_t sensor_id=info->sensor_id;
    qgdw12184_frame_packet_header_t packet_header=info->packet_header;
    //关闭分片
    packet_header.frag_ind=0;

    qgdw12184_frame_set_sensor_id(frame,frame_len,&sensor_id);
    qgdw12184_frame_set_packet_header(frame,frame_len,&packet_header);

    //复制pdu到帧
    uint8_t *data=&frame[7];
    size_t data_len=0;
    while(list_current!=NULL)
    {
        memcpy(&data[data_len],list_current->pdu_data,list_current->pdu_data_len);
        data_len+=list_current->pdu_data_len;
        list_current=list_current->next;
    }
    list_current=info->list;

    qgdw12184_crc_append(frame,frame_len);

    on_defragment(usr,list_current->fragment_header.sseq,frame,frame_len);

    qgdw12184_sysapi_free(frame);

    return ret;
}
