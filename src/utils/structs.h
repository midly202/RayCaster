#define PI 3.14159265358979323846
#define PI2 PI / 2.0
#define PI3 3 * PI / 2.0
#define DEGREE (PI / 180.0)

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
		1, 0, 2, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};
};