#pragma once
#include "GameObject.h"
#include "TileMap.h"

class Cell
{
public:
	vector<LPGAMEOBJECT> objects;
	Cell() { objects.resize(0); }
};
typedef Cell *LPCELL;

class Grid
{
public:
	int id;
	vector<vector<LPCELL>> grids;

	Grid();
	~Grid();

	void insertObjectIntoGrid(GameObject *obj);
	void getListObjectPotential(vector<LPGAMEOBJECT> &listObjects);
};

