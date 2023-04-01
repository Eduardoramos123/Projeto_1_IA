# Projeto_1_IA
Projeto de IA sobre pesquisa adversarial do jogo Bound 

## Bound

>### Description and Rules
>**Description**: **Bound** is a two-player strategy game played on a single sheet of
   paper. Each turn, move one of your four standing stones to encircle an opponent's
   stone.
> 
>**Rules**:
> - **Board Setup**: The first player places their pieces on four of the five forks around
    the outer ring. The second player places their four pieces on the central
    pentagon, each one on a fork opposite one of the older player’s pieces. 
> - **Moves**: Each piece can only be placed in a neighbor’s position that is empty. 
> - **Goal**: surround an opponent's piece so that can no longer be moved. If a player
    can no longer move one of their pieces, they lose the game.


## How to Run the Project
> We are currently running the project in CLion. For you to be able to run it you need the following:
>  - Have python installed (python311 version)
>  - Put the full path to your python311.lib in the CmakeLists.txt file.
>  - Put the full path to the teste.py and board.py files in the main funtion of main.cpp. This step is necessary because we are using the pygame to illustrate the game board and to interact with the User. So the main.cpp needs to get the content from both files to import the board.py module.
>  - You need to have pygame installed too.