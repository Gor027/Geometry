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

//konstruktor przenoszący
Vector::Vector(Position &&pos) {
    my_x = pos.x();
    my_y = pos.y();
    cout << "moving constructor vector\n";
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

//konstruktor przenoszący
Position::Position(Vector &&vec) {
    my_x = vec.x();
    my_y = vec.y();
    cout << "moving constuctor position\n";
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

int Rectangle::area() const {
    return recWidth * recHeight;
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