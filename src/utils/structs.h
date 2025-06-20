struct Player
{
	float posX, posY;
	float dirX, dirY, angle;
};

struct Map
{
	static const int width = 8, height = 8, size = 64;
	int map[width * height] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};
};