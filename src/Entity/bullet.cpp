#include"asteroid.cpp"


class Bullet : public WorldEntity {
private:
  sf::Clock * masterClock;

  double lifeSpan;

public:
  Bullet() : WorldEntity() {


    // in the future make a new shape - circle

    Polygon * newBody = new Polygon();

    double size = 1/10.0;

    newBody->addVertex(new Vector<double>(size, size));
    newBody->addVertex(new Vector<double>(-size, size));
    newBody->addVertex(new Vector<double>(-size, -size));
    newBody->addVertex(new Vector<double>(size, -size));

    setBody(newBody);

    masterClock = new sf::Clock;

    lifeSpan = 20;

    maxSpeed = 100;
    maxAcc = 200;

    density = 10.0;
  }

  double getTimeAlive() { return masterClock->getElapsedTime().asSeconds(); }

  void explode() {
    world->removeEntity(this);
    delete this;
  }

  void updateAcc() {
    acc->mult(0);

    Vector<double> * a = new Vector<double>(maxAcc, maxAcc);
    a->mult(*dir);

    acc->add(*a);

    delete a;
  }

  void update() {

    applyVel();

    //warpPos(1, 1);

    updateVel();

    updateAcc();

    if(getTimeAlive() > lifeSpan) { explode(); }

    clock->restart();

  }
};
