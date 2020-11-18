#include <bits/stdc++.h>

enum PlayStatus{
        // not important
};

enum Color{
        White, // Initital 0
        Blue, // Player One
        Red, // Player Two
        Black //Explosion
};

namespace playerOne
{
	
};

namespace playerTwo
{
        // Your Code
};








class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            // Your Code
			int alpha = -1000000;
			int beta = 1000000;
			x = -1;
			y = -1;
			minimax(0, Record, Max, color, inputColor, alpha, beta);
        }
		
		int minimax(int depth, int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor, int alpha, int beta){
			int blue = 0, red = 0, white = 0;
			int blueScore = 0, redScore = 0;
			for(int i=0; i<5; i++){
				for(int j=0; j<6; j++){
					if(Record[i][j]<Max[i][j]){
						if(color[i][j]==Blue){
							blue += Max[i][j]-Record[i][j];
							blueScore += 10*(Max[i][j]-Record[i][j]);
						}
						if(color[i][j]==Red){
							red += Max[i][j]-Record[i][j];
							redScore += 10*(Max[i][j]-Record[i][j]);
						}
						if(color[i][j]==White){
							white += Max[i][j]-Record[i][j];
							blueScore += Max[i][j]-Record[i][j];
							redScore += Max[i][j]-Record[i][j];
						}
					}
				}
			}
			int flag = (depth%2==0?1:-1);
			if(white==0){
				if(inputColor==Blue){
					if(blue==0) return -1000000 * flag;
					if(red==0) return 1000000 * flag;
				}
				if(inputColor==Red){
					if(red==0) return -1000000 * flag;
					if(blue==0) return 1000000 * flag;
				}
			}
			if(depth>3){
				if(inputColor==Blue) return (blueScore-redScore) * flag;
				if(inputColor==Red) return (redScore-blueScore) * flag;
				return 0;
			}
			
			
			int tmp_Record[5][6];
			Color tmp_color[5][6];
			for(int i=0; i<5; i++){
				for(int j=0; j<6; j++){
					tmp_Record[i][j] = Record[i][j];
					tmp_color[i][j] = color[i][j];
				}
			}
			Color nextColor = (inputColor==Blue ? Red:Blue);
			
			int maxScore = -1000001, minScore = 1000001;
			for(int i=0; i<5; i++){
				for(int j=0; j<6; j++){
					if(color[i][j]==White || color[i][j]==inputColor){
						makeMove(i, j, Record, Max, color, inputColor);
						int score = minimax(depth+1, Record, Max, color, nextColor, alpha, beta);
						//if(depth==0) printf("%d, %d,  depth= %d, score=%d, maxScore=%d\n",i,j,depth,score,maxScore);
						if(depth%2==0){
							if(maxScore<score){
								maxScore = score;
								if(depth==0){ this->x = i; this->y = j; }
							}
							if(score > alpha) alpha = score;
						}else{
							if(minScore>score) minScore = score;
							if(score < beta) beta = score;
						}
						
						// recover
						for(int ii=0; ii<5; ii++){
							for(int jj=0; jj<6; jj++){
								Record[ii][jj] = tmp_Record[ii][jj];
								color[ii][jj] = tmp_color[ii][jj];
							}
						}
						
						if(alpha >= beta) break;
					}
				}
				if(alpha >= beta) break;
			}
			return (depth%2==0 ?maxScore:minScore);
		}
		
		void makeMove(int px, int py, int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
			int q[30]={0}, qn = 0, d[8] = {-1, 0, 1, 0, 0, -1, 0, 1};
			Record[px][py] += 1;
			color[px][py] = inputColor;
			if(Record[px][py]>=Max[px][py]){
				q[qn++] = px*6+py;
				color[px][py] = Black;
			}
			
			while(qn>0){
				px = q[qn-1]/6;
				py = q[qn-1]%6;
				qn--;
				
				for(int i=0; i<8; i+=2){
					int xx = px + d[i];
					int yy = py + d[i+1];
					if(0<=xx && xx<5 && 0<=yy && yy<6 && color[xx][yy]!=Black){
						color[xx][yy] = inputColor;
						Record[xx][yy] += 1;
						if(Record[xx][yy]>=Max[xx][yy]){
							q[qn++] = xx*6+yy;
							color[xx][yy] = Black;
						}
					}
				}
			}
		}
		
        // Any Code You Want to Add
        int getX(){
            // Your Code
			return x;
        }
        int getY(){
            // Your Code
			return y;
        }
    private:
        int x;
        int y;
};










int main()
{
	int Record[5][6] = {0};
	int Max[5][6] = {0};
	Color color[5][6] = {White};
	for(int i=0; i<5; i++){
		for(int j=0; j<6; j++){
			Max[i][j] = 4;
			if(i==0 || i==4) Max[i][j]--;
			if(j==0 || j==5) Max[i][j]--;
			printf("%d ",Max[i][j]);
		}
		printf("\n");
	}
	printf("===========================\n");
	
	int x, y;
	Color inputColor;
	Student s;
	while(scanf("%d%d",&x,&y)==2){
		x--; y--;
	//for(int i=0; i<40; i++){
		//s.makeMove(Record, Max, color, Blue);
		//x = s.getX();
		//y = s.getY();
		printf("Blue: %d %d\n",x, y);
		if(x==-1 && y==-1){ printf("Blue loss\n"); break; }
		s.makeMove(x, y, Record, Max, color, Blue);
		
		for(int i=0; i<5; i++){
			for(int j=0; j<6; j++){
				printf("%d ",Record[i][j]);
			}
			printf("    \t");
			for(int j=0; j<6; j++){
				printf("%d ",color[i][j]);
			}
			printf("\n");
		}
		printf("===========================\n");
		
		
		s.makeMove(Record, Max, color, Red);
		x = s.getX();
		y = s.getY();
		printf("Red: %d %d\n",x, y);
		if(x==-1 && y==-1){ printf("Red loss\n"); break; }
		s.makeMove(x, y, Record, Max, color, Red);
		
		for(int i=0; i<5; i++){
			for(int j=0; j<6; j++){
				printf("%d ",Record[i][j]);
			}
			printf("    \t");
			for(int j=0; j<6; j++){
				printf("%d ",color[i][j]);
			}
			printf("\n");
		}
		printf("===========================\n");
		//break;
	}
}

