#pragma once
#define BIT(x) (1 << x)

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
	bool operator!=(const BlockPosition& b) {
		if ((x != b.x) || (y != b.y))
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