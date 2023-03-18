//
// Created by Ricky Olive on 3/18/23.
//

#include "GroupRotationClasses.h"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
        : wxFrame(nullptr, wxID_ANY, "Group-Rotation Scheduler")
{

    // Declares the three boxes (both list boxes and the text box)
    m_groupListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    m_rotationItemListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    printOut = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    // sizers to format the boxes
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *listBoxSizer = new wxBoxSizer(wxVERTICAL);

    // Adds boxes to the defined boxes
    listBoxSizer->Add(m_groupListBox, 1, wxEXPAND | wxALL, 5);
    listBoxSizer->Add(m_rotationItemListBox, 1, wxEXPAND | wxALL, 5);
    sizer->Add(listBoxSizer, 1, wxEXPAND | wxALL, 5);
    sizer->Add(printOut, 2, wxEXPAND | wxALL, 5);

    SetSizer(sizer);


    // elements within File Tab
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_SAVEAS, "&Save As...\tCtrl-A",
                     "Save schedule file");
    menuFile->Append(ID_EXIT, "&Exit...\tCtrl-E", "Closes app");

    // elements within Entry Tab
    wxMenu *menuEntry = new wxMenu;
    menuEntry->Append(ID_ADDGROUP, "&Add Group...\tCtrl-G",
                      "Add a new group");
    menuEntry->Append(ID_ADDROTATIONITEM, "&Add Rotation Item...\tCtrl-I",
                      "Add a new item to be rotated");
    menuEntry->Append(ID_DELETEENTRY, "&Delete Selected Item...\tCtrl-D",
                      "Select an item and click delete to remove it from the list");

    // elements within Output Tab
    wxMenu *menuOutput = new wxMenu;
    menuOutput->Append(ID_SELECTTIMEINTERVAL, "&Select Time Interval...\tCtrl-S",
                       "User specifies if they want a daily, weekly, or monthly rotation schedule");
    menuOutput->Append(ID_TIMESPAN, "&Enter Time Span...\tCtrl-T",
                       "User specifies how long they want the rotation schedule to be (Ex. '10' weeks)");
    menuOutput->Append(ID_PRINT, "&Print...\tCtrl-P",
                       "Prints rotated schedule on the rightmost box");


    // elements within Menu tab
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuEntry, "&Entry");
    menuBar->Append(menuOutput, "&Output");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar( menuBar );


    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, ID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAddGroup, this, ID_ADDGROUP);
    Bind(wxEVT_MENU, &MyFrame::OnAddRotationItem, this, ID_ADDROTATIONITEM);
    Bind(wxEVT_MENU, &MyFrame::OnDeleteEntry, this, ID_DELETEENTRY);
    Bind(wxEVT_MENU, &MyFrame::OnPrint, this, ID_PRINT);
    Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, ID_SAVEAS);
    Bind(wxEVT_MENU, &MyFrame::OnSelectTimeInterval, this, ID_SELECTTIMEINTERVAL);
    Bind(wxEVT_MENU, &MyFrame::OnTimeSpan, this, ID_TIMESPAN);

    // assigns necessary default values to class members
    timeIntervalSelection = "Daily";
    timeSpanValue = 1;
    timeSpanDefaultValue = 1;
    timeSpanMinValue = 1;
    timeSpanMaxValue = INT_MAX;
    groupIndexControl = 0;
    concatenatedArrayString = "";
}

/**
 * Closes the application
 * @param event
 */
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
* This will eventually allow the user to save the generated schedule
* @param click event
*/
void MyFrame::OnSaveAs (wxCommandEvent& event) {
    wxMessageBox("In development, this will allow you to save your generated schedule as a file",
                 "Save As...", wxOK | wxICON_INFORMATION);

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
 * Deletes a selected entry
 * @param event
 */
void MyFrame::OnDeleteEntry(wxCommandEvent& event)
{
    selectedGroupIndex = m_groupListBox->GetSelection();
    selectedRotationItemIndex = m_rotationItemListBox->GetSelection();

    if (selectedGroupIndex != wxNOT_FOUND) {
        m_groupListBox->Delete(selectedGroupIndex);
    }
    else if (selectedRotationItemIndex != wxNOT_FOUND) {
        m_rotationItemListBox->Delete(selectedRotationItemIndex);
    }
    else {
        wxMessageBox("Please make sure that you have selected an item to be deleted.",
                     "No Item Selected", wxOK | wxICON_INFORMATION);
    }
}

/**
 * Allows the user to pick the interval of time they want for their schedule
 * @param event
 */
void MyFrame::OnSelectTimeInterval(wxCommandEvent& event) {

    timeIntervalChoices.Add("Daily");
    timeIntervalChoices.Add("Weekly");
    timeIntervalChoices.Add("Monthly");

    wxSingleChoiceDialog dialog(this, "Select an option", "Selector", timeIntervalChoices, nullptr);

    if (dialog.ShowModal() == wxID_OK) {
        timeIntervalSelection = dialog.GetStringSelection();
        wxLogMessage("Selected: %s", timeIntervalSelection);
    }
}

/**
 * User enters a numerical input to decide how far out they want the schedule to be created
 * @param event
 */
void MyFrame::OnTimeSpan(wxCommandEvent& event) {

    timeSpanValue = wxGetNumberFromUser("Enter a number:", "Time Span", "Input", timeSpanDefaultValue, timeSpanMinValue, timeSpanMaxValue, this);

    if (timeSpanValue == -1) {
        timeSpanValue = timeSpanDefaultValue;
    }
    wxLogMessage("Time Span has been set to %d", timeSpanValue);

}

/**
 * prints out rotation schedule
 * @param event
 */
void MyFrame::OnPrint (wxCommandEvent& event) {

    if (m_rotationItemListBox->GetCount() == 0 || m_groupListBox->GetCount() == 0) {
        wxLogMessage("Please make sure that you have inputted at least one entry for each box.");
        return;
    }

    printOut->Clear();
    outputArray = std::vector<std::vector<std::string> >(m_rotationItemListBox->GetCount(), std::vector<std::string>(2, ""));

    for (int x = 0; x < timeSpanValue; x++) {
        for (int y = 0; y < m_rotationItemListBox->GetCount(); y++) {
            outputArray[y][0] = m_rotationItemListBox->GetString(y);
            outputArray[y][1] = m_groupListBox->GetString(groupIndexControl);
            groupIndexControl += 1;
            if (groupIndexControl == m_groupListBox->GetCount()) {
                groupIndexControl = 0;
            }
            concatenatedArrayString += "['" + outputArray[y][0] + "', '" + outputArray[y][1] + "'] ";
        }

        outputString = timeIntervalSelection + " " + std::to_string(x + 1) + ": " + concatenatedArrayString + "\n";
        concatenatedArrayString = "";
        printOut->AppendText(outputString);


    }
}