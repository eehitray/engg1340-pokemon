# Pokémon

Group 196

Eehit Ray - 3035665122

Dhruv Aggarwal - 3035663150

Game starts by main character leaving home on a Pokemon quest, and ends when he beats the regional champion.

Constants:

1. Enum - experience points need for each level (RXP) - medium priority

2. Enum - maximum health at each level - high priority

3. Enum - experience points gained by defeating a pokemon of a certain level - medium priority

4. Enum - damage done by tier 1 move at various levels (high priority)

5. Enum - damage done by tier 2 move at various levels (high priority)

6. Enum - damage done by tier 3 move at various levels (low priority)

class ScreenRenderer:

handles all screen related features

class Player:

Name - high priority

Pokemon - high priority, array of 3

class Pokemon:

Name - High priority

Nickname given by user - Low priority

Type - High priority

Health Points (HP) - High priority

Level - High priority

Experience - Medium priority

Moveset - High priority (implement as array of Moves)

class Move:

Name - High priority

Damage - High priority

Probability of hit - 0 to 1, high priority

Tier - do not implement, for reference only (bijection to damage and probability, see enums 4, 5, 6)

Gameplay:

The XP system:

Player starts at Level 1. Each subsequent level requires a certain XP (RXP) to move to. RXP increases with level i.e. Level 2 may need only 20XP, but Level 10 will need 150XP. XP is gained by defeating other pokemon. XP gained for defeating a pokemon at a certain level is a constant based on the level of the opponent pokemon and is independent of *your* current level. 

What do levels do?

1. Increases your max health (see enum 2)

2. Scales how much damage your moves do (see enums 4, 5, 6)

The moveset system:

Each move essentially has a name, and a damage value. Each pokemon has two moves - a tier 1 move and a tier 2 move (and maybe, if we have time, we add a tier 3 move unlocked at a certain level). The tier 1 move has a base damage at each level - at level 1 it does 5 damage, at level 2 it does 10 and so on (see enums 4, 5, 6). The damage done by each move is also scaled by some factor depending on the type of the pokemon you are fighting. A tier 1 move will have a higher (constant) probability of landing than a tier 2 move. This is to ensure you do not spam a higher tier move.

Camera/screen system:

Camera is centered on player at all times, as player moves up/down so does the camera. The entire width of the map is on the screen at all times.

We ask the user to enter their name and select starter pokemon (3). Player starts on his quest through the map. The nth grass area will have random encounters with other pokemon of level 1-n. Battles take place roughly according to the function "battle" shown below.






	func battle(Player p, opponent pokemon [1 or 3]):
		turn = 0
		current player pokemon = p.pokemons[0]
		current opp. pokenmon = opponent pokemons[0]

		while (all of p's pokemon have health > 0 && all of opponent pokemon health > 0):
			if turn % 2 == 0:
				if current player pokemon health == 0:
					force switch
					turn++
					continue loop
				inp = player input
				if inp == 'move 1':
					execute move 1
				elif inp == 'move 2':
					execute move 2
				elif inp == 'switch':
					inp2 = player input - which pokemon?
					set current player pokemon to inp2
			else:
				if current opponent pokemon health == 0:
					grant xp to current player pokemon
					force switch to next pokemon in array
				execute random move on current pokemon
			turn++

		result = all of pokemon health == 0 ? you won : opp won

		print result

		carry out level ups
