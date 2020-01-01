#include "../World/world.cpp"

class WorldEntity : public Entity {
protected:
  World * world;

  sf::Clock * clock;

  double getElapsedTime() { return clock->getElapsedTime().asSeconds(); }

  double getFrictionRate(double halfLife) { return pow(pow(.5, (1 / halfLife)), getElapsedTime()); }

public:
  WorldEntity() : Entity() {
    world = new World();

    clock = new sf::Clock();
  }

  // getters

  World * getWorld() { return world; }



  // setters

  virtual void setWorld(World * w) { world = w; w->addEntity(this); }

  //other

  virtual void applyVel() {
    Vector<double> * adjVel = new Vector<double>(vel->getX(), vel->getY());
    adjVel->mult(getElapsedTime());

    pos->add(*adjVel);

    delete adjVel;
  }

  virtual void applyFriction(double frictionRate) {
    vel->mult(frictionRate);
  }

  virtual void applyTurningFriction(double frictionRate) {
    turningVel *= frictionRate;
  }

  virtual void updateVel() {
    acc->limitMag(maxAcc);
    acc->mult(getElapsedTime());
    vel->add(*acc);
    vel->limitMag(maxSpeed);
  }

  virtual void updateTurningVel() {
    if(abs(turningAcc) > maxTAcc) { turningAcc /= abs(turningAcc); turningAcc *= maxTAcc; }

    turningVel += turningAcc;

    if(abs(turningVel) > maxTSpeed) { turningVel /= abs(turningVel); turningVel *= maxTSpeed; }
  }

  virtual void updateAcc() {
    acc->mult(0);
  }

  virtual void updateTurningAcc() {
    turningAcc = 0;
  }

  virtual void updateDir() {
    dir->turn(getElapsedTime() * turningVel);
  }

  virtual void warpPos(double widthBuffer, double heightBuffer) {

    Vector<double> * dim = new Vector<double>(world->getWidth() + ( 2 * widthBuffer ), world->getHeight() + ( 2 * heightBuffer ));
    dim->div(2);

    Vector<double> * shiftedPos = Vector<double>::sub(*pos, *(world->getOrigon()));
    shiftedPos->add(*dim);

    dim->mult(2.0);

    Vector<double> * warpedPos = Vector<double>::div(*shiftedPos, *dim);

    warpedPos->setX(floor(warpedPos->getX()));
    warpedPos->setY(floor(warpedPos->getY()));

    warpedPos->mult(*dim);
    warpedPos->mult(-1.0);

    warpedPos->add(*shiftedPos);

    warpedPos->add(*world->getOrigon());

    dim->div(2.0);

    warpedPos->sub(*dim);

    pos->setVector(*warpedPos);

    delete dim, shiftedPos, warpedPos;

  }

  virtual void update() {}

};
