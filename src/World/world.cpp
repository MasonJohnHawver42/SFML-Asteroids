#include "../Entity/entity.cpp"


class World {
private:
  vector<Entity*> * entities;

  vector<Entity*> * asteroids;

  Vector<double> * origon;

  double width;
  double height;

  int correctIndex(int index) {
    int n = entities->size();
    return (int)(index - (n * floor( index / ( (double) n ) )));
  }

public:
  World() {
    entities = new vector<Entity*>();

    origon = new Vector<double>(0, 0);

    width = 50;
    height = 25;
  }

  //getters

  Vector<double> * getOrigon() { return origon; }

  double getWidth() { return width; }
  double getHeight() { return height; }

  int getNumEntities() { return entities->size(); }
  int getNumAsteroids() { return asteroids->size(); }

  Entity * getEntity(int index) { return entities->at(correctIndex(index)); }
  Entity * getAsteroid(int index) { return asteroids->at(correctIndex(index)); }

  //setters

  void setOrigon(Vector<double> * o) { origon = o; }

  void setWidth(double w) { width = abs(w); }
  void setHeight(double h) { height = abs(h); }

  bool addEntity(Entity * newEntity) {

    for(int i = 0; i < entities->size(); i++) {
      Entity * other = entities->at(i);

      if(newEntity->equal(other)) {
        return 0;
      }
    }

    entities->push_back(newEntity);

    return 1;
  }

  bool addAsteroid(Entity * asteroid) {

    if (addEntity(asteroid)) {
        asteroids->push_back(asteroid);
        return 1;
    }

    return 0;
  }

  void removeEntity(int index) {
    entities->erase(entities->begin() + correctIndex(index));
  }

  bool removeEntity(Entity * oldEntity) {

    for(int i = 0; i < entities->size(); i++) {
      Entity * curr = entities->at(i);
      if(oldEntity->equal(curr)) { removeEntity(i); return 1;}
    }

    return 0;
  }

  void removeAsteroid(int index) {
    int ci = correctIndex(index);

    removeEntity(asteroids->at(ci));
    asteroids->erase(asteroids->begin() + ci);
  }

  // modifiers

  void update() {
    for(int i = 0; i < entities->size(); i++) {
      Entity * curr = entities->at(i);

      curr->update();
    }

    return;
  }

};
