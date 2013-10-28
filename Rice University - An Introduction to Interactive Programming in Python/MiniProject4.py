# Implementation of classic arcade game Pong
import simplegui
import random

# initialize globals - pos and vel encode vertical info for paddles
WIDTH = 600
HEIGHT = 400       
BALL_RADIUS = 20
PAD_WIDTH = 8
PAD_HEIGHT = 80
HALF_PAD_WIDTH = PAD_WIDTH / 2
HALF_PAD_HEIGHT = PAD_HEIGHT / 2
PAD_SPEED = 4 # change this to change the movement speed (constant) of the pads

# helper function that spawns a ball, returns a position vector and a velocity vector
# if right is True, spawn to the right, else spawn to the left
def ball_init(right):
    global ball_pos, ball_vel # these are vectors stored as lists
    
    ball_pos = [WIDTH/2, HEIGHT/2]
    x_vel = random.randrange(2, 4)
    y_vel = random.randrange(1, 3)
    if right == True: # ball goes upwards and to the right
        ball_vel = [x_vel, -y_vel]
    else: # ball goes upwards and to the left
        ball_vel = [-x_vel, -y_vel]

# define event handlers
def init():
    global paddle1_pos, paddle2_pos, paddle1_vel, paddle2_vel  # these are floats
    global score1, score2  # these are ints
    
    paddle1_pos = HEIGHT/2
    paddle2_pos = HEIGHT/2
    paddle1_vel = 0
    paddle2_vel = 0
    score1 = 0
    score2 = 0
    ball_init(True)

def draw(c):
    global score1, score2, paddle1_pos, paddle2_pos, ball_pos, ball_vel
 
    # update paddle's vertical position, keep paddle on the screen
    if paddle1_pos <= HALF_PAD_HEIGHT:
        paddle1_pos += 1
    elif paddle1_pos >= HEIGHT-1-HALF_PAD_HEIGHT:
        paddle1_pos -= 1
    else:
        paddle1_pos += paddle1_vel
    if paddle2_pos <= HALF_PAD_HEIGHT:
        paddle2_pos += 1
    elif paddle2_pos >= HEIGHT-1-HALF_PAD_HEIGHT:
        paddle2_pos -= 1
    else:
        paddle2_pos += paddle2_vel
        
    # draw mid line and gutters
    c.draw_line([WIDTH / 2, 0],[WIDTH / 2, HEIGHT], 1, "White")
    c.draw_line([PAD_WIDTH, 0],[PAD_WIDTH, HEIGHT], 1, "White")
    c.draw_line([WIDTH - PAD_WIDTH, 0],[WIDTH - PAD_WIDTH, HEIGHT], 1, "White")
    
    # draw paddles
    c.draw_line([HALF_PAD_WIDTH, paddle1_pos - HALF_PAD_HEIGHT], [HALF_PAD_WIDTH, paddle1_pos + HALF_PAD_HEIGHT], 8, "White")
    c.draw_line([WIDTH - HALF_PAD_WIDTH, paddle2_pos - HALF_PAD_HEIGHT], [WIDTH - HALF_PAD_WIDTH, paddle2_pos + HALF_PAD_HEIGHT], 8, "White")
     
    # update ball
    ball_pos[0] += ball_vel[0]
    ball_pos[1] += ball_vel[1]
    
    # top/bottom wall collision
    if ball_pos[1] <= BALL_RADIUS or ball_pos[1] >= HEIGHT-1-BALL_RADIUS:
        ball_vel[1] = -ball_vel[1]
    
    # left/right gutter collision
    if ball_pos[0] <= BALL_RADIUS+PAD_WIDTH:
        if ball_pos[1] >= paddle1_pos - HALF_PAD_HEIGHT and ball_pos[1] <= paddle1_pos-1+HALF_PAD_HEIGHT:
            ball_vel[0] = -ball_vel[0]*1.1 # 10% speed increase
        else:
            score2 += 1
            ball_init(True)
    elif ball_pos[0] >= WIDTH-1-BALL_RADIUS-PAD_WIDTH:
        if ball_pos[1] >= paddle2_pos - HALF_PAD_HEIGHT and ball_pos[1] <= paddle2_pos-1+HALF_PAD_HEIGHT:
            ball_vel[0] = -ball_vel[0]*1.1 # 10% speed increase
        else:
            score1 += 1
            ball_init(False)
    
    # draw ball and scores
    c.draw_circle(ball_pos, BALL_RADIUS, 2, "Red", "White")
    c.draw_text(str(score1), (WIDTH/2 - HEIGHT/4, HEIGHT/4), 36, "White")
    c.draw_text(str(score2), (WIDTH/2 + HEIGHT/4, HEIGHT/4), 36, "White")
    
def keydown(key):
    global paddle1_vel, paddle2_vel
    if key == simplegui.KEY_MAP["w"]:
        paddle1_vel = -PAD_SPEED
    elif key == simplegui.KEY_MAP["s"]:
        paddle1_vel = PAD_SPEED
    elif key == simplegui.KEY_MAP["up"]:
        paddle2_vel = -PAD_SPEED
    elif key == simplegui.KEY_MAP["down"]:
        paddle2_vel = PAD_SPEED
   
def keyup(key):
    global paddle1_vel, paddle2_vel
    if key == simplegui.KEY_MAP["w"]:
        paddle1_vel = 0
    elif key == simplegui.KEY_MAP["s"]:
        paddle1_vel = 0
    elif key == simplegui.KEY_MAP["up"]:
        paddle2_vel = 0
    elif key == simplegui.KEY_MAP["down"]:
        paddle2_vel = 0

# create frame
frame = simplegui.create_frame("Pong", WIDTH, HEIGHT)
frame.set_draw_handler(draw)
frame.set_keydown_handler(keydown)
frame.set_keyup_handler(keyup)
frame.add_button("Restart", init, 100)


# start frame
init()
frame.start()

