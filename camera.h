#ifndef _CAMERRA2D_
#define _CAMERA2D_
class Camera2D
{
public:
	void init(int x, int y);
	void update(int x, int y);
	inline int getPosX(){return posX;}
	inline int getPosY(){return posY;}
	void printPos();	
private:
	int posX;
	int posY;
};
#endif
