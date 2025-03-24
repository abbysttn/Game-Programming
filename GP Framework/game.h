#ifndef __GAME_H
#define __GAME_H

class Renderer;

class Sprite;

class Game {
	//member methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

protected:
	void Process(float deltaTime);
	void Draw(Renderer& renderer);

	void ProcessFrameCounting(float deltaTime);

private:
	Game();
	~Game();
	Game(const Game& game);
	Game& operator=(const Game& game);

	//Member data:

public:

protected:
	static Game* sm_pInstance;
	Renderer* m_pRenderer;
	Sprite* m_pCheckerboard1;
	Sprite* m_pCheckerboard2;
	Sprite* m_pCheckerboard3;
	Sprite* m_pCheckerboard4;
	Sprite* m_pCheckerboard5;

	__int64 m_iLastTime;
	float m_fExecutionTime;
	float m_fElapsedSeconds;
	int m_iFrameCount;
	int m_iFPS;

#ifdef USE_LAG
	float m_fLag;
	int m_iUpdateCount;
#endif // USE_LAG

	bool m_bLooping;

private:
};

#endif //__GAME_H