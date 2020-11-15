// Pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Bat.h"
#include "Ball.h"
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<SFML/Graphics.hpp>

using namespace sf;

int main()
{
    //Create a video mode object
    VideoMode vm(1366, 768);
    //Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    window.setMouseCursorVisible(false);
    int score = 0;
    int hiscore = 0;
    int lives = 3;
    //Create a bat at the bottom center of the screen
    Bat bat(1366 / 2, 700);
    //Create a ball
    Ball ball(1366 / 2, 0);
    //Create text object called HUD
    Text hud;
    Font font;
    font.loadFromFile("fonts/Gameplay.ttf");
    hud.setFont(font);
    hud.setCharacterSize(50);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    Text hiscoreText;
    hiscoreText.setFont(font);
    hiscoreText.setCharacterSize(50);
    hiscoreText.setFillColor(Color::Green);
    hiscoreText.setPosition(900, 20);
    //Hiscore
    std::ifstream inputFile("gamedata/hiscore.txt");
    if (inputFile.is_open())
    {
        inputFile >> hiscore;
        inputFile.close();
    }
    //Clock for timing everything
    Clock clock;
    while (window.isOpen()) {
        //Handle player input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                //Quit the game when the window is closed
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }

        //Update the bat, the ball and HUD
        //Update delta time
        Time dt = clock.restart();
        bat.update(dt);
        ball.update(dt);
        std::stringstream ss;
        ss << "Score: " << score << "  Lives: " << lives;
        hud.setString(ss.str());
        std::stringstream hi;
        hi << "High score: " << hiscore;
        hiscoreText.setString(hi.str());

        //Handle ball hitting bottom
        if (ball.getPosition().top > window.getSize().y) 
        {
            ball.reboundBottom();
            lives--;
            if (lives < 1)
            {
                score = 0;
                lives = 3;
                ball.resetSpeed();
                std::ofstream outputFile("gamedata/hiscore.txt");
                outputFile << hiscore;
                outputFile.close();
            }
        }
        //Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
        }
        //Handle ball hitting sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
        {
            ball.reboundSides();
        }
        //Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            ball.reboundBatOrTop();
            score++;
            if (score > hiscore)
                hiscore = score;
        }


        //Draw the bat, the ball and HUD
        window.clear();
        
        window.draw(hud);
        window.draw(hiscoreText);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
        //
    }


    return 0;
}

