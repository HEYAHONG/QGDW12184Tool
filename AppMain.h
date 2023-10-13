/***************************************************************
 * Name:      AppMain.h
 * Purpose:   Defines Application Frame
 * Author:    HYH (2229388563@qq.com)
 * Created:   2023-09-20
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifndef APPMAIN_H
#define APPMAIN_H



#include "AppApp.h"
#include "wx/string.h"
#include "wx/arrstr.h"
#include "GUIDialog.h"
#include <string>

class AppDialog: public GUIDialog
{
public:
    AppDialog(wxDialog *dlg);
    ~AppDialog();
private:
    virtual void OnClose(wxCloseEvent& event);
    virtual void OnQuit(wxCommandEvent& event);
    virtual void OnAbout(wxCommandEvent& event);
    virtual void OnButtonClickClearFrameParseLog( wxCommandEvent& event );
    virtual void OnButtonClickGetFrameParseHEX( wxCommandEvent& event );
    virtual void OnButtonClickCheckFrameParseCRC( wxCommandEvent& event );
    virtual void OnButtonClickFragmentDoFragment( wxCommandEvent& event );
    virtual void OnButtonClickFragmentDoDefragment( wxCommandEvent& event );
    //初始化关于文本框
    void InitAboutTextCtrl(wxTextCtrl* m_ctrl);
    //清除帧分析日志
    void ClearFrameParseLog();
    //添加帧分析日志
    void AppendFrameParseLog(wxString log_text);
    //获取帧分析输入
    wxString GetFrameParseInput();
    //获取帧分析输入(提取HEX)
    wxArrayString GetFrameParseInputHex(wxString input=_T(""));
    //HEX转二进制(需要严格按HEX输入，无空格)
    std::string HexToBin(std::string hex);
    //二进制转Hex
    std::string BinToHex(std::string bin);
};
#endif // APPMAIN_H
