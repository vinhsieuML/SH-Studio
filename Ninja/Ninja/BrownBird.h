#pragma once
#include "CGameObject.h"
#include"define.h"
#include"Texture.h"
class CBrownBird :
	public CGameObject
{
public:
	CBrownBird(float x, float y, int Direction);
	void LoadAni();
	void Render();
	void Update(DWORD dt);
	~CBrownBird();
};

