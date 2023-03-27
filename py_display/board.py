import math
import pygame
from math import sin, cos, radians
pygame.init()

# Set up the drawing window
SCREEN_X = 900
SCREEN_Y = 700
points=[]
center=(SCREEN_X//2, SCREEN_Y//2)
screen = pygame.display.set_mode([SCREEN_X, SCREEN_Y])

def draw_pieces(pts, player):
  if player == 1:
     color = (255, 255, 255)
  if player == 2:
     color = (0, 0, 0)
  pygame.draw.circle(screen, color, pts, 10)

def rotate(pts, angle, center):
  cx = center[0]
  cy = center[1]
  new_points = []
  del points[-5:]
  for p in pts:
      x, y = p[0], p[1]
      tx, ty = x-cx, y-cy
      new_x = ( tx*cos(angle) + ty*sin(angle)) + cx
      new_y = (-tx*sin(angle) + ty*cos(angle)) + cy
      new_points.append((new_x, new_y))
      points.append((new_x, new_y))
  return new_points
  
def create_points(num_sides, x, y, radius):
  pts = []
  for i in range(num_sides):
    x = x + radius * math.cos(math.pi * 2 * i / num_sides)
    y = y + radius * math.sin(math.pi * 2 * i / num_sides)
    pts.append([int(x), int(y)])
    points.append([int(x), int(y)])
  return pts
  
def draw_board(positions):
  # Fill the background with orange
  screen.fill((255, 160, 50))  

  num_layers = 5
  num_positions = 5
  radius = 50

  # Draw first polygon
  pts1 = create_points(num_positions, SCREEN_X//2-radius/2, SCREEN_Y//2-radius*(2/3), radius)
  pygame.draw.polygon(screen, (255, 253, 208), pts1, 5) #width=5
  radius += 50
  for k in range(1, num_layers):
    if (k == num_layers-1):
      pygame.draw.circle(screen, (255, 253, 208), center, radius, 5)
    if ((k-1)%2 == 0):
      pts2 = create_points(num_positions, SCREEN_X//2-radius/2, SCREEN_Y//2-radius*(2/3), radius)
      #pygame.draw.polygon(screen, (255, 253, 208), pts2, 5) #width=5
      for l in range(num_positions):
        pygame.draw.line(screen, (255, 253, 208), points[l], points[num_positions+l], 5) #width=5 
    else:
      pts3 = create_points(num_positions, SCREEN_X//2-radius/2, SCREEN_Y//2-radius*(2/3), radius)
      pts5 = rotate(pts3, math.pi/num_layers, center)
      #pygame.draw.polygon(screen, (255, 253, 208), pts5, 5)
      for m in range(num_positions):
        pygame.draw.line(screen, (255, 253, 208), points[k*num_positions+m], points[num_positions+m], 5) 
        pygame.draw.line(screen, (255, 253, 208), points[(k-1)*num_positions], points[((k-1)*num_positions)-1], 5)
        if m < (num_positions-1):
          pygame.draw.line(screen, (255, 253, 208), points[k*num_positions+m+1], points[num_positions+m], 5)
    radius += 50

  # Draw the pieces for player1
  draw_pieces(pts1[0], 1)
  # Draw the pieces for player2
  draw_pieces(pts1[2], 2)
  

  for i in range(len(positions)):
    for j in range(len(positions[i])):
            x = int(SCREEN_X / 2) + int(240 * (i - 2) / 3)
            y = int(SCREEN_Y / 2) + int(240 * (j - 2) / 3)
            # Draw the pieces for player1
            if positions[i][j] == 'X':
                draw_pieces((x, y), 1)
            # Draw the pieces for player2
            elif positions[i][j] == 'O':
                draw_pieces((x, y), 2)
    
  # Update display
  pygame.display.flip()
        

def quit():   
  # Done! Time to quit.
  pygame.quit()
