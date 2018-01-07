#include <bits/stdc++.h>
using namespace std;


#define N 3
#define INF 0x3f3f3f3f
#define MAX_DEPTH 7
#define score 100
#define PII pair < int , int >


char board[N][N][N][N];			// Complete board
char Mboard[N][N];				// Main Board
char eval[N][N];				// temporary Board


// Sub Board score
int SubBoard() {
	bool flag;
	char c;
	// left to right
	for(int i=0;i<N;i++) {
		c = eval[i][0];
		flag = 1;
		for(int j=0;j<N;j++){
			if(eval[i][j]!=c) {
				flag = 0;
				break;
			}
		}
		if(flag) {
			if(c=='X') return score;
			else if(c=='O') return -score;
		}
	}
	// top to bottom
	for(int i=0;i<N;i++) {
		c = eval[0][i];
		flag = 1;
		for(int j=0;j<N;j++) {
			if(eval[j][i]!=c) {
				flag = 0;
				break;
			}
		}
		if(flag){
			if(c=='X') return score;
			else if(c=='O') return -score;
		}
	}
	// diagnol - 1
	c = eval[0][0];
	flag = 1;
	for(int i=0;i<N;i++) {
		if(eval[i][i]!=c) {
			flag = 0;
			break;
		}
	}
	if(flag){
		if(c=='X') return score;
		else if(c=='O') return -score;
	}
	// diagnol - 2
	c = eval[0][N-1];
	flag = 1;
	for(int i=0;i<N;i++) {
		if(eval[i][N-i-1]!=c) {
			flag = 0;
			break;
		}
	}
	if(flag){
		if(c=='X') return score;
		else if(c=='O') return -score;
	}
	// done
	// if still no return
	// still we can play
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(eval[i][j]=='_') return -1;	
	// no we cant - its a TIE
	return 0;
}


// initially all set to '_'
void init() {
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) for(int k=0;k<N;k++) for(int l=0;l<N;l++) board[i][j][k][l] = '_';
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) Mboard[i][j] = '_';
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) eval[i][j] = '_';
}


// give it to temporary board
void GiveEval(int x , int y) {	// x=-1 && y=-1 -> main Board
	if(x==-1 && y==-1) for(int i=0;i<N;i++) for(int j=0;j<N;j++) eval[i][j] = Mboard[i][j];
	else for(int i=0;i<N;i++) for(int j=0;j<N;j++) eval[i][j] = board[x][y][i][j];
}


// evaluate winner of a sub-board & Main Board
char GetWinner(int x , int y) {		// x=-1 && y=-1 -> main Board
	GiveEval(x , y);
	int sc = SubBoard();
	if(sc==score) return 'X';
	else if(sc==-score) return 'O';
	else if(sc==0) return 'T';
	else if(sc==-1) return '_';
	cerr<<  "HELLL NOO!" << endl;
	return '_';
}


// update Main Board whenever sub board is updated
void UpdateMainBoard(int x , int y) {
	Mboard[x][y] = GetWinner(x , y);
}


// Read Input
void ReadBoard() {
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) for(int k=0;k<N;k++) for(int l=0;l<N;l++) cin >> board[i][k][j][l]; 

	// converting board to my format
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			for(int k=0;k<N;k++) {
				for(int l=0;l<N;l++) {
					if(board[i][j][k][l]=='x') board[i][j][k][l] = 'X';
					else if(board[i][j][k][l]=='o') board[i][j][k][l] = 'O';
					else if(board[i][j][k][l]=='-') board[i][j][k][l] = '_';
				}
			}
		}
	}
}


// Each sub - board of size N x N
void PrintSubBoard(int x, int y) {
	cout << endl << "Sub Board " << x << "," << y << " :" << endl;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++){
			cout << board[x][y][i][j];
		}cout << endl;
	}
}


// ultimate board of size N x N
void PrintMainBoard() {
	cout << endl << "Main Board :" << endl;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			cout << Mboard[i][j];
		}cout << endl;
	}
}


// Complete Board of size N x N x N x N
void PrintFullBoard() {
	cout << endl << "Full Board :" << endl;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			for(int k=0;k<N;k++) {
				for(int l=0;l<N;l++) {
					cout << board[i][k][j][l];
				}
			}cout << endl;
		}
	}
}


