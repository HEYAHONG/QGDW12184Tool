/***************************************************************
 * Name:      AppApp.cpp
 * Purpose:   Code for Application Class
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

#include "AppApp.h"
#include "AppMain.h"

IMPLEMENT_APP(AppApp);

bool AppApp::OnInit()
{
    
    AppDialog* dlg = new AppDialog(0L);
    dlg->Show();
    return true;
}
