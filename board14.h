#ifndef _BOARD14_H_
#define _BOARD14_H_

#include <stdio.h>

#define EMPTY	0
#define BLACK	1
#define WHITE	-1

#define B_SIZE	8
#define H_SIZE	B_SIZE * B_SIZE

#define	A1	0
#define	B1	1
#define	C1	2
#define	D1	3
#define	E1	4
#define	F1	5
#define	G1	6
#define	H1	7
#define	A2	8
#define	B2	9
#define	C2	10
#define	D2	11
#define	E2	12
#define	F2	13
#define	G2	14
#define	H2	15
#define	A3	16
#define	B3	17
#define	C3	18
#define	D3	19
#define	E3	20
#define	F3	21
#define	G3	22
#define	H3	23
#define	A4	24
#define	B4	25
#define	C4	26
#define	D4	27
#define	E4	28
#define	F4	29
#define	G4	30
#define	H4	31
#define	A5	32
#define	B5	33
#define	C5	34
#define	D5	35
#define	E5	36
#define	F5	37
#define	G5	38
#define	H5	39
#define	A6	40
#define	B6	41
#define	C6	42
#define	D6	43
#define	E6	44
#define	F6	45
#define	G6	46
#define	H6	47
#define	A7	48
#define	B7	49
#define	C7	50
#define	D7	51
#define	E7	52
#define	F7	53
#define	G7	54
#define	H7	55
#define	A8	56
#define	B8	57
#define	C8	58
#define	D8	59
#define	E8	60
#define	F8	61
#define	G8	62
#define	H8	63
#define WHITE -1  //白石
#define EMPTY  0  //石なし
#define BLACK  1  //黒石

//石の位置による評価値
int val_table[8][8] = {
  {120, -20,  20,   5,   5,  20, -20, 120},
  {-20, -40,  -5,  -5,  -5,  -5, -40, -20},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  {  5,  -5,   3,   3,   3,   3,  -5,   5},
  { 20,  -5,  15,   3,   3,  15,  -5,  20},
  {-20, -40,  -5,  -5,  -5,  -5, -40, -20},
  {120, -20,  20,   5,   5,  20, -20, 120}
};

//２次元配列のポインタ(board)を受け取って
//      黒から見た評価値を返す関数
int value(int **board);
// BOARD構造体
typedef struct BOARD{
	int data[H_SIZE];
	int color;
	//インデックス
	int index1[8];	//横
	int index2[8];	//縦
	int index3[11];	//右上
	int index4[11];	//左上
}BOARD;

//インデックス関連
int pow3(int n);
void allSetIndex(BOARD *board);
void reverseIndex(BOARD *board, int xy);
void setIndex(BOARD *board, int color, int xy);
// 盤面操作関数
void init(BOARD *board);
void create_mobility();
bool check(BOARD *board, int xy);
void move(BOARD *board, int xy);
void printBoard(BOARD *board);
int alpha_beta(BOARD *board,int lv,int al,int be);

//インデックス操作で役立つ番号テーブル
const int index_list1[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7,
};
const int index_list2[64] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
	0, 1, 2, 3, 4, 5, 6, 7,
};
const int index_list3[64] = {
	-1,-1, 0, 1, 2, 3, 4, 5,
	-1, 0, 1, 2, 3, 4, 5, 6,
	 0, 1, 2, 3, 4, 5, 6, 7,
	 1, 2, 3, 4, 5, 6, 7, 8,
	 2, 3, 4, 5, 6, 7, 8, 9,
	 3, 4, 5, 6, 7, 8, 9,10,
	 4, 5, 6, 7, 8, 9,10,-1,
	 5, 6, 7, 8, 9,10,-1,-1,
};
const int index_list4[64] = {
	 5, 4, 3, 2, 1, 0,-1,-1,
	 6, 5, 4, 3, 2, 1, 0,-1,
	 7, 6, 5, 4, 3, 2, 1, 0,
	 8, 7, 6, 5, 4, 3, 2, 1,
	 9, 8, 7, 6, 5, 4, 3, 2,
	10, 9, 8, 7, 6, 5, 4, 3,
	-1,10, 9, 8, 7, 6, 5, 4,
	-1,-1,10, 9, 8, 7, 6, 5,
};

//裏返せる位置
const bool index_list3c[64] = {
	0,0,1,1,1,1,1,1,
	0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,0,
};
const bool index_list4c[64] = {
	1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,0,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	0,0,1,1,1,1,1,1,
	0,0,1,1,1,1,1,1,
};

// メイン
int main(int argc, char **argv);

#endif