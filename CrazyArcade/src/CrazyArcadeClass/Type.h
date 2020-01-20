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
	BlockTree,
	BlockNone,
	BlockBush
};

enum class ItemType {
	ItemRangeUp,
	ItemSpeedUp,
	ItemBombLimitUp,
	ItemNone
};

enum TileIndex {
	tileGreenBlock, 
	tileMoreGreenBlock,
	tileGray,
	tileCenterLine,
	tileAcrossWalk
};

enum SoftBlockIndex {
	sbRed,
	sbOrange,
	sbBox
};

enum HardBlockIndex {
	hbYellow,
	hbBlue,
	hbOrange
};

enum CharacterState {
	
	CharacterOnMove			= BIT(0),
	CharacterNoMove			= BIT(1),
	CharacterOnLeftMove		= BIT(2),
	CharacterOnRightMove	= BIT(3),
	CharacterOnUpMove		= BIT(4),
	CharacterOnDownMove		= BIT(5),
	CharacterOnIdle			= BIT(6),
	CharacterOnRide			= BIT(7),
	CharacterInBalloon		= BIT(8),
	CharacterDead			= BIT(9)
};

inline void operator ^=(CharacterState& state, const CharacterState& state2) {
	int ret = (int)state;
	ret ^= (int)state2;
	state = (CharacterState)ret;
}
inline void operator &= (CharacterState& state, const CharacterState& state2) {
	int ret = (int)state;
	ret &= state2;
	state = (CharacterState)ret;
}
inline void operator |= (CharacterState& state, const CharacterState& state2) {
	int ret = (int)state;
	ret |= state2;
	state = (CharacterState)ret;
}

inline bool operator & (const CharacterState& state, const CharacterState& state2) {
	return (int)state & (int)state2;
}

inline bool operator | (const CharacterState& state, const CharacterState& state2) {
	return (int)state | (int)state2;
}




enum class CharacterType {
	Dao,
	Bazzi,
	//TODO : add another character

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