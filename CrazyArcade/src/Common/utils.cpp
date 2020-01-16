#include "Etc/stdafx.h"

namespace UTIL
{
	
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY -  startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float src_x, float src_y, float tar_x, float tar_y)
	{
		float dx = src_x - tar_x;
		float dy = src_y - tar_y;
		float angle =0.f;
		float distance = sqrtf(dx * dx + dy * dy);


		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);
		

		return angle;
	}

	bool isCircleCircleCollision(Circle& c1, Circle& c2) {
		float dist = getDistance(c1.p.x, c1.p.y, c2.p.x, c2.p.y);
		if (dist <= c1.radius + c2.radius)
			return true;
		return false;
	}

	bool isCircleRectCollision(Circle & c1, FRECT rect)
	{
		rect.left -= c1.radius;
		rect.top -= c1.radius;
		rect.right += c1.radius;
		rect.bottom += c1.radius;

		if (rect.left <= c1.p.x  && c1.p.x <= rect.right)
			if(rect.top <= c1.p.y  && c1.p.y <= rect.bottom)
				return true;

		return false;
	}

	bool isRectRectCollision(const RECT & rect1, const RECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}

	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}

	bool isPointRectCollison(const POINT & point, const RECT & rect)
	{
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollison(const FPOINT & point, const RECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

	bool isPointRectCollison(const FPOINT & point, const FRECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}

}
