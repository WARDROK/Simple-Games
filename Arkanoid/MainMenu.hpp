#pragma once

#include <memory>

#include <SFML/Graphics.hpp>


class MainMenu
{
private:
    std::shared_ptr<sf::RenderWindow> _window;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed = false;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed = false;

    sf::Font m_font;

public:
    MainMenu(std::shared_ptr<sf::RenderWindow>& window);
    ~MainMenu();

    virtual void Init();
    virtual void ProcessInput();
    virtual void Draw();
};