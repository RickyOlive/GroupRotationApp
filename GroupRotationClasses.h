//
// Created by Ricky Olive on 3/18/23.
//

#ifndef GROUPROTATIONAPP_GROUPROTATIONCLASSES_H
#define GROUPROTATIONAPP_GROUPROTATIONCLASSES_H

#include <wx/wx.h>
#include <wx/numdlg.h>
#include <vector>
#include <string>



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

    // members
    int selectedGroupIndex;
    int selectedRotationItemIndex;
    int timeSpanDefaultValue;
    int timeSpanMinValue;
    int timeSpanMaxValue;
    int timeSpanValue;
    std::string outputString;
    std::string concatenatedArrayString;
    int groupIndexControl;

    // Functions that are being called
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnAddGroup(wxCommandEvent &event);
    void OnAddRotationItem(wxCommandEvent &event);
    void OnDeleteEntry(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnSelectTimeInterval(wxCommandEvent &event);
    void OnTimeSpan(wxCommandEvent &event);
    void OnPrint(wxCommandEvent &event);


    wxListBox *m_groupListBox;
    wxListBox *m_rotationItemListBox;
    wxTextCtrl *printOut;
    wxArrayString timeIntervalChoices;
    wxString timeIntervalSelection;

    std::vector<std::vector<std::string> > outputArray;

};

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

#endif //GROUPROTATIONAPP_GROUPROTATIONCLASSES_H
