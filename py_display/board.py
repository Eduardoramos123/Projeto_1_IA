import math
import pygame

import os

current_file_path = os.path.realpath(__file__)

print(current_file_path)

pygame.init()

# Set up the drawing window
SCREEN_WIDTH = 900
SCREEN_HEIGHT = 700
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])
screen.fill((255, 140, 0))


def draw_pieces(pts, size, player):
    if player == 1:
        color = (255, 255, 255)
    if player == 2:
        color = (0, 0, 0)
    # Draw the pieces in the center
    pygame.draw.circle(screen, color, pts, size)


def create_points(num_sides, tilt_angle, x, y, radius):
    pts = []
    for i in range(num_sides):
        x = x + radius * math.cos(tilt_angle + math.pi * 2 * i / num_sides)
        y = y + radius * math.sin(tilt_angle + math.pi * 2 * i / num_sides)
        pts.append([int(x), int(y)])
    return pts


def draw_board(positions):
    # Fill the background with orange
    screen.fill((255, 140, 0))

    # Draw board and pieces using drawLayers function
    radius = 50
    for i in range(len(positions)):
        radius = radius + 50
        pts = create_points(5, 0, SCREEN_WIDTH // 2 - radius / 2, SCREEN_HEIGHT // 2 - radius * (2 / 3), radius)
        pygame.draw.polygon(screen, (255, 253, 208), pts, 5)
        for j in range(len(positions[i])):
            x = int(SCREEN_WIDTH / 2) + int(240 * (i - 2) / 3)
            y = int(SCREEN_HEIGHT / 2) + int(240 * (j - 2) / 3)
            if positions[i][j] == 'X':
                draw_pieces(screen, (x, y), 6, 1)
            elif positions[i][j] == 'O':
                draw_pieces(screen, (x, y), 6, 2)

    # Update display
    pygame.display.flip()


def quit():
    # Done! Time to quit.
    pygame.quit()
