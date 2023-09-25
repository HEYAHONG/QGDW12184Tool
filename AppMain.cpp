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
#include "libserialport.h"
#include <wx/regex.h>

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
                case QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA:
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
                                    }
                                }

                            }

                        };
                        qgdw12184_frame_monitor_no_fragment_parse((uint8_t*)frame_bin.c_str(),frame_bin.length(),on_monitor,this);
                    }
                }
                break;
                case QGDW12184_PACKET_HEADER_PACKET_TYPE_MONITOR_DATA_RESP:
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
    wxRegEx reFrame(_T("([0-9a-fA-F]{2}){6,}"));
    if(reFrame.IsValid())
    {
        if(reFrame.Matches(input_str))
        {
            size_t str_count=reFrame.GetMatchCount();
            for(size_t i=0; i<str_count; i++)
            {
                wxString temp=reFrame.GetMatch(input_str,i);
                if(temp.Length()<12)
                {
                    continue;
                }
                ret.push_back(temp);
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
