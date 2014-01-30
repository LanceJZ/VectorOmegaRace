#include "Collision.h"

void Collision::Update(void)
{

	if (pPlayer->GetActive())
	{
		if (pPlayer->GetHit())
		{
			if (!pPlayer->GetExplosionOn())
			{
				if (SafeForPlayer())
				{
					pPlayer->Spawn();
				}
			}
		}
		else
		{
			CheckUFO(); //Collisions that do not involve the rocks, for player.
		}
	}
	else
	{
		bool shotsDone = true;
		
		for (int shot = 0; shot < 4; shot++)
		{
			if (pPlayer->GetShotActive(shot))
				shotsDone = false;
		}

		if (shotsDone)
			pHUD->SetGameOver(true);
	}

	CheckLargeRocks();
	CheckMedRocks();
	CheckSmallRocks();
	CheckPlayer();
	pHUD->Update();
}

void Collision::Draw()
{
	pHUD->Draw();
}

void Collision::NewGame(void)
{
	pHUD->NewGame();
	pPlayer->NewGame();
	pPlayer->Spawn();
}

void Collision::RightArrowKey(bool KeyDown)
{
	pHUD->RightArrowKey(KeyDown);
}

void Collision::LeftArrowKey(bool KeyDown)
{
	pHUD->LeftArrowKey(KeyDown);
}

void Collision::DownArrowKey(bool KeyDown)
{
	pHUD->DownArrowKey(KeyDown);
}

void Collision::UpArrowKey(bool KeyDown)
{
	pHUD->UpArrowKey(KeyDown);
}

void Collision::FireKey(bool KeyDown)
{
	pHUD->FireKey(KeyDown);
}

Collision::Collision(Player *player)
{
	pPlayer = player;

	pHUD = new HUD();

	playerShotCount = pPlayer->GetNumberOfShots();
	playerShotRadius = pPlayer->GetShotRadius();
}


Collision::~Collision()
{
}

bool Collision::CirclesIntersect(Vector2i locationOne, Vector2i locationTwo, int radiusOne, int radiusTwo)
{
	float distance = sqrt((locationOne.x - locationTwo.x) * (locationOne.x - locationTwo.x) +
		(locationOne.y - locationTwo.y) * (locationOne.y - locationTwo.y));

	if (distance < radiusOne + radiusTwo)
	{
		return true;
	}

	return false;
}