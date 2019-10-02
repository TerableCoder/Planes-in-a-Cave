Physics Brainstorm

Goals:
* Ricochet of bullets in environment and bullet drop
* Destructible environments
* 2D flight simulation for acceleration and changing pitch
* Effective collisions with rockets, bullets, and NPCs

Strategies:
* When bullets detect a collision, calculate the new direction and speed to accurately depict the ricochet
* When bullets, rockets, or NPCs collide with a cave edge, remove a chunk of that cave
* W and S keys change the vertical speed of the aircraft, while A and D change the horizontal speed
* X and Y position of the aircraft is calculated using trigonometry:

* When a collision is detected between an aircraft and a rocket, bullet, or NPC, use both objects angle and velocity to calculate the effect of the collision.

Classes:

    * Plane
        * Update position, cap max speed, check collision functions
        * X and y speed, health variable
        * reads user input 
