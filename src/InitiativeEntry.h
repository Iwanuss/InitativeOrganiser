#pragma once
#ifndef __InitiativeEntry__
#define __InitiativeEntry__


#include "MainPage.xaml.h"


namespace InitativeOrganiser {
	// Class for all controls in a single page grid row. Object is a single InitiativeList entry.
	 ref class InitiativeEntry sealed
	{
	public:
		InitiativeEntry(MainPage^ Parent, Windows::UI::Xaml::Controls::Grid^ InitiativeList, int row);
		int GetInitiative();
		void RedrawEntry(int row);
		void DecreaseRow();
		void SetToInvisible();
	private:
		Windows::UI::Xaml::Controls::TextBox^ NameTextBox;
		Windows::UI::Xaml::Controls::TextBox^ InitiativeTextBox;
		Windows::UI::Xaml::Controls::TextBox^ HPTextBox;
		Windows::UI::Xaml::Controls::Button^ DeleteButton;
		MainPage^ Parent;
		int row;

		Windows::UI::Xaml::Controls::TextBox^ NewTextBox(Windows::UI::Xaml::Controls::Grid^ InitiativeList, int column);
		void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void DeleteButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
#endif