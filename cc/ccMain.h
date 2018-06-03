/***************************************************************
 * Name:      ccMain.h
 * Purpose:   Defines Application Frame
 * Author:    maliqi (909040969@qq.com)
 * Created:   2018-06-03
 * Copyright: maliqi (dfsF)
 * License:
 **************************************************************/

#ifndef CCMAIN_H
#define CCMAIN_H

//(*Headers(ccFrame)
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
//*)

class ccFrame: public wxFrame
{
    public:

        ccFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ccFrame();

    private:

        //(*Handlers(ccFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnComboBox1Selected(wxCommandEvent& event);
        void OnComboBox1Dropdown(wxCommandEvent& event);
        void OnComboBox1CloseUp(wxCommandEvent& event);
        void OnComboBox1TextUpdated(wxCommandEvent& event);
        void OnComboBox1TextEnter(wxCommandEvent& event);
        void OnOpenCom_ButtonClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ccFrame)
        static const long ID_STATICTEXT2;
        static const long ID_COMBOBOX1;
        static const long ID_BUTTON1;
        static const long ID_COMBOBOX2;
        static const long ID_STATICTEXT1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ccFrame)
        wxButton* OpenCom_Button;
        wxComboBox* ComboBox1;
        wxComboBox* ComboBox2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CCMAIN_H
