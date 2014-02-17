#include "GameController.h"

void GameController::Update(double *Frame)
{
	pTheBorders->Update();
	pThePlayer->Update(Frame);
	pTheEnemyController->Update(Frame);
	pFighter->SetPlayerLocation(&pThePlayer->GetLocation());
	pLeader->SetPlayerLocation(&pThePlayer->GetLocation());
	pStatus->SetScore(&m_Score);

	if (pThePlayer->GetActive())
	{
		for (int line = 0; line < 4; line++)
		{
			if (pThePlayer->GetInsideLineHit(&line))
				pTheBorders->SetInsideLineHit(&line);

			if (pFighter->GetActive())
			{
				if (pFighter->GetInsideLineHit(&line))
					pTheBorders->SetInsideLineHit(&line);
			}
		}

		for (int line = 0; line < 8; line++)
		{
			if (pThePlayer->GetOutsideLineHit(&line))
				pTheBorders->SetOutsideLineHit(&line);

			if (pFighter->GetActive())
			{
				if (pFighter->GetOutsideLineHit(&line))
					pTheBorders->SetOutsideLineHit(&line);
			}
		}
	}

	CheckCollisions();

	if (m_EndOfWave)
	{
		if (!pTheEnemyController->CheckExploding())
		{
			SpawnNewWave(pTheEnemyController->NewWave());
			m_EndOfWave = false;
		}
	}
}

void GameController::Draw(void)
{
	pThePlayer->Draw();
	pTheEnemyController->Draw();
	pTheBorders->Draw();
	pStatus->Draw();
}

void GameController::NewGame(void)
{
	pThePlayer->NewGame();
	pStatus->NewGame();
	SpawnNewWave(pTheEnemyController->NewGame());
	m_Score = 0;
	m_PlayerShips = 4;
	pStatus->SetShip(&m_PlayerShips);
	m_EndOfWave = false;
}

void GameController::OnEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYUP:
		if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT)
		{
			pThePlayer->SetTurnLeft(&False);
		}

		if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT)
		{
			pThePlayer->SetTurnRight(&False);
		}

		if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_UP)
		{
			pThePlayer->SetThrust(&False);
		}
		break;

	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT)
		{
			pThePlayer->SetTurnLeft(&True);
		}

		if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT)
		{
			pThePlayer->SetTurnRight(&True);
		}

		if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_UP)
		{
			pThePlayer->SetThrust(&True);
		}

		if (event->key.keysym.sym == SDLK_DOWN)
		{
		}

		if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_LCTRL)
		{
			pThePlayer->FireButtonPressed();
		}

		if (event->key.keysym.sym == SDLK_RCTRL)
		{

		}

		if (event->key.keysym.sym == SDLK_n)
		{
			NewGame();
		}

	default:
		break;
	}
}

void GameController::OnPause(bool paused)
{
	if (paused)
	{
		pTheEnemyController->TimerUnpause();
		pThePlayer->TimerUnpause();		
	}
	else
	{
		pTheEnemyController->TimerPause();
		pThePlayer->TimerPause();
	}
}

