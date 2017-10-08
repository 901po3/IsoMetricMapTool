#pragma once
#include"Object.h"

class Tile : public Object
{
private:
	TileStruct		CurTile;
	bool				WallOnTop;
public:
	Tile();
	void dealloc() {}
	
	static Tile *create()
	{
		Tile *tile = new Tile();
		return tile;
	}

	void SetWallOnTop(bool _wallOntop) {WallOnTop = _wallOntop;}
	bool	GetWallOnTop() {return WallOnTop;}
	void IncreaseTileHeight() {TileHeight++;}
	void SetIsoPos(CGPoint Ipt) { IsoPos = Ipt;}
	CGPoint GetIsoPos() { return IsoPos;}
	TileType GetCurTile() {return CurTile.typeName;}

	void ChangeTile(TileStruct type);
	void render();
	void render(int zth, int xth, int yth);
	void update(float dt) {}
};