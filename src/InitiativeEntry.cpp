#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "pch.h"
#include "InitiativeEntry.h"

using namespace Platform;
using namespace InitativeOrganiser;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI;
using namespace std;

/*
	@brief Constructor creating InitiativeEntry with initialized all TextBox adn Button fields and adding it to parent Grid
	@param MainPage^ Parent - handle to parent page to call it's methods on events
*/
InitiativeEntry::InitiativeEntry(MainPage^ Parent) {
	this->Parent = Parent;
	this->row = Parent->GetRowsNumber();

	// Initialize all text boxes
	this->AddNewField();

	// Initialize DeleteButton
	this->DeleteButton = NewButton(COLUMN_NUMBER, "X");
	this->DeleteButton->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::InitiativeEntry::DeleteButton_Click);

	// Autosorting on changing initiative value currently disabled
	//this->InitiativeTextBox->TextChanged += ref new TextChangedEventHandler(this, &InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed);
}

/*
	@brief Creates new text box and appends it to object parent grid
	@param int column - Index of grid column in which this text box will be placed
	@return TextBox^ - Handle to newly created tex box
*/
TextBox^ InitiativeEntry::NewTextBox(int column) {
	TextBox^ Tbox = ref new TextBox();
	this->Parent->GetInitiativeList()->Children->Append(Tbox);
	Grid::SetColumn(Tbox, column);
	Grid::SetRow(Tbox, this->row);
	return Tbox;
}

/*
	@brief Creates new button and appends it to object parent grid
	@param int column - Index of grid column in which this text box will be placed
	@param String^ Content - Text displayed on the button
	@return Button^ - Handle to newly created button
*/
Button^ InitiativeEntry::NewButton(int column, String^ Content) {
	Button^ But = ref new Button();
	But->Content = Content;
	this->Parent->GetInitiativeList()->Children->Append(But);
	Grid::SetColumn(But, column);
	Grid::SetRow(But, this->row);
	return But;
}

/*
	@brief Changed event callback for 'InitiativeTextBox' TextBox. Currently disabled and does nothing.
*/
void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e) {
	// Autosorting on changing initiative value currently disabled
	//this->Parent->SortInitiative();
}

/*
	@brief Returns numeric value of this->InitiativeTextBox
	@return int - content of this->InitiativeTextBox converted to int
*/
int InitiativeEntry::GetInitiative() {
	return _wtoi(this->Fields.at(INITIATIVE_COLUMN_INDEX)->Text->Data()); // Convert from Platform::String^ to int
}

/*
	@brief Sets grid row for all controls in this object
	@param int row - new index of grid row in which this object will be placed
*/
void InitiativeEntry::RedrawEntry(int row) {
	this->row = row;
	for (TextBox^ n : this->Fields) {
		Grid::SetRow(n, row);
	}
	Grid::SetRow(this->DeleteButton, row);
}

/*
	@brief Click event callback for 'DeleteButton" Button. Deletes InitiativeEntry related to this button.
*/
void InitiativeEntry::DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	this->Parent->DeleteEntry(this->row);
}

/*
	@brief Decrements this->row by 1
*/
void InitiativeEntry::DecreaseRow() {
	this->row--;
}

/*
	@brief Sets Visibility of all controls in object to Collapsed.
*/
void InitiativeEntry::SetToInvisible() {
	for (TextBox^ n : this->Fields) {
		n->Visibility = Visibility::Collapsed;
	}
	this->DeleteButton->Visibility = Visibility::Collapsed;
}

/*
	@brief Adds new InitiativeEntry to the list. It's placed in the grid betwwen last entry and button row.
*/
void InitiativeEntry::AddNewField() {
	TextBox^ Tbox;
	for (int i = 0; i < COLUMN_NUMBER-1; i++) {
		Tbox = this->NewTextBox(i);
		this->Fields.push_back(Tbox);
	}
}

/*
	@brief Highlights all text boxes in this entry to predefined color.
*/
void InitiativeEntry::SetActive() {
	for (TextBox^ n : this->Fields) {
		n->Background = ref new SolidColorBrush(Colors::Green);
	}
}

/*
	@brief Deletes special coloring in all text boxes in this entry.
*/
void InitiativeEntry::SetInactive() {
	for (TextBox^ n : this->Fields) {
		n->Background = ref new SolidColorBrush();
	}
}