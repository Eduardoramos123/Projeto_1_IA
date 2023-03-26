import math
import pygame

pygame.init()

# Set up the drawing window
SCREEN_WIDTH = 900
SCREEN_HEIGHT = 700
screen = pygame.display.set_mode([SCREEN_WIDTH, SCREEN_HEIGHT])


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
                draw_pieces(screen, (x, y), 6)
            elif positions[i][j] == 'O':
                draw_pieces(screen, (x, y), 6)

    # Update display
    pygame.display.flip()


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
                        if 1 <= computer_difficulty_1 <= 8:
                            break

            if computer_difficulty_1 is not None:
                break

    if mode == 3:
        while True:
            text = font.render("Please select a difficulty level for the computer:", True, (255, 255, 255))
            text_rect = text.get_rect(center=(screen_center[0], screen_center[1] - 70))
            screen.blit(text, text_rect)
            text = font.render("1. Easy", True, (255, 255, 255))
            screen.blit(text, (50, screen_center[1] - 20))
            text = font.render("2. Medium", True, (255, 255, 255))
            screen.blit(text, (50, screen_center[1] + 10))
            text = font.render("3. Hard", True, (255, 255, 255))
            screen.blit(text, (50, screen_center[1] + 40))
            text = font.render("Enter your choice for computer 1 (1-3):", True, (255, 255, 255))
            screen.blit(text, (50, screen_center[1] + 70))

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

            if computer_difficulty_2 is not None:
                break

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

        if turn is not None:
            break

    return turn


def exit_function():
    # Done! Time to quit.
    pygame.quit()
