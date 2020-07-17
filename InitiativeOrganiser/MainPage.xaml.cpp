//
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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	this->InitiativeList = ref new Grid();
	//InitiativeList->Width = 200;
	//InitiativeList->Height = 200;
	for (int i = 0; i < ROW_NUMBER; i++) {
		ColumnDefinition^ StandardColumn = ref new ColumnDefinition();
		StandardColumn->Width = *(ref new GridLength(1, GridUnitType::Auto));
		this->InitiativeList->ColumnDefinitions->Append(StandardColumn);
	}
	int number_of_button = 0;
	this->add_button = AddNewButton("Add", number_of_button++);
	this->add_button->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::MainPage::add_button_Click);
	this->SortButton = AddNewButton("Sort", number_of_button++);
	this->SortButton->Click += ref new RoutedEventHandler(this, &InitativeOrganiser::MainPage::SortButton_Click);
	this->AddNewRow();
	this->rowsNumber = 0;
	this->DrawHeader();
	this->AddNewTextBox();
	this->Content = InitiativeList;
}

Button^ MainPage::AddNewButton(String^ Content, int column) {
	Button^ Butt = ref new Button();
	Butt->Content = Content;
	this->InitiativeList->Children->Append(Butt);
	Grid::SetRow(Butt, 0);
	Grid::SetColumn(Butt, column);
	return Butt;
}

void MainPage::AddNewRow() {
	RowDefinition^ StandardRow = ref new RowDefinition();
	StandardRow->Height = *(ref new GridLength(0, GridUnitType::Auto));
	this->InitiativeList->RowDefinitions->Append(StandardRow);
}

void MainPage::AddNewTextBox() {
	this->AddNewRow();
	InitiativeEntry^ NewEntry = ref new InitiativeEntry(this, this->InitiativeList, this->rowsNumber);
	this->Entries.push_back(NewEntry);
	this->rowsNumber++;
	this->UpdateButtons();
}


void InitativeOrganiser::MainPage::add_button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->AddNewTextBox();
}

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

void MainPage::Redraw() {
	InitiativeEntry^ Entry;
	for (unsigned int i = 0; i < this->Entries.size(); i++) {
		Entry = this->Entries.at(i);
		Entry->RedrawEntry(i+1);
	}
}

void InitativeOrganiser::MainPage::SortButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	this->SortInitiative();
}

void MainPage::DrawHeader() {
	this->AddNewRow();
	int number_of_text = 0;
	this->AddNewText("Character", number_of_text++);
	this->AddNewText("Initiative", number_of_text++);
	this->AddNewText("HP", number_of_text++);
	this->rowsNumber++;
	this->UpdateButtons();
}

void MainPage::UpdateButtons() {
	Grid::SetRow(this->add_button, this->rowsNumber);
	Grid::SetRow(this->SortButton, this->rowsNumber);
}

void MainPage::AddNewText(String^ Content, int column) {
	TextBlock^ Text = ref new TextBlock();
	Text->Text = Content;
	this->InitiativeList->Children->Append(Text);
	Grid::SetRow(Text, 0);
	Grid::SetColumn(Text, column);
}

void MainPage::DeleteEntry(int entry_index) {
	InitiativeEntry^ Entry = this->Entries.at(entry_index - 1);
	Entry->SetToInvisible();
	this->Entries.erase(this->Entries.begin()+entry_index-1);
	/*for (unsigned int i = entry_index; i < Entries.size(); i++) {
		Entry = this->Entries.at(i);
		Entry->DecreaseRow();
	}*/
	this->rowsNumber--;
	this->UpdateButtons();
	this->Redraw();
}