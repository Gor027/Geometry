#include <iostream>
#include <typeinfo>

using namespace std;

class Vector {
  int my_x;
  int my_y;
  
  public:
    Vector() = delete;
    
    Vector(int a, int b) {
      my_x = a;
      my_y = b;
    }
    
    //konstruktor kopiujący
    Vector(const Vector &vec) : my_x(vec.my_x), my_y(vec.my_y) {
    }
    //konstruktor przenoszący
    Vector(Vector &&vec) : my_x(move(vec.my_x)), my_y(move(vec.my_y)) {
    }
    //destruktor
    ~Vector(){
    }
    
    bool operator== (const Vector &vec) {
      return (my_x == vec.x() && my_y == vec.y());
    }
    
    Vector& operator+= (const Vector &vec) {
      my_x += vec.x();
      my_y += vec.y();
      return *this;
    }
    
    Vector reflection() {
      return Vector(my_y, my_x);
    }
    
    int x() const {
      return my_x;
    }
    int y() const {
      return my_y;
    }
    
    void wypisz() {
      cout<<my_x<<" "<<my_y<<endl;
    }
};

class Position {
  int my_x;
  int my_y;
  
  public:
    Position() = delete;
    Position(int a, int b) {
      cout<<"tworze Position "<<a<<" "<<b<<endl;
      my_x = a;
      my_y = b;
    }
    
    //konstruktor kopiujący
    Position(const Position &pos) : my_x(pos.my_x), my_y(pos.my_y) {
    }
    //konstruktor przenoszący
    Position(Position &&pos) : my_x(move(pos.my_x)), my_y(move(pos.my_y)) {
    }
    //destruktor
    ~Position(){
    }
    
    bool operator== (const Position &pos) {
      return (my_x == pos.x() && my_y == pos.y());
    }
    
    Position& operator+= (const Vector &vec) {
      my_x += vec.x();
      my_y += vec.y();
      return *this;
    }
    
    Position reflection() {
      return Position(my_y, my_x);
    }
    
    int x() const{
      return my_x;
    }
    int y() const{
      return my_y;
    }
    
    static const Position& origin() {
      static const Position ans(0, 0);
      return ans;
    }
    
    void wypisz() {
      cout<<my_x<<" "<<my_y<<endl;
    }
    
};

Position operator+ (const Position &pos, const Vector &vec) {
  return (Position)(pos) += vec;
}
Position operator+ (const Vector &vec, const Position &pos) {
  return (Position)(pos) += vec;
}
Vector operator+ (const Vector &vec1, const Vector &vec2) {
  return (Vector)(vec1) += vec2;
}



int main() {
  Vector v = Vector(2, 1);
  Vector w = Vector(v);
  v.wypisz();
  w.wypisz();
  v += (Vector(1,1));
  v.wypisz();
  w.wypisz();
}
