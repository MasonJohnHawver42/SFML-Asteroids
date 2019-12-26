#include"../Polygon/polygon.cpp"

class Entity
{
protected:
  Vector<double> * pos;
  Vector<double> * dir;

  Vector<double> * vel; // unit per second
  Vector<double> * acc;

  double maxSpeed;
  double maxAcc;

  double turningVel;
  double turningAcc;

  double maxTSpeed;
  double maxTAcc;

  Shape * body;

  int id;
  static int nextId;


public:
  Entity()
  {
    pos = new Vector<double>(0, 0);
    dir = new Vector<double>(1, 0);
    vel = new Vector<double>(0, 0);
    acc = new Vector<double>(0, 0);

    maxSpeed = 10;
    maxAcc = 1 / 10.0;

    turningVel = 0;
    turningAcc = 0;

    maxTSpeed = 10;
    maxTAcc = 1 / 10.0;

    body = new Shape;

    id = nextId;
    nextId++;
  }

  // getters

  Vector<double> * getPos() { return pos; }
  Vector<double> * getDir() { return dir; }
  Vector<double> * getVel() { return vel; }

  double getTurningVel() { return turningVel; }

  double getMaxSpeed() { return maxSpeed; }
  double getMaxAcc() { return maxAcc; }

  double getMaxTurningSpeed() { return maxTSpeed; }
  double getMaxTurningAcc() { return maxTAcc; }

  Shape * getBody() { return body; }

  int getId() { return id; }

  //setters

  void setPos(Vector<double> * p) { pos = p; }
  void setVel(Vector<double> * v) { vel = v; }
  void setAcc(Vector<double> * a) { acc = a; }

  void setDir(double rad) { dir = Vector<double>::radianToVector(rad); }

  void setTurningVel(double v) { turningVel = v; }
  void setTurningAcc(double a) { turningAcc = a; }

  void setMaxSpeed(double ms) { maxSpeed = ms; }
  void setMaxAcc(double ma) { maxAcc = ma; }

  void setMaxTurningSpeed(double ms) { maxTSpeed = ms; }
  void setMaxTurningAcc(double ma) { maxTAcc = ma; }


  void setBody(Shape * b) { body = b; }

  // modifiers

  void turn(double radOffset) { dir->turn(radOffset); }

  void addAcc(Vector<double> * a) { acc->add(* a); }
  void addTurningAcc(double a) { turningAcc += a; }

  // other

  virtual bool equal(Entity * other) { return ( id == other->getId() ); }

  virtual void draw(sf::RenderWindow * window, Vector<double>* pos1, Vector<double>* scale) { body->draw(window, pos1, dir->getRad(), scale); }

  virtual void update() { return; }
};

int Entity::nextId = 0;
