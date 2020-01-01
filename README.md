# Asteroids
Asteroids, but with elastic collisions ( so it's really billards in space ).

# Needs
 - the sfml lib ( https://www.sfml-dev.org/ )

# Compiling
goto the ./run file.

# Bugs
  - things ( Entities ) can get stuck in each other. ( this is fixable ) ( fixed ! )
  - Collisions parrawell with the x or y axis will cause a seg-fault. ( this is also fixable )

# TODO
  - be able to break off pieces of the asteroid, so make them destroy-able.
  - uplift the graphics.
  - add different types of weapons ( misiles, lasers, bullets, etc ).
  - add collisions between polygons ( convex then maybe concave ) ( currently everything is simplified to a circle when there is a collision; this method isn't horrible, so this probaly won't change ).
   
# Demos on Desmos

All the maths for the elastic collisions between circles:
  - https://www.desmos.com/calculator/dpc3hnnecx ( This isn the heart of how the collitions work. )
  - https://www.desmos.com/calculator/o34kvvpife ( This fixes the first bug )
  - https://www.desmos.com/calculator/rgubue9cri ( This sums up everything; however, its not compete. )


All the maths for projecting the world onto a screen:
  - https://www.desmos.com/calculator/wv0pnjhr26 ( it scales and shifts everything into their apropiate position on the screen )
 
# Video ( Youtube )
There will be a video soon ( most likely after the first 3 items on the todo list are somewhat finished ).
 
# Collisions
( explination comming soon ) ( I might also post a video on how they work )
 
 
 -mcmc
