#include "CrazyUtil.h"
#include "packet.h"
#include "CrazyArcadeData.h"



BlockData protoHardYellow((char)BlockHard, (char)tileGreenBlock, (char)hbYellow);
BlockData protoHardBlue((char)BlockHard, (char)tileGreenBlock, (char)hbBlue);
BlockData protoHardOrange((char)BlockHard, (char)tileGreenBlock, (char)hbOrange);

BlockData protoSoftRed((char)BlockSoft, (char)tileGreenBlock, (char)sbRed);
BlockData protoSoftOrange((char)BlockSoft, (char)tileGreenBlock, (char)sbOrange);
BlockData protoSoftBox((char)BlockSoft, (char)tileGreenBlock, (char)sbBox);

BlockData protoTileGreen((char)BlockNone, (char)tileGreenBlock, 0);
BlockData protoTileMoreGreen((char)BlockNone, (char)tileMoreGreenBlock, 0);
BlockData protoTileRoad((char)BlockNone, (char)tileGray, 0);
BlockData protoTileRoadCenterLine((char)BlockNone, (char)tileCenterLine, 0);
BlockData protoTileRoadAcrossWalk((char)BlockNone, (char)tileAcrossWalk, 0);

BlockData protoTree((char)BlockSoft, (char)tileGreenBlock, 0);
BlockData protoBush((char)BlockBush, (char)tileGreenBlock, 0);

