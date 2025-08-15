#include "Game.h"

Game::~Game() {
   this->Shutdown();
}
bool Game::Init() {
    return true;
}
void Game::Update() { }
void Game::Draw() { }
void Game::Shutdown() { }
