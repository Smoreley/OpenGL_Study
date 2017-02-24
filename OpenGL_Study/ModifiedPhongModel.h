#pragma once
#include "Progbase.h"

class ModifiedPhongModel : public Progbase {
private:

public:
	int start();
	int end();
	int render(double dt);
};