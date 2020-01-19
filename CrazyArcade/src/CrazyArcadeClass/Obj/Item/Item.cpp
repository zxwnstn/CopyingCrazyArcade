#include "Etc/stdafx.h"
#include "Item.h"


Item::Item(const IRECT & _rect, const BlockPosition _pos)
	: collisionRect(_rect), pos(_pos)
{
	int temp = RND->getInt(100);
	if (temp < ItemCreationPer) {
		temp = RND->getInt((int)ItemType::ItemNone - 1);
		type = (ItemType)temp;
	}
	else {
		type = ItemType::ItemNone;
	}

	collisionRect.left	 += xMargin;
	collisionRect.right	 -= xMargin;
	collisionRect.top	 += yMargin;
	collisionRect.bottom -= yMargin;
	
	//image match
	if (type != ItemType::ItemNone) 
	curImage = IMAGEMANAGER->findImage("¾ÆÀÌÅÛ");
	
	switch (type)
	{
	case ItemType::ItemRangeUp:
		frameIndexY = 2;
		break;
	case ItemType::ItemSpeedUp:
		frameIndexY = 1;
		break;
	case ItemType::ItemBombLimitUp:
		frameIndexY = 0;
		break;
	/*case ItemType::ItemKick:
		break;
	case ItemType::ItemDart:*/
		break;
	}
}
Item::~Item()
{
}

void Item::update(float _deltaTime)
{
	deltaTime = _deltaTime;
}
void Item::render(HDC hdc)
{
	frameCounter += deltaTime;
	if (frameCounter > frameChageTimer) {
		frameIndex++;
		frameCounter = 0.f;
		if (frameIndex > curImage->getMaxFrameX())
			frameIndex = 0;
	}
	curImage->frameRender(hdc, collisionRect.left, collisionRect.top, frameIndex, frameIndexY);
	//curImage->frameAlphaRender(hdc, collisionRect.left, collisionRect.top, frameIndex, frameIndexY, 20);

}
void Item::debugRender(HDC hdc)
{
	switch (type)
	{
	case ItemType::ItemRangeUp:
		DrawColorRect(hdc, collisionRect, RGB(0, 0, 0));
		break;
	case ItemType::ItemSpeedUp:
		DrawColorRect(hdc, collisionRect, RGB(255, 0, 0));
		break;
	case ItemType::ItemBombLimitUp:
		DrawColorRect(hdc, collisionRect, RGB(0, 255, 0));
		break;
	//case ItemType::ItemKick:
	//	DrawColorRect(hdc, collisionRect, RGB(0, 0, 255));
	//	break;
	//case ItemType::ItemDart:
	//	DrawColorRect(hdc, collisionRect, RGB(255, 255, 0));
	//	break;
	}
}
void Item::release()
{
}

