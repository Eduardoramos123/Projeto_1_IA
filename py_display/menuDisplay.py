import pygame
import pygame_menu

myTheme = pygame_menu.Theme(background_color=(255, 253, 208),
                            cursor_color=(255, 69, 0),
                            cursor_selection_color=(255, 253, 208, 0),
                            selection_color=(255, 69, 0),
                            title_background_color=(255, 160, 50),
                            title_font_color=(255, 253, 208),
                            widget_padding=25,
                          )

pygame.init()
surface = pygame.display.set_mode((900, 700))

def set_difficulty(value, difficulty):
    # Code for difficulty
    pass

def start_the_game():
    # Code for the game
    pass


play_submenu = pygame_menu.Menu('Welcome', 900, 700, theme=myTheme)
for i in range(30):
    play_submenu.add.button(f'Back {i}', pygame_menu.events.BACK)
play_submenu.add.button('Return to main menu', pygame_menu.events.RESET)

menu1 = pygame_menu.Menu('Player vs Player', 900, 700, theme=myTheme)
menu1.add.text_input('Player 1 Name:')
menu1.add.text_input('Player 2 Name:')
menu1.add.button('Play', start_the_game)
menu1.add.button('Quit', pygame_menu.events.BACK)
menu1.mainloop(surface)

menu2 = pygame_menu.Menu('Player vs Computer', 900, 700, theme=myTheme)
menu2.add.text_input("Player's Name:")
menu2.add.button('Play', start_the_game)
menu2.add.button('Quit', pygame_menu.events.BACK)
menu2.mainloop(surface)

menu3 = pygame_menu.Menu('Computer vs Computer', 900, 700, theme=myTheme)
menu3.add.text_input("Player's Name:")
menu3.add.button('Play', start_the_game)
menu3.add.button('Quit', pygame_menu.events.BACK)
menu3.mainloop(surface)

# Create initial game menu
menu = pygame_menu.Menu('Welcome', 900, 700, theme=myTheme)
selectorr = menu.add.selector('Game Mode :', [('Player vs Player', 1), ('Player vs Computer', 2), ('Computer vs Computer', 3)])
if selectorr.get_value()[1] == 1:
    menu.add.button('Next', menu1)
if selectorr.get_value()[1] == 2:
    menu.add.button('Next', menu2)
if selectorr.get_value()[1] == 2:
    menu.add.button('Next', menu3)
menu.add.button('Quit', pygame_menu.events.EXIT)
menu.mainloop(surface)
