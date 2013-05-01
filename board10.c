#include "board10.h"

// 盤面初期化
void init(BOARD *board)
{
	int i;

	// 盤面初期化
	for(i = 0; i < H_SIZE; i++){
		// 壁（番兵）
		if(i <= B_SIZE || i >= H_SIZE - B_SIZE - 1 || i % (B_SIZE + 1) == 0){
			board->data[i] = WALL;
		}
		// 空
		else{
			board->data[i] = EMPTY;
		}
	}

	// 初期配置
	board->data[D4] = board->data[E5] = WHITE;
	board->data[D5] = board->data[E4] = BLACK;

	// 最初の色（黒）
	board->color = BLACK;
}

// チェック
bool check(BOARD *board, int xy)
{
	// 置く場所に石があれば置けない
	if(board->data[xy])return false;

	// 左上
	if(board->data[xy - 10] == -board->color &&
		check_sub(board, xy - 10, -10))return true;
	// 上
	if(board->data[xy - 9] == -board->color &&
		check_sub(board, xy - 9,  -9))return true;
	// 右上
	if(board->data[xy - 8] == -board->color &&
		check_sub(board, xy - 8, -8))return true;
	// 左
	if(board->data[xy - 1] == -board->color &&
		check_sub(board, xy - 1, -1))return true;
	// 右
	if(board->data[xy + 1] == -board->color &&
		check_sub(board, xy + 1,  1))return true;
	// 左下
	if(board->data[xy + 8] == -board->color &&
		check_sub(board, xy + 8, 8))return true;
	// 下
	if(board->data[xy + 9] == -board->color &&
		check_sub(board, xy + 9,  9))return true;
	// 右下
	if(board->data[xy + 10] == -board->color &&
		check_sub(board, xy + 10,  10))return true;

	return false;
}

// 一方向についてチェック（再帰）
bool check_sub(BOARD *board, int xy, int add)
{
	// 増分を足す
	xy += add;

	// 相手の色なら再帰
	if(board->data[xy] == -board->color)
		return check_sub(board, xy, add);

	// 自分の色なら裏返せる
	if(board->data[xy] == board->color)
		return true;

	return false;
}


// 裏返す
void move(BOARD *board, int xy)
{
	// 左上
	if(check_sub(board, xy, -10))move_sub(board, xy, -10);
	// 上
	if(check_sub(board, xy, -9))move_sub(board, xy, -9);
	// 右上
	if(check_sub(board, xy, -8))move_sub(board, xy, -8);
	// 左
	if(check_sub(board, xy, -1))move_sub(board, xy, -1);
	// 右
	if(check_sub(board, xy, 1))move_sub(board, xy, 1);
	// 左下
	if(check_sub(board, xy, 8))move_sub(board, xy, 8);
	// 下
	if(check_sub(board, xy, 9))move_sub(board, xy, 9);
	// 右下
	if(check_sub(board, xy, 10))move_sub(board, xy, 10);

	// 石を置く
	board->data[xy] = board->color;
	// 手番を入れ替える
	board->color = -board->color;
}

// 一方向について裏返す（再帰）
void move_sub(BOARD *board, int xy, int add)
{
	// 増分を足す
	xy += add;

	// 相手の色なら
	if(board->data[xy] == -board->color){
		// 自分の色に
		board->data[xy] = board->color;
		// 再帰
		move_sub(board, xy, add);
	}
}

// 盤面表示
void printBoard(BOARD *board)
{
	int i, j;

	printf("%s番\n", board->color == BLACK ? "●" : "○");
	// X座標と上罫線出力
	printf("  ＡＢＣＤＥＦＧＨ\n");
	printf(" +----------------+\n");

	// 石を出力
	for(i = 0; i < B_SIZE; i++){
		// Y座標と左罫線出力
		printf("%d|", i);
		for(j = 0; j < B_SIZE; j++){
			switch(board->data[(B_SIZE + 1) * i + j + B_SIZE + 2]){
			// 黒
			case BLACK:printf("●");break;
			// 白
			case WHITE:printf("○");break;
			// それ以外
			default:
				// 裏返せる場所
				if(check(board, (B_SIZE + 1) * i + j + B_SIZE + 2))printf("＊");
				// 空白
				else printf("　");
				break;
			}
		}
		// 右罫線出力
		printf("|\n");
	}

	// 下罫線出力
	printf(" +----------------+\n");
}

// メイン
int main(int argc, char **argv)
{
	BOARD board;

	init(&board);
	printBoard(&board);

	if(check(&board, F5)){
		move(&board, F5);
		printBoard(&board);
	}

	return 0;
}