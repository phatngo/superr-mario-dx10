#include "Map.h"
#include "Textures.h"
#include "debug.h"

CMap::CMap(int TileSetID, int TotalRowsOfMap, int TotalColumnsOfMap, int TotalRowsOfTileSet, int  TotalColumnsOfTileSet, int TotalTiles)
{
	//Tileset is the image
	
	TileSet = CTextures::GetInstance()->Get(TileSetID);
	this->TotalRowsOfMap = TotalRowsOfMap;
	this->TotalColumnsOfMap = TotalColumnsOfMap;
	this->TotalRowsOfTileSet = TotalRowsOfTileSet;
	this->TotalColumnsOfTileSet = TotalColumnsOfTileSet;
	this->TotalTiles = TotalTiles;
	TileMap = NULL;
	//DebugOut(L"CMap contructor");
}

CMap::~CMap()
{
}



void CMap::Render()
{
	int FirstColumn = 0 / TILE_WIDTH;
	int LastColumn = (int)ceil(320/TILE_WIDTH);
	if (LastColumn >= TotalColumnsOfMap)
		LastColumn = TotalColumnsOfMap - 1;

	int d = 0;
	for (int CurrentRow = 0; CurrentRow < TotalRowsOfMap; CurrentRow++)
		for (int CurrentColumn = 0; CurrentColumn <= LastColumn; CurrentColumn++)
		{
			int index = TileMap[CurrentRow][CurrentColumn];
			//DebugOut(L"index %d \n", index);
			if (index < TotalTiles)
				Tiles.at(index)->Draw((float) CurrentRow * TILE_WIDTH, (float) CurrentColumn * TILE_HEIGHT + 5);
		}
}

void CMap::SetTileMapData(int** TileMapData)
{
	TileMap = TileMapData;
}


void CMap::ExtractTileFromTileSet()
{
	for (int TileNum = 0; TileNum < TotalTiles; TileNum++)
	{
		int left = TileNum % TotalColumnsOfTileSet * TILE_WIDTH;
		int top = TileNum / TotalColumnsOfTileSet * TILE_HEIGHT;
		int right = left + TILE_WIDTH;
		int bottom = top + TILE_HEIGHT;
		//DebugOut(L"[DETAILS] left %d top %d right %d bottom %d\n", left, top, right, bottom);
		LPSPRITE NewTile = new CSprite(TileNum, left, top, right, bottom, TileSet); // get tile from tileset
		this->Tiles.push_back(NewTile);
	}
}

int CMap::GetMapWidth()
{
	return TotalColumnsOfMap * TILE_WIDTH;
}

int CMap::GetMapHeight()
{
	return TotalRowsOfMap * TILE_HEIGHT;
}
