#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:

    // Functions that are being called
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnAddGroup(wxCommandEvent &event);
    void OnAddRotationItem(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);


    // List Boxes that hold group names as well as rotation items
    wxListBox *m_groupListBox;
    wxListBox *m_rotationItemListBox;

};

enum
{
    ID_ADDGROUP = 1,
    ID_ADDROTATIONITEM = 2,
    ID_SAVEAS = 3
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
        : wxFrame(nullptr, wxID_ANY, "Group-Rotation Scheduler")
{
    m_groupListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));
    m_rotationItemListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(100, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(m_groupListBox, 1, wxEXPAND | wxALL, 5);
    sizer->Add(m_rotationItemListBox, 1, wxEXPAND | wxALL, 5);

    SetSizer(sizer);

    // elements within File Tab
    wxMenu *menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    menuFile->Append(ID_SAVEAS, "&Save As...\tCtrl-A",
                     "Save schedule file");

    // elements within Entry Tab
    wxMenu *menuEntry = new wxMenu;
    menuEntry->Append(ID_ADDGROUP, "&Add Group...\tCtrl-A",
                     "Add a new group");
    menuEntry->Append(ID_ADDROTATIONITEM, "&Add Rotation Item...\tCtrl-A",
                     "Add a new item to be rotated");


    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEntry, "&Entry");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );


    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAddGroup, this, ID_ADDGROUP);
    Bind(wxEVT_MENU, &MyFrame::OnAddRotationItem, this, ID_ADDROTATIONITEM);
    Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, ID_SAVEAS);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Prints out purpose of the program
 * @param click event
 */
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a desktop application where you can enter groups "
                 "and something to rotate between them such as a location, "
                 "and it creates a rotation schedule.",
                 "About Group-Rotation Scheduler", wxOK | wxICON_INFORMATION);
}

/**
 * User entry box allows user to input the names of the groups
 * @param event
 */
void MyFrame::OnAddGroup(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this, "Enter a new group name:", "Add Group");

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString groupName = dialog.GetValue();
        m_groupListBox->Append(groupName);

    }
}

/**
 * User entry box that allows user to enter the names of the items they are
 * rotating between the groups
 * @param click event
 */
void MyFrame::OnAddRotationItem(wxCommandEvent& event)
{
    wxTextEntryDialog dialog(this, "Enter an item you would like to be rotated "
                                   "(ex. name of a location, responsibilities, etc):", "Add Group");

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString rotatedItem = dialog.GetValue();
        m_rotationItemListBox->Append(rotatedItem);

    }
}

/**
 * This will eventually allow the user to save the generated schedule
 * @param click event
 */
void MyFrame::OnSaveAs (wxCommandEvent& event) {
    wxMessageBox("In development, this will allow you to save your generated schedule as a file",
                 "Save As...", wxOK | wxICON_INFORMATION);

}

