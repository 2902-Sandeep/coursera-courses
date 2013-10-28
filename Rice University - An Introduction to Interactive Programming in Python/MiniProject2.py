# template for "Guess the number" mini-project
# input will come from buttons and an input field
# all output for the game will be printed in the console
import simplegui
import random
import math

# initialize global variables used in your code
secret_number = 0
number_of_guesses = 0
number_range = 100

# helper function to initialize a new game
def init():
    global secret_number, number_of_guesses
    secret_number = random.randrange(0, number_range)
    number_of_guesses = math.ceil(math.log(number_range, 2))
    
    print ""
    print "New game. Range is from 0 to", number_range
    print "Number of remaining guesses is", number_of_guesses

# define event handlers for control panel
def range100():
    # button that changes range to range [0,100) and restarts
    global number_range
    number_range = 100
    init()

def range1000():
    # button that changes range to range [0,1000) and restarts
    global number_range
    number_range = 1000
    init()

def get_input(guess):
    # main game logic goes here
    global number_of_guesses
    player_guess = int(guess)
    number_of_guesses = number_of_guesses - 1
    
    print ""
    print "Guess was", player_guess
    print "Number of remaining guesses is", number_of_guesses
    if player_guess < secret_number:
        print "Higher!"
        if number_of_guesses == 0:
            print "You are out of guesses. Sorry, you lose!"
            init()
    elif player_guess > secret_number:
        print "Lower!"
        if number_of_guesses == 0:
            print "You are out of guesses. Sorry, you lose!"
            init()
    else:
        print "Correct! You win!"
        init()

# create frame
frame = simplegui.create_frame("Guess the number", 200, 200)

# register event handlers for control elements
frame.add_button("Range is [0, 100)", range100, 200)
frame.add_button("Range is [0, 1000)", range1000, 200)
frame.add_input("Enter a guess", get_input, 200)

# start frame
init()
frame.start()

# always remember to check your completed program against the grading rubric