#include "BulletDebugRender.h"

void BulletDebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	drawLine(from, to, color, color);
}

void BulletDebugRender::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	//SColorf fromC;  fromC.set(fromColor[0], fromColor[1], fromColor[2], fromColor[3]);
	//SColorf toC;    toC.set(toColor[0], toColor[1], toColor[2], toColor[3]);

	//Graphics->drawLine(from, to, fromC, toC);

	std::cout << "DRAW LINE WAS CALLED" << std::endl;
}