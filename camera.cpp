#include "camera.h"
#include <stdio.h>
void Camera2D::init(int x,int y)
{
	posX = x;
	posY =y;
}
void Camera2D::update(int x, int y)
{
	posX = x;
	posY = y;
}
void Camera2D::printPos()
{
	printf("Pos x: %i, Pos y: %i\n",posX, posY);
}	
