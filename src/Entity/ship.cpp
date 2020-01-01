#include "bullet.cpp"

class Ship : public WorldEntity {
private:
  double velHalfLife;
  double turningHalfLife;

  sf::Clock * reloadTimer;
  double reloadTime;

public:
  Ship() : WorldEntity() {
    Polygon * newBody = new Polygon();

    double x = 1 / sqrt(2);

    newBody->addVertex(new Vector<double>(0, 1));
    newBody->addVertex(new Vector<double>(-x, -x));
    newBody->addVertex(new Vector<double>(0, -.5));
    newBody->addVertex(new Vector<double>(x, -x));

    setBody(newBody);

    maxSpeed = 70;
    maxAcc = 50;

    maxTSpeed = 7;
    maxTAcc = 1;

    velHalfLife = 5;
    turningHalfLife = 1 / 20.0;

    reloadTimer = new sf::Clock();
    reloadTime = 1 / 10.0;

    density = 5.0;
  }

  double getReloadTimer() { return reloadTimer->getElapsedTime().asSeconds(); }

  void thrust() {

    Vector<double> * addAcc = new Vector<double>(maxAcc, maxAcc);
    addAcc->mult(*dir);

    acc->add(*addAcc);
    delete addAcc;
  }

  bool shoot() {

    if(getReloadTimer() > reloadTime) {
      Bullet * bill = new Bullet();

      Vector<double> * d = new Vector<double>(dir->getX(), dir->getY());

      bill->setDir(d->getRad() + (M_PI / 2.0));

      bill->getPos()->setX(pos->getX());
      bill->getPos()->setY(pos->getY());

      bill->getPos()->add(*Vector<double>::mult(*new Vector<double>(2,2), *dir));

      bill->setWorld(world);

      bill->getVel()->add(*vel);

      bill->updateAcc();

      reloadTimer->restart();

      return 1;
    }

    else { return 0; }
  }

  virtual void update() {
    applyVel();

    warpPos(1, 1);

    updateVel();

    updateAcc();

    applyFriction(getFrictionRate(velHalfLife));

    updateDir();

    applyTurningFriction(getFrictionRate( turningHalfLife ));

    updateTurningVel();

    updateTurningAcc();

    clock->restart();

    return;
  }

};
