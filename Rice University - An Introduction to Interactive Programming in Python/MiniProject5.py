# implementation of card game - Memory

import simplegui
import random

card_list = []      # list of card pairs numbering [0,8)
exposed = []        # list indicating whether the card is exposed or not
game_state = 0      # 0 = start of the game; 1 = one card exposed; 2 = end of turn
pair_idx = [-1, -1] # keeps track of the index of the pair of cards clicked
num_turns = 0       # keeps track of the number of turns

# helper function to initialize globals
def init():
    global card_list, exposed, game_state, num_turns
    # setup the card deck and their tags (exposed or not)
    card_list = [i % 8 for i in range(16)]
    random.shuffle(card_list)
    exposed = [False for i in range(16)]
    # reset the game state and score
    game_state = 0
    num_turns = 0
    label.set_text("Moves = " + str(num_turns))

# define event handlers
def mouseclick(pos):
    global game_state, num_turns
    idx = pos[0] // 50 # cards have width (x value) 50
    if not exposed[idx]:
        exposed[idx] = True # tag the card as exposed
        if game_state == 0:
            pair_idx[0] = idx   # remember the index of the first card
            game_state = 1      # move on to the next game state
            num_turns += 1      # increment the number of turns taken
            label.set_text("Moves = " + str(num_turns))
        elif game_state == 1:
            pair_idx[1] = idx   # remember the index of the second card
            game_state = 2      # move on to the next game state
        else: # game_state == 2
            if card_list[pair_idx[0]] != card_list[pair_idx[1]]: # check for paired cards
                exposed[pair_idx[0]] = False # cover the non-matching pairs
                exposed[pair_idx[1]] = False # cover the non-matching pairs
            pair_idx[0] = idx   # remember the index of the first card
            game_state = 1      # move on to the next game state
            num_turns += 1      # increment the number of turns taken
            label.set_text("Moves = " + str(num_turns))

# cards are logically 50x100 pixels in size    
def draw(canvas):
    for idx in range(len(card_list)):
        # the left, right, top, bottom (x, y) coordinates
        xl, xr, yt, yb = 0+idx*50, 49+idx*50, 0, 99
        if exposed[idx]:
            canvas.draw_polygon([(xl, yt), (xr, yt), (xr, yb), (xl, yb)], 1, "Red", "Black")
            canvas.draw_text(str(card_list[idx]), (10+idx*50, 70), 45, "White")
        else:
            canvas.draw_polygon([(xl, yt), (xr, yt), (xr, yb), (xl, yb)], 1, "Red", "Green")

# create frame and add a button and labels
frame = simplegui.create_frame("Memory", 800, 100)
frame.add_button("Restart", init)
label = frame.add_label("Moves = 0")

# initialize global variables
init()

# register event handlers
frame.set_mouseclick_handler(mouseclick)
frame.set_draw_handler(draw)

# get things rolling
frame.start()

# always remember to review the grading rubric