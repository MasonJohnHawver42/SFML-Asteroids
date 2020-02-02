# Asteroids
Asteroids, but with elastic collisions ( so it's really billards in space ).

# Needs
 - the sfml lib ( https://www.sfml-dev.org/ )

# Compiling
goto the ./run file.

# Bugs
  - things ( Entities ) can get stuck in each other. ( this is fixable ) ( fixed ! )
  - Collisions parrawell with the x or y axis will cause a seg-fault. ( this is also fixable ) ( This has been somewhat fixed ( its been fixed to the point where the program wont stop if this event occurs. No seg-faults! ) )

# TODO
  - be able to break off pieces of the asteroid, so make them destroy-able. ( done! see the video ( V1 ) )
  - uplift the graphics.
  - add different types of weapons ( misiles, lasers, bullets, etc ).
  - add collisions between polygons ( convex then maybe concave ) ( currently everything is simplified to a circle when there is a collision; this method isn't horrible, so this probaly won't change; however, collisions between pollygons can entail a more relistic system and more interesting gameplay. For example, a laser could crudly cut pieces of the asteroid off insead of the asteroid simply imploding after a number of hits. In conclution, maybe; however, there is a decent chance, so probaly yes. )
   
# Demos on Desmos

All the maths for the elastic collisions between circles:
  - https://www.desmos.com/calculator/dpc3hnnecx ( This isn the heart of how the collitions work. )
  - https://www.desmos.com/calculator/o34kvvpife ( This fixes the first bug )
  - https://www.desmos.com/calculator/rgubue9cri ( This sums up everything; however, its not compete. )


All the maths for projecting the world onto a screen:
  - https://www.desmos.com/calculator/wv0pnjhr26 ( it scales and shifts everything into their apropiate position on the screen )
 
# Video ( Youtube )
 - https://youtu.be/4oIpK1rjBes ( V1 )
 - https://youtu.be/M-CEo-lhDqE ( Still V1 but with max potential )


There will be a another video once I've finished my TODO list and some of the bugs.
 
# Collisions
( explination comming soon ) ( I might also post a video on how they work )
 
 
 -mcmc
