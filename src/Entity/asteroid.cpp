#include"worldEntity.cpp"

class Asteroid : public WorldEntity {
private:
  int vertCount;

  double size;

  void generateBody() {

    Polygon * newBody = new Polygon();

    double ang = 0;

    for(int i = 0; i < vertCount; i++)
    {
      Vector<double> * vert = Vector<double>::radianToVector(ang);
      vert->mult(size);
      newBody->addVertex(vert);

      ang += (M_PI * 2.0) / vertCount;
    }

    setBody(newBody); return;
  }

public:
  Asteroid() : WorldEntity() {
    vertCount = 5;
    size = 1.0;

    generateBody();
  }

  Asteroid(int vc, double s) : WorldEntity() {
    vertCount = vc;
    size = s;

    generateBody();

    maxSpeed = 100;

    density = 1;
  }

  //getters

  int getVertexeCount() { return vertCount; }

  double getSize() { return size; }

  //setters

  void setVertexCount(int vc) { vertCount = max(3, vc); }

  void setSize(double s) { size = s; }

  void setWorld(World * w) { world = w; world->addAsteroid(this); }

  // other

  void implode() {}

  virtual void update() {

    applyVel();

    warpPos(size, size);

    updateDir();

    vel->limitMag(maxSpeed);

    clock->restart();

  }



};

