
#include <GL/glew.h>
#include <iostream>
#include <SFML/Window.hpp>
int main(int argc, char *argv[])
{
  sf::Window window(sf::VideoMode(800, 600), "Graphics");

  GLenum err = glewInit();
  //Check for errors
  if (err != GLEW_OK)
    exit(1);
  if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    exit(1);


  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }

  std::cout << "Hello World" << std::endl;
  return 0;
}