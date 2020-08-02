//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
#ifndef __MainPage_xaml__
#define __MainPage_xaml__

#include <vector>

#include "MainPage.g.h"
//#include "InitiativeEntry.h"

#define COLUMN_NUMBER 4
#define INITIATIVE_MENU_OFFSET 2

namespace InitativeOrganiser
{
	ref class InitiativeEntry;
	/// <summary>
	/// Main page of the app, containing initiative list
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void DeleteEntry(int entry_index);
		Windows::UI::Xaml::Controls::Grid^ GetInitiativeList() { return this->InitiativeList; }
		int GetRowsNumber() { return this->rowsNumber; }
	private:
		Windows::UI::Xaml::Controls::Button^ add_button;
		Windows::UI::Xaml::Controls::Button^ SortButton;
		Windows::UI::Xaml::Controls::Button^ NextButton;
		std::vector<InitiativeEntry^> Entries;
		Windows::UI::Xaml::Controls::Grid^ InitiativeList;
		int rowsNumber;
		int initiativeToken; // Index of initiative entry which currently holds the initiative

		void SortInitiative();
		void add_button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SortButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void NextButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AddNewTextBox();
		void AddNewRow();
		void Redraw();
		void DrawHeader();
		void UpdateButtons();
		void AddNewText(Platform::String^ Content, int column);
		Windows::UI::Xaml::Controls::Button^ AddNewButton(Platform::String^ Content, int column);
		void MainPage::ShortcutHandler(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ args);
		void MainPage::DeleteLastEntry();
	};
}

#endif