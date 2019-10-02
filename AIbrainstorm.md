AI Brainstorm:



Goals:

	* Rockets that track player
		* could be a special type of "bullet"
		* or could be a special type of "enemy"

	* Planes that can shoot enemy player, or dodge them

	* AI dodges incoming fire from player

"Classes":

	* Entity Interface
		* header file
		* defines enemy functionality such as:
			* check speed
			* movement
			* check collision
			* "death" function for when the plane collides with an object or is shot
		* holds variables
			* XPosition
			* YPosition
			* XSpeed
			* YSpeed
			* Health
			* Sprite
			* Hitbox

	* Subclasses of Entity
		* must define specific characteristics such as:
			* define the functions from Entity
				* movement, shooting, or dodging might be different for different enemy types
					* Possible method of decision-making - have enemy predict the future by "running" a few seconds of gameplay, and selecting moves that are likely to result in the player's death
					* Possible method of decision-making - some type of enemy cooperation, i.e. enemies fire at the same time as each other to maximize chance of hitting player
					* Could have "kamikaze" planes that fly close to the player and ranged planes that stay farther away
					* Possible method of decision-making - have enemies be aware of each other and use this to fly in more complex patterns after the enemy in open air
		* Rocket would probably be one of these
		* Enemy
			* detect player
			* detect incoming fire
			* "dodge"
			* "shoot"

	* Some enemies restricted to certain areas of the screen
		* Some enemies stay back (right side of screen)
		* some move forward and attack player 
			* "kamikaze" planes

	* Week 10/2 - 10/9:
		*using enemy_test as our test environment, create a working enemy that moves about the screen and shoots bullets.
			*Requirements
				* implementation of an Enemy
					* sprite (Matt)
					* movement (Brandon)
					* shoot (Conner)
				* implementation of a bullet (Jeroen)
					* movement
