#include "../Viewer/viewer.cpp"

void play() {

  World * world = new World();

  Ship * ship = new Ship();

  ship->setVel(new Vector<double>(10, 0));

  world->addEntity(ship);

  Viewer * camera = new Viewer();

  camera->setWorld(world);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1200, 600), "Demo Game");

  sf::Event event;

  while (window->isOpen()){

    while (window->pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        window->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { ship->addAcc( ship->getDir() ); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { ship->addTurningAcc(10); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { ship->addTurningAcc(-10); }

    window->clear();

    camera->display(window);

    window->display();

    world->update();
  }

  return;
}
