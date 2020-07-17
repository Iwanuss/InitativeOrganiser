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

#define ROW_NUMBER 4

namespace InitativeOrganiser
{
	ref class InitiativeEntry;
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		void SortInitiative();
		void DeleteEntry(int entry_index);
	private:
		Windows::UI::Xaml::Controls::Button^ add_button;
		Windows::UI::Xaml::Controls::Button^ SortButton;
		std::vector<InitiativeEntry^> Entries;
		Windows::UI::Xaml::Controls::Grid^ InitiativeList;
		int rowsNumber;

		void add_button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SortButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void AddNewTextBox();
		void AddNewRow();
		void Redraw();
		void DrawHeader();
		void UpdateButtons();
		void AddNewText(Platform::String^ Content, int column);
		Windows::UI::Xaml::Controls::Button^ AddNewButton(Platform::String^ Content, int column);
	};
}

#endif