// ****************************************************************************
// eCamera.h
//
// 
// ****************************************************************************

#ifndef __ECAMERA_H__
#define __ECAMERA_H__

class Camera
{
public:
	Camera();
	Camera(float* x, float* y, float* zoom);
	
	float GetX();
	float GetY();
	float GetZoom();
	
	
private:
	float* m_x;
	float* m_y;
	float* m_zoom;
};

class Camerable
{
public:
	virtual Camera* GetCamera() = 0;
};

#endif
