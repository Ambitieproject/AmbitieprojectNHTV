#include "Game.h"
#include <iostream>

int main() {
	//Get game singleton's reference but sinds there
	//hasn't been any made yet so it makes an instance
	Game* game = Game::GetInstance();

	//Run start method of game class
	game->Start();

	//while the SFML Renderwindow is not closed
	while (!Window::IsClosed) {
		//Run Update method of game class
		game->Update();
	}
}