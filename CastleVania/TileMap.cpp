#include "TileMap.h"


TileMap::TileMap(int ID, LPCWSTR texFilePath, LPCWSTR dataFilePath, int mapWidth, int mapHeight, int tileWidth, int tileHeight)
{
	this->ID = ID;
	this->texFilePath = texFilePath;
	this->dataFilePath = dataFilePath;

	sprites = Sprites::GetInstance();

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	rows = mapHeight / tileHeight;
	columns = mapWidth / tileWidth;
}

void TileMap::LoadSpritesFromFile()
{
	Textures * texture = Textures::GetInstance();

	texture->Add(ID, texFilePath, D3DCOLOR_XRGB(255, 255, 255));


	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(ID);

	// lấy thông tin về kích thước của texture
	D3DSURFACE_DESC desc;
	texTileMap->GetLevelDesc(0, &desc);

	// tính toán số hàng, số cột cần thiết để load tile 
	int _rows = desc.Height / tileHeight;
	int _nums= desc.Width / tileWidth;


	// thực hiện lưu danh sách các tile vô sprites theo thứ tự id_sprite
	int spriteID = 1;

	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _nums; j++)
		{
			sprites->Add(spriteID, tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1), texTileMap);
			spriteID += 1;
		}
	}
}

void TileMap::Draw(D3DXVECTOR3 camPosition)
{
	int startColumn = (int)camPosition.x / tileWidth;
	int endColumn = (int)(camPosition.x + SCREEN_WIDTH) / tileHeight;

	for (int i = 0; i < rows; i++)
	{
		for (int j = startColumn; j <= endColumn; j++)
		{
			float x = tileWidth * (j - startColumn) + camPosition.x - (int)camPosition.x % tileWidth;
			float y = tileHeight * i;

			sprites->Get(matrix[i][j])->Draw(-1, x, y + 80);
		}
	}
}

void TileMap::LoadMatrixFromFile()
{
	ifstream file;
	file.open(dataFilePath, ios::in);

	if (file.is_open()) {
		string line = "";
		while (getline(file, line))
		{
			//cout << line << "\n";
			string str = "";
			vector<int> vec;
			for (int i = 0; i < line.size(); i++) {

				if (line[i] == ',') {
					int k;
					istringstream(str) >> k;
					//cout << k << " ";
					vec.push_back(k);
					str = "";
				}
				else if (line[i] == ' ')
					continue;
				else
					str += line[i];
			}
			matrix.push_back(vec);
			//cout << endl;
		}
		file.close();
	}
}