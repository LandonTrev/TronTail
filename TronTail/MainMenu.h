#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Enum for game states
enum GameState { MainMenuState, PlayingState };

class MainMenu {
public:
    MainMenu(float width, float height);
    void MoveUp();
    void MoveDown();
    int MainMenuPressed();
    void draw(RenderWindow& window);
    ~MainMenu();

private:
    Text mainMenu[3];  // Corrected to 3 items (Play, Options, Exit)
    Font font;
    int MainMenuSelected;
    Clock cooldownClock;

    // Adding background texture and sprite
    Texture backgroundTexture;
    Sprite backgroundSprite;

    // Function to setup menu item text
    void setupMenuItem(Text& menuItem, const string& text, float centerX, float startingY, int index);
};

#endif
