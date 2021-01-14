#include "game.hpp"

int main(int argc, char const* argv[])
{
  if (argc > 1)
  {
    printf("argv:%s\n", argv[1]);
  }

  Game game;
  game.run();
  
  return 0;
}
