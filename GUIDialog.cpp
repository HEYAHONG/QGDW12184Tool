///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIDialog.h"

///////////////////////////////////////////////////////////////////////////

GUIDialog::GUIDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_auinotebook_main = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxAUI_NB_TAB_MOVE|wxAUI_NB_TAB_SPLIT|wxAUI_NB_TOP );
	m_mgr.AddPane( m_auinotebook_main, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );

	m_panel_frame_parse = new wxPanel( m_auinotebook_main, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 1, 0, 0 );

	m_textCtrl_frame_parse_input = new wxTextCtrl( m_panel_frame_parse, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB );
	gSizer1->Add( m_textCtrl_frame_parse_input, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_button_clear_frame_parse_log = new wxButton( m_panel_frame_parse, wxID_ANY, wxT("清除日志"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_clear_frame_parse_log, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline_1 = new wxStaticLine( m_panel_frame_parse, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer3->Add( m_staticline_1, 0, wxEXPAND | wxALL, 5 );

	m_button_get_frame_parse_hex = new wxButton( m_panel_frame_parse, wxID_ANY, wxT("提取数据帧(HEX)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_get_frame_parse_hex, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button_check_frame_parse_crc = new wxButton( m_panel_frame_parse, wxID_ANY, wxT("检查CRC"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_check_frame_parse_crc, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline_2 = new wxStaticLine( m_panel_frame_parse, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer3->Add( m_staticline_2, 0, wxEXPAND | wxALL, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel_frame_parse, wxID_ANY, wxT("分片大小") ), wxVERTICAL );

	m_textCtrl_fragment_fragsize = new wxTextCtrl( sbSizer1->GetStaticBox(), wxID_ANY, wxT("243"), wxDefaultPosition, wxSize( 50,25 ), 0 );
	m_textCtrl_fragment_fragsize->SetMaxSize( wxSize( 50,25 ) );

	sbSizer1->Add( m_textCtrl_fragment_fragsize, 1, wxALL|wxFIXED_MINSIZE|wxEXPAND, 5 );


	bSizer3->Add( sbSizer1, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel_frame_parse, wxID_ANY, wxT("SSEQ") ), wxVERTICAL );

	m_textCtrl_fragment_sseq = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 50,25 ), 0 );
	m_textCtrl_fragment_sseq->SetMaxSize( wxSize( 50,25 ) );

	sbSizer2->Add( m_textCtrl_fragment_sseq, 1, wxALL|wxEXPAND, 5 );


	bSizer3->Add( sbSizer2, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( m_panel_frame_parse, wxID_ANY, wxT("优先级") ), wxVERTICAL );

	wxString m_choice_fragment_priorityChoices[] = { wxT("0"), wxT("1") };
	int m_choice_fragment_priorityNChoices = sizeof( m_choice_fragment_priorityChoices ) / sizeof( wxString );
	m_choice_fragment_priority = new wxChoice( sbSizer3->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( 50,25 ), m_choice_fragment_priorityNChoices, m_choice_fragment_priorityChoices, 0 );
	m_choice_fragment_priority->SetSelection( 0 );
	m_choice_fragment_priority->SetMaxSize( wxSize( 50,25 ) );

	sbSizer3->Add( m_choice_fragment_priority, 0, wxALL, 5 );


	bSizer3->Add( sbSizer3, 1, wxEXPAND, 5 );

	m_button_fragment_do_fragment = new wxButton( m_panel_frame_parse, wxID_ANY, wxT("分片"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_fragment_do_fragment, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticline3 = new wxStaticLine( m_panel_frame_parse, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer3->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );

	m_button_fragment_do_defragment = new wxButton( m_panel_frame_parse, wxID_ANY, wxT("重组"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_button_fragment_do_defragment, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	gSizer1->Add( bSizer3, 0, 0, 5 );


	bSizer2->Add( gSizer1, 1, wxEXPAND, 5 );

	m_textCtrl_frame_parse_log = new wxTextCtrl( m_panel_frame_parse, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( m_textCtrl_frame_parse_log, 1, wxALL|wxEXPAND, 5 );


	m_panel_frame_parse->SetSizer( bSizer2 );
	m_panel_frame_parse->Layout();
	bSizer2->Fit( m_panel_frame_parse );
	m_auinotebook_main->AddPage( m_panel_frame_parse, wxT("帧解析"), true, wxNullBitmap );
	m_panel_about = new wxPanel( m_auinotebook_main, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer_about;
	bSizer_about = new wxBoxSizer( wxVERTICAL );

	m_textCtrl_about = new wxTextCtrl( m_panel_about, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer_about->Add( m_textCtrl_about, 1, wxALL|wxEXPAND, 5 );


	m_panel_about->SetSizer( bSizer_about );
	m_panel_about->Layout();
	bSizer_about->Fit( m_panel_about );
	m_auinotebook_main->AddPage( m_panel_about, wxT("关于"), false, wxNullBitmap );


	m_mgr.Update();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::OnClose ) );
	m_button_clear_frame_parse_log->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickClearFrameParseLog ), NULL, this );
	m_button_get_frame_parse_hex->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickGetFrameParseHEX ), NULL, this );
	m_button_check_frame_parse_crc->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickCheckFrameParseCRC ), NULL, this );
	m_button_fragment_do_fragment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickFragmentDoFragment ), NULL, this );
	m_button_fragment_do_defragment->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickFragmentDoDefragment ), NULL, this );
}

GUIDialog::~GUIDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIDialog::OnClose ) );
	m_button_clear_frame_parse_log->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickClearFrameParseLog ), NULL, this );
	m_button_get_frame_parse_hex->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickGetFrameParseHEX ), NULL, this );
	m_button_check_frame_parse_crc->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickCheckFrameParseCRC ), NULL, this );
	m_button_fragment_do_fragment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickFragmentDoFragment ), NULL, this );
	m_button_fragment_do_defragment->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIDialog::OnButtonClickFragmentDoDefragment ), NULL, this );

	m_mgr.UnInit();

}
