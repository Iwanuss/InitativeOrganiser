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
using namespace std;

/*
	@brief Constructor creating InitiativeEntry with initialized all TextBox adn Button fields and adding it to parent Grid
	@param MainPage^ Parent - handle to parent page to call it's methods on events
	@param Grid^ InitiativeList - parent grid in which this object will be placed
	@param int row - index of grid row in which this object will be placed
*/
InitiativeEntry::InitiativeEntry(MainPage^ Parent, Grid^ InitiativeList, int row) {
	this->Parent = Parent;
	this->row = row;

	// Initialize all text boxes
	int number_of_box = 0;
	this->NameTextBox = NewTextBox(InitiativeList, number_of_box++);
	this->InitiativeTextBox = NewTextBox(InitiativeList, number_of_box++);
	this->HPTextBox = NewTextBox(InitiativeList, number_of_box++);

	// Initialize DeleteButton
	this->DeleteButton = ref new Button();
	this->DeleteButton->Content = "X";
	this->DeleteButton->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::InitiativeEntry::DeleteButton_Click);
	InitiativeList->Children->Append(this->DeleteButton);
	Grid::SetColumn(this->DeleteButton, number_of_box++);
	Grid::SetRow(this->DeleteButton, this->row);


	// Autosorting on changing initiative value currently disabled
	//this->InitiativeTextBox->TextChanged += ref new TextChangedEventHandler(this, &InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed);
}

/*
	@brief Creates new text box and appends it to object parent grid
	@param Grid^ InitiativeList - Object paren grid to which this new textbox will be appended
	@param int column - Index of grid column in which this text box will be placed
	@return TextBox^ - Handle to newly created tex box
*/
TextBox^ InitiativeEntry::NewTextBox(Grid^ InitiativeList, int column) {
	TextBox^ Tbox = ref new TextBox();
	InitiativeList->Children->Append(Tbox);
	Grid::SetColumn(Tbox, column);
	Grid::SetRow(Tbox, this->row);
	return Tbox;
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
	return _wtoi(this->InitiativeTextBox->Text->Data()); // Convert from Platform::String^ to int
}

/*
	@brief Sets grid row for all controls in this object
	@param int row - new index of grid row in which this object will be placed
*/
void InitiativeEntry::RedrawEntry(int row) {
	this->row = row;
	Grid::SetRow(this->NameTextBox, row);
	Grid::SetRow(this->InitiativeTextBox, row);
	Grid::SetRow(this->HPTextBox, row);
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
	this->NameTextBox->Visibility = Visibility::Collapsed;
	this->InitiativeTextBox->Visibility = Visibility::Collapsed;
	this->HPTextBox->Visibility = Visibility::Collapsed;
	this->DeleteButton->Visibility = Visibility::Collapsed;
}