std::vector<BlockData> createVillageBlocksData() {

	vector<BlockData> ret;
	ret.resize(195);

	if (1) {
		ret[0] = protoTileGreen;
		ret[1] = protoSoftOrange;
		ret[2] = protoSoftRed;
		ret[3] = protoSoftOrange;
		ret[4] = protoSoftRed;
		ret[5] = protoBush;
		ret[6] = protoTileRoad;
		ret[7] = protoTileRoadCenterLine;
		ret[8] = protoTileRoad;
		ret[9] = protoBush;
		ret[10] = protoHardYellow;
		ret[11] = protoSoftRed;
		ret[12] = protoHardYellow;
		ret[13] = protoTileGreen;
		ret[14] = protoHardYellow;
	}
	if (2) {
		ret[15] = protoTileGreen;
		ret[16] = protoHardOrange;
		ret[17] = protoSoftBox;
		ret[18] = protoHardOrange;
		ret[19] = protoSoftBox;
		ret[20] = protoTree;
		ret[21] = protoTileRoad;
		ret[22] = protoTileRoadCenterLine;
		ret[23] = protoTileRoad;
		ret[24] = protoTree;
		ret[25] = protoSoftRed;
		ret[26] = protoSoftOrange;
		ret[27] = protoTileGreen;
		ret[28] = protoTileGreen;
		ret[29] = protoTileGreen;
	}
	if (3) {
		ret[30] = protoTileGreen;
		ret[31] = protoTileGreen;
		ret[32] = protoSoftOrange;
		ret[33] = protoSoftRed;
		ret[34] = protoSoftOrange;
		ret[35] = protoBush;
		ret[36] = protoTileRoadAcrossWalk;
		ret[37] = protoTileRoadAcrossWalk;
		ret[38] = protoTileRoadAcrossWalk;
		ret[39] = protoBush;
		ret[40] = protoHardYellow;
		ret[41] = protoSoftBox;
		ret[42] = protoHardYellow;
		ret[43] = protoSoftBox;
		ret[44] = protoHardYellow;
	}
	if (4) {
		ret[45] = protoSoftBox;
		ret[46] = protoHardOrange;
		ret[47] = protoSoftBox;
		ret[48] = protoHardOrange;
		ret[49] = protoSoftBox;
		ret[50] = protoTree;
		ret[51] = protoTileRoad;
		ret[52] = protoTileRoadCenterLine;
		ret[53] = protoTileRoad;
		ret[54] = protoTree;
		ret[55] = protoSoftOrange;
		ret[56] = protoSoftRed;
		ret[57] = protoSoftOrange;
		ret[58] = protoSoftRed;
		ret[59] = protoSoftOrange;
	}
	if (5) {
		ret[60] = protoSoftRed;
		ret[61] = protoSoftOrange;
		ret[62] = protoSoftRed;
		ret[63] = protoSoftOrange;
		ret[64] = protoTileGreen;
		ret[65] = protoBush;
		ret[66] = protoTileRoad;
		ret[67] = protoTileRoadCenterLine;
		ret[68] = protoTileRoad;
		ret[69] = protoBush;
		ret[70] = protoHardYellow;
		ret[71] = protoSoftBox;
		ret[72] = protoHardYellow;
		ret[73] = protoSoftBox;
		ret[74] = protoHardYellow;
	}
	if (6) {
		ret[75] = protoSoftOrange;
		ret[76] = protoHardOrange;
		ret[77] = protoSoftOrange;
		ret[78] = protoHardOrange;
		ret[79] = protoSoftOrange;
		ret[80] = protoTree;
		ret[81] = protoTileRoad;
		ret[82] = protoTileRoadCenterLine;
		ret[83] = protoTileRoad;
		ret[84] = protoTileGreen;
		ret[85] = protoSoftRed;
		ret[86] = protoSoftOrange;
		ret[87] = protoSoftRed;
		ret[88] = protoSoftOrange;
		ret[89] = protoSoftRed;
	}
	if (7) {
		ret[90] = protoTree;
		ret[91] = protoBush;
		ret[92] = protoTree;
		ret[93] = protoBush;
		ret[94] = protoTree;
		ret[95] = protoBush;
		ret[96] = protoTileRoad;
		ret[97] = protoTileRoadCenterLine;
		ret[98] = protoTileRoad;
		ret[99] = protoBush;
		ret[100] = protoTree;
		ret[101] = protoBush;
		ret[102] = protoTree;
		ret[103] = protoBush;
		ret[104] = protoTree;
	}
	if (8) {
		ret[105] = protoSoftRed;
		ret[106] = protoSoftOrange;
		ret[107] = protoSoftRed;
		ret[108] = protoSoftOrange;
		ret[109] = protoTileGreen;
		ret[110] = protoTileGreen;
		ret[111] = protoTileRoad;
		ret[112] = protoTileRoadCenterLine;
		ret[113] = protoTileRoad;
		ret[114] = protoTree;
		ret[115] = protoSoftRed;
		ret[116] = protoHardOrange;
		ret[117] = protoSoftRed;
		ret[118] = protoHardOrange;
		ret[119] = protoSoftRed;
	}
	if (9) {
		ret[120] = protoHardBlue;
		ret[121] = protoSoftBox;
		ret[122] = protoHardBlue;
		ret[123] = protoSoftBox;
		ret[124] = protoHardBlue;
		ret[125] = protoBush;
		ret[126] = protoTileRoad;
		ret[127] = protoTileRoadCenterLine;
		ret[128] = protoTileRoad;
		ret[129] = protoBush;
		ret[130] = protoTileGreen;
		ret[131] = protoSoftRed;
		ret[132] = protoSoftOrange;
		ret[133] = protoSoftRed;
		ret[134] = protoSoftOrange;
	}
	if (10) {
		ret[135] = protoTileGreen;
		ret[136] = protoSoftOrange;
		ret[137] = protoSoftRed;
		ret[138] = protoSoftOrange;
		ret[139] = protoSoftRed;
		ret[140] = protoTree;
		ret[141] = protoTileRoad;
		ret[142] = protoTileRoadCenterLine;
		ret[143] = protoTileRoad;
		ret[144] = protoTree;
		ret[145] = protoSoftBox;
		ret[146] = protoHardOrange;
		ret[147] = protoSoftBox;
		ret[148] = protoHardOrange;
		ret[149] = protoSoftBox;
	}
	if (11) {
		ret[150] = protoHardBlue;
		ret[151] = protoTileGreen;
		ret[152] = protoHardBlue;
		ret[153] = protoSoftBox;
		ret[154] = protoHardBlue;
		ret[155] = protoBush;
		ret[156] = protoTileRoadAcrossWalk;
		ret[157] = protoTileRoadAcrossWalk;
		ret[158] = protoTileRoadAcrossWalk;
		ret[159] = protoBush;
		ret[160] = protoTileGreen;
		ret[161] = protoTileGreen;
		ret[162] = protoSoftRed;
		ret[163] = protoSoftOrange;
		ret[164] = protoSoftRed;
	}
	if (12) {
		ret[165] = protoTileGreen;
		ret[166] = protoTileGreen;
		ret[167] = protoSoftRed;
		ret[168] = protoSoftOrange;
		ret[169] = protoSoftRed;
		ret[170] = protoTree;
		ret[171] = protoTileRoad;
		ret[172] = protoTileRoadCenterLine;
		ret[173] = protoTileRoad;
		ret[174] = protoTree;
		ret[175] = protoSoftBox;
		ret[176] = protoHardOrange;
		ret[177] = protoSoftBox;
		ret[178] = protoHardOrange;
		ret[179] = protoTileGreen;
	}
	if (13) {
		ret[180] = protoHardBlue;
		ret[181] = protoTileGreen;
		ret[182] = protoHardBlue;
		ret[183] = protoSoftRed;
		ret[184] = protoHardBlue;
		ret[185] = protoBush;
		ret[186] = protoTileRoad;
		ret[187] = protoTileRoadCenterLine;
		ret[188] = protoTileRoad;
		ret[189] = protoBush;
		ret[190] = protoSoftOrange;
		ret[191] = protoSoftRed;
		ret[192] = protoSoftOrange;
		ret[193] = protoTileGreen;
		ret[194] = protoTileGreen;
	}

	for (int i = 0; i < 195; ++i) {
		ret[i].posX = i % 15;
		ret[i].posY = i / 15;
		int temp = rand() % 100;
		if (temp < itemGeneratePer)
			ret[i].innerItem = rand() % 3;
	}
	return ret;
}
