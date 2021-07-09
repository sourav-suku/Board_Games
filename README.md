# Board_Games
Programming AI agents to play `Tic Tac Toe` using Minimax Algorithm and  `Minesweeper Game` using propositional logic.
# Tic Tac Toe
Tic Tac Toe is a two player game played on a 3x3 gameboard where each player tries to place cross('x') or nought('o') along a row,coloumn or a diagonal.Here an AI agent is programmed such that given any initial board state it returns the best move the player can make.
# Minimax Algorithm
Minimax Algorithm is a backtracking algorithm used to solve two-player games where one player tries to maximise some score whereas the other tries to minimise the same. So the algorithm explores all the moves which a player can possibly make and returns the best move considering the fact that other player plays optimally. The moves are scaled on the basis of the values they return which are assigned on the basis of some evaluation function. A move leading to victory gets higher score whereas the move leading to a draw or failure will get low score accordingly.
\
Here the maximiser can be the player who plays the cross('x') and minimiser the player who plays the nought('o'). 
\
Since minimax algorithm explores all paths an upper bound to number of moves ot take is 9!. To optimise on it `Zobrist Hashing` and `Alpha Beta Pruninng` is added. Zobrist Hashing maps the hash of a particular board state to value obtained and whenever the board state is encountered again in the search the evaluated value is simply returned. Alpha Beta Pruning prunes the game tree by not exploring the moves which are guarenteed to not improve the answer.
# Minesweeper
Mine
# Usage 
`MineSweeper`
\
Requires Python(3) and Python package installer pip(3) to run 
\
Run Game: $python3 runner.py




