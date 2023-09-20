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



#include "GUIDialog.h"

class AppDialog: public GUIDialog
{
    public:
        AppDialog(wxDialog *dlg);
        ~AppDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};
#endif // APPMAIN_H
