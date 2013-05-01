#include "board10.h"

// �Ֆʏ�����
void init(BOARD *board)
{
	int i;

	// �Ֆʏ�����
	for(i = 0; i < H_SIZE; i++){
		// �ǁi�ԕ��j
		if(i <= B_SIZE || i >= H_SIZE - B_SIZE - 1 || i % (B_SIZE + 1) == 0){
			board->data[i] = WALL;
		}
		// ��
		else{
			board->data[i] = EMPTY;
		}
	}

	// �����z�u
	board->data[D4] = board->data[E5] = WHITE;
	board->data[D5] = board->data[E4] = BLACK;

	// �ŏ��̐F�i���j
	board->color = BLACK;
}

// �`�F�b�N
bool check(BOARD *board, int xy)
{
	// �u���ꏊ�ɐ΂�����Βu���Ȃ�
	if(board->data[xy])return false;

	// ����
	if(board->data[xy - 10] == -board->color &&
		check_sub(board, xy - 10, -10))return true;
	// ��
	if(board->data[xy - 9] == -board->color &&
		check_sub(board, xy - 9,  -9))return true;
	// �E��
	if(board->data[xy - 8] == -board->color &&
		check_sub(board, xy - 8, -8))return true;
	// ��
	if(board->data[xy - 1] == -board->color &&
		check_sub(board, xy - 1, -1))return true;
	// �E
	if(board->data[xy + 1] == -board->color &&
		check_sub(board, xy + 1,  1))return true;
	// ����
	if(board->data[xy + 8] == -board->color &&
		check_sub(board, xy + 8, 8))return true;
	// ��
	if(board->data[xy + 9] == -board->color &&
		check_sub(board, xy + 9,  9))return true;
	// �E��
	if(board->data[xy + 10] == -board->color &&
		check_sub(board, xy + 10,  10))return true;

	return false;
}

// ������ɂ��ă`�F�b�N�i�ċA�j
bool check_sub(BOARD *board, int xy, int add)
{
	// �����𑫂�
	xy += add;

	// ����̐F�Ȃ�ċA
	if(board->data[xy] == -board->color)
		return check_sub(board, xy, add);

	// �����̐F�Ȃ痠�Ԃ���
	if(board->data[xy] == board->color)
		return true;

	return false;
}


// ���Ԃ�
void move(BOARD *board, int xy)
{
	// ����
	if(check_sub(board, xy, -10))move_sub(board, xy, -10);
	// ��
	if(check_sub(board, xy, -9))move_sub(board, xy, -9);
	// �E��
	if(check_sub(board, xy, -8))move_sub(board, xy, -8);
	// ��
	if(check_sub(board, xy, -1))move_sub(board, xy, -1);
	// �E
	if(check_sub(board, xy, 1))move_sub(board, xy, 1);
	// ����
	if(check_sub(board, xy, 8))move_sub(board, xy, 8);
	// ��
	if(check_sub(board, xy, 9))move_sub(board, xy, 9);
	// �E��
	if(check_sub(board, xy, 10))move_sub(board, xy, 10);

	// �΂�u��
	board->data[xy] = board->color;
	// ��Ԃ����ւ���
	board->color = -board->color;
}

// ������ɂ��ė��Ԃ��i�ċA�j
void move_sub(BOARD *board, int xy, int add)
{
	// �����𑫂�
	xy += add;

	// ����̐F�Ȃ�
	if(board->data[xy] == -board->color){
		// �����̐F��
		board->data[xy] = board->color;
		// �ċA
		move_sub(board, xy, add);
	}
}

// �Ֆʕ\��
void printBoard(BOARD *board)
{
	int i, j;

	printf("%s��\n", board->color == BLACK ? "��" : "��");
	// X���W�Ə�r���o��
	printf("  �`�a�b�c�d�e�f�g\n");
	printf(" +----------------+\n");

	// �΂��o��
	for(i = 0; i < B_SIZE; i++){
		// Y���W�ƍ��r���o��
		printf("%d|", i);
		for(j = 0; j < B_SIZE; j++){
			switch(board->data[(B_SIZE + 1) * i + j + B_SIZE + 2]){
			// ��
			case BLACK:printf("��");break;
			// ��
			case WHITE:printf("��");break;
			// ����ȊO
			default:
				// ���Ԃ���ꏊ
				if(check(board, (B_SIZE + 1) * i + j + B_SIZE + 2))printf("��");
				// ��
				else printf("�@");
				break;
			}
		}
		// �E�r���o��
		printf("|\n");
	}

	// ���r���o��
	printf(" +----------------+\n");
}

// ���C��
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