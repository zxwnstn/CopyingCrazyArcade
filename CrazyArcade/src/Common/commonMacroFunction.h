#pragma once
#include <Windows.h>
#include "utils.h"
//==================================================
//commonMacroFunction(필요한 부분은 직접 만들어보시오)
//==================================================

//포인트
inline POINT PointMake(int x, int y)
{
	POINT pt = { x ,y };
	return pt;
}
//선그리는 함수
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
//RECT만들기(좌상단 기준)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y, x + width, y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}
//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void drawRect(HDC hdc, const RECT& rect) 
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
inline void drawRect(HDC hdc, const UTIL::FRECT& rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
inline void DrawColorRect(HDC hdc, const RECT& rect, COLORREF color = RGB(0, 0, 0)) {
	HBRUSH oldBrush, curBrush;
	curBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, curBrush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	SelectObject(hdc, oldBrush);
	DeleteObject(curBrush);
}

//사각형 그리기(중심점)
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
inline void DrawRect(HDC hdc, const RECT& rect) {
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}



//원그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//원그리기(중심점)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}