// swap players if current player is 'O'
void SwapPlayers() {
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) {
			for(int k=0;k<N;k++) {
				for(int l=0;l<N;l++) { 
					if(board[i][j][k][l]=='X') board[i][j][k][l] = 'O';
					else if(board[i][j][k][l]=='O') board[i][j][k][l] = 'X';
				}
			}
		}
	}
}


int scoreline(int me , int opp) {
	if(opp==0) return (int)(pow(10 , me - 1));
	if(me==0) return (int)(pow(10 , opp - 1));
	return 0;
}


// Evaluate Half Played Board
int EvaluateMainBoard() {
	bool flag;
	int sc = 0 , me , opp;
	// left to right
	for(int i=0;i<N;i++) {
		flag = 0;
		me = 0;
		opp = 0;
		for(int j=0;j<N;j++) {
			if(eval[i][j]=='T') {
				flag = 1;
				break;
			}
			else if(eval[i][j]=='X') me++;
			else if(eval[i][j]=='O') opp++;
		}
		if(!flag) sc += scoreline(me , opp);
	}
	// top to bottom
	for(int j=0;j<N;j++) {
		flag = 0;
		me = 0;
		opp = 0;
		for(int i=0;i<N;i++) {
			if(eval[i][j]=='T') {
				flag = 1;
				break;
			}
			else if(eval[i][j]=='X') me++;
			else if(eval[i][j]=='O') opp++;
		}
		if(!flag) sc += scoreline(me , opp);
	}

	// diagnol - 1
	me = 0; 
	opp = 0;
	flag = 0;
	for(int i=0;i<N;i++) {
		if(eval[i][i]=='T') {
			flag = 1;
			break;
		}
		else if(eval[i][i]=='X') me++;
		else if(eval[i][i]=='O') opp++;
	}
	if(!flag) sc += scoreline(me , opp);

	// diagnol - 2
	me = 0; 
	opp = 0;
	flag = 0;
	for(int i=0;i<N;i++) {
		if(eval[i][N-i-1]=='T') {
			flag = 1;
			break;
		}
		else if(eval[i][N-i-1]=='X') me++;
		else if(eval[i][N-i-1]=='O') opp++;
	}
	if(!flag) sc += scoreline(me , opp);
	return sc;
}


// minimax with alpha-beta pruning
int minimax(int x , int y , int turn , int depth , int alpha , int beta) {
	char MainWinner = GetWinner(-1 , -1);
	if(MainWinner=='_') {		// no winner
		if(depth==MAX_DEPTH) {		// no particular winner but Max depth reached so evaluate half played board
			GiveEval(-1 , -1);
			int sc = EvaluateMainBoard();
			return sc;
		}
		else {				// max depth not reached continue
			if(turn) {		// maximizer
				int best = -INF;
				if((x==-1 && y==-1) || (Mboard[x][y]=='X') || (Mboard[x][y]=='O') || (Mboard[x][y]=='T')) {
					// now he can go to any empty space
					for(int i=0;i<N;i++) {
						for(int j=0;j<N;j++) {
							for(int k=0;k<N;k++) {
								for(int l=0;l<N;l++) {
									if(board[i][j][k][l]=='_') {
										board[i][j][k][l] = 'X';
										UpdateMainBoard(i , j);
										best = max(best , minimax(k , l , turn^1 , depth + 1 , alpha , beta));
										alpha = max(alpha , best);
										board[i][j][k][l] = '_';
										UpdateMainBoard(i , j);
										if(beta <= alpha) break;
									}
								}
								if(beta <= alpha) break;
							}
							if(beta <= alpha) break;
						}
						if(beta <= alpha) break;
					}
					return best;
				}
				else {		// fixed
					for(int k=0;k<N;k++) {	
						for(int l=0;l<N;l++) {
							if(board[x][y][k][l]=='_') {
								board[x][y][k][l] = 'X';
								UpdateMainBoard(x , y);
								best = max(best , minimax(k , l , turn^1 , depth + 1 , alpha , beta));
								alpha = max(alpha , best);
								board[x][y][k][l] = '_';
								UpdateMainBoard(x , y);
								if(beta <= alpha) break;
							}
						}
						if(beta <= alpha) break;
					}
					return best;
				}
			}
			else {		// minimizer
				int best = INF;
				if((x==-1 && y==-1) || (Mboard[x][y]=='X') || (Mboard[x][y]=='O') || (Mboard[x][y]=='T')) {
					// now he can go to any empty space
					for(int i=0;i<N;i++) {
						for(int j=0;j<N;j++) {
							for(int k=0;k<N;k++) {
								for(int l=0;l<N;l++) {
									if(board[i][j][k][l]=='_') {
										board[i][j][k][l] = 'O';
										UpdateMainBoard(i , j);
										best = min(best , minimax(k , l , turn^1 , depth + 1 , alpha , beta));
										beta = min(beta , best);
										board[i][j][k][l] = '_';
										UpdateMainBoard(i , j);
										if(beta <= alpha) break;
									}
								}
								if(beta <= alpha) break;
							}
							if(beta <= alpha) break;
						}
						if(beta <= alpha) break;
					}
					return best;
				}
				else {		// fixed
					for(int k=0;k<N;k++) {
						for(int l=0;l<N;l++) {
							if(board[x][y][k][l]=='_') {
								board[x][y][k][l] = 'O';
								UpdateMainBoard(x , y);
								best = min(best , minimax(k , l , turn^1, depth + 1 , alpha , beta));
								beta = min(beta , best);
								board[x][y][k][l] = '_';
								UpdateMainBoard(x , y);
								if(beta <= alpha) break;
							}
						}
						if(beta <= alpha) break;
					}
					return best;
				}
			}
		}	
	}
	else {	// we got some winner or tie
		if(MainWinner=='T') return 0;
		else {
			GiveEval(-1 , -1);
			int sc = SubBoard();
			if(sc==score) return sc - depth;
			else return sc + depth;
		}
	}
}


