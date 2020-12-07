#pragma once
#ifndef __InitiativeEntry__
#define __InitiativeEntry__


#include "MainPage.xaml.h"

#define INITIATIVE_COLUMN_INDEX 1
#define HP_COLUMN_INDEX 2
#define DELETE_BUTTON_INDEX COLUMN_NUMBER - 1

#define TEXT_BOXES_COUNT 3
#define BUTTONS_COUNT 1
#define COLUMN_NUMBER TEXT_BOXES_COUNT + BUTTONS_COUNT


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
		//std::vector<Windows::UI::Xaml::Controls::TextBox^> Fields;
		std::vector<Windows::UI::Xaml::Controls::Control^> Fields;
		//Windows::UI::Xaml::Controls::Button^ DeleteButton;
		MainPage^ Parent;
		int row;

		Windows::UI::Xaml::Controls::TextBox^ NewTextBox(int column);
		void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InitiativeEntry::CommandInvokedHandler(Windows::UI::Popups::IUICommand^ command);
		void InitiativeEntry::AddNewField();
		Windows::UI::Xaml::Controls::Button^ NewButton(int column, Platform::String^ Content, void (InitativeOrganiser::InitiativeEntry::* fnPtr)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^));
	};
}
#endif