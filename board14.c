#include "board14.h"

//mobility table
struct MOBILITY{
	bool bmove[8];		//��
	bool wmove[8];		//��
	int  bnum[8][2];	//���̍��E�ɂ��ĕԂ��鐔	bnum[i][0]:�E�����@bnum[i][1]:������
	int  wnum[8][2];	//���̍��E�ɂ��ĕԂ��鐔	wnum[i][0]:�E�����@wnum[i][1]:������
}mobility[6561];

// �@�\  3^(7-n)�����߂�
int pow3(int n)
{
	if(n == 0)return 2187;
	if(n == 1)return 729;
	if(n == 2)return 243;
	if(n == 3)return 81;
	if(n == 4)return 27;
	if(n == 5)return 9;
	if(n == 6)return 3;

	return 1;
}

// index���X�g���Z�b�g
void allSetIndex(BOARD *board)
{
	int i;

	//�S�ċ󔒂ɏ�����
	for(i = 0; i < 11; i++){
		if(i < 8)board->index1[i] = board->index2[i] = 3280;
		board->index3[i] = board->index4[i] = 3280;
	}

	//�C���f�b�N�X�Z�b�g
	for(i = 0; i < H_SIZE; i++){
		board->index1[index_list1[i]] += board->data[i] * pow3(index_list2[i]);
		board->index2[index_list2[i]] += board->data[i] * pow3(index_list1[i]);
		if(index_list3[i] != -1)board->index3[index_list3[i]] += board->data[i] * pow3(index_list2[i]);
		if(index_list4[i] != -1)board->index4[index_list4[i]] += board->data[i] * pow3(index_list1[i]);
	}
}

// index�l�𗠕Ԃ�
void reverseIndex(BOARD *board, int xy)
{
	int i1 = index_list1[xy], i2 = index_list2[xy], i3 = index_list3[xy], i4 = index_list4[xy];

	if(board->data[xy] == BLACK){
		board->index1[i1] -= 2 * pow3(i2);
		board->index2[i2] -= 2 * pow3(i1);
		if(i3 != -1)board->index3[i3] -= 2 * pow3(i2);
		if(i4 != -1)board->index4[i4] -= 2 * pow3(i1);
	}
	else{
		board->index1[i1] += 2 * pow3(i2);
		board->index2[i2] += 2 * pow3(i1);
		if(i3 != -1)board->index3[i3] += 2 * pow3(i2);
		if(i4 != -1)board->index4[i4] += 2 * pow3(i1);
	}
}

// index�l���Z�b�g
void setIndex(BOARD *board, int color, int xy)
{
	int i1 = index_list1[xy], i2 = index_list2[xy], i3 = index_list3[xy], i4 = index_list4[xy];

	if(color == BLACK){
		board->index1[i1] += pow3(i2);
		board->index2[i2] += pow3(i1);
		if(i3 != -1)board->index3[i3] += pow3(i2);
		if(i4 != -1)board->index4[i4] += pow3(i1);
	}
	else{
		board->index1[i1] -= pow3(i2);
		board->index2[i2] -= pow3(i1);
		if(i3 != -1)board->index3[i3] -= pow3(i2);
		if(i4 != -1)board->index4[i4] -= pow3(i1);
	}
}

