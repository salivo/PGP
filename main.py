
import pygame
import threading


from canculate import Body





# pygame setup
pygame.init()
screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
clock = pygame.time.Clock()
running = True
 

x_offset = 640
y_offset = 360

scroll_senc = 0.5
zoom = 6   # 50        100       25 
tpp = 100  # 0.1       1       0.02


objects_colors = {"slunce":(255,255,0),
                  "zeme":(0,0,255),
                  "mars":(255,180,0),
                  4:(255,255,0),
                  5:(255,0,255),
                  6:(0,255,255)}

bodys = [
        Body("slunce", 1.989*10**30, 0, 0, 0,  0),
        Body("zeme", 5.972*10**24, 0, 29783, 147097000000, 0),
        Body("mars", 6.3*10**23, 0, -24077, -227900000000, 0),
        #Body(4, 100000, 0, 0, 2, 10)
        #Body(4, 1000000, 0, 0, 2, 10),
        ]

def calc_thread():
    global running
    while running:
        for body in bodys:
            body.canculate(bodys,tpp)
        
thread = threading.Thread(target=calc_thread)
thread.start()


while running:
    # poll for events
    object_display_size = 1*zoom
    m2px = 0.000000001*zoom
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEWHEEL:
            zoom += event.y*scroll_senc
        if event.type == pygame.KEYDOWN or event.type == pygame.KEYUP:
             if event.key == pygame.K_0:
                x_offset = 640
                y_offset = 360

    mouse_x, mouse_y = pygame.mouse.get_rel()
    if pygame.mouse.get_pressed()[0]:
        x_offset += mouse_x
        y_offset += mouse_y
    #clear screen
    screen.fill((0,0,0))
    #draw objects
    for body in bodys:
        pygame.draw.circle(screen,
                         objects_colors[body.id],
                         (body.pos[0]*m2px+x_offset,
                          body.pos[1]*m2px+y_offset),
                        object_display_size)
    
    #show screen
    pygame.display.flip()
    #add time to next canculation
    #wait to stabilizate frame
    clock.tick(24)
thread.join()
pygame.quit()
