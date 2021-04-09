#include "game.hpp"

Game::Game():
    _window(sf::VideoMode(800, 600), "02_Game_Archi"),
    _player(150)
{
    _player.setFillColor(sf::Color::Blue);
    _player.setPosition(10, 20);
}

void Game::run()
{
    run1();
}

void Game::run1()
{
    sf::Clock clock;
    while (_window.isOpen())
    {
        processEvents();
        // clock.restart()
        // 將時間計數器歸零
        // 返回自時鐘啓動以來經過的時間
        update(clock.restart());
        render();
    }
}

void Game::run2(int frame_per_seconds)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePreFrame = sf::seconds(1.f / frame_per_seconds);
    while (_window.isOpen())
    {
        processEvents();
        bool repaint = false;
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePreFrame)
        {
            timeSinceLastUpdate -= TimePreFrame;
            repaint = true;
            update(TimePreFrame);
        }
        if (repaint)
        {
            render();
        }
    }
}

void Game::run3(int minimum_frame_per_seconds)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate;
    sf::Time TimePreFrame = sf::seconds(1.f / minimum_frame_per_seconds);
    while (_window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate = clock.restart();
        while (timeSinceLastUpdate > TimePreFrame)
        {
            timeSinceLastUpdate -= TimePreFrame;
            update(TimePreFrame);
        }
        update(timeSinceLastUpdate);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed
        || (event.type == sf::Event::KeyPressed 
            && event.key.code == sf::Keyboard::Escape))
        {
            _window.close();
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Time time = deltaTime;
    time += deltaTime;
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);
    _window.display();
}
