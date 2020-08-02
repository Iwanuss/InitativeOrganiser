﻿//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "InitiativeEntry.h"

using namespace InitativeOrganiser;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Core;
using namespace std;


/*
	@brief Creates main page with Grid containing initiative list.
*/
MainPage::MainPage()
{
	InitializeComponent();
	this->InitiativeList = ref new Grid();

	//Setting grid coords
	//InitiativeList->Width = 200;
	//InitiativeList->Height = 200;

	// Initializaing grid columns
	for (int i = 0; i < COLUMN_NUMBER + INITIATIVE_MENU_OFFSET; i++) {
		ColumnDefinition^ StandardColumn = ref new ColumnDefinition();
		if (i != COLUMN_NUMBER + INITIATIVE_MENU_OFFSET-2)
			StandardColumn->Width = *(ref new GridLength(1, GridUnitType::Auto));
		else
			StandardColumn->Width = *(ref new GridLength(100, GridUnitType::Pixel)); // Adding buffor between entries table and list menu controls
		this->InitiativeList->ColumnDefinitions->Append(StandardColumn);
	}

	// Adding global buttons
	int number_of_button = 0;
	this->add_button = AddNewButton("Add", number_of_button++);
	this->add_button->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::MainPage::add_button_Click);
	this->SortButton = AddNewButton("Sort", number_of_button++);
	this->SortButton->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::MainPage::SortButton_Click);
	this->AddNewRow();

	// Adding header row with text box descirptions
	this->rowsNumber = 0;
	this->DrawHeader();
	this->AddNewTextBox();

	// Adding keyboard shortcuts handler
	CoreWindow::GetForCurrentThread()->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(this, &InitativeOrganiser::MainPage::ShortcutHandler);

	// Adding initiative list menu controls
	this->NextButton = AddNewButton("Start", COLUMN_NUMBER + INITIATIVE_MENU_OFFSET - 1);
	this->NextButton->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::MainPage::NextButton_Click);
	Grid::SetRow(NextButton, 1);

	// Setting created grid as page content
	this->Content = InitiativeList;

	// At the beggining, no entry has the initiative token
	this->initiativeToken = -1;
}

/*
	@brief Adds new button in the last row of the main page grid.
	@param String^ Content - string displayed on the button
	@param int column - index of grid column to be placed in
	@return Button^ - handle to created button
*/
Button^ MainPage::AddNewButton(String^ Content, int column) {
	Button^ Butt = ref new Button();
	Butt->Content = Content;
	this->InitiativeList->Children->Append(Butt);
	Grid::SetRow(Butt, 0);
	Grid::SetColumn(Butt, column);
	return Butt;
}

/*
	@brief Adds new row at the end of the grid
*/
void MainPage::AddNewRow() {
	RowDefinition^ StandardRow = ref new RowDefinition();
	StandardRow->Height = *(ref new GridLength(0, GridUnitType::Auto));
	this->InitiativeList->RowDefinitions->Append(StandardRow);
}

/*
	@brief Adds new InitiativeEntry to the list. It's placed in the grid betwwen last entry and button row.
*/
void MainPage::AddNewTextBox() {
	this->AddNewRow();
	InitiativeEntry^ NewEntry = ref new InitiativeEntry(this);
	this->Entries.push_back(NewEntry);
	this->rowsNumber++;
	this->UpdateButtons();
}

/*
	@brief Click event callback for 'add_button' button. Adds new InitiativeEntry to the list.
*/
void InitativeOrganiser::MainPage::add_button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->AddNewTextBox();
}

/*
	@brief Sorts Entries vector elements by InitiativeEntry->InitiativeTextBox->Text value from highest to lowest and redraws the list.
*/
void MainPage::SortInitiative() {
	InitiativeEntry ^present, ^next, ^tmp;
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (unsigned int i = 0; i < this->Entries.size() - 1; i++) {
			present = this->Entries.at(i);
			next = this->Entries.at(i + 1);
			if (present->GetInitiative() < next->GetInitiative()) {
				tmp = present;
				present = next;
				next = tmp;
				sorted = false;
				this->Entries.at(i) = present;
				this->Entries.at(i + 1) = next;
			}
		}
	}
	this->Redraw();
}

/*
	@brief Redraws all elements from Entries vector in order from lowest index to highest.
*/
void MainPage::Redraw() {
	InitiativeEntry^ Entry;
	for (unsigned int i = 0; i < this->Entries.size(); i++) {
		Entry = this->Entries.at(i);
		Entry->RedrawEntry(i+1); // header row is not part of the vector, thus i+1
	}
}

/*
	@brief Click event callback for 'SortButton' button. Sorts Entries vector elements by InitiativeEntry->InitiativeTextBox->Text value from highest to lowest and redraws the list.
*/
void InitativeOrganiser::MainPage::SortButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	this->SortInitiative();
}

