#pragma once

#define PI 3.141592654f
#define PI2 PI * 2

//프레임회전을 위한 각도값
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

namespace CLASS_TEN
{

	//거리
	float getDistance(float x1, float y1, float x2, float y2);

	//각도
	float getAngle(float x1, float y1, float x2, float y2);

	bool isCollisionReaction(RECT& mrcHold, RECT& mrcMove);

}
