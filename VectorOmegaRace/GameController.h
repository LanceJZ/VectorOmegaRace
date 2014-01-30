#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Borders.h"
#include "Player.h"
#include "EnemyController.h"
#include "StatusDisplay.h"

class GameController : Common
{
private:
	Fighter *pFighter = nullptr;
	FollowEnemy *pFollower = nullptr;
	LeadEnemy *pLeader = nullptr;

	Player *pThePlayer = nullptr;
	Borders *pTheBorders = nullptr;
	EnemyController *pTheEnemyController = nullptr;
	StatusDisplay *pStatus = nullptr;

	Mix_Chunk *p_EnemyHitSound = nullptr;
	Mix_Chunk *p_LeadEnemyHitSound = nullptr;
	Mix_Chunk *p_FollowEnemyHitSound = nullptr;
	Mix_Chunk *p_FighterHitSound = nullptr;
	Mix_Chunk *p_MineHitSound = nullptr;
	Mix_Chunk *p_PlayerHitSound = nullptr;

	bool m_EndOfWave;
	int m_Score;
	int m_PlayerShips;

	void NewGame(void);
	void CheckCollisions(void);
	void SpawnNewWave(int ships);
	bool PlayerHit(void);
	bool DoesPlayerShotEnemy(int shot);
	bool DoesPlayerShootLeadEnemy(int shot);
	bool DoesPlayerShootFollowEnemy(int shot);
	bool DoesPlayerShootFighter(int shot);
	bool DoesPlayerShootFollowMine(int shot);
	bool DoesPlayerShootFighterMine(int shot);
	bool DoesEnemyCollideWithPlayer(int ship);
	bool DoesLeadCollideWithPlayer(void);
	bool DoesFollowCollideWithPlayer(void);
	bool DoesFighterCollideWithPlayer(void);
	bool DoesFollowMineHitPalyer(int mine);
	bool DoesFighterMineHitPlayer(int mine);
	bool DoesLeadShootPlayer(void);
	bool DoesFighterShootPlayer(void);

public:
	GameController(void);
	~GameController(void);

	void Update(double *Frame);
	void Draw(void);
	void OnEvent(SDL_Event* event);
	void OnPause(bool paused);
	void Inialize(void);
};

#endif