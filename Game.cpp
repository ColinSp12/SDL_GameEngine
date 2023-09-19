#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;                                                             // Declare a pointer to a player GameObject
GameObject* enemy;                                                              // Declare a pointer to an enemy GameObject

Game::Game()                                                                    // Constructor for the Game class
{}

Game::~Game()                                                                   // Destructor for the Game class
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;                                          // Set the fullscreen flag if requested

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)                                     // Initialize SDL
    {
        std::cout << "Subsystems Initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);     // Create an SDL window
        if (window)
        {
            std::cout << "Window Created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);                   // Create an SDL renderer
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);       // Set the renderer's draw color
            std::cout << "Renderer Created!" << std::endl;
        }
        isRunning = true;               // Set the game loop flag to true
    }
    else {
        isRunning = false;              // Unable to initialize SDL, set the game loop flag to false
    }

    // Create player and enemy GameObjects 
    player = new GameObject("assets/player.png", renderer, 0, 0);
    enemy = new GameObject("assets/enemy.png", renderer, 50, 50);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);             // Poll for an SDL event
    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;             // If the event is quitting the game, set the game loop flag to false
    default:
        break;
    }
}

void Game::update()
{
    player->Update();                  // Update the player GameObject
    enemy->Update();                   // Update the enemy GameObject
}

void Game::render()
{
    SDL_RenderClear(renderer);         // Clear the renderer

    player->Render();                  // Render the player GameObject
    enemy->Render();                   // Render the enemy GameObject

    SDL_RenderPresent(renderer);       // Present the rendered objects on the screen
}

void Game::clean()
{
    SDL_DestroyWindow(window);          // Destroy the SDL window
    SDL_DestroyRenderer(renderer);      // Destroy the SDL renderer
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl; 
}
