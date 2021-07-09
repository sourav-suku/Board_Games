# Board_Games
Programming AI agents to play `Tic Tac Toe` using Minimax Algorithm and  `Minesweeper Game` based on its available knowledge base.
# Tic Tac Toe
Tic Tac Toe is a two player game played on a 3x3 gameboard where each player tries to place cross('x') or nought('o') along a row,coloumn or a diagonal.Here an AI agent is programmed such that given any initial board state it returns the best move the player can make.
# Minimax Algorithm
Minimax Algorithm is a backtracking algorithm used to solve two-player games where one player tries to maximise some score whereas the other tries to minimise the same. So the algorithm explores all the moves which a player can possibly make and returns the best move considering the fact that other player plays optimally. The moves are scaled on the basis of the values they return which are assigned on the basis of some evaluation function. A move leading to victory gets higher score whereas the move leading to a draw or failure will get low score accordingly.
\
Here the maximiser can be the player who plays the cross('x') and minimiser the player who plays the nought('o'). 
\
Since minimax algorithm explores all paths an upper bound to number of moves ot take is 9!. To optimise on it `Zobrist Hashing` and `Alpha Beta Pruninng` is added. Zobrist Hashing maps the hash of a particular board state to value obtained and whenever the board state is encountered again in the search the evaluated value is simply returned. Alpha Beta Pruning prunes the game tree by not exploring the moves which are guarenteed to not improve the answer.
# Minesweeper
Minesweeper is a puzzle game that consists of a grid of cells, where some of the cells contain hidden “mines.” Clicking on a cell that contains a mine detonates the mine, and causes the user to lose the game. Clicking on a “safe” cell (i.e., a cell that does not contain a mine) reveals a number that indicates how many neighboring cells – where a neighbor is a cell that is one square to the left, right, up, down, or diagonal from the given cell – contain a mine.
\
The goal of the game is to flag (i.e., identify) each of the mines. The AI agent here plays the Minesweeper making the best move based on the available knowledge base. The game may not always end in victory as at some point agent don’t have enough information to make a safe move.
# Knowledge Representation
The AI's knowledge is represented as the following logical sentence:

{A, B, C, D, E, F, G, H} = 1

where {A, B, C etc.} are a set of cells, and the number 1 is the count of mines among those cells. This representation allows the following inferences to be made, e.g.:

{D, E} = 0 This implies that none of D, E contain mines, i.e. all are safe cells.

{A, B, C} = 3 This implies that all cells A, B, C contain a mine.

Furthermore, in general when we have two sentences where sentence A is a subset of sentence B, a new sentence can be infered:

setB - setA = countB - countA

Hence while playing minesweeper and clicking on cells, logical sentences are added to the AI's knowledge base. Often as a new sentence is added to the knowledge base, further inferences can be made allowing the identification of mines or safe spaces.
# Usage 
`MineSweeper`
\
Requires Python(3) and Python package installer pip(3) to run 
\
Run Game: $python3 runner.py




