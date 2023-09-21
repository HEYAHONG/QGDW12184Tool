/***************************************************************
 * Name:      AppApp.h
 * Purpose:   Defines Application Class
 * Author:    HYH (2229388563@qq.com)
 * Created:   2023-09-20
 * Copyright: HYH (hyhsystem.cn)
 * License:
 **************************************************************/

#ifndef APPAPP_H
#define APPAPP_H

#include <wx/app.h>
#include "wxrc.h"

class AppApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // APPAPP_H
