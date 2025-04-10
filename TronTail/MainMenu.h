#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Enum for game states
enum GameState { MainMenuState, PlayingState, AboutState };

class MainMenu {
public:
    MainMenu(float width, float height);
    void MoveUp();
    void MoveDown();
    int MainMenuPressed();
    void draw(RenderWindow& window);
    ~MainMenu();

private:
    Text mainMenu[3]; // Menu: Play, About, Exit
    Font font;
    int MainMenuSelected;
    Clock cooldownClock;

    Texture backgroundTexture;
    Sprite backgroundSprite;

    void setupMenuItem(Text& menuItem, const string& text, float centerX, float startingY, int index);
};

#endif

