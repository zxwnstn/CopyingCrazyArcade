#include "Etc/stdafx.h"
#include "Item.h"


Item::Item(const RECT & _rect, const BlockPosition _pos)
	: rect(_rect), pos(_pos)
{
	int temp = RND->getInt(100);
	if (temp < ItemCreationPer) {
		temp = RND->getInt((int)ItemType::ItemNone - 1);
		type = (ItemType)temp;
	}
	else {
		type = ItemType::ItemNone;
	}

	rect.left += xMargin;
	rect.right -= xMargin;
	rect.top += yMargin;
	rect.bottom -= yMargin;
	
	//image match
	switch (type)
	{
	case ItemType::ItemRangeUp:
		break;
	case ItemType::ItemSpeedUp:
		break;
	case ItemType::ItemBombLimitUp:
		break;
	case ItemType::ItemKick:
		break;
	case ItemType::ItemDart:
		break;
	}
}

Item::~Item()
{
}

void Item::update(float deltaTime)
{
}

void Item::render(HDC hdc)
{
}

void Item::debugRender(HDC hdc)
{
	switch (type)
	{
	case ItemType::ItemRangeUp:
		DrawColorRect(hdc, rect, RGB(0, 0, 0));
		break;
	case ItemType::ItemSpeedUp:
		DrawColorRect(hdc, rect, RGB(255, 0, 0));
		break;
	case ItemType::ItemBombLimitUp:
		DrawColorRect(hdc, rect, RGB(0, 255, 0));
		break;
	case ItemType::ItemKick:
		DrawColorRect(hdc, rect, RGB(0, 0, 255));
		break;
	case ItemType::ItemDart:
		DrawColorRect(hdc, rect, RGB(255, 255, 0));
		break;
	}
}

void Item::release()
{
}

