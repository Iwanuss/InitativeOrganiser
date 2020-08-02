#pragma once
#ifndef __InitiativeEntry__
#define __InitiativeEntry__


#include "MainPage.xaml.h"

#define INITIATIVE_COLUMN_INDEX 1


namespace InitativeOrganiser {
	// Class for all controls in a single page grid row. Object is a single InitiativeList entry.
	 ref class InitiativeEntry sealed
	{
	public:
		InitiativeEntry(MainPage^ Parent);
		int GetInitiative();
		void RedrawEntry(int row);
		void DecreaseRow();
		void SetToInvisible();
		void SetActive();
		void SetInactive();
	private:
		std::vector<Windows::UI::Xaml::Controls::TextBox^> Fields;
		Windows::UI::Xaml::Controls::Button^ DeleteButton;
		MainPage^ Parent;
		int row;

		Windows::UI::Xaml::Controls::TextBox^ NewTextBox(int column);
		void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InitiativeEntry::AddNewField();
		Windows::UI::Xaml::Controls::Button^ NewButton(int column, Platform::String^ Content);
	};
}
#endif