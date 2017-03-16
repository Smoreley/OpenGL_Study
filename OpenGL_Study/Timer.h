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

	// Reset the timer
	void reset();

private:
	// When the timer started
	double startTime;

	double currentTime;
	double previousTime;
	double deltaTime;

	// How fast the timer is ticking by
	float speedfactor;

	// Is the timer paused
	bool paused;
	

};

Timer::Timer()
{
	startTime = glfwGetTime();
}

Timer::~Timer()
{
}

double Timer::getTime() {
	return currentTime;
}

void Timer::updateTime() {
	previousTime = currentTime;
	currentTime = glfwGetTime();
	deltaTime = currentTime - previousTime;
}