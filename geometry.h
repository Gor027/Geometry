#ifndef GEOMETRY_H

  class Position;
  
  class Vector {
    int my_x;
    int my_y;

    public:
      Vector() = delete;
      Vector(int a, int b);
      
      //konstruktor kopiujący
      Vector(const Position &pos);
      //konstruktor przenoszący
      Vector(Position &&pos);
   
      bool operator== (const Vector &vec);
      
      Vector& operator+= (const Vector &vec);
      
      Vector reflection();
      
      int x() const;
      int y() const;
      
      void wypisz();
  };
  
  class Position {
    int my_x;
    int my_y;
    
    public:
      Position() = delete;
      Position(int a, int b);
      
      //konstruktor kopiujący
      Position(const Vector &vec);
      //konstruktor przenoszący
      Position(Vector &&vec);
      
      bool operator== (const Position &pos);
      
      Position& operator+= (const Vector &vec);
      
      Position reflection();
      
      int x() const;
      int y() const;
      
      static const Position& origin();
      
      void wypisz();
  };
  
  Position operator+ (const Position &pos, const Vector &vec);
  Position operator+ (const Vector &vec, const Position &pos);
  Vector operator+ (const Vector &vec1, const Vector &vec2);
  
#endif /* GEOMETRY_H */