//mobility table������
void create_mobility()
{
	int i[8];
	int j, k, n;
	int  p = 0;

	//�S�Ẵp�^�[���ɂ��č��
	for(i[0] = 0; i[0]< 3; i[0]++){for(i[1] = 0; i[1]< 3; i[1]++){for(i[2] = 0; i[2]< 3; i[2]++){for(i[3] = 0; i[3]< 3; i[3]++){
	for(i[4] = 0; i[4]< 3; i[4]++){for(i[5] = 0; i[5]< 3; i[5]++){for(i[6] = 0; i[6]< 3; i[6]++){for(i[7] = 0; i[7]< 3; i[7]++, p++){
		//�W�̈ʒu�ɂ��Ē��ׂ�
		for(j = 0; j < 8; j++){
			if(i[j] == 1){
				//��
				//�E����
				for(k = 1, n = 0; j + k < 8 && i[j + k] == 0; k++)n++;
				if(k > 1 && j + k < 8 && i[j + k] == 2)mobility[p].bnum[j][0] = n;
				//������
				for(k = 1, n = 0; j - k >= 0 && i[j - k] == 0; k++)n++;
				if(k > 1 && j - k >= 0 && i[j - k] == 2)mobility[p].bnum[j][1] = n;
				//�ǂ����ɒu���邩
				mobility[p].bmove[j] = (mobility[p].bnum[j][0] + mobility[p].bnum[j][1]) > 0;

				//��
				//�E����
				for(k = 1, n = 0; j + k < 8 && i[j + k] == 2; k++)n++;
				if(k > 1 && j + k < 8 && i[j + k] == 0)mobility[p].wnum[j][0] = n;
				//������
				for(k = 1, n = 0; j - k >= 0 && i[j - k] == 2; k++)n++;
				if(k > 1 && j - k >= 0 && i[j - k] == 0)mobility[p].wnum[j][1] = n;
				//���v
				mobility[p].wmove[j] = (mobility[p].wnum[j][0] + mobility[p].wnum[j][1]) > 0;
			}
		}
	}}}}}}}}
}

// �Ֆʏ�����
void init(BOARD *board)
{
	int i;

	// �Ֆʏ�����
	for(i = 0; i < H_SIZE; i++)board->data[i] = EMPTY;

	// �����z�u
	board->data[D4] = board->data[E5] = WHITE;
	board->data[D5] = board->data[E4] = BLACK;

	// �ŏ��̐F�i���j
	board->color = BLACK;

	//mobility table������
	create_mobility();

	//index������
	allSetIndex(board);
}

// �`�F�b�N
bool check(BOARD *board, int xy)
{
	//�΂��Ȃ�
	if(!board->data[xy]){
		int i1 = index_list1[xy], i2 = index_list2[xy], i3 = index_list3[xy], i4 = index_list4[xy];
		//��
		if(board->color == BLACK){
			//�S�̃C���f�b�N�X�ɂ��Ē��ׂ�
			if(mobility[board->index1[i1]].bmove[i2])return true;
			if(mobility[board->index2[i2]].bmove[i1])return true;
			if(index_list3c[xy] && mobility[board->index3[i3]].bmove[i2])return true;
			if(index_list4c[xy] && mobility[board->index4[i4]].bmove[i1])return true;
		}
		//��
		else{
			//�S�̃C���f�b�N�X�ɂ��Ē��ׂ�
			if(mobility[board->index1[i1]].wmove[i2])return true;
			if(mobility[board->index2[i2]].wmove[i1])return true;
			if(index_list3c[xy] && mobility[board->index3[i3]].wmove[i2])return true;
			if(index_list4c[xy] && mobility[board->index4[i4]].wmove[i1])return true;
		}
	}
	return false;
}

