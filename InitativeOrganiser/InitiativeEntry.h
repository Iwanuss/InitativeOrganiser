#pragma once
#ifndef __InitiativeEntry__
#define __InitiativeEntry__


#include "MainPage.xaml.h"


namespace InitativeOrganiser {
	 ref class InitiativeEntry sealed
	{
	public:
		InitiativeEntry();
		InitiativeEntry(Windows::UI::Xaml::Controls::Grid^ InitiativeList, int row);
		int GetInitiative();
		void RedrawEntry(int row);
	private:
		Windows::UI::Xaml::Controls::TextBox^ NameTextBox;
		Windows::UI::Xaml::Controls::TextBox^ InitiativeTextBox;
		Windows::UI::Xaml::Controls::TextBox^ HPTextBox;
		int row;

		Windows::UI::Xaml::Controls::TextBox^ NewTextBox(Windows::UI::Xaml::Controls::Grid^ InitiativeList, int column);
		void InitativeOrganiser::InitiativeEntry::InitiativeTextBox_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
	};
}
#endif