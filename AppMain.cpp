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


AppDialog::AppDialog(wxDialog *dlg)
    : GUIDialog(dlg)
{
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
