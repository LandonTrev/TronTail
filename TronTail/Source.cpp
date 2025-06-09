#include <SFML/Graphics.hpp>
#include <time.h>
#include "MainMenu.h"

using namespace sf;

// Constants for screen resolution
const int windowWidth = 1280;
const int windowHeight = 720;
const int gridSize = 64; // Much larger grid size for significantly fewer tiles

// Dynamically calculated grid dimensions
int N = windowWidth / gridSize; // 20 tiles horizontally
int M = windowHeight / gridSize; // 11.25 tiles vertically

int dir, num = 2; // Starting length of the snake
struct Snake { int x, y; } s[100];
struct Fruit { int x, y; } f;

GameState currentState = MainMenuState;

void Tick() {
    // Move the body
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    // Move the head based on direction
    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    // Check if the snake hits the boundaries
    if (s[0].x >= N || s[0].x < 0 || s[0].y >= M || s[0].y < 0) {
        num = 2;
        s[0].x = N / 2;
        s[0].y = M / 2;
        for (int i = 1; i < num; ++i) {
            s[i].x = s[0].x - i;
            s[i].y = s[0].y;
        }
        return;
    }

    // Check if the snake eats the fruit
    if (s[0].x == f.x && s[0].y == f.y) {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }

    // Check if the snake collides with itself
    for (int i = 1; i < num; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y) {
            num = 2;
            s[0].x = N / 2;
            s[0].y = M / 2;
            for (int i = 1; i < num; ++i) {
                s[i].x = s[0].x - i;
                s[i].y = s[0].y;
            }
            return;
        }
    }
}

void showAbout(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("fonts/goodtiming.otf")) {
        std::cout << "Error loading font!" << std::endl;
        return;
    }

    Text aboutText;
    aboutText.setFont(font);
    aboutText.setCharacterSize(50);
    aboutText.setFillColor(Color::White);
    aboutText.setString("\n\n\nMove the snake with arrow keys\nEat the fruit to grow longer\nDon't run into yourself\nCreated by Harrison Conrado and Landon");
    aboutText.setPosition(50, 50);

    while (true) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                return;
            }
        }

        window.clear();
        window.draw(aboutText);
        window.display();
    }
}

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Tron Tail!");

    Texture t1, t2, bgTexture;
    if (!t1.loadFromFile("images/blue.png") || !t2.loadFromFile("images/red.png") || !bgTexture.loadFromFile("images/white.png")) {
        std::cout << "Error loading images!" << std::endl;
        return -1;
    }

    // Scale sprites to match the new larger grid size
    Sprite sprite1(t1), sprite2(t2), bgSprite(bgTexture);
    sprite1.setScale(gridSize / 16.0f, gridSize / 16.0f); // Assuming original sprites are 16x16
    sprite2.setScale(gridSize / 16.0f, gridSize / 16.0f);
    bgSprite.setScale(gridSize / 16.0f, gridSize / 16.0f);

    // Create a shape for the thin border
    RectangleShape cellBorder(Vector2f(gridSize - 1, gridSize - 1));
    cellBorder.setFillColor(Color::Transparent);
    cellBorder.setOutlineColor(Color(50, 50, 50, 128)); // Slightly translucent dark gray for less prominent borders
    cellBorder.setOutlineThickness(1);

    Clock clock;
    float timer = 0, delay = 0.15f; // Slightly slower gameplay due to larger grid

    // Initialize snake position
    s[0].x = N / 2;
    s[0].y = M / 2;
    for (int i = 1; i < num; ++i) {
        s[i].x = s[0].x - i;
        s[i].y = s[0].y;
    }

    // Initialize fruit position
    f.x = rand() % N;
    f.y = rand() % M;

    MainMenu menu(windowWidth, windowHeight);

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }

        if (currentState == MainMenuState) {
            if (Keyboard::isKeyPressed(Keyboard::Up)) menu.MoveUp();
            if (Keyboard::isKeyPressed(Keyboard::Down)) menu.MoveDown();
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                int selected = menu.MainMenuPressed();
                if (selected == 0) {
                    currentState = PlayingState;
                    // Reset snake position
                    dir = 2; // Start moving right
                    num = 2;
                    s[0].x = N / 2;
                    s[0].y = M / 2;
                    for (int i = 1; i < num; ++i) {
                        s[i].x = s[0].x - i;
                        s[i].y = s[0].y;
                    }
                    // Generate new fruit
                    f.x = rand() % N;
                    f.y = rand() % M;
                }
                if (selected == 1) showAbout(window);
                if (selected == 2) window.close();
            }
        }

        if (currentState == PlayingState) {
            if (timer > delay) {
                timer = 0;
                Tick();
            }

            if (Keyboard::isKeyPressed(Keyboard::Up) && dir != 0) dir = 3;
            if (Keyboard::isKeyPressed(Keyboard::Down) && dir != 3) dir = 0;
            if (Keyboard::isKeyPressed(Keyboard::Left) && dir != 2) dir = 1;
            if (Keyboard::isKeyPressed(Keyboard::Right) && dir != 1) dir = 2;
        }

        window.clear();

        if (currentState == MainMenuState) {
            menu.draw(window);
        }
        else if (currentState == PlayingState) {
            // Draw the white background with thin borders
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < M; ++y) {
                    bgSprite.setPosition(x * gridSize, y * gridSize);
                    window.draw(bgSprite);

                    // Draw thin border around each cell
                    cellBorder.setPosition(x * gridSize + 0.5, y * gridSize + 0.5);
                    window.draw(cellBorder);
                }
            }

            // Draw the snake
            for (int i = 0; i < num; i++) {
                sprite1.setPosition(s[i].x * gridSize, s[i].y * gridSize);
                window.draw(sprite1);
            }

            // Draw the fruit
            sprite2.setPosition(f.x * gridSize, f.y * gridSize);
            window.draw(sprite2);
        }

        window.display();
    }


    return 0;
}

