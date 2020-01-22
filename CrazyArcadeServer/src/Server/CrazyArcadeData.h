#pragma once
enum BlockType {
	BlockHard,
	BlockSoft,
	BlockTree,
	BlockNone,
	BlockBush
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