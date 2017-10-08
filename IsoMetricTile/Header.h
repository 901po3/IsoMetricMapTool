#pragma once
#include<Windows.h>
#include<iostream>
using namespace std;
#include<tchar.h>
#include<time.h>
#include"resource.h"
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")
#include<math.h>

#define Z				4
#define ROWS				250
#define COLUMNS			250

#define TILE_WITDH		64
#define TILE_HEIGHT		64

#define INVENTORY_WIDTH	450
#define INVENTORY_HEIGHT	800

#define INVENTORY_ROWS		9
#define INVENTOTY_COLUMNS	6

#define INVENTORY_CORD_Y	45
#define SLOT_SIZE_X		65
#define SLOT_SIZE_Y		65

struct CGPoint
{
	float x;
	float y;
};


enum TileType
{
	ROW_ONE_1, ROW_ONE_2, ROW_ONE_3, ROW_ONE_4, ROW_ONE_5, ROW_ONE_6,
	ROW_TWO_1, ROW_TWO_2, ROW_TWO_3, ROW_TWO_4, ROW_TWO_5, ROW_TWO_6,
	ROW_THREE_1, ROW_THREE_2, ROW_THREE_3, ROW_THREE_4, ROW_THREE_5, ROW_THREE_6,
	ROW_FOUR_1, ROW_FOUR_2, ROW_FOUR_3, ROW_FOUR_4, ROW_FOUR_5, ROW_FOUR_6,
	ROW_FIVE_1, ROW_FIVE_2, ROW_FIVE_3, ROW_FIVE_4, ROW_FIVE_5, ROW_FIVE_6,
	ROW_SIX_1, ROW_SIX_2, ROW_SIX_3, ROW_SIX_4, ROW_SIX_5, ROW_SIX_6,
	ROW_SEVEN_1, ROW_SEVEN_2, ROW_SEVEN_3, ROW_SEVEN_4, 
	//여기서부터 오브젝트
	ROW_SEVEN_5, ROW_SEVEN_6,
	ROW_EIGHT_1, ROW_EIGHT_2, ROW_EIGHT_3, ROW_EIGHT_4, ROW_EIGHT_5, ROW_EIGHT_6,
	ROW_NINE_1, ROW_NINE_2, ROW_NINE_3, ROW_NINE_4, ROW_NINE_5 ,ROW_NINE_6
};

struct TileStruct
{	
	TileType typeName;
	CGPoint TileSrcPos;
	CGPoint TileSize;
};

CGPoint MakePoint(float x, float y);

struct VectorInfo
{
	CGPoint		vector;
	float		distance;
};

VectorInfo Distance(CGPoint p1, CGPoint p2);

int RandomRange(int min, int max);

float Clamp(float value, float min, float max);


CGPoint IsoTo2D(CGPoint pos);
CGPoint twoDToIso(CGPoint pos);

enum EnemyType
{
	WAVE_ONE_UNIT
};

struct EnemyInfo
{
	int MaxHp;
	int Dmg;
	int MoveSpeed;
	int	StadingHeight;
	CGPoint EnemySrcPos;
	CGPoint EnemySize;
};

enum ButtonType
{
	TILE_INVENTORY, SAVE, LOAD, MENU
};

struct ButtonStruct
{
	ButtonType typeName;
	CGPoint ButtonSrcPos;
	CGPoint ButtonSize;
};

struct Rect
{
	int LEFT, RIGHT, TOP, BOTTOM;
};

enum SceneList
{
	SCENE_MENU, SCENE_MAKEMAP, SCENE_SAVED
};