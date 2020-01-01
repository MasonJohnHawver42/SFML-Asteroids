#include "../Viewer/viewer.cpp"

void play() {

  World * world = new World();

  Ship * ship = new Ship();

  ship->setVel(new Vector<double>(0, 0));

  ship->setWorld(world);

  Asteroid * aster = new Asteroid(14, 6.0);

  aster->getVel()->setX(-10);
  aster->getVel()->setY(0);

  aster->getPos()->setX(50);
  aster->getPos()->setY(.001);

  aster->setTurningVel(-4 / 10.0);

  aster->setWorld(world);

  Viewer * camera = new Viewer();

  camera->setWorld(world);

  sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(1200, 600), "Demo Game");

  sf::Event event;

  while (window->isOpen()){

    while (window->pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
        window->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { ship->thrust(); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { ship->addTurningAcc(5); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { ship->addTurningAcc(-5); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { ship->shoot(); }

    window->clear();

    camera->display(window);

    window->display();

    world->update();
  }

  return;
}
