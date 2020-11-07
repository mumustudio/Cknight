
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;
class Knight {  //騎士的物件 紀錄 座標 row col 與 step 步數 還有d 目標方向(k1~k8) 
public:
	int row, col;
	int d;
	int steps;
	Knight() { //初始建構 
		row = 0;
		col = 0;
		d = 0;
		steps = 0;
	}
	Knight(int _row, int _col, int _d, int _steps) { //附值建構 
		row = _row;
		col = _col;
		d = _d;
		steps = _steps;
	}
};
class Stack { //stack 物件  紀錄top , 大小   
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
	void push(Knight knight) { //實作push 
		if (top == size)
			cout << "Stack is full!" << endl;
		else {
			*(array + top) = knight;
			top++;
		}
	}
	Knight pop() { //實作pop 
		if (top == 0) { // top = 0 代表堆疊為空 回傳座標為-1的物件去做判斷 
			Knight knight(-1, -1, -1, -1);  
			return knight;
		}		
		else {  //堆疊不為空 回傳資料 
			Knight knight;
			top--;
			knight = *(array + top);
			return knight;
		}

	}

};
int inChess(int r, int c, int chesssize);  //判斷座標是否位於棋盤格內 
void knightMove(int r,int c, int rowsize); //移動函式 
int main() {
	
	//分別印出n=1~6的結果 
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
//判斷座標是否位於棋盤各內的實作 (座標要大於0 並且小於棋盤大小) 
int inChess(int row, int col, int chesssize){
		if(row >=0 && row < chesssize && col >=0 && col < chesssize){
			return 1;
		}else{
			return 0;
		}	
}
//移動函式的實作 
void knightMove(int row, int col, int rowsize){
		int temp_chess[rowsize][rowsize]; //產生棋盤陣列 rowsize x rowsize 的大小 
		Stack temp_stk(rowsize*rowsize); //產生Stack物件 
		int i,j;
		for(i=0;i<rowsize;i++){ //將棋盤歸0 
			for(j=0;j<rowsize;j++){
				temp_chess[i][j] = 0;			
			}
		}
		int chesssize; //總部數 為棋盤總格數 
		chesssize = rowsize*rowsize;
		int colMove[] = {1,2,2,1,-1,-2,-2,-1}; // 所有可走方向的索引 colMove[1]rowMove[1] 代表 k1  目標座標變化為 1 -2 
		int rowMove[] = {-2,-1,1,2,2,1,-1,-2};
		int steps = 1, d = 0, nRow, nCol; //宣告步數 ,d 方向 , 目前row col位置 
		Knight knight; //產生一個knight物件 
		temp_chess[row][col] = steps++;
		while(steps <= chesssize){ //當步數小於棋盤格數 代表還沒走完 開始不斷嘗試行走 
			for(; d<8;d++){
				nRow = row + rowMove[d];//d 會從 1 ~8 及代表 k1~ k8 
				nCol = col + colMove[d]; 
				if(inChess(nRow, nCol,rowsize)&&temp_chess[nRow][nCol]==0){ //當目前位置位於棋盤格內 並且此棋盤格還未走過 及代表為合格目的 便將結果push進堆疊中 
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
			if(d ==8){ //當d 為8 時 代表1~8個方向皆已嘗試 並且沒有可走距離 退回上一個位置並且開始嘗試 
				knight = temp_stk.pop();
				if(knight.col == -1){ //如果stack拿出來的knight物件位置為-1 代表stack已經空了 無解 
					cout <<"no solution"<<endl;
					return;
				}  
				row = knight.row;  //獲得上一個位置的資料 並且繼續嘗試 
				col = knight.col;
				d = knight.d;
				steps = knight.steps;
				nRow = row + rowMove[d];
				nCol = col+ colMove[d];
				temp_chess[nRow][nCol] = 0;
				d++;
			}
			
		}
		
		for(i=0;i<rowsize;i++){ //印出結果 
			for(j=0;j<rowsize;j++){				
				cout <<setw(3)<<temp_chess[i][j]<<" ";
				if(j == rowsize-1){
					cout << "\n";
					
				}
				
		}
	}
		
}



