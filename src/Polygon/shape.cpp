#include "../vector.cpp"
#include <SFML/Graphics.hpp>

class Shape {
public:
  Shape() {}
  virtual void draw(sf::RenderWindow * window, Vector<double> * pos, double dir, Vector<double> * scale) {}
};
