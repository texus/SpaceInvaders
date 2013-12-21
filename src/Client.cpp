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


#include <SpaceInvaders/Client.hpp>
#include <SpaceInvaders/View/SFMLView.hpp>

namespace Game
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    Client::Client()
    {
        loadNextLevel(Event{Event::Type::LevelComplete});
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void Client::mainLoop()
    {
        sf::Clock clock;

        // The main loop
        while (m_running)
        {
            if (m_gameState == GameState::Playing)
                m_controller->update(clock.restart());
            else
                clock.restart();

            m_view->handleEvents();
            m_view->draw();

            sf::sleep(sf::milliseconds(1));
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void Client::loadNextLevel(const Event&)
    {
        m_difficulty++;

        m_view       = std::unique_ptr<View::AbstractView>(new View::SFMLView{m_gameState, m_score});
        m_controller = std::unique_ptr<Controller::Controller>(new Controller::Controller{m_view.get(), m_difficulty});

        m_view->addObserver(std::bind(&Client::gameStateChanged, this, std::placeholders::_1), Event::Type::GameStateChanged);

        // This function should be called again when the level is over
        m_controller->addObserver(std::bind(&Client::loadNextLevel, this, std::placeholders::_1), Event::Type::LevelComplete);

        // The program should quit when receiving the exit event
        m_view->addObserver([this](const Event&){ m_running = false; }, Event::Type::ApplicationExit);
        m_controller->addObserver(std::bind(&Client::gameOver, this, std::placeholders::_1), Event::Type::GameOver);

        // Increase the score when an enemy gets killed
        m_controller->addObserver([this](const Event& event){ m_score += event.score; }, Event::Type::ScoreChanged);

        // Let the view know the current score
        Event scoreEvent{Event::Type::ScoreChanged};
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void Client::gameStateChanged(const Event& event)
    {
        m_gameState = event.gameState;

        if (m_gameState == GameState::MainMenu)
            m_score = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    void Client::gameOver(const Event& event)
    {
        m_gameState = GameState::GameOver;
        m_difficulty = 0;

        loadNextLevel(event);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
}
