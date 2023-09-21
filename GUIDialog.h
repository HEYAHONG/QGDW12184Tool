///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/aui/auibook.h>
#include <wx/dialog.h>
#include <wx/aui/aui.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIDialog
///////////////////////////////////////////////////////////////////////////////
class GUIDialog : public wxDialog
{
	private:

	protected:
		wxAuiNotebook* m_auinotebook_main;
		wxPanel* m_panel_frame_parse;
		wxTextCtrl* m_textCtrl_frame_parse_input;
		wxButton* m_button_clear_frame_parse_log;
		wxButton* m_button_get_frame_parse_hex;
		wxButton* m_button_check_frame_parse_crc;
		wxTextCtrl* m_textCtrl_frame_parse_log;
		wxPanel* m_panel_about;
		wxTextCtrl* m_textCtrl_about;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnButtonClickClearFrameParseLog( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickGetFrameParseHEX( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnButtonClickCheckFrameParseCRC( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("QGDW12184Tool"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER );
		wxAuiManager m_mgr;

		~GUIDialog();

};

