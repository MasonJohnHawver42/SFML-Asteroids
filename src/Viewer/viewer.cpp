#include "../Entity/ship.cpp"


class Viewer {
private:
  World * world;

  double width;
  double height;

public:
  Viewer() {
    world = new World();

    width = world->getWidth();
    height = world->getHeight();
  }

  //getters

  double getWidth() { return width; }
  double getHeight() { return height; }

  World * getWorld() { return world; }

  //setters

  void setWidth(double w) { width = w; }
  void setHeight(double h) { height = h; }

  void setWorld(World * w) { world = w; }

  // other

  void display(sf::RenderWindow * window) {
     double mappedWidth = window->getSize().x;
     double mappedHeight = window->getSize().y;

     mappedHeight *= -1;

     Vector<double> * mappedOrigon = new Vector<double>(mappedWidth,  mappedHeight);
     mappedOrigon->div(2.0);

     Vector<double> * scale = new Vector<double>(mappedWidth, mappedHeight);
     scale->div(* new Vector<double>(width, height));

     for(int i = 0; i < world->getNumEntities(); i++) {
       Entity * curr = world->getEntity(i);

       Vector<double> * pos = new Vector<double>(curr->getPos()->getX(), curr->getPos()->getY());

       pos->sub(*world->getOrigon());
       pos->mult(*scale);
       pos->add(*mappedOrigon);
       pos->setY(abs(pos->getY()));

       curr->draw(window, pos, scale);
     }
  }
};
