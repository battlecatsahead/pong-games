import pygame
pygame.init()

from paddle import paddle
from ball import Ball
black = (0, 0, 0)
white = (255, 255, 255)




#open a new window
size = (700,500)
screen = pygame.display.set_mode(size)
pygame.display.set_caption("pong")

paddleA = paddle(white, 10, 100)
paddleA.rect.x = 20
paddleA.rect.y = 200
 
paddleB = paddle(white, 10, 100)
paddleB.rect.x = 670
paddleB.rect.y = 200

ball = Ball(white, 10, 10)
ball.rect.x = 345
ball.rect.y = 195

all_sprites_list = pygame.sprite.Group()

all_sprites_list.add(paddleA)
all_sprites_list.add(paddleB)
all_sprites_list.add(ball)

#the loop will carry on until the user exits the game
carryOn = True


#the clock will be used to control how fast teh screen updates
clock = pygame.time.Clock()


#initialise player scores
scoreA = 0
scoreB = 0
#--------main program loop--------#
while carryOn:
    #-----main event loop----#
    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
              carryOn = False # Flag that we are done so we exit this loop
        elif event.type==pygame.KEYDOWN:
                if event.key==pygame.K_x: #Pressing the x Key will quit the game
                     carryOn=False  


    #moving the paddles when the user uses the right keys
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        paddleA.moveup(5)

    if keys[pygame.K_s]:
        paddleA.movedown(5)

    if keys[pygame.K_UP]:
        paddleB.moveup(5)

    if keys[pygame.K_DOWN]:
        paddleB.movedown(5)


        
    #----game logic should go here----#
    all_sprites_list.update()


    #check if ball is bouncing against any of the 4 walls:
    if ball.rect.x>=690:
        scoreA+=1
        ball.rect.x = 345
        ball.rect.y = 195
        ball.velocity[0] = -ball.velocity[0]
    if ball.rect.x<=0:
        scoreB+=1
        ball.rect.x = 345
        ball.rect.y = 195
        ball.velocity[0] = -ball.velocity[0]
    if ball.rect.y>490:
        ball.velocity[1] = -ball.velocity[1]
    if ball.rect.y<0:
        ball.velocity[1] = -ball.velocity[1] 

    #detect collisions between teh ball and teh paddles
    if pygame.sprite.collide_mask(ball, paddleA) or pygame.sprite.collide_mask(ball, paddleB):
        ball.bounce()

    #----drawing code should go here----#

            
    #first, clear the screen to black
    screen.fill(black)
    #draw the net
    pygame.draw.line(screen, white, [349, 0], [349, 500], 5)

    #now lets draw all the sprites in one go
    all_sprites_list.draw(screen)


    #Display scores:
    font = pygame.font.Font(None, 74)
    text = font.render(str(scoreA), 1, white)
    screen.blit(text, (250,10))
    text = font.render(str(scoreB), 1, white)
    screen.blit(text, (420,10))

    
    #---- go ahead and update the screen with what weve drawn
    pygame.display.flip()

    #limit to 60 frames per second
    clock.tick(60)

#Once we have exited the main program loop we can stop the game engine:
pygame.quit()




    
