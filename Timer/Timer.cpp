#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace sf;

class Timer {
private:
    Texture texture;

    vector<Sprite> digits;
    Sprite colon;
    Sprite semicolon;

    int minutes;
    int seconds;
    int milliseconds;
public:
    Timer(Vector2i characterSize) {
        texture.loadFromFile("HUD.png");
        int numCols = texture.getSize().x / characterSize.x;
        for (int i = 0; i < numCols; ++i) {
            IntRect spritePos(i * characterSize.x, 0, 
                characterSize.x, characterSize.y);
            Sprite digit;
            digit.setTexture(texture);
            digit.setTextureRect(spritePos);
            digits.push_back(digit);
        }

        colon.setTexture(texture);
        colon.setTextureRect(IntRect(0, 13, 9, 13));
        colon.setScale(10.0f, 10.0f);

        semicolon.setTexture(texture);
        semicolon.setTextureRect(IntRect(9, 13, 9, 13));
        semicolon.setScale(10.0f, 10.0f);

        minutes = 0;
        seconds = 0;
        milliseconds = 0;
    }

    void update() {
        milliseconds += 16;

        if (milliseconds >= 1000) {
            milliseconds = 0;
            seconds++;

            if (seconds >= 60) {
                seconds = 0;
                minutes++;
                if (minutes >= 60) {
                    minutes = 0;
                }
            }
        }
    }

    void drawMinutes(RenderWindow& window) {
        digits[minutes / 10].setScale(10.0f, 10.0f);
        digits[minutes / 10].setPosition(0, 10);
        window.draw(digits[minutes / 10]);

        digits[minutes % 10].setScale(10.0f, 10.0f);
        digits[minutes % 10].setPosition(90, 10);
        window.draw(digits[minutes % 10]);
    }

    void drawSeconds(RenderWindow& window) {
        colon.setPosition(180, 10);
        window.draw(colon);

        digits[seconds / 10].setScale(10.0f, 10.0f);
        digits[seconds / 10].setPosition(270, 10);
        window.draw(digits[seconds / 10]);

        digits[seconds % 10].setScale(10.0f, 10.0f);
        digits[seconds % 10].setPosition(360, 10);
        window.draw(digits[seconds % 10]);
    }

    void drawMilliseconds(RenderWindow& window) {
        semicolon.setPosition(450, 10);
        window.draw(semicolon);

        digits[milliseconds / 100].setScale(10.0f, 10.0f);
        digits[milliseconds / 100].setPosition(540, 10);
        window.draw(digits[milliseconds / 100]);

        digits[(milliseconds % 100) / 10].setScale(10.0f, 10.0f);
        digits[(milliseconds % 100) / 10].setPosition(630, 10);
        window.draw(digits[(milliseconds % 100) / 10]);
    }

    void draw(RenderWindow& window) {
        drawMinutes(window);
        drawSeconds(window);
        drawMilliseconds(window);
    }
};

int main() {
    RenderWindow window(VideoMode(720, 150), "Timer");

    Timer timer(Vector2i(9, 13));

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        timer.update();
        window.clear();
        timer.draw(window);
        window.display();
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}