// ���Ԃ�
void move(BOARD *board, int xy)
{
	int i1 = index_list1[xy], i2 = index_list2[xy], i3 = index_list3[xy], i4 = index_list4[xy];
	int i, n, t;

	//��
	if(board->color == BLACK){
		//��
		if(n = mobility[board->index1[i1]].bnum[i2][1]){
			t = xy;
			for(i = 0; i < n; i++){
				t--;
				reverseIndex(board, t);
				board->data[t] = BLACK;
			}
		}
		//�E
		if(n = mobility[board->index1[i1]].bnum[i2][0]){
			t = xy;
			for(i = 0; i < n; i++){
				t++;
				reverseIndex(board, t);
				board->data[t] = BLACK;
			}
		}
		//��
		if(n = mobility[board->index2[i2]].bnum[i1][1]){
			t = xy;
			for(i = 0; i < n; i++){
				t -= 8;
				reverseIndex(board, t);
				board->data[t] = BLACK;
			}
		}
		//��
		if(n = mobility[board->index2[i2]].bnum[i1][0]){
			t = xy;
			for(i = 0; i < n; i++){
				t += 8;
				reverseIndex(board, t);
				board->data[t] = BLACK;
			}
		}
		if(index_list3c[xy]){
			//����
			if(n = mobility[board->index3[i3]].bnum[i2][1]){
				t = xy;
				for(i = 0; i < n; i++){
					t += 7;
					reverseIndex(board, t);
					board->data[t] = BLACK;
				}
			}
			//�E��
			if(n = mobility[board->index3[i3]].bnum[i2][0]){
				t = xy;
				for(i = 0; i < n; i++){
					t -= 7;
					reverseIndex(board, t);
					board->data[t] = BLACK;
				}
			}
		}
		if(index_list4c[xy]){
			//����
			if(n = mobility[board->index4[i4]].bnum[i1][1]){
				t = xy;
				for(i = 0; i < n; i++){
					t -= 9;
					reverseIndex(board, t);
					board->data[t] = BLACK;
				}
			}
			//�E��
			if(n = mobility[board->index4[i4]].bnum[i1][0]){
				t = xy;
				for(i = 0; i < n; i++){
					t += 9;
					reverseIndex(board, t);
					board->data[t] = BLACK;
				}
			}
		}
	}
	//��
	else{
		//��
		if(n = mobility[board->index1[i1]].wnum[i2][1]){
			t = xy;
			for(i = 0; i < n; i++){
				t--;
				reverseIndex(board, t);
				board->data[t] = WHITE;
			}
		}
		//�E
		if(n = mobility[board->index1[i1]].wnum[i2][0]){
			t = xy;
			for(i = 0; i < n; i++){
				t++;
				reverseIndex(board, t);
				board->data[t] = WHITE;
			}
		}
		//��
		if(n = mobility[board->index2[i2]].wnum[i1][1]){
			t = xy;
			for(i = 0; i < n; i++){
				t -= 8;
				reverseIndex(board, t);
				board->data[t] = WHITE;
			}
		}
		//��
		if(n = mobility[board->index2[i2]].wnum[i1][0]){
			t = xy;
			for(i = 0; i < n; i++){
				t += 8;
				reverseIndex(board, t);
				board->data[t] = WHITE;
			}
		}
		if(index_list3c[xy]){
			//����
			if(n = mobility[board->index3[i3]].wnum[i2][1]){
				t = xy;
				for(i = 0; i < n; i++){
					t += 7;
					reverseIndex(board, t);
					board->data[t] = WHITE;
				}
			}
			//�E��
			if(n = mobility[board->index3[i3]].wnum[i2][0]){
				t = xy;
				for(i = 0; i < n; i++){
					t -= 7;
					reverseIndex(board, t);
					board->data[t] = WHITE;
				}
			}
		}
		if(index_list4c[xy]){
			//����
			if(n = mobility[board->index4[i4]].wnum[i1][1]){
				t = xy;
				for(i = 0; i < n; i++){
					t -= 9;
					reverseIndex(board, t);
					board->data[t] = WHITE;
				}
			}
			//�E��
			if(n = mobility[board->index4[i4]].wnum[i1][0]){
				t = xy;
				for(i = 0; i < n; i++){
					t += 9;
					reverseIndex(board, t);
					board->data[t] = WHITE;
				}
			}
		}
	}

	//�΂�u��
	setIndex(board, board->color, xy);
	board->data[xy] = board->color;

	//���̐F
	board->color = -board->color;
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
			switch(board->data[i * B_SIZE + j]){
			// ��
			case BLACK:printf("��");break;
			// ��
			case WHITE:printf("��");break;
			// ����ȊO
			default:
				// ���Ԃ���ꏊ
				if(check(board, i * B_SIZE + j))printf("��");
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

int alpha_beta(BOARD *board,int lv,int al,int be)
{
	int val
	BOARD copy;
	if(lv == 0)
	return value(board);
	int i=0;
	int j=0;
		for(i = 0; i < B_SIZE; i++){
		for(j = 0; j < B_SIZE; j++){
			if(check(board, i * B_SIZE + j))
			{
				copy = board;
				move(board, i * B_SIZE + j);
				val = -alpha_beta(board,lv-1,-be,-al);
				board = copy;
				if(val >=be)return al;
				if(al < val)al = val;
			}
			}
		}
	return al;
}
int value(int **board)
{
  int i, j, val = 0;

  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      val += val_table[i][j] * board[i][j];
    }
  }
  return val;
}

// ���C��
int main()
{
	BOARD board;
	int i,put,k;

	init(&board);
	scanf("%d %d",&put,&k);
	put+=k*8;
	if(check(&board, put))move(&board, put);
	printBoard(&board);
	printf("CPU \n \n");
	printBoard(&board);
	return 0;
}