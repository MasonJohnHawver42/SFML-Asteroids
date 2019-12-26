#include "../World/world.cpp"

class WorldEntity : public Entity {
protected:
  World * world;

  sf::Clock * clock;

public:
  WorldEntity() : Entity() {
    world = new World();

    clock = new sf::Clock();
  }

  // getters

  World * getWorld() { return world; }

  // setters

  void setWorld(World * w) { world = w; }

};
