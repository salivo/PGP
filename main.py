
import pygame

from canculate import Body

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True

 

x_offset = 640
y_offset = 360

scroll_senc = 0.5
zoom = 6   # 50        100       25 
tpp = 1000  # 0.1        1       0.02


objects_colors = {1:(255,0,0),
                  2:(0,0,255),
                  3:(0,255,0),
                  4:(255,255,0),
                  5:(255,0,255),
                  6:(0,255,255)}

bodys = [
        Body(1, 1000000, 0, 0, 0,  0),
        Body(2, 1000000, 0, 0, 8, 0),
        Body(3, 1000000, 0, 0, 4, 6.92820323),
        #Body(4, 100000, 0, 0, 2, 10)
        #Body(4, 1000000, 0, 0, 2, 10),
        ]
time = 0

pause = False

waitforpause = False


while running:
    # poll for events
    object_display_size = 2*zoom
    m2px = 5*zoom
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEWHEEL:
            zoom += event.y*scroll_senc
            time += event.y*0.5
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                print("pause")
                #if not waitforpause:
                 #   pause = !pause
            if event.key == pygame.K_RIGHT:
                time += 0
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_SPACE:
                print("play")
                pause = False
    #clear screen
    screen.fill((0,0,0))
    #draw objects
    for body in bodys:
        if not pause:
            body.canculate(bodys,10)

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

pygame.quit()
