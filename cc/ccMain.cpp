/***************************************************************
 * Name:      ccMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    maliqi (909040969@qq.com)
 * Created:   2018-06-03
 * Copyright: maliqi (dfsF)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "ccMain.h"
#include <wx/msgdlg.h>
#include "SerialPort.h"
#include "stdio.h"
#include "tchar.h"
 #include <iostream>
#include "Windows.h"

#include <string.h>
#include <list>
#include <stdlib.h>

//(*InternalHeaders(ccFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)
using namespace std;
using namespace itas109;
CSerialPort m_SerialPort;
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ccFrame)
const long ccFrame::ID_STATICTEXT2 = wxNewId();
const long ccFrame::ID_COMBOBOX1 = wxNewId();
const long ccFrame::ID_BUTTON1 = wxNewId();
const long ccFrame::ID_COMBOBOX2 = wxNewId();
const long ccFrame::ID_STATICTEXT1 = wxNewId();
const long ccFrame::idMenuQuit = wxNewId();
const long ccFrame::idMenuAbout = wxNewId();
const long ccFrame::ID_STATUSBAR1 = wxNewId();
//*)
BEGIN_EVENT_TABLE(ccFrame,wxFrame)
    //(*EventTable(ccFrame)
    //*)
END_EVENT_TABLE()

ccFrame::ccFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ccFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("comm"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(478,523));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("串口:"), wxPoint(24,32), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    ComboBox1 = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxPoint(64,32), wxSize(88,22), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    OpenCom_Button = new wxButton(this, ID_BUTTON1, _("打开串口"), wxPoint(336,32), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    ComboBox2 = new wxComboBox(this, ID_COMBOBOX2, wxEmptyString, wxPoint(216,32), wxSize(64,22), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    ComboBox2->Append(_("300"));
    ComboBox2->Append(_("600"));
    ComboBox2->Append(_("1200"));
    ComboBox2->Append(_("2400"));
    ComboBox2->Append(_("4800"));
    ComboBox2->Append(_("9600"));
    ComboBox2->Append(_("14400"));
    ComboBox2->Append(_("19200"));
    ComboBox2->Append(_("38400"));
    ComboBox2->Append(_("56000"));
    ComboBox2->Append(_("57300"));
    ComboBox2->Append(_("115200"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("波特率:"), wxPoint(168,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&ccFrame::OnComboBox1Selected);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_DROPDOWN,(wxObjectEventFunction)&ccFrame::OnComboBox1Dropdown);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_CLOSEUP,(wxObjectEventFunction)&ccFrame::OnComboBox1CloseUp);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ccFrame::OnComboBox1TextUpdated);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&ccFrame::OnComboBox1TextEnter);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ccFrame::OnOpenCom_ButtonClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ccFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ccFrame::OnAbout);
    //*)

   //获取串口号
   CSerialPortInfo a;

   list<string> m_portsList = CSerialPortInfo::availablePorts();
   	list<string>::iterator itor;
	TCHAR m_regKeyValue[255];
	for (itor = m_portsList.begin(); itor != m_portsList.end(); ++itor)
	{
#ifdef UNICODE
		int iLength;
		const char * _char = (*itor).c_str();
		iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, m_regKeyValue, iLength);
#else
		strcpy_s(m_regKeyValue, 255, (*itor).c_str());
#endif
		//m_PortNr.AddString(m_regKeyValue);
		ComboBox1->Append(_(m_regKeyValue));
		ComboBox1->SetSelection(0);
		ComboBox2->SetSelection(5);
	}

}

ccFrame::~ccFrame()
{
    //(*Destroy(ccFrame)
    //*)
}

void ccFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ccFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void ccFrame::OnComboBox1Selected(wxCommandEvent& event)
{
}

void ccFrame::OnComboBox1Dropdown(wxCommandEvent& event)
{
}

void ccFrame::OnComboBox1CloseUp(wxCommandEvent& event)
{
}

void ccFrame::OnComboBox1TextUpdated(wxCommandEvent& event)
{
}

void ccFrame::OnComboBox1TextEnter(wxCommandEvent& event)
{

}

void ccFrame::OnOpenCom_ButtonClick(wxCommandEvent& event)
{
    wxString temp;
    wxString msg;
   temp =  OpenCom_Button->GetLabel();
   if(temp ==_("关闭串口"))
   {
       m_SerialPort.ClosePort();
     OpenCom_Button->SetLabel(_("打开串口"));
   }
   else if(ComboBox1->GetCount() > 0)
    {
		int SelPortNO, SelBaudRate;
		//temp = ComboBox1->GetCurrentSelection();

		temp = ComboBox1->GetString(ComboBox1->GetCurrentSelection());
		//m_PortNr.GetWindowText(temp);///CString temp
		temp.erase(0,3);
		//memset((char*)temp,0,3);
		SelPortNO = atoi(temp);
        ComboBox2->GetCurrentSelection();
        temp = ComboBox2->GetString(ComboBox2->GetCurrentSelection());
		SelBaudRate = atoi(temp);

		if (m_SerialPort.InitPort(this->GetHandle(), SelPortNO, SelBaudRate))
		{

			m_SerialPort.StartMonitoring();
			OpenCom_Button->SetLabel(_("关闭串口"));
			//m_OpenCloseCtrl.SetWindowText(_T("关闭串口"));
		}
		else
		{
    msg.Printf(wxT("Hello and welcome to %s"),
               wxVERSION_STRING);

    wxMessageBox(msg, wxT("About Minimal"),
                 wxOK | wxICON_INFORMATION, this);
			//AfxMessageBox(_T("串口已被占用！"));
		}
    }
}
