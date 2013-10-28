# program template for Spaceship
import simplegui
import math
import random

# globals for user interface
width = 800
height = 600
score = 0
lives = 3
time = 0

class ImageInfo:
    def __init__(self, center, size, radius = 0, lifespan = None, animated = False):
        self.center = center
        self.size = size
        self.radius = radius
        if lifespan:
            self.lifespan = lifespan
        else:
            self.lifespan = float('inf')
        self.animated = animated

    def get_center(self):
        return self.center

    def get_size(self):
        return self.size

    def get_radius(self):
        return self.radius

    def get_lifespan(self):
        return self.lifespan

    def get_animated(self):
        return self.animated

    
# art assets created by Kim Lathrop, may be freely re-used in non-commercial projects, please credit Kim
    
# debris images - debris1_brown.png, debris2_brown.png, debris3_brown.png, debris4_brown.png
#                 debris1_blue.png, debris2_blue.png, debris3_blue.png, debris4_blue.png, debris_blend.png
debris_info = ImageInfo([320, 240], [640, 480])
debris_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/debris2_blue.png")

# nebula images - nebula_brown.png, nebula_blue.png
nebula_info = ImageInfo([400, 300], [800, 600])
nebula_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/nebula_blue.png")

# splash image
splash_info = ImageInfo([200, 150], [400, 300])
splash_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/splash.png")

# ship image
ship_info = ImageInfo([45, 45], [90, 90], 35)
ship_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/double_ship.png")

# missile image - shot1.png, shot2.png, shot3.png
missile_info = ImageInfo([5,5], [10, 10], 3, 50)
missile_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/shot2.png")

# asteroid images - asteroid_blue.png, asteroid_brown.png, asteroid_blend.png
asteroid_info = ImageInfo([45, 45], [90, 90], 40)
asteroid_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/asteroid_blue.png")

# animated explosion - explosion_orange.png, explosion_blue.png, explosion_blue2.png, explosion_alpha.png
explosion_info = ImageInfo([64, 64], [128, 128], 17, 24, True)
explosion_image = simplegui.load_image("http://commondatastorage.googleapis.com/codeskulptor-assets/lathrop/explosion_alpha.png")

# sound assets purchased from sounddogs.com, please do not redistribute
soundtrack = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulptor-assets/sounddogs/soundtrack.mp3")
missile_sound = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulptor-assets/sounddogs/missile.mp3")
missile_sound.set_volume(.5)
ship_thrust_sound = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulptor-assets/sounddogs/thrust.mp3")
explosion_sound = simplegui.load_sound("http://commondatastorage.googleapis.com/codeskulptor-assets/sounddogs/explosion.mp3")

# helper functions to handle transformations
def angle_to_vector(ang):
    return [math.cos(ang), math.sin(ang)]

def dist(p,q):
    return math.sqrt((p[0]-q[0])**2+(p[1]-q[1])**2)


# Ship class
class Ship:
    def __init__(self, pos, vel, angle, image, info):
        self.pos = [pos[0],pos[1]]
        self.vel = [vel[0],vel[1]]
        self.thrust = False
        self.angle = angle
        self.angle_vel = 0
        self.image = image
        self.image_center = info.get_center()
        self.image_size = info.get_size()
        self.radius = info.get_radius()
        
        self.turn_speed = math.pi/32 # turning speed of the ship
        self.forward = [0, 0]        # the ship's forward vector
        self.forward_factor = 0.50   # fraction of the forward vector
        self.friction_factor = 0.95  # friction
        self.forward_multiple = 5    # multiple of the forward vector (for missile)
        
    def draw(self, canvas):
        # change the image center if thrusters are turned on
        image_center = [self.image_center[0] + self.image_size[0] if self.thrust else self.image_center[0], self.image_center[1]]
        # draw the ship
        canvas.draw_image(self.image, image_center, self.image_size, self.pos, self.image_size, self.angle)

    def update(self):
        # position update
        self.pos[0] = (self.pos[0] + self.vel[0]) % width
        self.pos[1] = (self.pos[1] + self.vel[1]) % height
        # velocity update
        self.vel[0] *= self.friction_factor
        self.vel[1] *= self.friction_factor
        # angle update
        self.angle += self.angle_vel
        # compute forward vector and update velocity
        self.forward = angle_to_vector(self.angle)
        if self.thrust:
            self.vel[0] += (self.forward[0]*self.forward_factor)
            self.vel[1] += (self.forward[1]*self.forward_factor)
    
    def increment_angle_vel(self):
        self.angle_vel = self.turn_speed
    
    def decrement_angle_vel(self):
        self.angle_vel = -self.turn_speed
    
    def reset_angle_vel(self):
        self.angle_vel = 0
    
    def toggle_thrusters(self, thrusters_val):
        self.thrust = thrusters_val
        if self.thrust:
            ship_thrust_sound.play()
        else:
            ship_thrust_sound.pause()
            ship_thrust_sound.rewind()
    
    def shoot(self):
        global a_missile
        position = [self.pos[0] + self.forward[0]*self.image_size[0]/2, self.pos[1] + self.forward[1]*self.image_size[1]/2]
        velocity = [self.vel[0] + self.forward[0]*self.forward_multiple, self.vel[1] + self.forward[1]*self.forward_multiple]
        # create a new missile with the appropriate position and velocity
        a_missile = Sprite(position, velocity, 0, 0, missile_image, missile_info, missile_sound)