void GameController::Inialize(void)
{
	// Initialize borders.
	pTheBorders->Initialize();
	pThePlayer->SetInsideBorder(&pTheBorders->GetInsideBorder());
	pTheEnemyController->SetInisdeBorder(&pTheBorders->GetInsideBorder());
	pFighter = pTheEnemyController->GetFighterPointer();
	pFollower = pTheEnemyController->GetFollowPointer();
	pLeader = pTheEnemyController->GetLeadPointer();
	pStatus->Initilize();

	Mix_VolumeChunk(p_EnemyHitSound, MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(p_LeadEnemyHitSound, MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(p_FollowEnemyHitSound, MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(p_FighterHitSound, MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(p_MineHitSound, MIX_MAX_VOLUME / 5);
	Mix_VolumeChunk(p_PlayerHitSound, MIX_MAX_VOLUME / 5);
}

GameController::GameController(void)
{
	pThePlayer = new Player();
	pTheBorders = new Borders();
	pTheEnemyController = new EnemyController();
	pStatus = new StatusDisplay();
	m_Score = 0;
	m_PlayerShips = 0;
	m_EndOfWave = false;

	p_EnemyHitSound = Mix_LoadWAV("EnemyHit.wav");
	p_LeadEnemyHitSound = Mix_LoadWAV("LeadEnemyHit.wav");
	p_FollowEnemyHitSound = Mix_LoadWAV("FollowerHit.wav");
	p_FighterHitSound = Mix_LoadWAV("FighterHit.wav");
	p_MineHitSound = Mix_LoadWAV("MineHit.wav");
	p_PlayerHitSound = Mix_LoadWAV("PlayerHit.wav");
}

GameController::~GameController(void)
{
	pThePlayer = nullptr;
	pTheBorders = nullptr;
	pTheEnemyController = nullptr;
	pStatus = nullptr;

	delete pThePlayer;
	delete pTheBorders;
	delete pTheEnemyController;
	delete pStatus;

	p_EnemyHitSound = nullptr;
	p_FighterHitSound = nullptr;
	p_FollowEnemyHitSound = nullptr;
	p_LeadEnemyHitSound = nullptr;
	p_MineHitSound = nullptr;
	p_PlayerHitSound = nullptr;

	delete p_EnemyHitSound;
	delete p_FighterHitSound;
	delete p_FollowEnemyHitSound;
	delete p_LeadEnemyHitSound;
	delete p_MineHitSound;
	delete p_PlayerHitSound;

	pFighter = nullptr;
	pFollower = nullptr;
	pLeader = nullptr;

	delete pFighter;
	delete pFollower;
	delete pLeader;
}

void GameController::CheckCollisions(void)
{
	for (int shot = 0; shot < 4; shot++)
	{
		if (pThePlayer->GetShotActive(&shot))
		{
			if (DoesPlayerShotEnemy(shot))
			{
				std::printf("Player shot Drone enemy. ");
				Mix_PlayChannel(-1, p_EnemyHitSound, 0);
				m_Score += 1000;
			}

			if (DoesPlayerShootLeadEnemy(shot))
			{
				std::printf("Player shot Lead enemy. ");
				Mix_PlayChannel(-1, p_LeadEnemyHitSound, 0);
				m_Score += 1500;
			}

			if (DoesPlayerShootFollowEnemy(shot))
			{
				std::printf("Player shot Follow enemy. ");
				Mix_PlayChannel(-1, p_FollowEnemyHitSound, 0);
				m_Score += 1500;
			}

			if (DoesPlayerShootFighter(shot))
			{
				std::printf("Player shot Fighter enemy. ");
				Mix_PlayChannel(-1, p_FighterHitSound, 0);
				m_Score += 2500;
			}

			if (DoesPlayerShootFollowMine(shot))
			{
				std::printf("Player shot Follower Mine. ");
				Mix_PlayChannel(-1, p_MineHitSound, 0);
				m_Score += 350;
			}

			if (DoesPlayerShootFighterMine(shot))
			{
				std::printf("Player shot Fighter Mine. ");
				Mix_PlayChannel(-1, p_MineHitSound, 0);
				m_Score += 500;
			}
		}		
	}

	if (pThePlayer->GetActive())
	{
		for (int ship = 0; ship < pTheEnemyController->GetEnemyCount(); ship++)
		{
			if (pTheEnemyController->GetEnemyActive(&ship))
			{
				if (DoesEnemyCollideWithPlayer(ship))
				{
					std::printf("Player collided with Drone. \n");
					Mix_PlayChannel(-1, p_PlayerHitSound, 0);
				}
			}
		}

		if (pLeader->GetActive())
		{
			if (DoesLeadCollideWithPlayer())
			{
				std::printf("Player collided with Shooter. \n");
				Mix_PlayChannel(-1, p_PlayerHitSound, 0);
			}
		}

		if (pFollower->GetActive())
		{
			if (DoesFollowCollideWithPlayer())
			{
				std::printf("Player collided with Mine Layer. \n");
				Mix_PlayChannel(-1, p_PlayerHitSound, 0);
			}
		}

		if (pFighter->GetActive())
		{
			if (DoesFighterCollideWithPlayer())
			{
				std::printf("Player collided with Fighter. \n");
				Mix_PlayChannel(-1, p_PlayerHitSound, 0);
			}
		}

		if (pFollower->GetMineCount() > 0)
		{
			for (int mine = 0; mine < pFollower->GetMineCount(); mine++)
			{
				if (pFollower->GetMineActive(&mine))
				{
					if (DoesFollowMineHitPalyer(mine))
					{
						std::printf("Player collided with Mine from mine layer. \n");
						Mix_PlayChannel(-1, p_PlayerHitSound, 0);
					}
				}
			}
		}

		if (pFighter->GetMineCount() > 0)
		{
			for (int mine = 0; mine < pFighter->GetMineCount(); mine++)
			{
				if (pFighter->GetMineActive(&mine))
				{
					if (DoesFighterMineHitPlayer(mine))
					{
						std::printf("Player collided with Mine from Fighter. \n");
						Mix_PlayChannel(-1, p_PlayerHitSound, 0);
					}
				}
			}
		}

		if (pLeader->GetShotActive())
		{
			if (DoesLeadShootPlayer())
			{
				std::printf("Player collided with shot from Lead Ship. \n");
				Mix_PlayChannel(-1, p_PlayerHitSound, 0);
			}
		}

		if (pFighter->GetShotActive())
		{
			if (DoesFighterShootPlayer())
			{
				std::printf("Player collided with Shot from Fighter. \n");
				Mix_PlayChannel(-1, p_PlayerHitSound, 0);
			}
		}
	}
}

bool GameController::DoesPlayerShotEnemy(int shot)
{
	for (int ship = 0; ship < pTheEnemyController->GetEnemyCount(); ship++)
	{
		if (pTheEnemyController->GetEnemyActive(&ship))
		{
			// Get radius because it wont work inside of other function for unknown reason.
			float radius = pTheEnemyController->GetEnemyRadius();

			if (pThePlayer->GetShotCircle(&pTheEnemyController->GetEnemyLocaiton(&ship), &radius, &shot))
			{
				pTheEnemyController->EnemyHit(&ship);
				pThePlayer->SetShotActive(&shot, &False);
				return true;
			}
		}
	}

	return false;
}

bool GameController::DoesPlayerShootLeadEnemy(int shot)
{
	if (pLeader->GetActive())
	{
		float radius = pLeader->GetRadius();

		if (pThePlayer->GetShotCircle(&pLeader->GetLocation(), &radius, &shot))
		{
			pTheEnemyController->LeadEnemyHit();
			pThePlayer->SetShotActive(&shot, &False);

			if (pTheEnemyController->CheckEndOfWave())
			{				
				m_EndOfWave = true;				
			}

			return true;
		}
	}

	return false;
}

bool GameController::DoesPlayerShootFollowEnemy(int shot)
{
	if (pFollower->GetActive())
	{
		float radius = pFollower->GetRadius();

		if (pThePlayer->GetShotCircle(&pFollower->GetLocation(), &radius, &shot))
		{
			pTheEnemyController->FollowEnemyHit();
			pThePlayer->SetShotActive(&shot, &False);
			return true;
		}
	}

	return false;
}

bool GameController::DoesPlayerShootFighter(int shot)
{
	if (pFighter->GetActive())
	{
		float radius = pFighter->GetRadius();

		if (pThePlayer->GetShotCircle(&pFighter->GetLocation(), &radius, &shot))
		{
			pFighter->Explode();
			pThePlayer->SetShotActive(&shot, &False);

			if (pTheEnemyController->CheckEndOfWave())
			{				
				m_EndOfWave = true;				
			}

			return true;
		}
	}

	return false;
}

bool GameController::DoesPlayerShootFollowMine(int shot)
{
	if (pFollower->GetMineCount() > 0)
	{
		float mineRadius = pFollower->GetMineRadius();

		for (int mine = 0; mine < pFollower->GetMineCount(); mine++)
		{
			if (pFollower->GetMineActive(&mine))
			{
				if (pThePlayer->GetShotCircle(&pFollower->GetMineLocaiton(&mine), &mineRadius, &shot))
				{
					pFollower->MineHit(&mine);
					pThePlayer->SetShotActive(&shot, &False);
					return true;
				}
			}
		}
	}

	return false;
}

bool GameController::DoesPlayerShootFighterMine(int shot)
{
	int mineCount = pFighter->GetMineCount();

	if (mineCount > 0)
	{
		float mineRadius = pFighter->GetMineRadius();

		for (int mine = 0; mine < mineCount; mine++)
		{
			if (pFighter->GetMineActive(&mine))
			{
				if (pThePlayer->GetShotCircle(&pFighter->GetMineLocaiton(&mine), &mineRadius, &shot))
				{
					pFighter->MineHit(&mine);
					pThePlayer->SetShotActive(&shot, &False);
					return true;
				}
			}
		}
	}

	return false;
}

bool GameController::DoesEnemyCollideWithPlayer(int ship)
{
	float radius = pTheEnemyController->GetEnemyRadius();

	if (pThePlayer->CirclesIntersect(&pTheEnemyController->GetEnemyLocaiton(&ship), &radius))
	{
		pTheEnemyController->EnemyHit(&ship);
		
		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesLeadCollideWithPlayer(void)
{
	float radius = pLeader->GetRadius();

	if (pThePlayer->CirclesIntersect(&pLeader->GetLocation(), &radius))
	{
		pTheEnemyController->LeadEnemyHit();

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesFollowCollideWithPlayer(void)
{
	float radius = pFollower->GetRadius();

	if (pThePlayer->CirclesIntersect(&pFollower->GetLocation(), &radius))
	{
		pTheEnemyController->FollowEnemyHit();

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesFighterCollideWithPlayer(void)
{
	float radius = pFighter->GetRadius();

	if (pThePlayer->CirclesIntersect(&pFighter->GetLocation(), &radius))
	{
		pFighter->Explode();

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesFollowMineHitPalyer(int mine)
{
	float radius = pFollower->GetMineRadius();

	if (pThePlayer->CirclesIntersect(&pFollower->GetMineLocaiton(&mine), &radius))
	{
		pFollower->MineHit(&mine);

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesFighterMineHitPlayer(int mine)
{
	float radius = pFighter->GetMineRadius();

	if (pThePlayer->CirclesIntersect(&pFighter->GetMineLocaiton(&mine), &radius))
	{
		pFighter->MineHit(&mine);

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesLeadShootPlayer(void)
{
	float radius = pLeader->GetShotRadius();

	if (pThePlayer->CirclesIntersect(&pLeader->GetShotLocation(), &radius))
	{
		pLeader->ShotHitTarget();

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

bool GameController::DoesFighterShootPlayer(void)
{
	float radius = pFighter->GetShotRadius();

	if (pThePlayer->CirclesIntersect(&pFighter->GetShotLocation(), &radius))
	{
		pFighter->ShotHitTarget();

		if (PlayerHit())
			SpawnNewWave(pTheEnemyController->RestartWave());

		return true;
	}

	return false;
}

void GameController::SpawnNewWave(int ships)
{
	bool rightSide;	

	if (Window::Random(0, 1))
		rightSide = true;
	else
		rightSide = false;

	pThePlayer->Spawn(&rightSide);
	pTheEnemyController->SpawnNewWave(&rightSide, &ships);
}

bool GameController::PlayerHit(void)
{
	m_PlayerShips--;

	if (m_PlayerShips > 0)
	{
		pStatus->SetShip(&m_PlayerShips);
		return true;
	}
	else
	{
		pThePlayer->SetActive(&False);
		pStatus->SetShip(&m_PlayerShips);
	}

	return false;
}
