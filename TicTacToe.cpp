// C++ program to find the next optimal move for any initial board state
#include<bits/stdc++.h>
using namespace std;
mt19937 mt(01234567);
struct cell{
    int x,y;
};
typedef struct cell cell;

//Generates a Randome number from 0 to 2^64-1
unsigned long long int randomInt(){
    uniform_int_distribution<unsigned long long int> dist(0, UINT64_MAX);
    return dist(mt);
}

char cross = 'x', nought = 'o';

class TicTacToe{
    public:
    vector<vector<char> > board;
    vector<vector<vector<unsigned long long int> > >  ZobristTable;
    unordered_map<unsigned long long int,int> bestScore;
    TicTacToe(vector<vector<char> > x){
        board.assign(3,vector<char>(3));
        ZobristTable.assign(3,vector<vector<unsigned long long int> >(3,vector<unsigned long long int>(2)));
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                board[i][j]=x[i][j];
            }
        }
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                for(int k=0;k<2;++k){
                    ZobristTable[i][j][k]=randomInt( );
                }
            }
        }
    }

    //If cross wins score will be +10
    //If nought wins score will be -10
    //Else score will be 0
    int evaluate( ){
        // Checking for coloumns
        for(int c=0;c<3;++c){
            unordered_map<char,int> cnt;
            for(int r=0;r<3;++r){
                ++cnt[board[r][c]];
            }
            if(cnt['x']==3)return +10;
            else if(cnt['o']==3)return -10;
        }

        // Checking for rows
        for(int r=0;r<3;++r){
            unordered_map<char,int> cnt;
            for(int c=0;c<3;++c){
                ++cnt[board[r][c]];
            }
            if(cnt['x']==3)return +10;
            else if(cnt['o']==3)return -10;
        }

        // Checking for Diagonals
        unordered_map<char,int> cnt;
        int r=0,c=0;
        while(r<3&&c<3){
            ++cnt[board[r][c]];
            ++r;    ++c;
        }
        if(cnt['x']==3)return +10;
        else if(cnt['o']==3)return -10;

        cnt.clear( );
        r=0,c=2;
        while(r<3&&c>=0){
            ++cnt[board[r][c]];
            ++r;    --c;
        }
        if(cnt['x']==3)return +10;
        else if(cnt['o']==3)return -10;

        // No victory yet for cross or nought
        return 0;
    }

    bool isMovesLeft( )
    {
        bool ok=false;
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                ok|=(board[i][j]=='_');
            }
        }
        return ok;
    }

    
    int minimax(bool isMax,int depth,int alpha,int beta,unsigned long long int hash){
        if(bestScore.find(hash)!=bestScore.end( )){
            return bestScore[hash];
        }
        int score = evaluate( );
        // If Maximizer has won the game return his/her
        // evaluated score 
        if (score == 10){
            bestScore.insert(make_pair(hash,score-depth));
            return score-depth;
        }
        //The evaluation function is created such that it ensures faster victory or delayed failure
        //Win at earlier depths will get greater score,so does failure at later depths
        if (score == -10){
            bestScore.insert(make_pair(hash,score+depth));
            return score+depth;
        }
        
        //Tie
        if (isMovesLeft( )==false){
            bestScore.insert(make_pair(hash,0));
            return 0;
        }
        if (isMax){
            int best = INT_MIN;
            for (int i = 0; i<3; i++){
                for (int j = 0; j<3; j++){
                    if (board[i][j]=='_'){
                        board[i][j] = cross;
                        hash^=ZobristTable[i][j][1];
                        best = max(best,minimax(!isMax,depth+1,alpha,beta,hash));
                        //Updating the value of alpha the best value the maximiser can provide at this level or above    
                        alpha=max(alpha,best);
                        // Undo the move
                        board[i][j] = '_';
                        hash^=ZobristTable[i][j][1];
                        //If the current maximiser is
                        if(alpha>=beta){
                            bestScore.insert(make_pair(hash,best));
                            return best;
                        }
                    }
                }
            }
            bestScore.insert(make_pair(hash,best));
            return best;
        }

        // If this minimizer's move
        else{
            int best = INT_MAX;

            // Traverse all cells
            for (int i = 0; i<3; i++){
                for (int j = 0; j<3; j++){
                    // Check if cell is empty
                    if (board[i][j]=='_'){
                        // Make the move
                        board[i][j] = nought;
                        hash^=ZobristTable[i][j][0];
                        // Call minimax recursively and choose
                        // the minimum value
                        best = min(best,minimax(!isMax,depth+1,alpha,beta,hash));
                        beta=min(best,beta);
                        // Undo the move
                        board[i][j] = '_';
                        hash^=ZobristTable[i][j][0];
                        if(beta<=alpha){
                            bestScore.insert(make_pair(hash,best));
                            return best;
                        }
                    }
                }
            }
            bestScore.insert(make_pair(hash,best));
            return best;
        }
    }

    // This will return the best possible move for the cross
    cell findBestMove( ){
        int bestVal = INT_MIN;
        cell bestMove;
        bestMove.x = -1;
        bestMove.y = -1;
        unsigned long long int hash=0;
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                if(board[i][j]!='_'){
                    if(board[i][j]=='o'){
                        hash^=ZobristTable[i][j][0];
                    }
                    else{
                        hash^=ZobristTable[i][j][1];
                    }
                }
            }
        }
        // Traverse all cells, evaluate minimax function for
        // all empty cells. And return the cell with optimal
        // value.
        for (int i = 0; i<3; i++){
            for (int j = 0; j<3; j++){
                // Check if cell is empty
                if (board[i][j]=='_'){
                    // Make the move
                    board[i][j] = cross;
                    hash^=ZobristTable[i][j][1];
                    // compute evaluation function for this
                    // move.
                    int moveVal = minimax(false,0,INT_MIN,INT_MAX,hash);

                    // Undo the move
                    board[i][j] = '_';
                    hash^=ZobristTable[i][j][1];
                    // If the value of the current move is
                    // more than the best value, then update
                    // best/
                    if (moveVal > bestVal){
                        bestMove.x = i;
                        bestMove.y = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        cout<<"The value of the best move is : "<<bestVal<<endl;

        return bestMove;
    }
};

// Driver code
int main()
{
	vector<vector<char> > board(3,vector<char>(3));
	//Reading the initial board state from the user
    cout<<"Enter the initial board state : "<<endl;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cin>>board[i][j];
        }
    }
    //Asking AI the best move
    TicTacToe* AI=new TicTacToe(board);
    cell bestMove = AI->findBestMove( );
	cout<<"The optimal move for the given board state is : ("<<bestMove.x<<","<<bestMove.y<<")"<<endl;
	return 0;
}
