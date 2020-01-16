#pragma once
#define BIT(x) (1 << x)

#define BLOCK_WIDTH 30
#define BLOCK_HEIGHT 30
#define NUM_BLOCK_X 21
#define NUM_BLOCK_Y 21

#define SPEED_UP_RATE 50.f

struct BlockPosition {
	int x, y;
	BlockPosition() {}
	BlockPosition(int _x, int _y) {
		x = _x;
		y = _y;
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
	CharacterOnLeftMove		=	BIT(0) ,
	CharacterOnRightMove	=	BIT(1),
	CharacterOnUpMove		=	BIT(2),
	CharacterOnDownMove		=	BIT(3),
	CharacterOnIdle			=	BIT(4),
	CharacterOnRide			=	BIT(5),
	CharacterInBallon		=	BIT(6),
	CharacterDead			=	BIT(7)
};