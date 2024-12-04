/*       



#include <SFML/Graphics.hpp>
#include <time.h>
#include "MainMenu.h"

using namespace sf;

int N = 30, M = 20;
int gridSize = 16;
int w = gridSize * N;
int h = gridSize * M;

int dir, num = 4;
struct Snake { int x, y; } s[100];
struct Fruit { int x, y; } f;

GameState currentState = MainMenuState;

void Tick() {
    // Move the snake’s body
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    // Move the snake’s head based on direction
    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    // If the snake eats the fruit
    if (s[0].x == f.x && s[0].y == f.y) {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }

    // Handle wall collisions (wrap-around screen)
    if (s[0].x >= N) s[0].x = 0;
    if (s[0].x < 0) s[0].x = N - 1;
    if (s[0].y >= M) s[0].y = 0;
    if (s[0].y < 0) s[0].y = M - 1;

    // Snake collides with itself
    for (int i = 1; i < num; i++) {
        if (s[0].x == s[i].x && s[0].y == s[i].y) num = i; // End game if collides
    }
}

int main() {
    srand(time(0)); // Initialize random seed
    RenderWindow window(VideoMode(w, h), "Tron Tail!");

    Texture t1, t2, bgTexture;  // Texture for snake, fruit, and background
    if (!t1.loadFromFile("images/green.png") || !t2.loadFromFile("images/red.png") || !bgTexture.loadFromFile("images/white.png")) {
        cout << "Error loading images!" << endl;
        return -1;
    }

    Sprite sprite1(t1), sprite2(t2), bgSprite(bgTexture);

    Clock clock;
    float timer = 0, delay = 0.1f;
    f.x = 10;
    f.y = 10;

    // Add the snake length text
    Font font;
    if (!font.loadFromFile("fonts/SnakeGameDemoRegular.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    Text lengthText;
    lengthText.setFont(font);
    lengthText.setCharacterSize(24);
    lengthText.setFillColor(Color::White);

    MainMenu menu(w, h);

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
                if (selected == 0) currentState = PlayingState;
                if (selected == 3) window.close();
            }
        }

        if (currentState == PlayingState) {
            if (timer > delay) {
                timer = 0;
                Tick();
            }

            // Handle snake movement based on arrow keys
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
            // Tiling the grid background
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < M; ++y) {
                    bgSprite.setPosition(x * gridSize, y * gridSize);
                    window.draw(bgSprite); // Draw background for each tile
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

            // Update and draw the snake length counter
            lengthText.setString("Length: " + std::to_string(static_cast<float>(num)));  // Display snake length
            window.draw(lengthText);
        }

        window.display();
    }

    return 0;
}
*/

