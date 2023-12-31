/***************************************************************
 * Name:      AppMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2023-09-20
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "AppMain.h"
#include "Version.h"
#include "qgdw12184_crc.h"
#include "qgdw12184_frame.h"
#include "qgdw12184_fragment.h"
#include "libserialport.h"
#include <wx/regex.h>
#include "inttypes.h"

AppDialog::AppDialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
    InitAboutTextCtrl(m_textCtrl_about);
}

AppDialog::~AppDialog()
{

}

void AppDialog::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void AppDialog::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void AppDialog::OnAbout(wxCommandEvent &event)
{

}

void AppDialog::OnButtonClickClearFrameParseLog( wxCommandEvent& event )
{
    ClearFrameParseLog();
}

void AppDialog::OnButtonClickGetFrameParseHEX( wxCommandEvent& event )
{
    wxArrayString strlist=GetFrameParseInputHex();
    for(size_t i=0; i<strlist.size(); i++)
    {
        AppendFrameParseLog(wxString(_T("已找到数据帧(Hex):\n"))+strlist[i]+_T("\n"));
        std::string frame_bin=HexToBin(strlist[i].ToStdString());
        if(qgdw12184_crc_check((uint8_t*)frame_bin.c_str(),frame_bin.length()))
        {

            {
                //传感器ID
                qgdw12184_frame_sensor_id_t sensor_id;
                qgdw12184_frame_get_sensor_id((uint8_t*)frame_bin.c_str(),frame_bin.length(),&sensor_id);
                char buff[1024]= {0};
                sprintf(buff,"ManufacturerID=%04X(%d),VersionLetter=%02X(%d=%c),VersionNumber=%02X(%d),SerialNumber=%08X(%d)\n",(int)sensor_id.manufacturer_id,(int)sensor_id.manufacturer_id,(int)sensor_id.version_letter,(int)sensor_id.version_letter,'a'+sensor_id.version_letter-1,(int)sensor_id.version_number,(int)sensor_id.version_number,(int)sensor_id.serial_number,(int)sensor_id.serial_number);
                AppendFrameParseLog(buff);
            }

            {
                //数据包头
                qgdw12184_frame_packet_header_t packet_header;
                qgdw12184_frame_get_packet_header((uint8_t*)frame_bin.c_str(),frame_bin.length(),&packet_header);
                {

                    char buff[1024]= {0};
                    sprintf(buff,"DataLen=%d,FragInd=%d(%s),PacketType=%d(%s)\n",packet_header.data_len,packet_header.frag_ind,qgdw12184_frame_packet_header_frag_ind_str(static_cast<qgdw12184_frame_packet_header_frag_ind_t>(packet_header.frag_ind)),packet_header.packet_type,qgdw12184_frame_packet_header_packet_type_str(static_cast<qgdw12184_frame_packet_header_packet_type_t>(packet_header.packet_type)));
                    AppendFrameParseLog(buff);
                }
                switch(static_cast<qgdw12184_frame_packet_header_packet_type_t>(packet_header.packet_type))
                {
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_monitor=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,size_t index,const qgdw12184_frame_data_header_t *data_header,const uint8_t *data_content,size_t data_content_length)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL)
                            {
                                {
                                    char buff[1024];
                                    sprintf(buff,"Data Index=%d,Data Type=%04X(%d),Data Length=%d,Data:\n",(int)index,(int)data_header->data_type,(int)data_header->data_type,(int)data_content_length);
                                    dlg->AppendFrameParseLog(buff);
                                }

                                {
                                    if(data_content!=NULL && data_content_length!=0)
                                    {
                                        std::string data((char *)data_content,data_content_length);
                                        dlg->AppendFrameParseLog(_T("\t"));
                                        dlg->AppendFrameParseLog(dlg->BinToHex(data));
                                        dlg->AppendFrameParseLog(_T("\n"));
                                        if(data_content_length==4)
                                        {
                                            //四字节数据(可能是浮点数)
                                            uint32_t data;
                                            data=data_content[3];
                                            data<<=8;
                                            data+=data_content[2];
                                            data<<=8;
                                            data+=data_content[1];
                                            data<<=8;
                                            data+=data_content[0];
                                            dlg->AppendFrameParseLog(wxString::Format(_T("\tuint32_t:%" PRIu32 ",int32_t:%" PRId32 ",float:%f\n"),data,*(int32_t*)&data,*(float*)&data));
                                        }
                                    }
                                }

                            }

                        };
                        qgdw12184_frame_monitor_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_monitor,this);
                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_monitor_resp=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_monitor_resp_status_t status)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL)
                            {
                                switch(status)
                                {
                                case QGDW12184_FRAME_MONITOR_RESP_STATUS_FAILURE:
                                {
                                    dlg->AppendFrameParseLog(_T("Status=Failure\n"));
                                }
                                break;
                                case QGDW12184_FRAME_MONITOR_RESP_STATUS_SUCCESS:
                                {
                                    dlg->AppendFrameParseLog(_T("Status=Success\n"));
                                }
                                break;
                                }
                            }

                        };
                        qgdw12184_frame_monitor_resp_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_monitor_resp,this);
                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_alarm=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,size_t index,const qgdw12184_frame_data_header_t *data_header,const uint8_t *data_content,size_t data_content_length)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL)
                            {
                                {
                                    char buff[1024];
                                    sprintf(buff,"Data Index=%d,Data Type=%04X(%d),Data Length=%d,Data:\n",(int)index,(int)data_header->data_type,(int)data_header->data_type,(int)data_content_length);
                                    dlg->AppendFrameParseLog(buff);
                                }

                                {
                                    if(data_content!=NULL && data_content_length!=0)
                                    {
                                        std::string data((char *)data_content,data_content_length);
                                        dlg->AppendFrameParseLog(_T("\t"));
                                        dlg->AppendFrameParseLog(dlg->BinToHex(data));
                                        dlg->AppendFrameParseLog(_T("\n"));
                                        if(data_content_length==4)
                                        {
                                            //四字节数据(可能是浮点数)
                                            uint32_t data;
                                            data=data_content[3];
                                            data<<=8;
                                            data+=data_content[2];
                                            data<<=8;
                                            data+=data_content[1];
                                            data<<=8;
                                            data+=data_content[0];
                                            dlg->AppendFrameParseLog(wxString::Format(_T("\tuint32_t:%" PRIu32 ",int32_t:%" PRId32 ",float:%f\n"),data,*(int32_t*)&data,*(float*)&data));
                                        }
                                    }
                                }

                            }

                        };
                        qgdw12184_frame_alarm_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_alarm,this);
                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_ALARM_DATA_RESP:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_alarm_resp=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_alarm_resp_status_t status)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL)
                            {
                                switch(status)
                                {
                                case QGDW12184_FRAME_ALARM_RESP_STATUS_FAILURE:
                                {
                                    dlg->AppendFrameParseLog(_T("Status=Failure\n"));
                                }
                                break;
                                case QGDW12184_FRAME_ALARM_RESP_STATUS_SUCCESS:
                                {
                                    dlg->AppendFrameParseLog(_T("Status=Success\n"));
                                }
                                break;
                                }
                            }

                        };
                        qgdw12184_frame_alarm_resp_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_alarm_resp,this);
                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_data_content=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,uint8_t *data,size_t data_len)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL && data!=NULL && data_len > 0)
                            {
                                dlg->AppendFrameParseLog(wxString(_T("Data Content:\n"))+dlg->BinToHex(std::string((const char *)data,data_len))+"\n");
                                qgdw12184_frame_control_header_t control_header= {0};
                                qgdw12184_frame_get_control_header(data,data_len,&control_header);
                                dlg->AppendFrameParseLog(wxString(_T("CtrlType="))+std::to_string(control_header.ctrl_type)+"("+qgdw12184_frame_control_header_ctrl_type_str(static_cast<uint8_t>(control_header.ctrl_type))+")"+",RequestSetFlag="+std::to_string(control_header.request_set_flag)+"("+qgdw12184_frame_control_header_request_set_flag_str(static_cast<qgdw12184_frame_control_header_request_set_flag_t>(control_header.request_set_flag))+")"+"\n");
                            }
                        };
                        qgdw12184_frame_control_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_data_content,this);


                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_CONTROL_RESP:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_data_content=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,uint8_t *data,size_t data_len)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL && data!=NULL && data_len > 0)
                            {
                                dlg->AppendFrameParseLog(wxString(_T("Data Content:\n"))+dlg->BinToHex(std::string((const char *)data,data_len))+"\n");
                                qgdw12184_frame_control_header_t control_header= {0};
                                qgdw12184_frame_get_control_header(data,data_len,&control_header);
                                dlg->AppendFrameParseLog(wxString(_T("CtrlType="))+std::to_string(control_header.ctrl_type)+"("+qgdw12184_frame_control_header_ctrl_type_str(static_cast<uint8_t>(control_header.ctrl_type))+")"+",RequestSetFlag="+std::to_string(control_header.request_set_flag)+"("+qgdw12184_frame_control_header_request_set_flag_str(static_cast<qgdw12184_frame_control_header_request_set_flag_t>(control_header.request_set_flag))+")"+"\n");
                            }

                        };
                        qgdw12184_frame_control_resp_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_data_content,this);
                    }
                }
                break;
                case QGDW12184_FRAME_PACKET_HEADER_PACKET_TYPE_FRAGMENT_ACK:
                {
                    //本程序只支持非分片
                    if(packet_header.frag_ind==0)
                    {
                        auto on_ackdata=[](void *usr,const qgdw12184_frame_sensor_id_t *sensor_id,const qgdw12184_frame_packet_header_t *packet_header,qgdw12184_frame_fragment_ack_ackdata_t *ackdata)
                        {
                            AppDialog *dlg=(AppDialog*)usr;
                            if(dlg!=NULL)
                            {
                                char buff[2048]= {0};
                                sprintf(buff,"Ack=%d(%s),SSEQ=%d,Priority=%d(%s),PSEQ=%d\n",(int)ackdata->ack,qgdw12184_frame_fragment_ack_ackdata_ack_str((qgdw12184_frame_fragment_ack_ackdata_ack_t)ackdata->ack),(int)ackdata->sseq,(int)ackdata->priority,qgdw12184_frame_fragment_ack_ackdata_priority_str((qgdw12184_frame_fragment_ack_ackdata_priority_t)ackdata->priority),(int)ackdata->pseq);
                                dlg->AppendFrameParseLog(buff);
                            }

                        };
                        qgdw12184_frame_fragment_ack_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_ackdata,this);
                    }
                }
                break;
                default:
                {

                }
                break;
                }

            }



        }
    }
}

void AppDialog::OnButtonClickCheckFrameParseCRC( wxCommandEvent& event )
{
    wxArrayString strlist=GetFrameParseInputHex();
    for(size_t i=0; i<strlist.size(); i++)
    {
        AppendFrameParseLog(wxString(_T("数据帧(Hex):\n"))+strlist[i]+_T("\n"));
        std::string frame_bin=HexToBin(strlist[i].ToStdString());
        if(qgdw12184_crc_check((uint8_t*)frame_bin.c_str(),frame_bin.length()))
        {
            AppendFrameParseLog(wxString(_T("CRC校验正确!\n")));
        }
        else
        {
            AppendFrameParseLog(wxString(_T("CRC校验错误!")));
            //修正CRC
            qgdw12184_crc_append((uint8_t*)frame_bin.c_str(),frame_bin.length());
            AppendFrameParseLog(wxString(_T(" 修正CRC后数据帧:\n"))+BinToHex(frame_bin)+_T("\n"));

        }
    }
}

void AppDialog::OnButtonClickFragmentDoFragment( wxCommandEvent& event )
{
    int fragsize=0;
    int sseq=0;
    int priority=0;
    fragsize=atoi(m_textCtrl_fragment_fragsize->GetValue().ToStdString().c_str());
    sseq=atoi(m_textCtrl_fragment_sseq->GetValue().ToStdString().c_str());
    priority=m_choice_fragment_priority->GetSelection();
    if(fragsize<=0 || fragsize >(1400-9-4))
    {
        fragsize=(1400-9-4);
        AppendFrameParseLog(_T("分片大小非法，将设置为1387\n"));
    }
    if(sseq <= 0 || sseq > 63)
    {
        sseq=1;
        AppendFrameParseLog(_T("SSEQ非法，将设置为1\n"));
    }
    if(priority < 0 )
    {
        priority=0;
        AppendFrameParseLog(_T("优先级非法，将设置为0\n"));
    }
    AppendFrameParseLog(wxString::Format(_T("FragSize=%d,SSEQ=%d,Priority=%d\n"),fragsize,sseq,priority));
    wxArrayString strlist=GetFrameParseInputHex();
    for(size_t i=0; i<strlist.size(); i++)
    {
        AppendFrameParseLog(wxString(_T("已找到数据帧(Hex):\n"))+strlist[i]+_T("\n"));
        std::string frame_bin=HexToBin(strlist[i].ToStdString());
        if(qgdw12184_crc_check((uint8_t*)frame_bin.c_str(),frame_bin.length()))
        {
            if(1==qgdw12184_frame_get_packet_header_frag_ind((uint8_t*)frame_bin.c_str(),frame_bin.length()))
            {
                AppendFrameParseLog(_T("数据帧已分片!\n"));
                continue;
            }
            qgdw12184_fragment_fragment_info_t *info=qgdw12184_fragment_fragment_info_new();
            if(info==NULL)
            {
                AppendFrameParseLog(_T("内部错误!\n"));
                continue;
            }

            qgdw12184_fragment_fragment_set_frame(info,(uint8_t*)frame_bin.c_str(),frame_bin.length(),sseq);

            if(qgdw12184_fragment_can_fragment(info,fragsize))
            {
                auto on_fragment=[](void *usr,uint8_t pseq,uint8_t *frame,size_t frame_len)
                {
                    AppDialog *dlg=(AppDialog*)usr;
                    if(dlg!=NULL)
                    {
                        dlg->AppendFrameParseLog(wxString::Format(_T("数据帧(含PDU%d):\n%s\n"),(int)pseq,dlg->BinToHex(std::string((char *)frame,frame_len)).c_str()));
                    }
                };
                qgdw12184_fragment_do_fragment(info,fragsize,priority,on_fragment,this);
                AppendFrameParseLog(_T("数据帧分片完成!\n"));
            }
            else
            {
                AppendFrameParseLog(_T("数据帧无需分片!\n"));
            }

            qgdw12184_fragment_fragment_info_delete(info);

        }
    }
}

void AppDialog::OnButtonClickFragmentDoDefragment( wxCommandEvent& event )
{
    AppendFrameParseLog(_T("重组需要某一数据帧的所有分片，且需要可显示的非HEX字符（如-）作为分片的间隔!\n"));
    wxArrayString strlist=GetFrameParseInputHex();
    if(strlist.size() == 0)
    {
        return;
    }
    if(strlist.size() < 2)
    {
        AppendFrameParseLog(_T("单个数据帧不可重组!\n"));
        return;
    }
    qgdw12184_fragment_defragment_info_t *info=qgdw12184_fragment_defragment_info_new();
    if(info==NULL)
    {
        AppendFrameParseLog(_T("内部错误!\n"));
        return;
    }
    for(size_t i=0; i<strlist.size(); i++)
    {
        AppendFrameParseLog(wxString(_T("已找到数据帧(Hex):\n"))+strlist[i]+_T("\n"));
        std::string frame_bin=HexToBin(strlist[i].ToStdString());
        if(qgdw12184_crc_check((uint8_t*)frame_bin.c_str(),frame_bin.length()))
        {
            if(0==qgdw12184_frame_get_packet_header_frag_ind((uint8_t*)frame_bin.c_str(),frame_bin.length()))
            {
                AppendFrameParseLog(_T("数据帧未分片!\n"));
                continue;
            }

            qgdw12184_fragment_defragment_add_frame(info,(uint8_t*)frame_bin.c_str(),frame_bin.length());
            AppendFrameParseLog(_T("数据帧已添加!\n"));
        }
    }


    if(qgdw12184_fragment_can_defragment(info))
    {
        auto on_defragment=[](void *usr,uint8_t sseq,uint8_t *frame,size_t frame_len)
        {
            AppDialog *dlg=(AppDialog*)usr;
            if(dlg!=NULL)
            {
                dlg->AppendFrameParseLog(wxString::Format(_T("数据帧(含SDU（%d）):\n%s\n"),(int)sseq,dlg->BinToHex(std::string((char *)frame,frame_len)).c_str()));
            }
        };
        qgdw12184_fragment_do_defragment(info,on_defragment,this);
    }
    else
    {
        AppendFrameParseLog(_T("分片不够，不可重组!\n"));
    }


    qgdw12184_fragment_defragment_info_delete(info);

}

//初始化关于文本框
void AppDialog::InitAboutTextCtrl(wxTextCtrl* m_ctrl)
{
    if(m_ctrl==NULL)
    {
        return;
    }

    {
        //输出版本号
        m_ctrl->AppendText(_T("QGDW12184Tool BY HYH"));
        m_ctrl->AppendText(_T("\n"));
        m_ctrl->AppendText(wxString(_T("程序版本号:\t"))+PROJECT_VERSION_STR);
        m_ctrl->AppendText(_T("\n"));
    }

    {
        //libserialport版本号
        m_ctrl->AppendText(_T("\n"));
        m_ctrl->AppendText(wxString(_T("libserialport:\t"))+sp_get_lib_version_string());
        m_ctrl->AppendText(_T("\n"));

    }

    {
        //许可证信息
        m_ctrl->AppendText(_T("\n"));
        m_ctrl->AppendText(_T("许可证:"));
        m_ctrl->AppendText(_T("\n"));
        const char *license=(const char *)wxRCGetHandle("LICENSE");
        if(license!=NULL)
        {
            m_ctrl->AppendText(wxString::FromUTF8(license));
        }
    }
}

void AppDialog::ClearFrameParseLog()
{
    m_textCtrl_frame_parse_log->Clear();
}

void AppDialog::AppendFrameParseLog(wxString log_text)
{
    m_textCtrl_frame_parse_log->AppendText(log_text);
}

wxString AppDialog::GetFrameParseInput()
{
    return m_textCtrl_frame_parse_input->GetValue();
}

wxArrayString AppDialog::GetFrameParseInputHex(wxString input)
{
    wxArrayString ret;
    wxString input_str;
    if(input.IsEmpty())
    {
        input_str=GetFrameParseInput();
    }
    else
    {
        input_str=input;
    }
    //去除空格
    input_str.Replace(_T(" "),_T(""));
    //去除回车换行符
    input_str.Replace(_T("\r"),_T(""));
    input_str.Replace(_T("\n"),_T(""));

    wxRegEx reFrame(_T("([0-9a-fA-F]{2}){6,}"));
    if(reFrame.IsValid())
    {
        while(reFrame.Matches(input_str))
        {
            {
                size_t start=0;
                size_t len=0;
                if(reFrame.GetMatch(&start,&len))
                {
                    wxString temp=input_str.substr(start,len);
                    if(temp.Length()>=12)
                    {
                        ret.push_back(temp);
                    }
                    input_str=input_str.substr(start+len);
                }
                else
                {
                    break;
                }
            }
        }
    }
    return ret;
}

std::string AppDialog::HexToBin(std::string hex)
{
    if(hex.length()<2)
    {
        return std::string();
    }
    uint8_t buff[hex.length()]= {0};
    size_t bin_count=0;
    for(size_t i=0; i<hex.length()/2; i++)
    {
        bin_count++;
        try
        {
            buff[i]=std::stoul(hex.substr(i*2,2),0,16);
        }
        catch(...)
        {
            break;
        }
    }
    return std::string((char *)buff,bin_count);
}

std::string  AppDialog::BinToHex(std::string bin)
{
    std::string ret;
    for(size_t i=0; i<bin.length(); i++)
    {
        uint8_t *bin_start=(uint8_t *)bin.c_str();
        char buff[32]= {0};
        sprintf(buff,"%02X",(int)bin_start[i]);
        ret+=buff;
    }
    return ret;
}
