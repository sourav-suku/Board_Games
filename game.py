import sys
import time

from minesweeper import Minesweeper, MinesweeperAI

HEIGHT = 8
WIDTH = 8
MINES = 8

# Create game and AI agent
game = Minesweeper(height=HEIGHT, width=WIDTH, mines=MINES)
ai = MinesweeperAI(height=HEIGHT, width=WIDTH)


# Keep track of revealed cells, flagged cells, and if a mine was hit
revealed = set()
lost = False
ok=True

def printboard( ):
    # Draw board
    for i in range(HEIGHT):
        for j in range(WIDTH):
            if (i,j) in ai.mines:
                print("* ",end="")
            elif (i,j) in revealed:
                print(str(game.nearby_mines((i, j))),end="")
                print(" ",end="")
            else:
                print("_ ",end="")
        print( )
    print( )

while ok:
    move = None

    # If AI button clicked, make an AI move
    if  not lost:
        move = ai.make_safe_move()
        if move is None:
            move = ai.make_random_move()
            if move is None:
                print("No moves left to make.")
            else:
                print("No known safe moves, AI making random move.")
        else:
            print("AI making safe move.")
        time.sleep(0.3)

    # Make move and update AI knowledge
    if move:
        if game.is_mine(move):   #
            lost = True   
        else:
            nearby = game.nearby_mines(move)#
            revealed.add(move) #
            ai.add_knowledge(move, nearby) #
    if lost:
        ok=False
    if game.mines==ai.mines:
        ok=False
    printboard( )
if lost:
    printboard( )
    print("The AI lost")
elif game.mines==ai.mines:
    print("The AI won")         
