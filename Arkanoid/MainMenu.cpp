#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(std::shared_ptr<sf::RenderWindow>& window)
    : _window(window), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false),
      m_isExitButtonSelected(false), m_isExitButtonPressed(false)
{

}

MainMenu::~MainMenu()
{
    
}

void MainMenu::Init()
{
    int SCALE = _window->getSize().y / 500;
    // Font
    m_font.loadFromFile("assets/Arkanoid/Silkscreen-Regular.ttf");

    // Title
    m_gameTitle.setFont(m_font);
    m_gameTitle.setString("ARKANOID");
    m_gameTitle.setCharacterSize(45*SCALE);
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(_window->getSize().x / 2, _window->getSize().y / 2 - 125.f*SCALE);

    // Play Button
    m_playButton.setFont(m_font);
    m_playButton.setString("Play");
    m_playButton.setCharacterSize(30*SCALE);
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(_window->getSize().x / 2, _window->getSize().y / 2 - 0.f*SCALE);

    // Exit Button
    m_exitButton.setFont(m_font);
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(30*SCALE);
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(_window->getSize().x / 2, _window->getSize().y / 2 + 75.f*SCALE);


    ProcessInput();
}

void MainMenu::ProcessInput()
{
    sf::Event event;
    
    while (!m_isPlayButtonPressed && !m_isExitButtonPressed)
    {
        _window->pollEvent(event);
        
        if (event.type == sf::Event::Closed)
        {
            _window->close();
        }
        else if(event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                if(!m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                if(!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            case sf::Keyboard::Return:
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;
                if(m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }
                break;
            default:
                break;
            }
        }

        if(m_isPlayButtonSelected)
        {
            m_playButton.setFillColor(sf::Color::Yellow);
            m_exitButton.setFillColor(sf::Color::White);
        }
        else 
        {
            m_exitButton.setFillColor(sf::Color::Yellow);
            m_playButton.setFillColor(sf::Color::White);
        }
        if(m_isExitButtonPressed)
        {
            _window->close();
        }

        Draw();
    }

}

void MainMenu::Draw()
{
    _window->clear(sf::Color::Blue);
    _window->draw(m_gameTitle);
    _window->draw(m_playButton);
    _window->draw(m_exitButton);
    _window->display();
}
