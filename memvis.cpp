#include <iostream>
#include <fstream>
#include <array>
#include <wx/wx.h>
#include <wx/grid.h>

#define memsz 65536
std::array<uint8_t, memsz> memory = {0};
#define table_width 8
#define table_height (memory.size() / table_width)
#define filename "C:\\Users\\sebkl\\prg\\spaceinvaders-emul\\bin\\invaders.rom"

// Class declarations
class MyApp : public wxApp
{
public:
	bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
	MyFrame();
private:
	void OnExit(wxCommandEvent& evt);
	void OnAbout(wxCommandEvent& evt);
};
// -----

// MyApp definitions
bool MyApp::OnInit()
{
	// Read ROM file into memory
	std::ifstream file(filename, std::ifstream::binary);
	uint8_t byte;
	for (int i = 0; i < memsz && file >> byte; i++) {
		memory[i] = byte;
	}
	
	MyFrame* frame = new MyFrame();
	frame->Show();
	return true;
}

wxIMPLEMENT_APP(MyApp);
// -----

// MyFrame definitions
MyFrame::MyFrame()
	: wxFrame(nullptr, wxID_ADD, "Hello World")
{
	wxGrid* grid = new wxGrid(this, -1, wxPoint(0, 0), wxSize(700, 500));
	grid->CreateGrid(table_height, table_width + 1);
	wxGridSizesInfo rowSizesInfo;
	rowSizesInfo.m_sizeDefault = 25;
	grid->SetRowSizes(rowSizesInfo);
	wxGridSizesInfo colSizesInfo;
	colSizesInfo.m_sizeDefault = 50;
	grid->SetColSizes(colSizesInfo);
	grid->SetColSize(table_width, 150);
	grid->SetColSize(3, 75);
	grid->SetColSize(7, 75);
	for (int i = 0; i < table_width; i++) {
		grid->SetColLabelValue(i, wxString::Format("+%02X", i));
	}
	grid->SetColLabelValue(table_width, "ASCII");
	for (int i = 0; i < table_height; i++) {
		grid->SetRowLabelValue(i, wxString::Format("%04X", table_width * i));
	}

	for (int i = 0; i < table_height; i++) {
		for (int j = 0; j < table_width; j++) {
			int index = table_width * i + j;
			grid->SetCellFont(i, j, wxFont(wxFontInfo(12).FaceName("Consolas")));
			grid->SetCellValue(i, j, wxString::Format("%02X", memory[index]));
		}
#define MEM(X) memory[table_width*i + X]
		grid->SetCellFont(i, table_width, wxFont(wxFontInfo(12).FaceName("Consolas")));
		grid->SetCellValue(i, table_width,
			wxString::Format("%c%c%c%c %c%c%c%c",
			MEM(0), MEM(1), MEM(2), MEM(3),
			MEM(4), MEM(5), MEM(6), MEM(7))
		);
#undef MEM
	}

	wxMenu* menuFile = new wxMenu;
	menuFile->Append(wxID_EXIT, "&Quit");

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	this->SetMenuBar(menuBar);
	this->CreateStatusBar();
	this->SetStatusText("Welcome to wxWidgets!");

	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	Fit();
}

void MyFrame::OnExit(wxCommandEvent& evt)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& evt)
{
	wxMessageBox("This is a wxWidgets Hello World example.",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
// -----
