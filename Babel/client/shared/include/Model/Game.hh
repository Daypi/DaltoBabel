#pragma once

namespace RType
{
  namespace Model
  {
    class		Game
    {
    public:
      Game();
      Game(const Game &);
      ~Game();

      Game	&operator =(const Game &);
    };
  }
}
