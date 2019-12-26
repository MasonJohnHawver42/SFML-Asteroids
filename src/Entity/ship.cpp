#include "worldEntity.cpp"

class Ship : public WorldEntity {
public:
  Ship() : WorldEntity() {
    Polygon * newBody = new Polygon();

    double x = 1 / sqrt(2);

    newBody->addVertex(new Vector<double>(0, 1));
    newBody->addVertex(new Vector<double>(-x, -x));
    newBody->addVertex(new Vector<double>(0, -.5));
    newBody->addVertex(new Vector<double>(x, -x));

    setBody(newBody);
  }

  virtual void draw(sf::RenderWindow * window, Vector<double>* pos1, Vector<double>* scale) {
    double rad = dir->getRad() - (M_PI / 1.0);
    body->draw(window, pos1, rad, scale);
  }

  virtual void update() {

    double timeJump = clock->getElapsedTime().asSeconds();
    clock->restart();



    Vector<double> * fv = Vector<double>::mult(*vel, * new Vector<double>(timeJump, timeJump));
    pos->add(*fv);

    Vector<double> * dim = new Vector<double>(world->getWidth(), world->getHeight());
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

    pos = warpedPos;

    double halfLife = 5.0;

    double frictionRate = pow(pow(.5, (1 / halfLife)), timeJump);

    vel->mult(frictionRate);

    double maxChange = 1 / 200.0;

    acc->limitMag(maxChange);

    vel->add(*acc);

    double maxSpeed = 100;

    vel->limitMag(maxSpeed);

    acc->mult(0);

    dir->turn(timeJump * turningVel);

    double turningHalfLife = 1 / 40.0;

    frictionRate = pow(pow(.5, (1 / turningHalfLife)), timeJump);

    turningVel *= frictionRate;

    double maxChangeInTurn = 3;

    if(abs(turningAcc) > maxChangeInTurn) { turningAcc /= abs(turningAcc); turningAcc *= maxChangeInTurn; }

    turningVel += turningAcc;

    double maxTurningVel = 10;

    if(abs(turningVel) > maxTurningVel) { turningVel /= abs(turningVel); turningVel *= maxTurningVel; }

    turningAcc = 0;

    return;
  }
};
