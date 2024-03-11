# File: File Name
# Purpose: In this game 2 players pick a number from a list of numbers at their own turn and the
# player that picks 3 numbers that add up to 15 the first wins and if the list is finished and
# no one has 2 numbers that add up to 15 then it's a draw
# Author: Matthew Ashraf Moris Farag
# ID: 20230596

# player related variables
num_list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
player1_list = []
player2_list = []
player1_turn = True
player1_winner = True

# game_state to control when the game is on and off
game_state = True


# function to check if the sum of any three numbers in a list is equal 15
def check_sum(num_list):
    result = False
    for x in range(len(num_list) - 2):
        for y in range(x + 1, len(num_list) - 1):
            for z in range(y + 1, len(num_list)):
                if num_list[x] + num_list[y] + num_list[z] == 15:
                    result = True
    return result


while True:
    if num_list and game_state:
        # player one's turn:
        if player1_turn:
            # display both players lists and the remaining numbers
            print(f'The number list: {num_list}')
            print(f' player 1 picks: {player1_list}')
            print(f' player 2 picks: {player2_list}')
            # get the player input
            pick = int(input('player 1 pick a number:  '))
            if num_list.count(pick) == 1:
                # add the player's pick to the player's list and remove the pick from the remaining numbers
                player1_list.append(pick)
                pick_index = num_list.index(pick)
                num_list.pop(pick_index)
                player1_turn = False
                # check if any three numbers in the player's list add up to 15
                if check_sum(player1_list):
                    game_state = False
                    player1_winner = True

            else:
                print('number not available')

        # player two's turn:
        else:
            # display both players lists and the remaining numbers
            print(f'The number list: {num_list}')
            print(f' player 1 picks: {player1_list}')
            print(f' player 2 picks: {player2_list}')
            # get the player input
            pick = int(input('player 2 pick a number:  '))
            if num_list.count(pick) == 1:
                # add the player's pick to the player's list and remove the pick from the remaining numbers
                player2_list.append(pick)
                pick_index = num_list.index(pick)
                num_list.pop(pick_index)
                player1_turn = True
                # check if any three numbers in the player's list add up to 15
                if check_sum(player2_list):
                    game_state = False
                    player1_winner = False

            else:
                print('number not available')
    elif not num_list:
        # here no one won
        print('draw')
        # asking the user if he wants to play again or quit
        restart = int(input('1 to play again, and 2 to exit: '))
        if restart == 1:
            # resetting the players stats
            num_list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
            player1_list = []
            player2_list = []
            player1_turn = True
            game_state = True
        elif restart == 2:
            # quit
            break
        else:
            print('not a valid input')
    elif not game_state and player1_winner:
        # here player 1 won
        print('player 1 won!')
        # asking the user if he wants to play again or quit
        restart = int(input('1 to play again, and 2 to exit: '))
        if restart == 1:
            # resetting the players stats
            num_list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
            player1_list = []
            player2_list = []
            player1_turn = True
            game_state = True
        elif restart == 2:
            # quit
            break
        else:
            print('not a valid input')
    elif not game_state and not player1_winner:
        # player 2 won
        print('player 2 won!')
        # asking the user if he wants to play again or quit
        restart = int(input('1 to play again, and 2 to exit: '))
        if restart == 1:
            # resetting the players stats
            num_list = [1, 2, 3, 4, 5, 6, 7, 8, 9]
            player1_list = []
            player2_list = []
            player1_turn = True
            game_state = True
        elif restart == 2:
            # quit
            break
        else:
            print('not a valid input')

