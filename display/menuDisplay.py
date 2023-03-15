import pygame
import pygame_menu


pygame.init()
surface = pygame.display.set_mode((900, 700))

def set_difficulty(value, difficulty):
    # Code for difficulty
    pass

def start_the_game():
    # Code for the game
    pass

def game_mode(value: tuple[any, int], mode: int):
    if mode == 1:
        menu = pygame-menu.Menu(value, 900, 700, theme=pygame_menu.themes.THEME_SOLARIZED)
        menu.add.text_input('Player 1 Name:')
        menu.add.text_input('Player 2 Name:')
        menu.add.button('Play', start_the_game)
        menu.add.button('Quit', pygame_menu.events.EXIT)
        menu.mainloop(surface)
    if mode == 2:
        menu = pygame-menu.Menu(value, 900, 700, theme=pygame_menu.themes.THEME_SOLARIZED)
        menu.add.text_input("Player's Name:")
        menu.add.button('Play', start_the_game)
        menu.add.button('Quit', pygame_menu.events.EXIT)
        menu.mainloop(surface)
    if mode == 3:
        menu = pygame-menu.Menu(value, 900, 700, theme=pygame_menu.themes.THEME_SOLARIZED)
        menu.add.text_input("Player's Name:")
        menu.add.button('Play', start_the_game)
        menu.add.button('Quit', pygame_menu.events.EXIT)
        menu.mainloop(surface)
    pass


# Create initial game menu
menu = pygame_menu.Menu('Welcome', 900, 700,
                       theme=pygame_menu.themes.THEME_SOLARIZED)

menu.add.selector('Game Mode :', [('Player vs Player', 1), ('Player vs Computer', 2), ('Computer vs Computer', 3)], onchange=game_mode)
menu.add.button('Next', game_mode)
menu.add.button('Quit', pygame_menu.events.EXIT)

menu.mainloop(surface)