# Sprite class
class Sprite:
    def __init__(self, pos, vel, ang, ang_vel, image, info, sound = None):
        self.pos = [pos[0],pos[1]]
        self.vel = [vel[0],vel[1]]
        self.angle = ang
        self.angle_vel = ang_vel
        self.image = image
        self.image_center = info.get_center()
        self.image_size = info.get_size()
        self.radius = info.get_radius()
        self.lifespan = info.get_lifespan()
        self.animated = info.get_animated()
        self.age = 0
        if sound:
            sound.rewind()
            sound.play()
   
    def draw(self, canvas):
        # draw the rock
        canvas.draw_image(self.image, self.image_center, self.image_size, self.pos, self.image_size, self.angle)
    
    def update(self):
        # position update
        self.pos[0] = (self.pos[0] + self.vel[0]) % width
        self.pos[1] = (self.pos[1] + self.vel[1]) % height
        # angle update
        self.angle += self.angle_vel

           
def draw(canvas):
    global time
    
    # animate background
    time += 1
    center = debris_info.get_center()
    size = debris_info.get_size()
    wtime = (time / 8) % center[0]
    canvas.draw_image(nebula_image, nebula_info.get_center(), nebula_info.get_size(), [width/2, height/2], [width, height])
    canvas.draw_image(debris_image, [center[0]-wtime, center[1]], [size[0]-2*wtime, size[1]], 
                                [width/2+1.25*wtime, height/2], [width-2.5*wtime, height])
    canvas.draw_image(debris_image, [size[0]-wtime, center[1]], [2*wtime, size[1]], 
                                [1.25*wtime, height/2], [2.5*wtime, height])

    # draw ship and sprites
    my_ship.draw(canvas)
    a_rock.draw(canvas)
    a_missile.draw(canvas)
    
    # update ship and sprites
    my_ship.update()
    a_rock.update()
    a_missile.update()
    
    # draw lives and score
    canvas.draw_text("Lives: " + str(lives) + " left", (50, 50), 20, "White")
    canvas.draw_text("Score: " + str(score) + " points", (570, 50), 20, "White")

# keydown handler
def keydown(key):
    if key == simplegui.KEY_MAP["left"]:
        my_ship.decrement_angle_vel()
    elif key == simplegui.KEY_MAP["right"]:
        my_ship.increment_angle_vel()
    elif key == simplegui.KEY_MAP["up"]:
        my_ship.toggle_thrusters(True)
    elif key == simplegui.KEY_MAP["space"]:
        my_ship.shoot()

# keyup handler
def keyup(key):
    if key == simplegui.KEY_MAP["left"]:
        my_ship.reset_angle_vel()
    elif key == simplegui.KEY_MAP["right"]:
        my_ship.reset_angle_vel()
    elif key == simplegui.KEY_MAP["up"]:
        my_ship.toggle_thrusters(False)

# computes a random +/- sign
def sign():
    return math.pow(-1, random.randint(0, 1))

# timer handler that spawns a rock
MAX_VEL = 4
MAX_ANG_VEL = math.pi/24
def rock_spawner():
    global a_rock
    velocity = [random.random()*MAX_VEL*sign(), random.random()*MAX_VEL*sign()]
    position = [random.randrange(0, width), random.randrange(0, height)]
    angular_velocity = random.random()*MAX_ANG_VEL*sign()
    # create a new rock with random position, velocity and angular velocity
    a_rock = Sprite(position, velocity, 0, angular_velocity, asteroid_image, asteroid_info)

# initialize frame
frame = simplegui.create_frame("Asteroids", width, height)

# initialize ship and two sprites
my_ship = Ship([width / 2, height / 2], [0, 0], 0, ship_image, ship_info)
a_rock = Sprite([width / 3, height / 3], [1, 1], 0, 0, asteroid_image, asteroid_info)
a_missile = Sprite([width/2 + ship_info.get_size()[0]/2, height/2], [5, 0], 0, 0, missile_image, missile_info, missile_sound)

# register handlers
frame.set_draw_handler(draw)
frame.set_keydown_handler(keydown)
frame.set_keyup_handler(keyup)

# create timer
timer = simplegui.create_timer(1000.0, rock_spawner)

# get things rolling
timer.start()
frame.start()
