# Mini-project #6 - Blackjack

import simplegui
import random

# load card sprite - 949x392 - source: jfitz.com
CARD_SIZE = (73, 98)
CARD_CENTER = (36.5, 49)
card_images = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/cards.jfitz.png")

CARD_BACK_SIZE = (71, 96)
CARD_BACK_CENTER = (35.5, 48)
card_back = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/card_back.png")    

# initialize some useful global variables
in_play = False
outcome = ""
score = 0

# define globals for cards
SUITS = ('C', 'S', 'H', 'D')
RANKS = ('A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K')
VALUES = {'A':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9, 'T':10, 'J':10, 'Q':10, 'K':10}

# define card class
class Card:
    def __init__(self, suit, rank):
        if (suit in SUITS) and (rank in RANKS):
            self.suit = suit
            self.rank = rank
        else:
            self.suit = None
            self.rank = None
            print "Invalid card: ", suit, rank

    def __str__(self):
        return self.suit + self.rank

    def get_suit(self):
        return self.suit

    def get_rank(self):
        return self.rank

    def draw(self, canvas, pos):
        card_loc = (CARD_CENTER[0] + CARD_SIZE[0] * RANKS.index(self.rank), 
                    CARD_CENTER[1] + CARD_SIZE[1] * SUITS.index(self.suit))
        canvas.draw_image(card_images, card_loc, CARD_SIZE, [pos[0] + CARD_CENTER[0], pos[1] + CARD_CENTER[1]], CARD_SIZE)
        
# define hand class
class Hand:
    def __init__(self):
        self.hand = [] # list of cards

    def __str__(self):
        return [str(card) for card in self.hand]

    def add_card(self, card):
        self.hand += [card]

    # count aces as 1, if the hand has an ace, then add 10 to hand value if it doesn't bust
    def get_value(self):
        values = [VALUES[card.rank] for card in self.hand]
        # the hand has 1 or more aces and adding 10 does not cause the hand to bust
        if (values.count(VALUES['A'])) and (sum(values) + 10 <= 21):
            return sum(values) + 10
        # the hand has no aces or adding 10 causes the hand to bust
        return sum(values)

    def busted(self):
        # unnecessary
        pass	# replace with your code
    
    def draw(self, canvas, pos):
        # handle card spacing
        increment = 100
        if len(self.hand) >= 5:
            increment = 50
        for card in self.hand:
            card.draw(canvas, pos)
            pos[0] += increment

# define deck class
class Deck:
    def __init__(self):
        self.deck = [Card(suit, rank) for suit in SUITS for rank in RANKS]
        random.shuffle(self.deck)

    # add cards back to deck and shuffle
    def shuffle(self):
        self.__init__()

    def deal_card(self):
        return self.deck.pop(0)
    
    def __str__(self):
        return self.deck



#define event handlers for buttons
def deal():
    global outcome, in_play, score, player_hand, dealer_hand, deck
    # player loses the hand if "Deal" button is hit in the middle of the hand
    if in_play:
        score -= 1
    # create the hands and initializes the deck
    player_hand = Hand()
    dealer_hand = Hand()
    deck = Deck()
    # deals cards to the player and the dealer
    for n in range(2):
        player_hand.add_card(deck.deal_card())
        dealer_hand.add_card(deck.deal_card())
    # display hands in console (for debugging)
#    print "Player Hand:", str(player_hand), player_hand.get_value()
#    print "Dealer Hand:", str(dealer_hand), dealer_hand.get_value()
    outcome = ""
    in_play = True

def hit():
    global outcome, in_play, score, player_hand, deck
    if in_play: # if the hand is in play, hit the player
        player_hand.add_card(deck.deal_card())
        # if busted, assign a message to outcome, update in_play and score
        if player_hand.get_value() > 21:
            outcome = "You went bust and lose!"
            in_play = False
            score -= 1

def stand():
    global outcome, in_play, score, player_hand, dealer_hand, deck
    if in_play:
        # if hand is in play, repeatedly hit dealer until his hand has value 17 or more
        while dealer_hand.get_value() < 17:
            dealer_hand.add_card(deck.deal_card())
        # assign a message to outcome, update in_play and score
        if dealer_hand.get_value() > 21:
            outcome = "Dealer busts! You win!"
            score += 1
        elif player_hand.get_value() <= dealer_hand.get_value():
            outcome = "Sorry, you lose!"
            score -= 1
        else:
            outcome = "Congratulations, you win!"
            score += 1
        in_play = False

# draw handler
def draw(canvas):
    canvas.draw_text("Blackjack", [75, 100], 40, "Cyan")
    canvas.draw_text("Dealer", [50, 175], 25, "Black")
    canvas.draw_text("Player", [50, 375], 25, "Black")
    canvas.draw_text("Score: " + str(score), [400, 100], 25, "Black")
    canvas.draw_text(outcome, [200, 175], 25, "Black")
    
    player_hand.draw(canvas, [100, 400])
    dealer_hand.draw(canvas, [100, 200])
    
    if in_play:
        canvas.draw_text("Hit or stand?", [200, 375], 25, "Black")
        canvas.draw_image(card_back, CARD_BACK_CENTER, CARD_BACK_SIZE, [101 + CARD_BACK_CENTER[0], 201 + CARD_BACK_CENTER[1]], CARD_BACK_SIZE)
    else:
        canvas.draw_text("New deal?", [200, 375], 25, "Black")

# initialization frame
frame = simplegui.create_frame("Blackjack", 600, 600)
frame.set_canvas_background("Green")

#create buttons and canvas callback
frame.add_button("Deal", deal, 200)
frame.add_button("Hit",  hit, 200)
frame.add_button("Stand", stand, 200)
frame.set_draw_handler(draw)

# deal an initial hand
player_hand = Hand()
dealer_hand = Hand()
deck = Deck()
deal()

# get things rolling
frame.start()

# remember to review the gradic rubric