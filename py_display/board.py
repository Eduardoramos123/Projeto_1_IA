import math
from math import sin, cos

import pygame

pygame.init()

# Set up the drawing window
SCREEN_X = 900
SCREEN_Y = 700
points = []
center = (SCREEN_X // 2, SCREEN_Y // 2)
screen = pygame.display.set_mode([SCREEN_X, SCREEN_Y])


def draw_pieces(pts, player):
    if player == 1:
        color = (255, 255, 255)
    if player == 2:
        color = (0, 0, 0)
    pygame.draw.circle(screen, color, pts, 10)


def rotate(pts, angle, penta_center):
    cx = penta_center[0]
    cy = penta_center[1]
    new_points = []
    del points[-5:]
    for p in pts:
        x, y = p[0], p[1]
        tx, ty = x - cx, y - cy
        new_x = (tx * cos(angle) + ty * sin(angle)) + cx
        new_y = (-tx * sin(angle) + ty * cos(angle)) + cy
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
    num_layers = 5
    num_positions = 5
    radius = 50

    # Draw first polygon
    pts1 = create_points(num_positions, SCREEN_X // 2 - radius / 2, SCREEN_Y // 2 - radius * (2 / 3), radius)
    pygame.draw.polygon(screen, (255, 253, 208), pts1, 5)  # width=5
    radius += 50

    pts2 = create_points(num_positions, SCREEN_X // 2 - radius / 2, SCREEN_Y // 2 - radius * (2 / 3), radius)
    pygame.draw.line(screen, (255, 253, 208), points[0], points[5], 5)
    pygame.draw.line(screen, (255, 253, 208), points[1], points[6], 5)
    pygame.draw.line(screen, (255, 253, 208), points[2], points[7], 5)
    pygame.draw.line(screen, (255, 253, 208), points[3], points[8], 5)
    pygame.draw.line(screen, (255, 253, 208), points[4], points[9], 5)

    radius += 50
    pts3 = create_points(num_positions, SCREEN_X // 2 - radius / 2, SCREEN_Y // 2 - radius * (2 / 3), radius)
    pts4 = rotate(pts3, math.pi / num_layers, center)

    pygame.draw.line(screen, (255, 253, 208), points[10], points[5], 5)
    pygame.draw.line(screen, (255, 253, 208), points[11], points[6], 5)
    pygame.draw.line(screen, (255, 253, 208), points[12], points[7], 5)
    pygame.draw.line(screen, (255, 253, 208), points[13], points[8], 5)
    pygame.draw.line(screen, (255, 253, 208), points[14], points[9], 5)

    pygame.draw.line(screen, (255, 253, 208), points[10], points[9], 5)
    pygame.draw.line(screen, (255, 253, 208), points[11], points[5], 5)
    pygame.draw.line(screen, (255, 253, 208), points[12], points[6], 5)
    pygame.draw.line(screen, (255, 253, 208), points[13], points[7], 5)
    pygame.draw.line(screen, (255, 253, 208), points[14], points[8], 5)

    radius += 50
    pts5 = create_points(num_positions, SCREEN_X // 2 - radius / 2, SCREEN_Y // 2 - radius * (2 / 3), radius)
    pts6 = rotate(pts5, math.pi / num_layers, center)

    pygame.draw.line(screen, (255, 253, 208), points[10], points[15], 5)
    pygame.draw.line(screen, (255, 253, 208), points[11], points[16], 5)
    pygame.draw.line(screen, (255, 253, 208), points[12], points[17], 5)
    pygame.draw.line(screen, (255, 253, 208), points[13], points[18], 5)
    pygame.draw.line(screen, (255, 253, 208), points[14], points[19], 5)
    pygame.draw.circle(screen, (255, 253, 208), center, radius - (radius / 8), 5)

    for i in range(len(positions)):
        for j in range(len(positions[i])):
            # Draw the pieces for player1
            if positions[i][j] == 'x':
                draw_pieces(points[i*5 + j], 1)
            # Draw the pieces for player2
            elif positions[i][j] == 'o':
                draw_pieces(points[i*5 + j], 2)

    # Update display
    pygame.display.update()


def get_piece(positions):
    font = pygame.font.Font(None, 36)
    pos1 = None
    pos2 = None
    screen_center = screen.get_rect().center

    while True:
        draw_board(positions)
        text = font.render("Enter the row and column of the piece you want to move (lin and col e.g. 1 2)", True,
                           (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1]+230))
        screen.blit(text, text_rect)

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

            if event.type == pygame.KEYDOWN and event.unicode.isdigit():
                if pos1 is None:
                    pos1 = int(event.unicode)
                else:
                    pos2 = int(event.unicode)

        if pos1 is not None and pos2 is not None:
            break

    return [pos1, pos2]


def get_pos():
    font = pygame.font.Font(None, 36)
    pos1 = None
    pos2 = None
    screen_center = screen.get_rect().center

    while True:
        text = font.render("To which position? (lin and col e.g. 1 2)", True, (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1] + 260))
        screen.blit(text, text_rect)

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

            if event.type == pygame.KEYDOWN and event.unicode.isdigit():
                if pos1 is None:
                    pos1 = int(event.unicode)
                else:
                    pos2 = int(event.unicode)

        if pos1 is not None and pos2 is not None:
            break

    return [pos1, pos2]


def print_turn(string):
    # Fill the background with orange
    screen.fill((255, 160, 50))
    font = pygame.font.Font(None, 36)
    screen_center = screen.get_rect().center

    text = font.render(string, True, (255, 255, 255))
    screen.blit(text, (screen_center[0]-400, screen_center[1]-300))

    pygame.display.update()


def print_warnings(string):
    screen.fill((255, 140, 0))
    font = pygame.font.Font(None, 36)
    flag = None
    screen_center = screen.get_rect().center

    while True:
        text = font.render(string, True, (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 100))
        screen.blit(text, text_rect)

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return False

            if event.type == pygame.KEYDOWN and event.unicode == ' ':
                flag = True

        if flag:
            break


def print_string(string):
    screen.fill((255, 140, 0))
    font = pygame.font.Font(None, 36)
    flag = None
    screen_center = screen.get_rect().center

    while True:
        text = font.render(string, True, (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1]))
        screen.blit(text, text_rect)

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return False

            if event.type == pygame.KEYDOWN and event.unicode == ' ':
                flag = True

        if flag:
            break


def get_game_options():
    screen.fill((255, 140, 0))
    font = pygame.font.Font(None, 36)
    mode = None
    computer_difficulty_1 = None
    computer_difficulty_2 = None
    screen_center = screen.get_rect().center

    while True:
        text = font.render("Please select a game mode:", True, (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 100))
        screen.blit(text, text_rect)
        text = font.render("1. Player vs Player", True, (255, 255, 255))
        screen.blit(text, (screen_center[0] - 150, screen_center[1] - 50))
        text = font.render("2. Player vs Computer", True, (255, 255, 255))
        screen.blit(text, (screen_center[0] - 150, screen_center[1] - 20))
        text = font.render("3. Computer vs Computer", True, (255, 255, 255))
        screen.blit(text, (screen_center[0] - 150, screen_center[1] + 10))
        text = font.render("Enter your choice (1-3):", True, (255, 255, 255))
        screen.blit(text, (screen_center[0] - 150, screen_center[1] + 40))

        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

            if event.type == pygame.KEYDOWN and event.unicode.isdigit():
                mode = int(event.unicode)
                if 1 <= mode <= 3:
                    break

            if mode is not None and (mode < 1 or mode > 3):
                mode = None

        if mode is not None:
            break

    screen.fill((255, 140, 0))

    if mode == 2 or mode == 3:
        while True:
            text = font.render("Please select a difficulty level for the computer:", True, (255, 255, 255))
            text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 70))
            screen.blit(text, text_rect)
            text = font.render("1. Easy", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] - 20))
            text = font.render("2. Medium", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] + 10))
            text = font.render("3. Hard", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] + 40))
            text = font.render("Enter your choice for computer 1 (1-3):", True, (255, 255, 255))
            text_rect = text.get_rect(center=(screen_center[0], screen_center[1] + 90))
            screen.blit(text, text_rect)

            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    return

                if event.type == pygame.KEYDOWN:
                    if event.unicode.isdigit():
                        computer_difficulty_1 = int(event.unicode)
                        if 1 <= computer_difficulty_1 <= 3:
                            break

                if computer_difficulty_1 is not None and (computer_difficulty_1 < 1 or computer_difficulty_1 > 3):
                    computer_difficulty_1 = None

            if computer_difficulty_1 is not None:
                break

    if mode == 3:
        screen.fill((255, 140, 0))
        while True:
            text = font.render("Please select a difficulty level for the computer:", True, (255, 255, 255))
            text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 70))
            screen.blit(text, text_rect)
            text = font.render("1. Easy", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] - 20))
            text = font.render("2. Medium", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] + 10))
            text = font.render("3. Hard", True, (255, 255, 255))
            screen.blit(text, (screen_center[0] - 100, screen_center[1] + 40))
            text = font.render("Enter your choice for computer 2 (1-3):", True, (255, 255, 255))
            text_rect = text.get_rect(center=(screen_center[0], screen_center[1] + 90))
            screen.blit(text, text_rect)

            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    return

                if event.type == pygame.KEYDOWN:
                    if event.unicode.isdigit():
                        computer_difficulty_2 = int(event.unicode)
                        if 1 <= computer_difficulty_2 <= 8:
                            break

                if computer_difficulty_2 is not None and (computer_difficulty_2 < 1 or computer_difficulty_2 > 3):
                    computer_difficulty_2 = None

            if computer_difficulty_2 is not None:
                break

    if mode == 1:
        return [mode]
    elif mode == 2:
        turn = get_turn()
        return [mode, computer_difficulty_1, turn]
    else:
        return [mode, computer_difficulty_1, computer_difficulty_2]


def get_turn():
    screen.fill((255, 140, 0))
    font = pygame.font.Font(None, 36)
    turn = None
    screen_center = screen.get_rect().center

    while True:
        text = font.render("Do you want to play first? Enter 1 for yes, 0 for no:", True, (255, 255, 255))
        text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 70))
        screen.blit(text, text_rect)
        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return

            if event.type == pygame.KEYDOWN and event.unicode.isdigit():
                turn = int(event.unicode)
                if 0 <= turn <= 1:
                    break

            if turn is not None and (turn < 0 or turn > 1):
                turn = None

        if turn is not None:
            break

    return turn


def exit_function():
    # Done! Time to quit.
    pygame.quit()

