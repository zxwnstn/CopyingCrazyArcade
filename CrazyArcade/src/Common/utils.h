#pragma once

#define PI		3.141592653
#define PI2		PI*2

namespace UTIL
{
	struct FPOINT {
		float x, y;
	};
	struct Circle {
		FPOINT p;
		int radius;
	};
	struct FRECT {
		float left, top, right, bottom;
	};
	struct IRECT {
		int left, top, right, bottom;
		int bPos_x, bPos_y;
		IRECT()
			:left(0), top(0), right(0), bottom(0)
		{}
		IRECT(int _left, int _top, int _right, int _bottom)
			: left(_left), top(_top), right(_right), bottom(_bottom)
		{}
		
		void setBpos();
		void moveUp(int dist);
		void moveDown(int dist);
		void moveLeft(int dist);
		void moveRight(int dist);
		void reset();
		void operator=(const IRECT& rect) {
			left = rect.left;
			right = rect.right;
			top = rect.top;
			bottom = rect.bottom;
			bPos_x = rect.bPos_x;
			bPos_y = rect.bPos_y;
		}
		std::pair<int, int> operator-(const IRECT& rect) {
			int dx = bPos_x - rect.bPos_x;
			int dy = bPos_y - rect.bPos_y;
			return  std::make_pair(dx, dy);
		}
	};


	//거리
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);

	bool isCircleCircleCollision(Circle& c1, Circle& c2);
	bool isCircleRectCollision(Circle& c1, FRECT rect);

	bool isRectRectCollision(const RECT & rect1, const RECT& rect2);
	bool isRectRectCollision(const RECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const IRECT& rect1, const IRECT & rect2);

	bool isPointRectCollision(const POINT & point, const RECT& rect);
	bool isPointRectCollision(const POINT & point, const FRECT& rect);
	bool isPointRectCollision(const FPOINT & point, const RECT& rect);
	bool isPointRectCollision(const FPOINT & point, const FRECT& rect);
	bool isPointRectCollision(const POINT & point, const IRECT & rect);

	bool operator==(const IRECT& rect1, const IRECT& rect2);
}