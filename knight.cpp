
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
class Knight {  //�M�h������ ���� �y�� row col �P step �B�� �٦�d �ؼФ�V(k1~k8) 
public:
	int row, col;
	int d;
	int steps;
	Knight() { //��l�غc 
		row = 0;
		col = 0;
		d = 0;
		steps = 0;
	}
	Knight(int _row, int _col, int _d, int _steps) { //���ȫغc 
		row = _row;
		col = _col;
		d = _d;
		steps = _steps;
	}
};
class Stack { //stack ����  ����top , �j�p   
private:
	int top; 
	int size;
	Knight *array;  
public:
	Stack(int s) {
		size = s;
		array = new Knight[s];
		top = 0;
	}
	void push(Knight knight) { //��@push 
		if (top == size)
			cout << "Stack is full!" << endl;
		else {
			*(array + top) = knight;
			top++;
		}
	}
	Knight pop() { //��@pop 
		if (top == 0) { // top = 0 �N����|���� �^�Ǯy�Ь�-1������h���P�_ 
			Knight knight(-1, -1, -1, -1);  
			return knight;
		}		
		else {  //���|������ �^�Ǹ�� 
			Knight knight;
			top--;
			knight = *(array + top);
			return knight;
		}

	}

};
int inChess(int r, int c, int chesssize);  //�P�_�y�ЬO�_���ѽL�椺 
void knightMove(int r,int c, int rowsize); //���ʨ禡 
int main() {
	
	//���O�L�Xn=1~6�����G 
	cout <<"n=1" << endl;
	knightMove(0,0,1);
	cout <<"\n";
	cout <<"n=2" << endl;
	knightMove(0,0,2);
	cout <<"\n";
	cout <<"n=3" << endl;
	knightMove(0,0,3);
	cout <<"\n";
	cout <<"n=4" << endl;
	knightMove(0,0,4);
	cout <<"\n";
	cout <<"n=5" << endl;
	knightMove(0,0,5);
	cout <<"\n";
	cout <<"n=6" << endl;
	knightMove(0,0,6);
	cout <<"\n";
	system("pause");

	
	return 0;
}
//�P�_�y�ЬO�_���ѽL�U������@ (�y�Эn�j��0 �åB�p��ѽL�j�p) 
int inChess(int row, int col, int chesssize){
		if(row >=0 && row < chesssize && col >=0 && col < chesssize){
			return 1;
		}else{
			return 0;
		}	
}
//���ʨ禡����@ 
void knightMove(int row, int col, int rowsize){
		int temp_chess[rowsize][rowsize]; //���ʹѽL�}�C rowsize x rowsize ���j�p 
		Stack temp_stk(rowsize*rowsize); //����Stack���� 
		int i,j;
		for(i=0;i<rowsize;i++){ //�N�ѽL�k0 
			for(j=0;j<rowsize;j++){
				temp_chess[i][j] = 0;			
			}
		}
		int chesssize; //�`���� ���ѽL�`��� 
		chesssize = rowsize*rowsize;
		int colMove[] = {1,2,2,1,-1,-2,-2,-1}; // �Ҧ��i����V������ colMove[1]rowMove[1] �N�� k1  �ؼЮy���ܤƬ� 1 -2 
		int rowMove[] = {-2,-1,1,2,2,1,-1,-2};
		int steps = 1, d = 0, nRow, nCol; //�ŧi�B�� ,d ��V , �ثerow col��m 
		Knight knight; //���ͤ@��knight���� 
		temp_chess[row][col] = steps++;
		while(steps <= chesssize){ //��B�Ƥp��ѽL��� �N���٨S���� �}�l���_���զ樫 
			for(; d<8;d++){
				nRow = row + rowMove[d];//d �|�q 1 ~8 �ΥN�� k1~ k8 
				nCol = col + colMove[d]; 
				if(inChess(nRow, nCol,rowsize)&&temp_chess[nRow][nCol]==0){ //��ثe��m���ѽL�椺 �åB���ѽL���٥����L �ΥN���X��ت� �K�N���Gpush�i���|�� 
					temp_chess[nRow][nCol] = steps;
					knight.row = row;
					knight.col = col;
					knight.d=d;
					knight.steps = steps;
					temp_stk.push(knight);
					d = 0;
					row = nRow;
					col = nCol;
					steps++;											
					break;
				}
			}
			if(d ==8){ //��d ��8 �� �N��1~8�Ӥ�V�Ҥw���� �åB�S���i���Z�� �h�^�W�@�Ӧ�m�åB�}�l���� 
				knight = temp_stk.pop();
				if(knight.col == -1){ //�p�Gstack���X�Ӫ�knight�����m��-1 �N��stack�w�g�ŤF �L�� 
					cout <<"no solution"<<endl;
					return;
				}  
				row = knight.row;  //��o�W�@�Ӧ�m����� �åB�~����� 
				col = knight.col;
				d = knight.d;
				steps = knight.steps;
				nRow = row + rowMove[d];
				nCol = col+ colMove[d];
				temp_chess[nRow][nCol] = 0;
				d++;
			}
			
		}
		
		for(i=0;i<rowsize;i++){ //�L�X���G 
			for(j=0;j<rowsize;j++){				
				cout <<setw(3)<<temp_chess[i][j]<<" ";
				if(j == rowsize-1){
					cout << "\n";
					
				}
				
		}
	}
		
}



