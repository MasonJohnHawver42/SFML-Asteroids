#include "shape.cpp"

class Vertex {
private:
  Vector<double> * loc;

  int id;
  static int nextId;

public:
  Vertex() {
    loc = new Vector<double>(0, 0);

    id = nextId;
    nextId++;
  }

  //getters

  Vector<double> * getLoc() { return loc; }

  int getID() { return id; }

  // setters

  void setLoc(Vector<double> * newLoc) { loc = newLoc; }

  // --

  bool equal(Vertex * other) { return loc->equal(other->getLoc()); }
};

int Vertex::nextId = 0;


// Done
