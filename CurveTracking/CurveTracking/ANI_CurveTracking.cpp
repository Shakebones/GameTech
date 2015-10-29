/*
 * ANI_CurveTracking.cpp
 * Xue Cui
 * Desc:
 *
 */
#include "ANI_CurveTracking.h"

CANICurveTracking::CANICurveTracking()
{
}

CANICurveTracking::CANICurveTracking(const CANICurveTracking& source)
{
}

CANICurveTracking::~CANICurveTracking()
{
	_shutdown();
}

bool 
CANICurveTracking::Init(int frequencyPerSec, VFXEpoch::Vector2Df ejectorPos, VFXEpoch::Vector2Df direction, float lifeSpan)
{
	bool result;
	result = _initialize(frequencyPerSec, ejectorPos, direction, lifeSpan);
	if (!result)
		return false;

	return true;
}

void 
CANICurveTracking::Reset()
{
}

void 
CANICurveTracking::Update(bool active, VFXEpoch::Vector2Df targetPos)
{
}

void 
CANICurveTracking::Render()
{
}

void 
CANICurveTracking::Shutdown()
{
}

/*-------------------------------- Kernels ---------------------------------------*/
bool 
CANICurveTracking::_initialize(int frequencyPerSec, VFXEpoch::Vector2Df ejectorPos, VFXEpoch::Vector2Df direction, float lifeSpan)
{
	return true;
}

void 
CANICurveTracking::_reset()
{
}

bool 
CANICurveTracking::_losingTarget(float thetaCur, float thetaPrev)
{
	return (thetaCur - thetaPrev) > m_angularChangeLimitation ? true : false;
}

bool 
CANICurveTracking::_isHit(VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos, float blastRadius)
{
	float length = (targetPos - missilePos).length();
	return length <= blastRadius ? true : false;
}

bool 
CANICurveTracking::_isCollinear(VFXEpoch::Vector2Df missileDir, VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos)
{
	VFXEpoch::SIDE side;

	VFXEpoch::Vector2Df targetVec = targetPos - missilePos;
	targetVec.normalize();
	missileDir.normalize();

	targetVec.m_x = (float)((int)(targetVec.m_x * 100)) / 100;
	targetVec.m_y = (float)((int)(targetVec.m_y * 100)) / 100;
	missileDir.m_x = (float)((int)(missileDir.m_x * 100)) / 100;
	missileDir.m_y = (float)((int)(missileDir.m_y * 100)) / 100;

	side = VFXEpoch::Vector2Df::isRightLeft(missileDir, targetVec);
	if (VFXEpoch::SIDE::EQUAL == side)
		return true;
	else
		return false;
}

bool 
CANICurveTracking::_isCollinear_same_direction(VFXEpoch::Vector2Df missileDir, VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos)
{
	VFXEpoch::SIDE side;

	VFXEpoch::Vector2Df targetVec = targetPos - missilePos;
	targetVec.normalize();
	missileDir.normalize();

	targetVec.m_x = (float)((int)(targetVec.m_x * 100)) / 100;
	targetVec.m_y = (float)((int)(targetVec.m_y * 100)) / 100;
	missileDir.m_x = (float)((int)(missileDir.m_x * 100)) / 100;
	missileDir.m_y = (float)((int)(missileDir.m_y * 100)) / 100;

	side = VFXEpoch::Vector2Df::isRightLeft(missileDir, targetVec);
	if (VFXEpoch::SIDE::EQUAL == side && (missileDir == targetVec))
		return true;
	else
		return false;
}

void 
CANICurveTracking::_move(VFXEpoch::Vector2Df& missilePos, VFXEpoch::Vector2Df missileDir, float dt)
{
	missilePos += missileDir * dt;
}

void 
CANICurveTracking::_tracking(VFXEpoch::Vector2Df targetVec, VFXEpoch::Vector2Df& missileVel, float accScaling)
{
	VFXEpoch::SIDE side;
	float degreeDiff;

	side = VFXEpoch::Vector2Df::isRightLeft(missileVel, targetVec);
	degreeDiff = VFXEpoch::Vector2Df::getDegree(missileVel, targetVec);
	std::cout << "Degree difference between missile direction and the vector of missile position to target" << std::endl;
	std::cout << "Degree:" << degreeDiff << std::endl;

	if (degreeDiff <= 1.0)
	{
		std::cout << "Bias less than 1.0 degree, now correct to the exact direction" << std::endl;
		targetVec.normalize();
		missileVel = targetVec;
		return;
	}

	if (side == VFXEpoch::SIDE::LEFT)
	{
		missileVel.rotate(-accScaling);
	}
	else if (side == VFXEpoch::SIDE::RIGHT)
	{
		missileVel.rotate(accScaling);
	}

	// The only case is 180, then the
	// program will randomly choose a
	// rotation way to do so.
	else
	{
		srand(time(NULL));
		int rnd = rand() % 2;

		if (0 == rnd)
		{
			missileVel.rotate(-accScaling);
		}
		else
		{
			missileVel.rotate(accScaling);
		}
	}

	missileVel.normalize();
}

void 
CANICurveTracking::_render()
{
}

void 
CANICurveTracking::_shutdown()
{
}