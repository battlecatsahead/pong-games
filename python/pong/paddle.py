import pygame
black = (0,0,0)
 
class paddle(pygame.sprite.Sprite):
    #This class represents a paddle. It derives from the "Sprite" class in Pygame.
    
    def __init__(self, color, width, height):
        # Call the parent class (Sprite) constructor
        super().__init__()
        
        # Pass in the color of the paddle, its width and height.
        # Set the background color and set it to be transparent
        self.image = pygame.Surface([width, height])
        self.image.fill(black)
        self.image.set_colorkey(black)
 
        # Draw the paddle (a rectangle!)
        pygame.draw.rect(self.image, color, [0, 0, width, height])
        
        # Fetch the rectangle object that has the dimensions of the image.
        self.rect = self.image.get_rect()

    def moveup(self, pixels):
        self.rect.y -= pixels
        #check that you are not going too far ( off the screen)
        if self.rect.y < 0:
            self.rect.y = 0

    def movedown(self, pixels):
        self.rect.y += pixels

    #check that you are not going too far (off the screen)
        if self.rect.y > 400:
            self.rect.y = 400
            
    
