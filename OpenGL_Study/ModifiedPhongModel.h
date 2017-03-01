#pragma once
#include "Progbase.h"

// Demo showing of the Modified-Phong Model
class ModifiedPhongModel : public Progbase {
private:

public:
	int start();
	int end();
	int render(double dt);
};