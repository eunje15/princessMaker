#include "stdafx.h"
#include "utils.h"


namespace CLASS_TEN
{

	//�Ÿ�
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	//����
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

		//������� �����Դٸ� �浹�� ��Ȳ
		int interW = rcInter.right - rcInter.left;
		int interH = rcInter.bottom - rcInter.top;

		//�����浹�̳�
		if (interW > interH)
		{
			//��
			if (rcInter.top == mrcHold.top)
			{
				OffsetRect(&mrcMove, 0, -interH);
			}
			//�Ʒ�
			else if (rcInter.bottom == mrcHold.bottom)
			{
				OffsetRect(&mrcMove, 0, interH);
			}
		}
		//�����浹�̳�
		else
		{
			if (rcInter.left == mrcHold.left)
			{
				OffsetRect(&mrcMove, -interW, 0);
			}
			//�Ʒ�
			else if (rcInter.right == mrcHold.right)
			{
				OffsetRect(&mrcMove, interW, 0);
			}
		}
		return true;
	}

}
