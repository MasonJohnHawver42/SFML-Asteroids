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

  Polygon * body;
  double density;

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

    body = new Polygon();
    density = 1;

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

  Polygon * getBody() { return body; }
  double getDensity() { return density; }
  double getMass() { return ( density * body->getArea() ); }

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

  void setBody(Polygon * b) { body = b; }
  void setDensity(double d) { density = d; }

  // modifiers

  void turn(double radOffset) { dir->turn(radOffset); }

  virtual void addAcc(Vector<double> * a) { acc->add(* a); }
  void addTurningAcc(double a) { turningAcc += a; }

  // other

  double getDis(Entity * other) {
    double dis = pos->getDis(*other->getPos());
    dis = dis - body->getSize() - other->getBody()->getSize();

    return dis;
  }

  virtual bool collide(Entity * other) {

    double dis = getDis(other);

    if( dis <= 0 ) {

      Vector<double> * posDiff = Vector<double>::sub(*pos, *other->getPos());

      double slope = posDiff->getY() / posDiff->getX();

      double mySize = body->getSize();
      double otherSize = other->getBody()->getSize();

      if ( dis < min(mySize, otherSize) / -2 ) {

        double flip = (pos->getX() < other->getPos()->getX() ? 1 : -1);

        double myDis = ( dis * flip ) / ( 1 + ( mySize / otherSize ) );
        double otherDis = ( myDis * flip ) * ( mySize / otherSize );

        Vector<double> * myShiftedPos = new Vector<double>(pos->getX(), pos->getY());
        myShiftedPos->sub(*pos);

        Vector<double> * otherShiftedPos = new Vector<double>(other->getPos()->getX(), other->getPos()->getY());
        otherShiftedPos->sub(*pos);

        Vector<double> * myNewPos = new Vector<double>(0,0);
        myNewPos->setX( ( ( myDis > 0 ? 1 : -1 ) * sqrt( (myDis * myDis) / ( 1 + ( slope * slope ) ) ) ) + myShiftedPos->getX() );
        myNewPos->setY( myNewPos->getX() * slope );

        Vector<double> * otherNewPos = new Vector<double>(0,0);
        otherNewPos->setX( ( ( otherDis > 0 ? 1 : -1 ) * sqrt( (otherDis * otherDis) / ( 1 + ( slope * slope ) ) ) ) + otherShiftedPos->getX() );
        otherNewPos->setY( otherNewPos->getX() * slope );

        myNewPos->add(*pos);
        otherNewPos->add(*pos);

        setPos(myNewPos);
        other->setPos(otherNewPos);

      }

      double b1 = vel->getY() + ( vel->getX() / slope );
      double b2 = other->getVel()->getY() + ( other->getVel()->getX() / slope );

      Vector<double> * myBasisVectorX = new Vector<double>(0, 0);
      myBasisVectorX->setX(b1 / (slope + ( 1 / slope ) ) );
      myBasisVectorX->setY(slope * myBasisVectorX->getX());

      Vector<double> * myBasisVectorY = Vector<double>::sub(*vel, *myBasisVectorX);

      Vector<double> * otherBasisVectorX = new Vector<double>(0, 0);
      otherBasisVectorX->setX(b2 / (slope + ( 1 / slope ) ) );
      otherBasisVectorX->setY(slope * otherBasisVectorX->getX());

      Vector<double> * otherBasisVectorY = Vector<double>::sub(*other->getVel(), *otherBasisVectorX);

      double myVel = myBasisVectorX->getMag();
      myVel *= ( myBasisVectorX->getX() > 0 ? 1 : -1 );

      double otherVel = otherBasisVectorX->getMag();
      otherVel *= ( otherBasisVectorX->getX() > 0 ? 1 : -1 );

      double myMass = getMass();
      double otherMass = other->getMass();

      double myFinalVel = ( ( myVel * ( myMass - otherMass ) ) + ( 2 * otherMass * otherVel ) ) / ( myMass + otherMass );
      double otherFinalVel = ( ( otherVel * ( otherMass - myMass ) ) + ( 2 * myMass * myVel ) ) / ( myMass + otherMass );

      double x1 = sqrt( ( myFinalVel * myFinalVel ) / ( 1 + ( slope * slope ) ) ) * (myFinalVel > 0 ? 1 : -1);
      double y1 = x1 * slope;

      double x2 = sqrt( ( otherFinalVel * otherFinalVel ) / ( 1 + ( slope * slope ) ) ) * (otherFinalVel > 0 ? 1 : -1);
      double y2 = x2 * slope;

      Vector<double> * myNewVel = new Vector<double>(x1, y1);
      myNewVel->add(*myBasisVectorY);

      Vector<double> * otherNewVel = new Vector<double>(x2, y2);
      otherNewVel->add(*otherBasisVectorY);

      setVel(myNewVel);
      other->setVel(otherNewVel);

      return 1;
    }

    return 0;
  }


  virtual bool equal(Entity * other) { return ( id == other->getId() ); }

  virtual void draw(sf::RenderWindow * window, Vector<double>* pos1, Vector<double>* scale) { body->draw(window, pos1, dir->getRad(), scale); }

  virtual void update() { return; }
};

int Entity::nextId = 0;
