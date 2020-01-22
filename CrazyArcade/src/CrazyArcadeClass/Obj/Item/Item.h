#pragma once

class Item{
public:
	Item(const IRECT& _rect, const BlockPosition _pos, ItemType type);
	~Item();

public:
	//interface
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

	//getter
	ItemType getType() { return type; }
	const IRECT& getCollisionRect() { return collisionRect; }

private:
	//basic item info
	ItemType		type;
	IRECT			collisionRect;
	BlockPosition	pos;
	Image*			curImage = nullptr;

	//for image render
	int frameIndex = 0;
	int frameIndexY;
	float frameCounter = 0.0f;
	float frameChageTimer = 0.5f;
	float deltaTime = 0.f;


private:
	const int xMargin = 5;
	const int yMargin = 5;
};

