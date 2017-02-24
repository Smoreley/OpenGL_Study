#pragma once
#include "Progbase.h"

class FlyingCamera : public  Progbase {
private:

public:
	int start();
	int end();
	int render(double dt);

};