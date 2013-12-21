////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2013 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <SpaceInvaders/View/SFMLView.hpp>
#include <SpaceInvaders/View/SFMLEntityRepresentation.hpp>
#include <SpaceInvaders/Model/Entities.hpp>

namespace Game
{
    namespace View
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        SFMLView::SFMLView(GameState gameState, unsigned int score) :
            m_window   {sf::VideoMode{800, 600}, "Space Invaders"},
            m_gameState{gameState}
        {
            // Load the font
            if (!m_font.loadFromFile("Resources/DejaVuSans.ttf"))
                throw std::runtime_error("Failed to load the font 'Resources/DejaVuSans.ttf'.");

            // Load the background
            if (!m_backgroundTexture.loadFromFile("Resources/Background.png"))
                throw std::runtime_error("Failed to load 'Resources/Background.png'.");

            m_backgroundSprite.setTexture(m_backgroundTexture);
            m_backgroundSprite.setScale(static_cast<float>(SCREEN_WIDTH) / m_backgroundTexture.getSize().x,
                                        static_cast<float>(SCREEN_HEIGHT) / m_backgroundTexture.getSize().y);

            m_score.setFont(m_font);
            m_lives.setFont(m_font);
            m_message.setFont(m_font);

            m_score.setCharacterSize(30);
            m_lives.setCharacterSize(30);
            m_message.setCharacterSize(30);

            m_score.setPosition(10, 0);
            m_score.setString("0");

            // Change the game state when the signal gets send
            addObserver([this](const Event& e){ m_gameState = e.gameState; }, Event::Type::GameStateChanged);

            Event scoreEvent{Event::Type::ScoreChanged};
            scoreEvent.score = score;
            scoreChanged(scoreEvent);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::addEntity(const EntityPtr entity)
        {
            m_entities.push_back(std::unique_ptr<AbstractEntityRepresentation>(new SFMLEntityRepresentation(m_window, entity)));

            entity->addObserver(std::bind(&AbstractView::entityDestroyed, this, std::placeholders::_1, m_entities.back().get()), Event::Type::Destroyed);
            entity->addObserver(std::bind(&SFMLView::scoreChanged, this, std::placeholders::_1), Event::Type::ScoreChanged);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::handleEvents()
        {
            sf::Event event;
            while (m_window.pollEvent(event))
            {
                // The window can be closed at any time
                if (event.type == sf::Event::Closed)
                {
                    m_window.close();
                    notifyObservers(Event{Event::Type::ApplicationExit});
                    break;
                }

                // Most events are only used when playing the game
                if (m_gameState == GameState::Playing)
                {
                    switch (event.type)
                    {
                        case sf::Event::KeyPressed:
                        {
                            if (event.key.code == sf::Keyboard::Left)
                                notifyObservers(Event{Event::Type::MoveLeftKeyPressed});
                            else if (event.key.code == sf::Keyboard::Right)
                                notifyObservers(Event{Event::Type::MoveRightKeyPressed});
                            else if (event.key.code == sf::Keyboard::Space)
                                notifyObservers(Event{Event::Type::FireKeyPressed});

                            break;
                        }
                        case sf::Event::KeyReleased:
                        {
                            if (event.key.code == sf::Keyboard::Left)
                                notifyObservers(Event{Event::Type::MoveLeftKeyReleased});
                            else if (event.key.code == sf::Keyboard::Right)
                                notifyObservers(Event{Event::Type::MoveRightKeyReleased});
                            else if (event.key.code == sf::Keyboard::Space)
                                notifyObservers(Event{Event::Type::FireKeyReleased});

                            break;
                        }
                        case sf::Event::LostFocus:
                        {
                            // If the window losed focus while playing the game then the game should be paused
                            if (m_gameState == GameState::Playing)
                            {
                                Event event{Event::Type::GameStateChanged};
                                event.gameState = GameState::Paused;
                                notifyObservers(event);

                                // We will not be alerted when a key goes up while the window isn't focused.
                                // To avoid bugs we will fake that all keys are released.
                                notifyObservers(Event{Event::Type::MoveLeftKeyReleased});
                                notifyObservers(Event{Event::Type::MoveRightKeyReleased});
                                notifyObservers(Event{Event::Type::FireKeyReleased});
                            }
                        }

                        default:
                            break;
                    };
                }

                // The return key has multiple meanings in different game states
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return))
                {
                    Event event{Event::Type::GameStateChanged};

                    switch (m_gameState)
                    {
                        case GameState::MainMenu:
                        case GameState::Paused:
                            event.gameState = GameState::Playing;
                            break;
                        case GameState::Playing:
                            event.gameState = GameState::Paused;
                            break;
                        case GameState::GameOver:
                            event.gameState = GameState::MainMenu;
                            m_score.setString("0");
                            break;
                    };

                    notifyObservers(event);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::draw()
        {
            m_window.clear();
            m_window.draw(m_backgroundSprite);

            switch (m_gameState)
            {
                case GameState::MainMenu:
                {
                    sf::Text header("Space Invaders", m_font, 72);
                    sf::Text instruction("[ Press return key to start playing ]", m_font, 24);

                    header.setColor(sf::Color::Green);
                    instruction.setColor(sf::Color::Yellow);

                    header.setPosition((m_window.getSize().x / 2.0f) - (header.getLocalBounds().width / 2.0f),
                                       (m_window.getSize().y / 3.0f) - (header.getLocalBounds().height / 2.0f));

                    instruction.setPosition((m_window.getSize().x / 2.0f) - (instruction.getLocalBounds().width / 2.0f),
                                            (m_window.getSize().y * 2.0f / 3.0f) - (instruction.getLocalBounds().height / 2.0f));

                    m_window.draw(header);
                    m_window.draw(instruction);

                    break;
                }
                case GameState::Paused:
                {
                    for (auto& entity : m_entities)
                        entity->draw();

                    m_window.draw(m_score);
                    m_window.draw(m_lives);

                    sf::Text header("Paused", m_font, 64);
                    sf::Text instruction("[ Press return key to continue ]", m_font, 24);

                    header.setPosition((m_window.getSize().x / 2.0f) - (header.getLocalBounds().width / 2.0f),
                                       (m_window.getSize().y / 3.0f) - (header.getLocalBounds().height / 2.0f));

                    instruction.setPosition((m_window.getSize().x / 2.0f) - (instruction.getLocalBounds().width / 2.0f),
                                            (m_window.getSize().y * 2.0f / 3.0f) - (instruction.getLocalBounds().height / 2.0f));

                    m_window.draw(header);
                    m_window.draw(instruction);

                    break;
                }
                case GameState::Playing:
                {
                    for (auto& entity : m_entities)
                        entity->draw();

                    m_window.draw(m_score);
                    m_window.draw(m_lives);
                    m_window.draw(m_message);

                    break;
                }
                case GameState::GameOver:
                {
                    sf::Text header("Game Over", m_font, 64);
                    sf::Text score(m_score.getString(), m_font, 42);
                    sf::Text instruction("[ Press return key to continue ]", m_font, 24);

                    header.setPosition((m_window.getSize().x / 2.0f) - (header.getLocalBounds().width / 2.0f),
                                       (m_window.getSize().y / 3.0f) - (header.getLocalBounds().height / 2.0f));

                    score.setPosition((m_window.getSize().x / 2.0f) - (score.getLocalBounds().width / 2.0f),
                                      (m_window.getSize().y / 2.0f) - (score.getLocalBounds().height / 2.0f));

                    instruction.setPosition((m_window.getSize().x / 2.0f) - (instruction.getLocalBounds().width / 2.0f),
                                            (m_window.getSize().y * 2.0f / 3.0f) - (instruction.getLocalBounds().height / 2.0f));

                    m_window.draw(header);
                    m_window.draw(score);
                    m_window.draw(instruction);

                    break;
                }
            }

            m_window.display();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::setMessage(const std::string& message)
        {
            m_message.setString(message);
            m_message.setPosition(sf::Vector2f{(SCREEN_WIDTH - m_message.getLocalBounds().width) / 2.0f, 0});
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::removeMessage()
        {
            m_message.setString("");
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::scoreChanged(const Event& event)
        {
            m_score.setString(std::to_string(std::stoi(m_score.getString().toAnsiString()) + event.score));
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        void SFMLView::updateLives(unsigned int lives)
        {
            m_lives.setString("Lives: " + std::to_string(lives));
            m_lives.setPosition(SCREEN_WIDTH - m_lives.getLocalBounds().width - 10, 0);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}
