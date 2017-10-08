#include"Tile.h"
#include"GameMananger.h"

Tile::Tile()
{
	Object::Object();
	m_HResource			= GameManager::call()->TM.GetpResource();
	CurTile.TileSize		= MakePoint(0.f, 0.f);
	CurTile.TileSrcPos	= MakePoint(0.f, 0.f);
	WallOnTop			= false;
}

void Tile::ChangeTile(TileStruct type)
{
	CurTile = type;
}

void Tile::render(int zth, int xth, int yth)
{
	GameManager::call()->SetNumberTag++;
	NumberTag = GameManager::call()->SetNumberTag;

	SetTileHeight(zth);
	SetTileXth(xth);
	SetTileYth(yth);
	CGPoint pos = GetPosition();
	CGPoint scroll = GameManager::call()->ScrollOffSet;

	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;
	SelectObject(m, m_HResource);

	pos.x = xth * CurTile.TileSize.x / 2;
	pos.y = yth * CurTile.TileSize.y / 2;
	SetPosition(pos);

	CGPoint _isoPos = GetIsoPos();

	_isoPos.x = pos.x - pos.y;
	_isoPos.y = (pos.x + pos.y) / 2;

	_isoPos.x += (CurTile.TileSize.x*9)+scroll.x;
	_isoPos.y += (CurTile.TileSize.y)+scroll.y;
	_isoPos.y -= zth * CurTile.TileSize.y/2;

	SetIsoPos(_isoPos);

	m_OffSet.y = CurTile.TileSize.y / 2;
	_isoPos.y += m_OffSet.y;

	TransparentBlt(b, _isoPos.x,_isoPos.y,
		CurTile.TileSize.x, CurTile.TileSize.y,
		m, 
		CurTile.TileSrcPos.x ,CurTile.TileSrcPos.y, 
		128, 128,
		RGB(255, 255, 255));
}

void Tile::render()
{
	if( !GetActive() ) return;
	
	CGPoint pos = GetPosition();
	CGPoint _isoPos = GetIsoPos();

	CGPoint scroll = GameManager::call()->ScrollOffSet;

	GameManager::call()->TM.SetIsSomethingOnTop(TileHeight, TileXth, TileYth);

	HDC b = GameManager::call()->backDC;
	HDC m = GameManager::call()->memDC;
	SelectObject(m, m_HResource);

	pos.x = TileXth * CurTile.TileSize.x / 2;
	pos.y = TileYth * CurTile.TileSize.y / 2;
	SetPosition(pos);

	_isoPos.x = pos.x - pos.y;
	_isoPos.y = (pos.x + pos.y) / 2;

	_isoPos.x += (CurTile.TileSize.x*9)+scroll.x;
	_isoPos.y += (CurTile.TileSize.y)+scroll.y;
	_isoPos.y -= TileHeight * CurTile.TileSize.y/2;
	SetIsoPos(_isoPos);

	if(GameManager::call()->pNowRunningScene->PointExitCheck(_isoPos))
		return;

	m_OffSet.y = CurTile.TileSize.y / 2;
	_isoPos.y += m_OffSet.y;

	TransparentBlt(b, _isoPos.x,_isoPos.y,
		CurTile.TileSize.x, CurTile.TileSize.y,
		m, 
		CurTile.TileSrcPos.x ,CurTile.TileSrcPos.y, 
		128, 128,
		RGB(255, 255, 255));
}