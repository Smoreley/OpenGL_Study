#pragma once
#include "stdafx.h"

class Timer
{
public:
	Timer();
	~Timer();

	// Get current time
	double getTime();

	void updateTime();
	void incrementTime() { currentTime += timeIncrement; }

	void reset() { currentTime = 0; previousTime = 0; deltaTime = 0; }	// Reset the timer

	// Set
	void setTimeIncrement(double timeIncrement) { this->timeIncrement = timeIncrement; }
	void setUpdateByIncrement(const bool ubi) { updateByIncrement = ubi; }

	// Get
	const double getDelta() { return deltaTime;  }

private:
	// When the timer started
	double startTime;

	double currentTime;
	double previousTime;
	double deltaTime;

	double timeIncrement;	// How much to increment time by
	bool updateByIncrement;

	float speedfactor;	// How fast the timer is ticking by

	bool paused;		// Is the timer paused
	

};

Timer::Timer()
{
	startTime = glfwGetTime();
	updateByIncrement = false;
}

Timer::~Timer()
{
}

double Timer::getTime() {
	return currentTime;
}

void Timer::updateTime() {
	if (!paused) {
		previousTime = currentTime;

		if (updateByIncrement)
			currentTime += timeIncrement;
		else
			currentTime = glfwGetTime();

		deltaTime = currentTime - previousTime;
	}
}