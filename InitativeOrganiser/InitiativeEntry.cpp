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

InitiativeEntry::InitiativeEntry() {
	this->row = 0;
}

InitiativeEntry::InitiativeEntry(Grid^ InitiativeList, int row) {
	this->row = row;
	int number_of_box = 0;
	this->NameTextBox = NewTextBox(InitiativeList, number_of_box++);
	this->InitiativeTextBox = NewTextBox(InitiativeList, number_of_box++);
	this->HPTextBox = NewTextBox(InitiativeList, number_of_box++);
	// Autosorting on changing initiative value currently disabled
	//this->InitiativeTextBox->TextChanged += ref new TextChangedEventHandler(this, &InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed);
}

TextBox^ InitiativeEntry::NewTextBox(Grid^ InitiativeList, int column) {
	TextBox^ Tbox = ref new TextBox();
	InitiativeList->Children->Append(Tbox);
	Grid::SetColumn(Tbox, column);
	Grid::SetRow(Tbox, this->row);
	return Tbox;
}

void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e) {
	// Autosorting on changing initiative value currently disabled
	//this->Parent->SortInitiative();
}

int InitiativeEntry::GetInitiative() {
	return _wtoi(this->InitiativeTextBox->Text->Data());
}

void InitiativeEntry::RedrawEntry(int row) {
	this->row = row;
	Grid::SetRow(this->NameTextBox, row);
	Grid::SetRow(this->InitiativeTextBox, row);
	Grid::SetRow(this->HPTextBox, row);
}