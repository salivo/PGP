
import pygame

from canculate import Body

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True

 

x_offset = 640
y_offset = 360


zoom = 25   # 50        100       25 
tpp = 1  # 0.1        1       0.02



object_display_size = 400/zoom
objects_colors = {1:(255,0,0),
                  2:(0,0,255),
                  3:(0,255,0)}
m2px = 50/zoom

bodys = [
        Body(1, 100000, 0, 0, 0),
        Body(2, 100000, 0, 100, 0),
        Body(3, 100000, 0, 50, 86.60254038)
        ]

time = 0
while running:
    # poll for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    #clear screen
    screen.fill((0,0,0))
    #draw objects
    for body in bodys:
        body.canculate(bodys,time)
        pygame.draw.circle(screen,
                         objects_colors[body.id],
                         (body.pos[0]*m2px+x_offset,
                          body.pos[1]*m2px+y_offset),
                        object_display_size)
    
    #show screen
    pygame.display.flip()
    #add time to next canculation
    time += tpp
    #wait to stabilizate frame
    clock.tick(24)

pygame.quit()
