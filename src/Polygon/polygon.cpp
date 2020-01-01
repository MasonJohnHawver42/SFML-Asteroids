#include "vertex.cpp"
#include <vector>

class Polygon : public Shape {
private:
  vector<Vertex *> * vertices;

  double size;

public:

  Polygon () {
    vertices = new vector<Vertex *>();

    size = 0;
  }

  //getters
  double getSize() { return size; }

  int getNumVertices() { return vertices->size(); }

  Vertex getVertex(int vertexNum) { return * vertices->at(validVertexNum(vertexNum)); }

  double getArea() { return M_PI * ( size * size); }

  //setters

  void setSize(double s) { size = s; }

  // modifiers

  bool addVertex(Vector<double> * loc) {
    Vertex * newVert = new Vertex();
    newVert->setLoc(loc);

    return addVertex(newVert);
  }

  bool addVertex(Vertex * newVert) {
    if (validVertex(newVert))
    {

      vertices->insert(vertices->begin() + (vertices->size()), newVert);

      size = max(size, newVert->getLoc()->getMag());

      return 1;
    }

    return 0;
  }

  void removeVertex(int vertexNum) { vertices->erase(vertices->begin() + vertexNum); }


  // checkers:

  virtual bool validVertex(Vertex * newVert) { return 1; }

  // other

  int validVertexNum(int vertexNum) {
    int n = getNumVertices();
    return vertexNum - (n * floor(vertexNum / n));
  }

  void draw(sf::RenderWindow * window, Vector<double> * pos, double dir, Vector<double> * scale) {

    int vn = vertices->size();

    if(vn > 0) {

      Vector<double> * last = vertices->at(0)->getLoc();

      for( int i = 1; i <= vn; i++ ) {

        Vector<double> * curr = vertices->at(validVertexNum(i))->getLoc();

        Vector<double> * v1 = new Vector<double>(last->getX(), last->getY());
        v1->mult(*scale);
        v1->turn(dir);
        v1->add(*pos);

        Vector<double> * v2 = new Vector<double>(curr->getX(), curr->getY());
        v2->mult(*scale);
        v2->turn(dir);
        v2->add(*pos);


        sf::ConvexShape partialPolygon;

        partialPolygon.setPointCount(3);

        partialPolygon.setPoint(0, sf::Vector2f(pos->getX(), pos->getY()));
        partialPolygon.setPoint(1, sf::Vector2f(v1->getX(), v1->getY()));
        partialPolygon.setPoint(2, sf::Vector2f(v2->getX(), v2->getY()));

        //partialPolygon->setOutlineColor(sf::Color::Blue);
        //partialPolygon->setOutlineThickness(1);

        window->draw(partialPolygon);

        last = curr;

        delete v1, v2, curr, partialPolygon;
      }

    }

    return;
  }

};
