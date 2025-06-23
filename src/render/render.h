void Display();

void Init();

void DrawPlayer(int windowWidth, int windowHeight);

void DrawMap(int windowWidth, int windowHeight);

void Render3D(int rayIndex, float distance, float rayAngle, int wallType, bool shading, int windowWidth, int windowHeight);

void CastRay(int windowWidth, int windowHeight);

float Distance(float startX, float startY, float endX, float endY, float angle);