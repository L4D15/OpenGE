#ifndef OPENGE_TIME_H
#define OPENGE_TIME_H

class Time
{
public:
	Time();
	~Time();

	void					Update();
	int						GetFPS();
	void					WaitForNextFrame();

public:
	static float			deltaTime;
	static float			time;

private:
	float					currentTime;	// Ticks at the start of the frame
	float					oldTime;		// Ticks at start of the last frame

	int						FPS;
	int						FPSCounter;
	float					FPSTimer;
};

#endif // OPENGE_TIME_H