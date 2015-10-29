/*
 * ANI_CurveTracking.h
 * Xue Cui
 * Desc:
 */
#ifndef _ANI_CURVE_TRACKING_H_
#define _ANI_CURVE_TRACKING_H_

#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <vector>
#include <random>
#include "UTL_Vector.h"

class CANICurveTracking
{
private:
	typedef struct _2D_Missile
	{
		VFXEpoch::Vector2Df pos;
		VFXEpoch::Vector2Df dir;
		float speed;
		float lifeSpan;
	}Missile2D;

public:
	CANICurveTracking();
	CANICurveTracking(const CANICurveTracking& source);
	~CANICurveTracking();

public:
	bool Init(int frequencyPerSec, VFXEpoch::Vector2Df ejectorPos, VFXEpoch::Vector2Df direciton, float lifeSpan);
	void Reset();
	void Update(bool active, VFXEpoch::Vector2Df targetPos);
	void Render();
	void Shutdown();

	// TODO: Hidden the kernels
public:
	bool _initialize(int frequencyPerSec, VFXEpoch::Vector2Df ejectorPos, VFXEpoch::Vector2Df direction, float lifeSpan);
	void _reset();
	bool _losingTarget(float thetaCur, float thetaPrev);
	bool _isHit(VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos, float blasRadius);
	bool _isCollinear(VFXEpoch::Vector2Df missileDir, VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos);
	bool _isCollinear_same_direction(VFXEpoch::Vector2Df missileDir, VFXEpoch::Vector2Df missilePos, VFXEpoch::Vector2Df targetPos);
	void _move(VFXEpoch::Vector2Df& missilePos, VFXEpoch::Vector2Df missileDir, float momentum);
	void _tracking(VFXEpoch::Vector2Df targetVec, VFXEpoch::Vector2Df& missileDir, float angularMomemtum);
	void _render();
	void _shutdown();

private:
	int m_maximumMissiles;
	float m_deflectionIntegral;
	float m_missileVelConstant;
	float m_differentialAngularChange;
	float m_angularChangeLimitation;
};

#endif