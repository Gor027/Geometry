#include <iostream>
#include <typeinfo>
#include <cassert>
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
    cout << "copying constructor vector\n";
}

bool Vector::operator==(const Vector &other) const {
    return (my_x == other.x() && my_y == other.y());
}

Vector &Vector::operator+=(const Vector &vec) {
    my_x += vec.x();
    my_y += vec.y();

    return *this;
}

Vector Vector::reflection() const {
    return Vector(my_y, my_x);
}

int Vector::x() const {
    return my_x;
}

int Vector::y() const {
    return my_y;
}

void Vector::wypisz() {
    cout << my_x << " " << my_y << endl;
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
    cout << "copying constuctor position\n";
}

bool Position::operator==(const Position &other) const {
    return (my_x == other.x() && my_y == other.y());
}

Position &Position::operator+=(const Vector &vec) {
    my_x += vec.x();
    my_y += vec.y();
    return *this;
}

Position Position::reflection() const {
    return Position(my_y, my_x);
}

int Position::x() const {
    return my_x;
}

int Position::y() const {
    return my_y;
}

const Position &Position::origin() {
    static const Position ans(0, 0);
    return ans;
}

void Position::wypisz() {
    cout << my_x << " " << my_y << endl;
}

Position operator+(const Position &pos, const Vector &vec) {
    return (Position) (pos) += vec;
}

Position operator+(const Vector &vec, const Position &pos) {
    return (Position) (pos) += vec;
}

Vector operator+(const Vector &vec1, const Vector &vec2) {
    return (Vector) (vec1) += vec2;
}

Rectangle Vector::operator+(const Rectangle &rhs) const {
    Rectangle result(rhs);
    result += *this;

    return result;
}

Rectangle::Rectangle(int width, int height) : recPosition(0, 0) {
    assert(width > 0 && height > 0);
    recWidth = width;
    recHeight = height;
}

Rectangle::Rectangle(int width, int height, Position pos) : recPosition(pos) {
    assert(width > 0 && height > 0);
    recWidth = width;
    recHeight = height;
}

bool Rectangle::operator==(const Rectangle &rhs) {
    return recWidth == rhs.recWidth && recHeight == rhs.recHeight && recPosition == rhs.recPosition;
}

int Rectangle::width() const {
    return recWidth;
}

int Rectangle::height() const {
    return recHeight;
}

Position Rectangle::pos() const {
    return recPosition;
}

Rectangle Rectangle::reflection() const {
    return Rectangle(recHeight, recWidth, recPosition.reflection());
}

int_fast64_t Rectangle::area() const {
    return static_cast<int_fast64_t>(recWidth) * recHeight;
}

Rectangle &Rectangle::operator+=(const Vector &rhs) {
    recPosition += rhs;

    return *this;
}

Rectangle Rectangle::operator+(const Vector &rhs) const {
    Rectangle result = *this;
    result += rhs;

    return result;
}

void printRectangle(const Rectangle &rec) {
    cout << "starting printing rectangle..." << endl;
    rec.pos().wypisz();
    cout << "width: " << rec.width() << " " << "height: " << rec.height() << endl;
    cout << "ending printing rectangle" << endl << endl;
}

Rectangles::Rectangles(std::initializer_list<Rectangle> rectanglesList) {
    std::vector<Rectangle> vec = rectanglesList;
    rectangles = vec;
}

Rectangles::Rectangles(Rectangles &&other) : rectangles(std::move(other.rectangles)) {
}

Rectangles &Rectangles::operator=(Rectangles &&other) {
    rectangles = other.rectangles;

    return *this;
}

size_t Rectangles::size() {
    return rectangles.size();
}

const size_t Rectangles::size() const {
  return rectangles.size();
}

Rectangle &Rectangles::operator[](size_t i) {
    assert(i > 0 && i < size());

    return rectangles[i];
}

const Rectangle &Rectangles::operator[](size_t i) const {
  assert(i > 0 && i < size());

  return rectangles[i];
}

bool Rectangles::operator==(const Rectangles &rhs) {
    for (auto r1 : rectangles) {
        bool isFound = false;
        for (auto r2 : rhs.rectangles) {
            if (r1 == r2) {
                isFound = true;
            }
        }

        if (!isFound) {
            return false;
        }
    }

    return true;
}

Rectangles &Rectangles::operator+=(const Vector &rhs) {
    for (auto r : rectangles) {
        r += rhs;
    }

    return *this;
}

static bool horizontally_possible(const Rectangle &rect1, const Rectangle &rect2) {
  if (rect1.pos() + Vector(0, rect1.height()) == rect2.pos()
      && rect1.width() == rect2.width())
    return true;
    
  return false;
}

static bool vertically_possible(const Rectangle &rect1, const Rectangle &rect2) {
  if (rect1.pos() + Vector(rect1.width(), 0) == rect2.pos()
      && rect1.height() == rect2.height())
    return true;
    
  return false;
}

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
  assert (horizontally_possible(rect1, rect2));
  
  return Rectangle(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
  assert(vertically_possible(rect1, rect2));
  
  return Rectangle(rect1.width() + rect2.width(), rect1.height(), rect1.pos());
}
/*
static void Rectangle::add_height(int height) {
  recHeight += height;
}
static void Rectangle::add_width(int width) {
  recWidth += width;
}*/

Rectangle merge_all(const Rectangles &rects) {
  /*assert(rects.size() > 0);
  
  Position pos = rects[0].pos();
  int height = rects[0].height;
  int width = rects[0].width;
  
  for (size_t i = 1; i < rects.size(); i++) {
    if (width == rects[i].width() && pos + Vector(0, height) == rects[i].pos()) {
      height += rects[i].height();
    }
    else if (height == rects[i].height() && pos + Vector(width, 0) == rects[i].pos()) {
      width += rects[i].width();
    }
  }
  
  return Rectangle(width, height, pos);*/
  return (Rectangle)rects[0];
}

int main() {
    Position p1(1, 2);
    Vector v1(p1);
    Vector v2(2, 3);
    Position p2(v2);
    p2 = Position(v1);
    v1 = Vector(p2);

//    Position p = Position(Vector(Position(1, 2)));
//    p.wypisz();


    cout << endl << "============ RECTANGLES ============" << endl << endl;

    Rectangle r1(1, 1, p1);

    printRectangle(r1);

    Rectangle r2 = r1.reflection();

    printRectangle(r2);

    Rectangle r3 = r1 + v1;

    printRectangle(r3);

    Rectangle r4 = v1 + r1;

    printRectangle(r4);
}