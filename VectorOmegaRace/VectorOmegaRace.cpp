#include "Game.h"
// ============================================================================
// [Entry-Point]
// ============================================================================
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char* argv[])
{
	Game *game;
	game = new Game();
	game->OnExecute();

	return 1;
}