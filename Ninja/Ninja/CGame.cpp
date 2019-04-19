#include "CGame.h"
#include"debug.h"


CGame * CGame::_instance = NULL;


void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;
	D3DPRESENT_PARAMETERS d3dpp;


	ZeroMemory(&d3dpp, sizeof(d3dpp));
		
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hWnd, L"Init d3ddev errors", L"Error", MB_OK);
		return;
	}
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);
	//back = LoadSurface("NinjaGaidenMapStage3-1BG.png", NULL);
	//Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddev, &spriteHandler);
}

void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture ,int left, int top, int right, int bottom, int flipX)
{

	D3DXMATRIX matScale;
	if (flipX == 1)// Co Flip Sang X
	{
		D3DXMatrixScaling(&matScale, -1.0, 1.0, 0.0f);
		spriteHandler->SetTransform(&(matScale));
		x = -x;
	}
	else
	{
		/*D3DXMatrixScaling(&matScale, 1.0, 1.0, 0.0f);
		spriteHandler->SetTransform(&(matScale));*/
	}

	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	D3DXVECTOR3 center((right-left)/2, (bottom-top) / 2, 0);
	spriteHandler->Draw(texture, &r, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
	D3DXMatrixScaling(&matScale, 1.0, 1.0, 0.0f);
	spriteHandler->SetTransform(&(matScale));
}


//void CGame::SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float & t, float & nx, float & ny)
//{
//	float dx_entry, dx_exit, tx_entry, tx_exit;
//	float dy_entry, dy_exit, ty_entry, ty_exit;
//
//	float t_entry;
//	float t_exit;
//
//	t = -1.0f;
//	nx = ny = 0;
//
//}






CGame * CGame::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CGame();
	}
	return _instance;
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backbuffer != NULL) backbuffer->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (d3d != NULL) d3d->Release();
	if (back != NULL) back->Release();
}

LPDIRECT3DSURFACE9 CGame:: LoadSurface(const char *filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFileA(filename, &info);
	if (result != D3D_OK)
	{
		return NULL;
	}

	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&image,
		NULL
	);
	if (result != D3D_OK)
	{
		return NULL;
	}

	result = D3DXLoadSurfaceFromFileA(
		image,
		NULL,
		NULL,
		filename,
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL
	);
	if (result != D3D_OK)
	{
		return NULL;
	}
	return image;
}

