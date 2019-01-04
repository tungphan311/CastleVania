#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"
#include "Define.h"

using namespace std;

class TileMap
{
	int mapWidth;			// chiều rộng của map
	int mapHeight;			// chiều cao của map

	int rows;				// số hàng của map
	int columns;			// số cột của map

	int tileWidth;			// chiều rộng một tile
	int tileHeight;			// chiều cao một tile

	LPCWSTR texFilePath;
	LPCWSTR dataFilePath;

	int ID;					// ID của tile map, dùng để tạo class quản lí TileMaps sau này ...

public:
	vector<vector<int>> matrix;		// ma trận lưu dữ liệu map

	Sprites * sprites;		// lưu các tile


	TileMap(int ID, LPCWSTR textFilePath, LPCWSTR dataFilePath, int mapWidth, int mapHeight, int tileWidth, int tileHeight);

	void LoadSpritesFromFile();		// load tất cả các block tile lưu vào sprites
	void LoadMatrixFromFile();		// load ma trận dữ liệu map 

	void Draw(D3DXVECTOR3 camPosition);	// vẽ tất cả các tile nằm trong camera

	int GetMapWidth() { return mapWidth; }

};


