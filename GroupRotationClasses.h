// COP 3003 - CRN 15050 - Programming II
// Header file containing Class declaration and function prototypes
// also has an enum.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GROUPROTATIONAPP_GROUPROTATIONCLASSES_H
#define GROUPROTATIONAPP_GROUPROTATIONCLASSES_H

// Directives
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/numdlg.h>
#include <vector>
#include <string>
#include <fstream>
// --------------------------------------------------------------------------------------------------------------------


// File struct
struct File {
    std::string filename;
    std::string filePath;
    std::ofstream myFile;
};
// --------------------------------------------------------------------------------------------------------------------

// MyApp Class
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
// --------------------------------------------------------------------------------------------------------------------

// MyFrame Class
class MyFrame : public wxFrame
{
public:
    MyFrame();

private:

    // members
    int selectedGroupIndex;
    int selectedRotationItemIndex;
    int timeSpanDefaultValue;
    int timeSpanMinValue;
    int timeSpanMaxValue;
    int timeSpanValue;
    std::string outputString;
    std::string concatenatedArrayString;
    int countIndexControl;
    int startIndexControl;

    // Functions that are being called
    void OnAbout(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent &event);
    void OnExit(wxCommandEvent& event);
    void OnAddGroup(wxCommandEvent &event);
    void OnAddRotationItem(wxCommandEvent &event);
    void OnDeleteEntry(wxCommandEvent &event);
    void OnSelectTimeInterval(wxCommandEvent &event);
    void OnTimeSpan(wxCommandEvent &event);
    void OnPrint(wxCommandEvent &event);
    void WriteFile();


    // wxWidgets declaration;
    wxGrid *m_grid;
    wxListBox *m_groupListBox;
    wxListBox *m_rotationItemListBox;
    wxArrayString timeIntervalChoices;
    wxString timeIntervalSelection;
    wxBoxSizer *sizer;
    wxBoxSizer *listBoxSizer;
    File File;

    // 2D vector being used to print out the output
    std::vector<std::vector<std::string> > outputArray;

};

// --------------------------------------------------------------------------------------------------------------------




// Enum with ID's
enum
{
    ID_SAVEAS = 1,
    ID_EXIT = 2,
    ID_ADDGROUP = 3,
    ID_ADDROTATIONITEM = 4,
    ID_DELETEENTRY = 5,
    ID_SELECTTIMEINTERVAL = 6,
    ID_TIMESPAN = 7,
    ID_PRINT = 8
};
// --------------------------------------------------------------------------------------------------------------------

#endif //GROUPROTATIONAPP_GROUPROTATIONCLASSES_H
