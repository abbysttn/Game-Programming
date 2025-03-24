#include "game.h"

#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"

#include <iostream>

Game* Game::sm_pInstance = 0;

Game& Game::GetInstance()
{
    if (sm_pInstance == 0) {
        sm_pInstance = new Game();
    }

    return (*sm_pInstance);
}

void Game::DestroyInstance() {
    delete sm_pInstance;
    sm_pInstance = 0;
}

Game::Game() : m_pRenderer(0), m_bLooping(true) {

}

Game::~Game() {
    delete m_pRenderer;
    m_pRenderer = 0;
}

void Game::Quit() {
    m_bLooping = false;
}

bool Game::Initialise() {
    int bbWidth = 1500;
    int bbHeight = 900;

    m_pRenderer = new Renderer();
    if (!m_pRenderer->Initialise(true, bbWidth, bbHeight)) {
        LogManager::GetInstance().Log("Renderer failed to initialise!");
        return false;
    }

    bbWidth = m_pRenderer->GetWidth();
    bbHeight = m_pRenderer->GetHeight();

    m_iLastTime = SDL_GetPerformanceCounter();

    m_pRenderer->SetClearColour(0, 255, 255);

    m_pCheckerboard1 = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");
    m_pCheckerboard2 = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");
    m_pCheckerboard3 = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");
    m_pCheckerboard4 = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");
    m_pCheckerboard5 = m_pRenderer->CreateSprite("..\\assets\\board8x8.png");

    int spriteW = m_pCheckerboard1->GetWidth();
    int spriteH = m_pCheckerboard1->GetHeight();


    //top left corner
    m_pCheckerboard1->SetX(spriteW / 2);
    m_pCheckerboard1->SetY(spriteH / 2);


    //bottom left corner
  
    m_pCheckerboard2->SetX(spriteW / 2);
    m_pCheckerboard2->SetY(bbHeight - (spriteH / 2));
    m_pCheckerboard2->SetBlueTint(1.0f);
    m_pCheckerboard2->SetGreenTint(0.0f);
    m_pCheckerboard2->SetRedTint(0.0f);
    

    //bottom right corner
    m_pCheckerboard3->SetX(bbWidth - (spriteW / 2));
    m_pCheckerboard3->SetY(bbHeight - (spriteH / 2));
    m_pCheckerboard3->SetBlueTint(0.0f);
    m_pCheckerboard3->SetGreenTint(1.0f);
    m_pCheckerboard3->SetRedTint(0.0f);

    //top right corner
    m_pCheckerboard4->SetX(bbWidth - (spriteW / 2));
    m_pCheckerboard4->SetY(spriteH / 2);
    m_pCheckerboard4->SetBlueTint(0.0f);
    m_pCheckerboard4->SetGreenTint(0.0f);
    m_pCheckerboard4->SetRedTint(1.0f);

    //center
    m_pCheckerboard5->SetX(bbWidth / 2);
    m_pCheckerboard5->SetY(bbHeight / 2);
    m_pCheckerboard5->SetAngle(45.0f);


    return true;
}

bool Game::DoGameLoop() {
    const float stepSize = 1.0f / 60.0f;
    // TODO: Process input here!
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        continue;
    }
    if (m_bLooping)
    {
        Uint64 current = SDL_GetPerformanceCounter();
        float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        m_iLastTime = current;
        m_fExecutionTime += deltaTime;
        Process(deltaTime);
#ifdef USE_LAG
        m_fLag += deltaTime;
        int innerLag = 0;
        while (m_fLag >= stepSize)
        {
            Process(stepSize);
            m_fLag -= stepSize;
            ++m_iUpdateCount;
            ++innerLag;
        }
#endif //USE_LAG
        Draw(*m_pRenderer);
    }
    return m_bLooping;
}

void Game::Process(float deltaTime)
{
    ProcessFrameCounting(deltaTime);

    m_pCheckerboard1->Process(deltaTime);
    m_pCheckerboard2->Process(deltaTime);
    m_pCheckerboard3->Process(deltaTime);
    m_pCheckerboard4->Process(deltaTime);
    m_pCheckerboard5->Process(deltaTime);
    // TODO: Add game objects to process here!
}

void Game::Draw(Renderer& renderer)
{
    ++m_iFrameCount;
    renderer.Clear();
    // TODO: Add game objects to draw here!
    m_pCheckerboard1->Draw(renderer);
    m_pCheckerboard2->Draw(renderer);
    m_pCheckerboard3->Draw(renderer);
    m_pCheckerboard4->Draw(renderer);
    m_pCheckerboard5->Draw(renderer);

    renderer.Present();
}
void
Game::ProcessFrameCounting(float deltaTime)
{
    // Count total simulation time elapsed:
    m_fElapsedSeconds += deltaTime;
    // Frame Counter:
    if (m_fElapsedSeconds > 1.0f)
    {
        m_fElapsedSeconds -= 1.0f;
        m_iFPS = m_iFrameCount;
        m_iFrameCount = 0;
    }
}
