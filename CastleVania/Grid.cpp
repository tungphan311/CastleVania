#include "Grid.h"

Grid::Grid()
{
	id = 0;

	grids.resize(2);
	for (int i = 0; i < 2; i++)
		grids.at(i).resize(25);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			grids[i][j] = new Cell();
		}
	}
}


Grid::~Grid()
{
}

void Grid::insertObjectIntoGrid(GameObject *obj)
{
	id++;
	obj->id = id;

	float left, top, right, bot;
	obj->GetBoundingBox(left, top, right, bot);

	int cell_top, cell_right, cell_left, cell_bot;
	cell_top = top / CELL_HEIGHT;
	cell_left = left / CELL_WIDTH;
	cell_right = right / CELL_WIDTH;
	cell_bot = bot / CELL_HEIGHT;

	for (int i = cell_top; i <= cell_bot; i++)
	{
		for (int j = cell_left; j <= cell_right; j++)
		{
			grids[i][j]->objects.push_back(obj);
		}
	}
}

void Grid::getListObjectPotential(vector<LPGAMEOBJECT>& listObjects)
{
	listObjects.clear();
	D3DXVECTOR3 cam = Game::GetInstance()->GetCameraPosition();
	unordered_map<int, LPGAMEOBJECT> list;

	float left, top, right, bot; 
	left = cam.x;
	top = cam.y;
	right = left + SCREEN_WIDTH;
	bot = top + SCREEN_HEIGHT;

	int cell_top, cell_right, cell_left, cell_bot;
	cell_top = top / CELL_HEIGHT;
	cell_left = left / CELL_WIDTH;
	cell_right = right / CELL_WIDTH;
	cell_bot = bot / CELL_HEIGHT;

	for (int i = cell_top; i <= cell_bot; i++)
	{
		for (int j = cell_left; j <= cell_right; j++)
		{
			for (int k = 0; k < grids[i][j]->objects.size(); k++)
			{		if (list.find(grids[i][j]->objects[k]->id) != list.end())
				continue;
		else
					list[grids[i][j]->objects[k]->id] = grids[i][j]->objects[k];
			}
		}
	}

	for (auto& obj : list)
	{
		listObjects.push_back(obj.second);
	}
}

