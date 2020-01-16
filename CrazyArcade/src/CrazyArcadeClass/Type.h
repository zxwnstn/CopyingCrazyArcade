#pragma once
#define BIT(x) (1 << x)

#define BLOCK_WIDTH 60
#define BLOCK_HEIGHT 60
#define NUM_BLOCK_X 15
#define NUM_BLOCK_Y 13

#define SPEED_UP_RATE 50.f
#define BLOCK_DIS_DELAY 0.2f

struct BlockPosition {
	int x, y;
	BlockPosition() {}
	BlockPosition(int _x, int _y) {
		x = _x;
		y = _y;
	}
	bool operator==(const BlockPosition& b) {
		if ((x == b.x) && (y == b.y))
			return true;
		return false;
	}
};

enum class BoomState {
	BoomCenter,
	BoomHorizenRight,
	BoomHorizenRightEnd,
	BoomHorizenLeft,
	BoomHorizenLeftEnd,
	BoomVerticalUp,
	BoomVerticalUpEnd,
	BoomVerticalDown,
	BoomVerticalDownEnd,
};

enum class BlockType {
	BlockHard,
	BlockSoft,
	BlockNone
};

enum class ItemType {
	ItemRangeUp,
	ItemSpeedUp,
	ItemBombLimitUp,
	ItemKick,
	ItemDart,
	ItemNone
};



enum class CharacterState {
	CharacterOnLeftMove		= BIT(0),
	CharacterOnRightMove	= BIT(1),
	CharacterOnUpMove		= BIT(2),
	CharacterOnDownMove		= BIT(3),
	CharacterOnIdle			= BIT(4),
	CharacterOnRide			= BIT(5),
	CharacterInBalloon		= BIT(6),
	CharacterDead			= BIT(7)
};

enum Direction {
	eUp,
	eDown,
	eRight,
	eLeft,
	eSlipUp,
	eSlipDown,
	eSlipRight,
	eSlipLeft,
	eNoMove,
	eMove
};