// Get Best Move for 'X'
pair < PII , PII > GetBestMove(int x , int y) {
	int best = -INF , tmpbest;	
	pair < int , int > Mans;	// Main block ans
	pair < int , int > Sans;	// Sub block ans 
	if((x==-1 && y==-1) || (Mboard[x][y]=='X') || (Mboard[x][y]=='O') || (Mboard[x][y]=='T')) {
		// now he can go to any empty space
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++) {
				for(int k=0;k<N;k++) {
					for(int l=0;l<N;l++) {
						if(board[i][j][k][l]=='_') {
							board[i][j][k][l] = 'X';
							UpdateMainBoard(i, j);		// update Main board for every sub board change
							tmpbest = minimax(k , l , 0 , 0 , -INF , INF);
							if(best < tmpbest) {
								best = tmpbest;
								Mans = {i , j};
								Sans = {k , l};
							}
							board[i][j][k][l] = '_';
							UpdateMainBoard(i , j);		// update Main board for every sub board change
						}
					}
				}
			}
		}
	}
	else {	// we should go to suggested block
		Mans = {x , y};		// fixed
		for(int k=0;k<N;k++) {
			for(int l=0;l<N;l++) {
				if(board[x][y][k][l]=='_') {
					board[x][y][k][l] = 'X';
					UpdateMainBoard(x , y);				// update Main board for every sub board change
					tmpbest = minimax(k , l , 0 , 0 , -INF , INF);
					if(best < tmpbest) {
						best = tmpbest;
						Sans = {k , l};
					}
					board[x][y][k][l] = '_';
					UpdateMainBoard(x , y);				// update Main board for every sub board change
				}
			}
		}
	}
	//cout << endl << "score for position = " << best << endl;
	board[Mans.first][Mans.second][Sans.first][Sans.second] = 'X';
	return {Mans , Sans};
}

/*  STEPS:

1. Read Board
2. Player
3. Start Block

*/

int main(int argc, char const *argv[])
{
	//freopen("input.txt" ,"r" , stdin);
	//freopen("output.txt" , "w", stdout);
	
	init();

	// read player 
	bool PlayersSwapped = 0;
	char player;
	cin >> player;

	// Start block for X
	int x, y;
	cin >> x >> y;

	// Read Board
	ReadBoard();


	// Print Board before best move
	//PrintFullBoard();

	// if X then OK else change
	if(player=='O' || player=='o') {
		SwapPlayers();
		PlayersSwapped = 1;
	}

	// now get Main board for given board
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) UpdateMainBoard(i , j);

	// now get best move for X
	pair < PII , PII > bstmove = GetBestMove(x , y);
	//cout << endl << "BEST move is : " << endl;
	cout << bstmove.first.first << " " << bstmove.first.second << " ";
	cout << bstmove.second.first << " " << bstmove.second.second << endl;


	// if players are swapped return to normal
	if(PlayersSwapped) {
		SwapPlayers();
		PlayersSwapped = 0;
	}

	// Print Full Board after best move
	//PrintFullBoard();
	return 0;
}