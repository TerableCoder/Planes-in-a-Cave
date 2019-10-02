Procedural Generation Brainstorming

Goals:
	* Random level generation
	* Create a mapping system that allows for switching between cave and open air
	* Cave system will be randomly generated with obstacles (stalagmites/stalactites).
	* Randomness of AA guns on the ground and rockets/planes that are shot at the player

Strategies for procedural generation:

	* Noise functions:
		* Perlin noise for terrain
			Amount of open air between top and bottom of cave could be changed for difficulty scaling
	* Switching from cave to open air & placement of AA guns could be a simple randomness function
	* The frequency of AA guns could be changed as a difficulty option.




Classes:

	* AA Guns
		* Detect player but bullets do not track
		* Aiming to intercept the player in flight
		* Randomness of shooting delay/ bullet speed
