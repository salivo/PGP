# Example file showing a basic pygame "game loop"
import pygame

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True



object_display_size = 50
objects_color = (255,0,0)

class Body():
    def __init__(self,x,y,mass):
        self.x = x
        self.y = y
        self.mass = mass
    def draw(self, screen):
        pygame.draw.rect(screen, objects_color, (self.x, self.y, object_display_size, object_display_size))



bodys = [
        Body(100,100,10),
        Body(300,100,10)
        ]


while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    for body in bodys:


        body.draw(screen)




    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(24)  # limits FPS to 60

pygame.quit()
