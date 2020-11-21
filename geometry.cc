#include <iostream>
#include <typeinfo>
#include "geometry.h"

using namespace std;

Vector::Vector(int a, int b) {
  my_x = a;
  my_y = b;
}

//konstruktor kopiujący
Vector::Vector(const Position &pos) {
  my_x = pos.x();
  my_y = pos.y();
  cout<<"copying constructor vector\n";
}
//konstruktor przenoszący
Vector::Vector(Position &&pos) {
  my_x = move(pos.x());
  my_y = move(pos.y());
  cout<<"moving constructor vector\n";
}

bool Vector::operator== (const Vector &vec) {
  return (my_x == vec.x() && my_y == vec.y());
}

Vector& Vector::operator+= (const Vector &vec) {
  my_x += vec.x();
  my_y += vec.y();
  return *this;
}

Vector Vector::reflection() {
  return Vector(my_y, my_x);
}

int Vector::x() const {
  return my_x;
}
int Vector::y() const {
  return my_y;
}

void Vector::wypisz() {
  cout<<my_x<<" "<<my_y<<endl;
}

Position::Position(int a, int b) {
  //cout<<"tworze Position "<<a<<" "<<b<<endl;
  my_x = a;
  my_y = b;
}


//konstruktor kopiujący
Position::Position(const Vector &vec) {
  my_x = vec.x();
  my_y = vec.y();
  cout<<"copying constuctor position\n";
}
//konstruktor przenoszący
Position::Position(Vector &&vec) {
  my_x = move(vec.x());
  my_y = move(vec.y());
  cout<<"moving constuctor position\n";
}

bool Position::operator== (const Position &pos) {
  return (my_x == pos.x() && my_y == pos.y());
}

Position& Position::operator+= (const Vector &vec) {
  my_x += vec.x();
  my_y += vec.y();
  return *this;
}

Position Position::reflection() {
  return Position(my_y, my_x);
}

int Position::x() const{
  return my_x;
}
int Position::y() const{
  return my_y;
}

const Position& Position::origin() {
  static const Position ans(0, 0);
  return ans;
}

void Position::wypisz() {
  cout<<my_x<<" "<<my_y<<endl;
}


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
  /*
  Position p1(1, 2);
  Vector v1(p1);
  Vector v2(2, 3);
  Position p2(v2);
  p2 = Position(v1);
  v1 = Vector(p2);
  */
  Position p = Position(Vector(Position(1,2)));
  p.wypisz();
}
