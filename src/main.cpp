#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct PixelGrid
{
  sf::Uint8* pixels;
  int W;
  int H;
  PixelGrid(int W_in, int H_in)
  {
    W = W_in;
    H = H_in;
    pixels = new sf::Uint8[W*H*4];
  }
  inline sf::Uint8 operator() (int row, int col, int color) const
  {
    return pixels[4*W*row + 4*col + color];
  }
  inline sf::Uint8& operator() (int row, int col, int color)
  {
    return pixels[4*W*row + 4*col + color];
  }
  ~PixelGrid()
  {
    cout << "PixelGrid destructor called" << endl;
    delete [] pixels;
  }

};
struct Application
{
  sf::RenderWindow* window;
  PixelGrid* pixelgrid;
  unsigned int W;
  unsigned int H;
  sf::Texture* texture;
  sf::Sprite* sprite;

  Application()
  {
    W = 200;
    H = 200; // you can change this to full window size later

    // sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!");
    window = new sf::RenderWindow(sf::VideoMode(W, H), "SFML works!");

    // sf::Uint8* pixels = new sf::Uint8[W*H*4];
    pixelgrid = new PixelGrid(W,H);

    texture = new sf::Texture;
    texture->create(W, H);
    sprite = new sf::Sprite(*texture);

  }
  void run()
  {
    int colorvalue = 255;
    while (window->isOpen())
    {
      sf::Event event;
      while (window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window->close();
        if(event.type == sf::Event::MouseButtonPressed) {
          cout << "mouse pressed" << endl;
          sf::Vector2i position = sf::Mouse::getPosition();
          cout << "x" << position.x << endl;
          cout << "y" << position.y << endl;
        }
        if(event.type == sf::Event::MouseButtonReleased) {
          cout << "mouse released" << endl;
        }
      }
      // update pixels
      if(colorvalue >= 255)
        colorvalue = 0;
      colorvalue++;

      for(register int i = 0; i < W*H*4; i += 4) {
        pixelgrid->pixels[i] = colorvalue; // r
        pixelgrid->pixels[i+1] = colorvalue; // g
        pixelgrid->pixels[i+2] = 1; // b
        pixelgrid->pixels[i+3] = 255; // a
      }

      // access by index
      int row = 100;
      for(int col=100; col < 120; col++) {
        (*pixelgrid)(row,col,0) = 255;
        (*pixelgrid)(row,col,1) = 0;
        (*pixelgrid)(row,col,2) = 0;
        (*pixelgrid)(row,col,3) = 255;
      }

      // pixelgrid.pixels[4*W*row + 4*col + 0] = 0;
      // pixelgrid.pixels[4*W*row + 4*col + 1] = 0;
      // pixelgrid.pixels[4*W*row + 4*col + 2] = 0;
      // pixelgrid.pixels[4*W*row + 4*col + 3] = 0;

      texture->update((*pixelgrid).pixels);

      window->clear();
      window->draw(*sprite);
      window->display();
    }
  }
  ~Application()
  {
    delete window;
    delete pixelgrid;
    delete texture;
    delete sprite;
  }
};


int main()
{
  Application app;
  app.run();
  return 0;
}
