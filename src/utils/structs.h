#define PI 3.14159265358979323846
#define PI2 PI / 2.0
#define PI3 3 * PI / 2.0
#define DEGREE (PI / 180.0)
#define WIDTH 800
#define HEIGHT 600
#define FOV (60 * DEGREE)
#define NUM_RAYS 100
#define RAY_WIDTH (WIDTH / NUM_RAYS)

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
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 2, 0, 1,
		1, 0, 2, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};
};