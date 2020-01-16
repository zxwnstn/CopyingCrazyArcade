#pragma once

class Item
{
public:
	Item(const FRECT& _rect, const BlockPosition _pos);

	~Item();

	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

	ItemType getType() { return type; }
	const FRECT& getRect() { return rect; }

private:
	ItemType		type;
	Image*			image = nullptr;
	FRECT			rect;
	BlockPosition	pos;
	const int xMargin = 5;
	const int yMargin = 5;

	//100 is max;
	int ItemCreationPer = 50;
};

