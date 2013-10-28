# template for "Stopwatch: The Game"
import simplegui

# define global variables
current_time = 0  # global integer timer
tenths = 0        # tenths of a second (for checking whole second)
x = 0             # number of successful stops
y = 0             # number of total stops
is_stopped = True # boolean check for a stopped timer

# define helper function format that converts integer
# counting tenths of seconds into formatted string A:BC.D
def format_time(t):
    # formats integer time into a string
    global tenths
    mins = int(t / 600)
    secs = int((t % 600) / 10)
    tenths = t % 10
    return "%d:%02d.%d" % (mins, secs, tenths)

# define event handlers for buttons; "Start", "Stop", "Reset"
def start_button_handler():
    # event handler for the start button
    global is_stopped
    timer.start()
    is_stopped = False

def stop_button_handler():
    # event handler for the stop button
    global is_stopped, x, y
    timer.stop()
    if not is_stopped:
        is_stopped = True
        y = y + 1
        if tenths == 0:
            x = x + 1

def reset_button_handler():
    # event handler for the reset button
    global current_time, x, y
    timer.stop()
    current_time = 0
    x = 0
    y = 0

# define event handler for timer with 0.1 sec interval
def timer_handler():
    global current_time
    current_time = current_time + 1

# define event handler responsible for all the drawing
def draw_handler(canvas):
    canvas.draw_text(format_time(current_time), (50, 90), 30, "White")
    canvas.draw_text(str(x) + "/" + str(y), (10, 25), 20, "Green")

# create frame
frame = simplegui.create_frame("Stopwatch: The Game", 200, 150)

# register event handlers
timer = simplegui.create_timer(100, timer_handler)
frame.set_draw_handler(draw_handler)
frame.add_button("Start", start_button_handler, 100)
frame.add_button("Stop", stop_button_handler, 100)
frame.add_button("Reset", reset_button_handler, 100)

# start frame
frame.start()

# remember to review the grading rubric