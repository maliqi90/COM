/***************************************************************
 * Name:      ccApp.cpp
 * Purpose:   Code for Application Class
 * Author:    maliqi (909040969@qq.com)
 * Created:   2018-06-03
 * Copyright: maliqi (dfsF)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ccApp.h"

//(*AppHeaders
#include "ccMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ccApp);

bool ccApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ccFrame* Frame = new ccFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
