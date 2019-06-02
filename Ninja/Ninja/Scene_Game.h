#pragma once
#include "Scene.h"
#include"Ninja.h"
#include"Camera.h"
#include"CGame.h"
#include"CGameObject.h"
#include"GameMap.h"
#include"Texture.h"
#include"Sprite.h"
#include"Sound.h"
#include"Grid.h"
#include"EffectManager.h"
#include"ItemsManager.h"
#include"CBoard.h"
class Scene_Game :
	public Scene
{
	bool isTransitionScene;
	DWORD StartTranTime;



	int State;
	CBoard *mBoard;
	EffectManager *listEffect;
	CGame * Cgame;
	Ninja * ninja;
	GameMap *gamemap;
	Grid *mGrid;
	ItemsManager * listItem;
	CCamera * mCamera = CCamera::GetInstance();
	vector<LPGAMEOBJECT> objStatic;
	vector<LPGAMEOBJECT> objDynamic;
	vector<LPGAMEOBJECT> obj;
public:
	Scene_Game(int State);
	~Scene_Game();
	void LoadResources();
	void Render();
	void Update(DWORD dt);
	void KeyState(BYTE *state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

