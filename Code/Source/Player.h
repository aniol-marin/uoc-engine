#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"
#include <PxPhysicsAPI.h>

class CFPSCameraController;

class CPlayer 
{
private:
	XMFLOAT3				m_Position;
	float					m_Speed;
	float					m_FastSpeed;
	float					m_VerticalSpeed;
	float					m_VerticalSpeedJump;

	CFPSCameraController	*m_FPSCameraController;
	physx::PxController		*m_Controller;
public:
	CPlayer();
	virtual ~CPlayer();
	
	void Update(float ElapsedTime);
	void Move(float Strafe, float Forward, bool Fast, float ElapsedTime);
	void Jump();
};

#endif
