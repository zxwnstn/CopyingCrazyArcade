#pragma once

class Item{
public:
	Item(const IRECT& _rect, const BlockPosition _pos);
	~Item();

public:

	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

	ItemType getType() { return type; }
	const IRECT& getCollisionRect() { return collisionRect; }

private:
	ItemType		type;
	Image*			image = nullptr;
	IRECT			collisionRect;
	BlockPosition	pos;

private:
	const int xMargin = 5;
	const int yMargin = 5;
	
	//100 is max;
	int ItemCreationPer = 50;
};

