#include "stdafx.h"
#include "utils.h"


namespace CLASS_TEN
{

	//거리
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	//각도
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = 2 * PI - angle;
			if (angle >= PI * 2) angle -= PI * 2;
		}

		return angle;
	}

	bool isCollisionReaction(RECT& mrcHold, RECT& mrcMove)
	{
		RECT rcInter;

		if (!IntersectRect(&rcInter, &mrcHold, &mrcMove)) return false;

		//여기까지 내려왔다면 충돌한 상황
		int interW = rcInter.right - rcInter.left;
		int interH = rcInter.bottom - rcInter.top;

		//수직충돌이냐
		if (interW > interH)
		{
			//위
			if (rcInter.top == mrcHold.top)
			{
				OffsetRect(&mrcMove, 0, -interH);
			}
			//아래
			else if (rcInter.bottom == mrcHold.bottom)
			{
				OffsetRect(&mrcMove, 0, interH);
			}
		}
		//수평충돌이냐
		else
		{
			if (rcInter.left == mrcHold.left)
			{
				OffsetRect(&mrcMove, -interW, 0);
			}
			//아래
			else if (rcInter.right == mrcHold.right)
			{
				OffsetRect(&mrcMove, interW, 0);
			}
		}
		return true;
	}

}
