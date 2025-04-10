#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// enum to represent different states of the game
enum GameState { MainMenuState, PlayingState, AboutState };

class MainMenu {
public:
    MainMenu(float width, float height); // constructor 
    void MoveUp();                       // function to navigate menu upward
    void MoveDown();                     // function to navigate menu downward
    int MainMenuPressed();               // returns the currently selected menu item
    void draw(RenderWindow& window);     // draws the menu on the window
    ~MainMenu();                         // destructor

private:
    Text mainMenu[3];          // Array to store menu options: Play, About, Exit
    Font font;                 // Font used for the menu text
    int MainMenuSelected;      // Index of the currently selected menu option
    Clock cooldownClock;       // Clock to handle input cooldown for smooth navigation
    Texture backgroundTexture; // Background texture for the menu
    Sprite backgroundSprite;   // Sprite to render the background texture

    void setupMenuItem(Text& menuItem, const string& text, float centerX, float startingY, int index);
};

#endif