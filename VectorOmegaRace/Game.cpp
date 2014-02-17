#include "Game.h"

Game::Game() :
	running(false){}

Game::~Game()
{
	OnCleanup();
}

int Game::OnInit()
{
	//Screen Size
	int screenWidth = 800;
	int screenHeight = 600;

	try
	{
		Window::Init(screenWidth, screenHeight, "Vector Omega Race in SDL2 Alpha 00.06");
	}
	catch (const std::runtime_error &error)
	{
		Window::logSDLError(std::cout, "Window OnInit error code: " + std::string(error.what()));
		Window::Quit();
		return APP_FAILED;
	}

	// Success
	return APP_OK;
}

void Game::OnCleanup()
{
	delete pGameController;
	delete pTimer;
}

int Game::OnExecute()
{
	// Initialize application.
	int status = OnInit();
	// Did Game initialize.
	if (status != APP_OK)
	{
		return status;
	}
	//************ None of your code before this point. ************
	// Instance game objects here -----------------------
	pTimer = new Timer();
	pGameController = new GameController();
	//--------------------------------------------------	
	// Initialize classes here-------------
	pGameController->Inialize();
	// Start the Timer.
	pTimer->Start();
	// ----------------------------------

	// Enter the SDL event loop.
	SDL_Event event;

	//Get it running.
	running = true;

	//Record ticks this first frame.
	m_LastTickTime = pTimer->Ticks();

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			OnEvent(&event);
		}

		OnUpdate();
		std::this_thread::yield();
		OnRender();
		std::this_thread::yield();
	}

	return status;
}

void Game::OnUpdate()
{
	// Update your game logic here
	double frame;
	int ticksThisFrame = pTimer->Ticks() - m_LastTickTime;
	frame = (double)ticksThisFrame * 0.001;

	// Game object updates here.
	if (!pTimer->Paused())
	{
		pGameController->Update(&frame);
	}
	//Record ticks this frame.
	m_LastTickTime = pTimer->Ticks();
}

void Game::OnRender()
{	
	Window::Clear();
	// Do your drawing here ----------------------------------------------

	// Render Lines here ------------------------------------------------
	pGameController->Draw();
	// Render textures here ----------------------------------------------
	// Render text here -------------------------------------------------
	
	// End your drawing --------------------------------------------------
	Window::Present();
}

void Game::OnEvent(SDL_Event* event)
{
	pGameController->OnEvent(event);

	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_p)
		{
			pGameController->OnPause(pTimer->Paused());

			if (pTimer->Paused())
				pTimer->Unpause();
			else
				pTimer->Pause();
		}

		if (event->key.keysym.sym == SDL_QUIT)
			running = false;

		if (event->key.keysym.sym == SDLK_ESCAPE)
			running = false;
	}
}
