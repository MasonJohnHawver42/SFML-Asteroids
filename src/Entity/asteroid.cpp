#include"ship.cpp"

class Asteroid : public Entity {
private:
  int vertCount;

  double size;

  void generateBody() {

  }

public:
  Asteroid() : WorldEntity() {
    vertCount = 5;
    size = 1.0;
  }

  Asteroid(int vc, double s) : WorldEntity() {
    vertCount = vd;
    size = s;
  }

  //getters

  int getVertexeCount() { return vertCount; }

  double getSize() { return size; }

  //setters

  void setVertexCount(int vc) { vertCount = max(3, vc); }

  void setSize(double s) { size = s; }

  // other

  void implode() {}



};
