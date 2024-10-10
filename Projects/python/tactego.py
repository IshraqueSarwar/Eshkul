'''Filename: FILENAME.py
Author: Ayon Rahman
Date: 11/14/23
Section: 51
E-mail: ayonr1@umbc.edu
Description: A Python program to simulate a game of Tactego, a simplified version of Stratego.
The game involves two players with Red and Blue pieces,
 aiming to capture the enemy's flag or all enemy pieces on a 2D grid board.'''
import random

# Define constants for piece types and their strengths
FLAG = 'F'
ASSASSIN = 'A'
MINE = 'M'
SAPPER = 'S'


# Define a function to initialize the game board
def initialize_board(length, width):
    # Create an empty game board as a 2D list
    board = [[' ' for _ in range(width)] for _ in range(length)]
    return board


# Define a function to load pieces from a file
def load_pieces_from_file(filename):
    # Implement code to read the pieces from the file and create a list of pieces
    # Each piece should have a type (FLAG, ASSASSIN, MINE, SAPPER, or a number for strength)
    # and a count indicating how many of that piece type there are.
    pieces = []
    # Read the file and populate the pieces list
    f = open(filename, 'r')
    raw_data = f.readlines()
    for line in raw_data:
        l = line.replace('\n','').split(' ')
        for i in range(int(l[1])):
            pieces.append(l[0])

    return pieces


# Define a function to display the current state of the board
def display_board(board):
    # Implement code to print the board with appropriate formatting
    row_size = len(board)
    column_size = len(board[0])
    lines = []
    for i in range(len(board)):
        line = '  '
        for j in range(len(board[i])):
            if board[i][j] !=' ':
                line+=board[i][j]+'  '
            else:
                line+='    '
        lines.append(line)

    for r in range(row_size+1):
        # if first row we put the numbers
        if r == 0:
            Header = '   0'
            for i in range(column_size-1):
                Header+= '   '+str(i+1)
            print(Header)
        else:
            print(str(r-1)+lines[r-1])




# Define a function to place pieces randomly on the board
def place_pieces_on_board(board, pieces, player):
    # Implement code to place pieces on the board according to the rules you provided
    random.shuffle(pieces)
    pieces_left_to_place = len(pieces)
    if player == 'Red':
        for r in range(len(board)):
            for c in range(len(board[r])):
                if pieces_left_to_place:
                    board[r][c] = 'R'+ pieces[len(pieces)-pieces_left_to_place]
                    pieces_left_to_place-=1

    else:
        for r in range(len(board),0,-1):
            for c in range(len(board[r-1])):
                if pieces_left_to_place:
                    board[r-1][c] = 'B'+ pieces[len(pieces)-pieces_left_to_place]
                    pieces_left_to_place-=1
        



def is_starting_position_valid(board, player, start_position):
    is_valid = True
    if player == 'Red':
        if board [int(start_position[0])] [int(start_position[1])] [0]!='R':
            is_valid = False
        if board [int(start_position[0])] [int(start_position[1])] == 'RF' or board [int(start_position[0])] [int(start_position[1])] == ' ':
            print('You must select a starting position with one of your pieces, not a flag.')
            is_valid = False
    else:
        if board [int(start_position[0])] [int(start_position[1])] [0]!='B':
            is_valid = False
        if board [int(start_position[0])] [int(start_position[1])] == 'BF' or board [int(start_position[0])] [int(start_position[1])] == ' ':
            print('You must select a starting position with one of your pieces, not a flag.')
            is_valid = False
    return is_valid




def is_ending_position_valid(board, player, start_position, end_position):
    is_valid = True
    
    row_size = len(board)
    column_size = len(board[0])

    endx = int(end_position[0])
    endy = int(end_position[1])

    startx = int(start_position[0])
    starty = int(start_position[1])

    # check of x-coord is within rowsize and 0
    # And y-coord is within colsize and 0
    # the difference between (start x and end x) and (start y and end y) is at most 1
    
    '''
    print((startx, starty), (endx, endy))
    print(abs(endx-startx))
    print(abs(endy- starty ))'''

    if (endx>=row_size or endx<0) or (endy>=column_size or endy<0) or (abs(endx-startx) > 1) or (abs(endy- starty)>1):
        is_valid = False

    # and the end pos doesn't contain its own piece or flag
    if (player == 'Blue' and board[endx][endy][0] == 'B') or (player == 'Red' and board[endx][endy][0] == 'R'):
        is_valid = False

    if (player == 'Blue' and board[endx][endy] == 'BF') or (player == 'Red' and board[endx][endy] == 'RF'):
        is_valid = False

    return is_valid



