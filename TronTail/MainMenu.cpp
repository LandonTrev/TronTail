#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {
    // Load the font for the menu text
    if (!font.loadFromFile("fonts/SnakeGameDemoRegular.ttf")) { // Adjust the font path if necessary
        cout << "Error: No font file found!" << endl;
    }

    // Load the background texture (ensure the path is correct)
    if (!backgroundTexture.loadFromFile("texture/background1.jpg")) { // Adjust the background path if needed
        cout << "Error loading background texture!" << endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Set up the number of menu items (now 3 instead of 4)
    int numMenuItems = 3;  // Play, Options, Exit

    // Center coordinates for the menu
    float centerX = width / 2;
    float centerY = height / 2;

    // Calculate the total height for all menu items
    float totalMenuHeight = numMenuItems * 70;  // Each item has a height of 70 pixels (set character size)

    // Position the menu so that it's vertically centered
    float startingY = centerY - (totalMenuHeight / 2);

    // Set up menu items (Play, Options, Exit)
    setupMenuItem(mainMenu[0], "Play", centerX, startingY, 0);
    setupMenuItem(mainMenu[1], "Options", centerX, startingY, 1);
    setupMenuItem(mainMenu[2], "Exit", centerX, startingY, 2);

    MainMenuSelected = 0; // Highlight "Play" by default

    // Initialize the clock for cooldown
    cooldownClock.restart();
}

void MainMenu::setupMenuItem(Text& menuItem, const string& text, float centerX, float startingY, int index) {
    menuItem.setFont(font);
    menuItem.setFillColor(index == MainMenuSelected ? Color::Blue : Color::White); // Highlight selected option
    menuItem.setString(text);
    menuItem.setCharacterSize(70);
    menuItem.setPosition(centerX - menuItem.getGlobalBounds().width / 2, startingY + index * menuItem.getCharacterSize());
}

void MainMenu::MoveUp() {
    if (cooldownClock.getElapsedTime().asSeconds() >= 0.2f) { // Check if 0.2 seconds have passed
        cooldownClock.restart();  // Reset cooldown clock

        if (MainMenuSelected > 0) {
            mainMenu[MainMenuSelected].setFillColor(Color::White);  // Reset previous selected color
            --MainMenuSelected;
            mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Set new selected color
        }
        else {
            // If already at the top, wrap to the bottom (Exit)
            mainMenu[MainMenuSelected].setFillColor(Color::White);
            MainMenuSelected = 2;  // Changed to 2 to reflect "Exit" being the last menu item
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);
        }
    }
}

void MainMenu::MoveDown() {
    if (cooldownClock.getElapsedTime().asSeconds() >= 0.2f) { // Check if 0.2 seconds have passed
        cooldownClock.restart();  // Reset cooldown clock

        if (MainMenuSelected < 2) {  // Change the condition to ensure it doesn't go beyond "Exit"
            mainMenu[MainMenuSelected].setFillColor(Color::White);  // Reset previous selected color
            ++MainMenuSelected;
            mainMenu[MainMenuSelected].setFillColor(Color::Blue); // Set new selected color
        }
        else {
            // If already at the bottom, wrap to the top (Play)
            mainMenu[MainMenuSelected].setFillColor(Color::White);
            MainMenuSelected = 0;  // Wrap to the top (Play)
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);
        }
    }
}

int MainMenu::MainMenuPressed() {
    return MainMenuSelected;  // This will return the index of the selected menu item
}

void MainMenu::draw(RenderWindow& window) {
    // Draw the background first
    window.draw(backgroundSprite);

    // Then draw all the menu items
    for (int i = 0; i < 3; ++i) {  // Updated to 3 since there are only 3 menu items
        window.draw(mainMenu[i]);
    }
}

MainMenu::~MainMenu() {
    // Destructor, if needed for cleanup (not used here)
}