/*
	@brief Draws header row for the entire InitiativeList grid table with description of each column.
*/
void MainPage::DrawHeader() {
	this->AddNewRow();
	int number_of_text = 0;
	this->AddNewText("Character", number_of_text++);
	this->AddNewText("Initiative", number_of_text++);
	this->AddNewText("HP", number_of_text++);
	this->rowsNumber++;
	this->UpdateButtons();
}

/*
	@brief Updates buttons row, ensuring they are moved to the last row in the InitiativeList grid.
*/
void MainPage::UpdateButtons() {
	Grid::SetRow(this->add_button, this->rowsNumber);
	Grid::SetRow(this->SortButton, this->rowsNumber);
}

/*
	@brief Creates new TextBlock control and appends it to the InitiativeList grid in row 0.
	@param String^ Content - string displayed in TextBlock.
	@param int column - index of column in which TextBlock will be placed.
*/
void MainPage::AddNewText(String^ Content, int column) {
	TextBlock^ Text = ref new TextBlock();
	Text->Text = Content;
	this->InitiativeList->Children->Append(Text);
	Grid::SetRow(Text, 0);
	Grid::SetColumn(Text, column);
}


/*
	@brief Erases InitiativeEntry in given row from the vector, sets it as invisible, adjusts other fields and redraws the grid.
	@param int entry_index - index of grid row in which deleted entry is located.
*/
void MainPage::DeleteEntry(int entry_index) {
	InitiativeEntry^ Entry = this->Entries.at(entry_index - 1); // entry_index - 1 is adjustment for header row, which is not part of the vector
	Entry->SetToInvisible(); // Workaround, deleting Entry from InitiativeList Grid would require keeping track of each object index in Grid->Children.
	this->Entries.erase(this->Entries.begin()+entry_index-1);
	this->rowsNumber--;
	this->UpdateButtons();
	this->Redraw();
}

/*
	@brief Deletes last entry from the list, if any is left
*/
void MainPage::DeleteLastEntry() {
	if(this->rowsNumber > 1) // no entries to delete if only button row left
		this->DeleteEntry(this->rowsNumber - 1);
}

/*
	@brief Handles keyboard shortcuts via global window TypedEventHandler
*/
//void MainPage::ShortcutHandler(CoreDispatcher^ sender, AcceleratorKeyEventArgs^ args) {
void MainPage::ShortcutHandler(CoreWindow^ sender, KeyEventArgs^ args) {
	CoreVirtualKeyStates ConstrolState = CoreWindow::GetForCurrentThread()->GetKeyState(Windows::System::VirtualKey::Control); // is control key pressed
	Windows::System::VirtualKey PressedKey = args->VirtualKey; // key which triggered this event

	// Ctrl+A shortcut for adding new entry
	if (PressedKey == Windows::System::VirtualKey::A && args->KeyStatus.WasKeyDown
 		&& (ConstrolState == CoreVirtualKeyStates::Down + CoreVirtualKeyStates::Locked || ConstrolState == CoreVirtualKeyStates::Down)) {
		this->AddNewTextBox();
	}

	// Ctrl+S shortcut for sorting the list
	if (PressedKey == Windows::System::VirtualKey::S && args->KeyStatus.WasKeyDown
		&& (ConstrolState == CoreVirtualKeyStates::Down + CoreVirtualKeyStates::Locked || ConstrolState == CoreVirtualKeyStates::Down)) {
		this->SortInitiative();
	}

	// Ctrl+D deleting last entry
	// Ctrl+S shortcut for sorting the list
	if (PressedKey == Windows::System::VirtualKey::D && args->KeyStatus.WasKeyDown
		&& (ConstrolState == CoreVirtualKeyStates::Down + CoreVirtualKeyStates::Locked || ConstrolState == CoreVirtualKeyStates::Down)) {
		this->DeleteLastEntry();
	}
}

/*
	@brief  Click event callback for 'NextButton' button. Highlights next entry in the list and sets previous to inactive. If list hasn't been started yet, highlights first entry.
*/
void InitativeOrganiser::MainPage::NextButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	if (this->initiativeToken == -1) {
		this->Entries.at(0)->SetActive();
		this->initiativeToken = 0;
		this->NextButton->Content = "Next";
	}
	else if (this->initiativeToken++ < this->Entries.size() - 1){
		this->Entries.at(this->initiativeToken)->SetActive();
		this->Entries.at(this->initiativeToken-1)->SetInactive();
	}
	else {
		this->Entries.at(0)->SetActive();
		this->Entries.at(Entries.size()-1)->SetInactive();
		this->initiativeToken = 0;
	}
}