# Define a function to check if a move is valid
def is_valid_move(board, player, start_position, end_position):
    # Implement code to check if the move is valid according to the game rules
    is_valid = False
    
    
    #cleaning the input string coordinates to list
    if end_position is None:
        is_valid = is_starting_position_valid(board, player, start_position)
    else:
        
        is_valid = is_ending_position_valid(board, player, start_position, end_position)
        
    return is_valid




# Define a function to resolve combat between two pieces
def resolve_combat(attacker, defender):
    # Implement code to determine the outcome of combat
    if defender[1]!='F':
        if int(attacker[1])>=int(defender[1]):
            return attacker
        else:
            return defender
    else:
        return attacker


def check_victory(board):
    rf_count = 0
    bf_count = 0
    for r in range(len(board)):
        for c in range(len(board[r])):
            if board[r][c] == 'RF':
                rf_count+=1
            elif board[r][c]=='BF':
                bf_count+=1

    game_over = False
    if not rf_count:
        game_over = True
        print('R has won the game')
    elif not bf_count:
        game_over = True
        print('B has won the game')
    return game_over



# Define a function to play the main game loop
def play_game(filename, length, width):
    # Initialize the game board
    board = initialize_board(length, width)

    # Load pieces from the file
    pieces = load_pieces_from_file(filename)

    # Randomly place pieces for both players
    place_pieces_on_board(board, pieces, 'Red')
    place_pieces_on_board(board, pieces, 'Blue')

    # Initialize other game-related variables, e.g., player's turn, victory condition
    player_red_turn = True
    game_over = False
    # Enter the main game loop
    while not game_over:
        # Display the current state of the board
        display_board(board)
        if player_red_turn:
            print("\nR Player's Turn: ")
        else:
            print("\nB Player's Turn: ")
        
        # Get the player's move (start_position and end_position)

        
        start_position = None
        end_position = None

        # Check if the move is valid
        
        while True:
            start_position = input("Select Piece to Move by Position >> ").strip().split(' ')
            if (player_red_turn and is_valid_move(board, 'Red', start_position, end_position)) or (not player_red_turn and is_valid_move(board, 'Blue', start_position, end_position)):
                    break
        
        while True:
            end_position = input("Select Position to move Piece >> ").strip().split(' ')
            if(player_red_turn and is_valid_move(board, 'Red', start_position, end_position)) or (not player_red_turn and is_valid_move(board, 'Blue', start_position, end_position)):
                    break

        # Move the piece on the board
        endx = int(end_position[0])
        endy = int(end_position[1])

        startx = int(start_position[0])
        starty = int(start_position[1])
        

        print((startx, starty), (endx, endy))

        # Resolve combat if necessary
        if board[endx][endy]!=' ':
            winner = resolve_combat(board[startx][starty], board[endx][endy])
        else:
            winner = board[startx][starty]
        print(winner)
        board[endx][endy] = winner
        board[startx][starty] = ' '

        # Check for victory condition
        game_over = check_victory(board)

        # Switch the player's turn
        player_red_turn = not player_red_turn

# Define the main function to start the game
def tactego(pieces_file, length, width):
    play_game(pieces_file, length, width)


if __name__ == '__main__':
    ### Actual submission code. uncomment this below
    random.seed(input('What is seed? '))
    file_name = input('What is the filename for the pieces? ')
    length = int(input('What is the length? '))
    width = int(input('What is the width? '))
    tactego(file_name, length, width)

    
    ### Inputs for testing purposes. comment out below
    # random.seed('asdf')
    # file_name = 'small_game.pieces'
    # length = 6
    # width = 4
    # tactego(file_name, length, width)
