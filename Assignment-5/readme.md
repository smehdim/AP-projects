## Doodle jump
In fifth project we aim to implement a graphical game called Doodle jump uning cpp.there is an online demo for doodle jump which can be found at [this domain](https://doodlejump.io/). in order to do that we use rsdl library which it's documentation can be found [here](https://github.com/UTAP/RSDL/wiki/Documentation).
rules of the game are quiet simple , you need to go high as possible and dont fall!
there are several files needed to run this game including the starting map and assests like background or image of the objects that will  be detailed.
player must be able to move left or right using a and d keys.beside falling lower from bottom of the screen player may lose from colliding to enemies too. if the player moves out from the one side of the screen it must come into the screen from the other side. objects used in project are depicted below.
### Platforms 
in order to go higher we need to bounce jump on platforms and each kind of platform has it's own specifications.there are 3 types of platform :
- Normal platforms (green) : this platforms are basic type of platform and when players land on this kind of platforms ,will be moving upward with some constant initial speed.
- moving platforms(blue) : this platforms move from one side of the screen toward the other side of the screen and will change direction when reached one end. the speed that the players will have after landing on this type of platforms are equall to normal ones.
- breakable platforms : landing on this platforms will break platforms instantly and the player keeps falling down.in fact this platform does not affect player's movement.
### Enemies
there are only one type of enemies in game which and colliding into them will cause player to lose instantly. enemies does not move.
### Springs 
spring are some kind of objects that will cause player to have a upward moving speed of twice as musch as a normal platform.

### how to run 
using `make` command 
