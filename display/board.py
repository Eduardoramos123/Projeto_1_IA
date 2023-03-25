import math
import pygame
pygame.init()

# Set up the drawing window
SCREEN_WIDTH = 900
SCREEN_HEIGHT = 700
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])

def drawPieces(screen, pts, size, player):
  if player == 1:
     color = (255, 255, 255)
  if player == 2:
     color = (0, 0, 0)
  # Draw the pieces in the place
  #pygame.draw.circle(screen, (0, 0, 0), (SCREEN_WIDTH//2+10, SCREEN_HEIGHT//2+10), 6)
  # Draw the pieces in the center
  pygame.draw.circle(screen, color, pts, size)
    
def createPoints(numSides, tiltAngle, x, y, radius):
  pts = []
  for i in range(numSides):
    x = x + radius * math.cos(tiltAngle + math.pi * 2 * i / numSides)
    y = y + radius * math.sin(tiltAngle + math.pi * 2 * i / numSides)
    pts.append([int(x), int(y)])
  return pts
  
def drawLayers(screen, numLayers):
  # Fill the background with orange
  screen.fill((255, 140, 0))
  
  # Draw center
  drawPieces(screen, (SCREEN_WIDTH//2, SCREEN_HEIGHT//2), 6, 1)

  radius = 50
  # Draw polygons
  for i in range(numLayers):
    radius = radius + 50
    pts = createPoints(5, 0, SCREEN_WIDTH//2-radius/2, SCREEN_HEIGHT//2-radius*(2/3), radius)
    #pygame.draw.lines(screen, color, True, pts, 5) #closed = true, width=5
    pygame.draw.polygon(screen, (255, 253, 208), pts, 5)
    # Draw the pieces for player1
    drawPieces(screen, pts[i], 6, 1)
    # Draw the pieces for player2
    drawPieces(screen, pts[i], 6, 2)



# Run until the user asks to quit
running = True
while running:
    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    # Draw Game Board
    drawLayers(screen, 5)
    # Flip the display
    pygame.display.flip()

# Done! Time to quit.
pygame.quit()

