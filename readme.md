# Initiative Organiser
## Introduction
Initiative Organiser is a simple app created for turn based tabletop RPGs. Game (Dungeon) Masters in most systems face a chllenge of keeping track of everything happening in combat. A lot of calculations and only scrap paper to note it and calculate everything. You could use an excel-like soft, but it's not comfortable and easy to turn into mess. There are some smartphone apps fot this, but they support only DnD or aren't really flexible.

So, your party encountered BBEG and the most climatic battle of your campaing is about to start. Then, everything has to stop for 5 minutes, because you have to write everything down and manually sort initiative.

This project has been created to end this. General idea is to create a fast and easy to use tool with flexibility to adapt to your system and gamestyle, where you can keep track of all important information regarding an RPG combat encounter.
## Installation
Currently, this app is designed for Windows 10 only. You can download installation `.zip` pack from release section on github. You can then install it with `.bundle` file or execute `Install.ps1` powershell scriipt and follow instructions prompted on screen. Since the project is in very early stage of development, it's possible you'll need to change settings in order to install apps from "untrusted" sources. To do this go to `Settings -> Security and updates -> For developers -> Chose developer mode`. It's possible that you'll also need to install self-signed cert attached to installation package.
## Curent features
Currently, main features of our tool are:
* Adding and deleting entries to the initiative list consisting of 3 values: 
  * Character name
  * Initiative value
  * Hit points
* Sorting the initiative list based on initiatie value of its entries (currently only from highest to lowest).

With much, much more to come!