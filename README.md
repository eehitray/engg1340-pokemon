# Pokémon	

## Group 196
### Eehit Ray - 3035665122
### Dhruv Aggarwal - 3035663150

Gameplay video link: https://drive.google.com/open?id=1lGBFBL5esh7TYzKJPLvIltGmG_rdbjOB

Our version of **Pokémon** is a text-based game, where the user's goal is to become the regional Pokémon Champion.
The game is based on the famous anime/game Pokémon.
The player begins the game with 3 pokémon, and travels through the map, battling other trainers, exploring the new world and fighting pokémon so as to train and level up his/her own Pokémon. He ultimtely battles out the region's champion for the coveted position of Pokémon Champion.

**Game Rules**
1. The player starts the game and enters his name. 
2. The player begins with 2 random pokemon of level 1 and 1 random pokemon of level 2. It is level that determines the base damage of the moves (attacks) the pokemon possesses as well as its hp (health points). The player battles other pokemon and trainers to gain experience points and level up his own pokemon, so that they become stonger. As the pokemon levels up, it has to gain more experience points to reach the next level.
	- Upon reaching level 2, a pokemon learns a new move.
3. As you progress through the map, the level of difficulty increases with stronger pokemon appearing. Within the map you will encounter grass areas where you will have battles with wild (random) pokemon.
	- Colours on the map are as follows :
		- Green: Grass areas where wild pokemon are encountered.
		- Yellow: Roads where no pokemon are encountered.
		- Red: Pokemon centre, where you can replenish your pokemons' health.
	- Your objective is to move upwards in the map where you will encounter trainers and finally the regional champion.
	- The map is divided into 3 sections by trainers. In order to proceed to the next section, the player must defeat the trainer for that section. The 3rd trainer is the regional champion.
	- Once a trainer has been defeated, he does not need to be battled again.
4. The Pokemon battle system works as follows :
	- The player sees his pokemon and their respective moves, HP (health points), type & level, as well his opponent's pokemon and their HP, type & level.  
	- The player can either choose to execute a move of his current pokemon or switch to a different pokemon.
	- The effectiveness of the move depends on your pokemon's level, type and the type of Pokémon being battled.
	- Fire pokemon have an advantage over Grass pokemon. Similarly, Water pokemon have an advantage over Fire and Grass pokemon have an advantage over Water pokemon.
	- The probability of the move hitting decreases as the strength of the move increases.
	- The objective is to ensure you knock out the opponent's pokemon by making the pokemon HP 0. By doing so, you would even gain experience points for your pokemon.
	- If your pokemon faints, you have to switch out your current pokemon for another.
	- Wild pokemon appear individually, and trainers have a set of 3 pokemon each. 
	- The battle ends when either party has all pokemon at HP 0.
5. To heal your hurt pokemon you can approach pokemon centres (red tiles) that are located at specific places on the map.
6. You can also check your pokemon details such as HP, level etc, at any time.
7. If you feel like taking a break you can save and exit the game, and carry on with your previous progress later on.
	- The game gets saved with your player name as the filename.
	- On starting the game again, you can load your saved file by entering the player name you had used earlier (see point 1).
8. The final frontier of the map is the battle with the regional champion. If you defeat the Champion, you are declared the new regional Pokémon Champion and you are then free to play indefinitely.

**Controls**
1. Start Screen:
	- Press 1 to start the game.
	- Press 2 to exit the game.
2. Name Input Screen:
	- Enter your name.
	- If you have a saved game with this player name, you will be given the option to load it. Press y to load or n to start a new game with the player name.
	- Press y to start playing.
3. Core Controls:
	- Press w to move up.
	- Press s to move down.
	- Press a to move left.
	- Press d to move right.
	- Press p to display your player and pokemon details.
	- Press h when in a pokemon centre (red tiles) to heal your pokemon.
	- Press b when confronted by a trainer to initiate the battle.
	- Press z to save and exit the game.
4. Battle Controls:
	- Press 0, 1 or 2 to execute the corresponding move of your Pokemon.
	- Press s to switch your pokemon. 
		- When prompted to switch pokemon, press 0, 1 or 2 to switch to the corresponding pokemon.
		- You cannot switch to pokemon that have fainted.
5. Other Screens:
	- Press any key to continue when faced with descriptive screens such as that on healing of pokemon, defeat of trainer etc.

**Features and Functions vis-a-vis given code requirements**
1. Generation of random game sets or events:
	- The pokemon that the player starts with are randomly generated.
	- The pokemon that appear in the wild will be generated by random from a list of Pokemon created by us.
	- The pokemon that trainers have as well as trainer names will be generated randomly.
	- The moves an opponent pokemon plays, will be genereated randomly.
	- The probability of a move hitting also depends on chance. Probabiltiy of hit decreases with strength of move.
2. Data structures for storing game status:
	- The player is represented using a `Player` class whose data members are
		- player name
		- player position on map
		- player's roster of pokemon
		- player level (indicates how many trainers the player has beaten)
	- The Pokémon are represented by a `Pokemon` class whose data members are
		- pokemon name
		- pokemon type
		- pokemon level
		- pokemon health and maximum health
		- pokemon current experience and required experience to level up
		- number of moves the pokemon has
		- set of moves of a pokemon
	- The move of a pokemon is defined as a structure called `Move` with elements name, damage and hit (probability of move being successful).
	- There are also utility classes for making core game functions easier, such as MainGame (for running the all core game functions), ScreenRenderer (for printing to the screen and taking input) and Map (to represent the in-game map) etc.
3. Dynamic memory management: 
	- Vectors are used throughout the program. E.g. storing the moves of a pokemon, storing the pokemon a player has.
	- In `Map.cpp` an integer array is dynamically allocated using the `new` operator to store the positions of the trainers.
4. File input/output :
	- The list of pokemon (with their moves & type) are stored in a text file (`poklist.txt`) which is read by the game during battles to generate random pokemon as well as during creation of the player's roster.
	- The map of the game and the player's starting coordinates are stored in a text file (`map.txt`) which is read, while printing the map.
	- While exiting the game, the player's details (including name, roster and map location) are stored in a file, so that the player can carry on from where they left off.
	- The names of the trainers are stored in a text file (`trainer_names.txt`).
	- The artwork for the various pokemon and the start screen logo are stored in files such as `Vaporeon.txt` and `pokemon_logo.ans`. 
5. Program codes in multiple files:
	- The program's code is divided into multiple .cpp and .h files. E.g.: `Pokemon.cpp` and `Pokemon.h`


**Complilation and Execution Instructions**
1. After cloning the repository, create a directory called `out` in the same directory as `src`, `make`, `test` and `text`.
2. Copy all files from the `text` directory and paste them in the `out` directory.
3. Navigate to the `make` directory and execute the command `make` in the linux shell.
4. Navigate to the `out` directory and execute the command `./game.exe` to start the game.

**We hope you enjoy the game and become the Pokémon Champion!**

**References**
1. Credit for the original idea of Pokemon goes to Nintento Co., Ltd	
2. Generation of files of pokemon and logo artwork was done via:
	- https://www.ascii-art-generator.org/
	- https://manytools.org/hacker-tools/convert-images-to-ascii-art/
