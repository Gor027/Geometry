#include <iostream>
#include <cassert>
#include "geometry.h"

using namespace std;

Vector::~Vector() = default;

Vector::Vector(int a, int b) {
    my_x = a;
    my_y = b;
}

Vector::Vector(const Position &pos) {
    my_x = pos.x();
    my_y = pos.y();
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

Position::~Position() = default;

Position::Position(int a, int b) {
    my_x = a;
    my_y = b;
}

Position::Position(const Vector &vec) {
    my_x = vec.x();
    my_y = vec.y();
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
    static const Position result(0, 0);

    return result;
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

Rectangle::~Rectangle() = default;

Rectangle::Rectangle(int width, int height) : recPosition(0, 0) {
    assert(width > 0 && height > 0);
    recWidth = width;
    recHeight = height;
}

Rectangle::Rectangle(int width, int height, const Position &pos) : recPosition(pos) {
    assert(width > 0 && height > 0);
    recWidth = width;
    recHeight = height;
}

bool Rectangle::operator==(const Rectangle &rhs) const {
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

size_t Rectangle::area() const {
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

Rectangles::Rectangles() = default;

Rectangles::Rectangles(std::initializer_list<Rectangle> rectanglesList) {
    std::vector<Rectangle> vec = rectanglesList;
    rectangles = vec;
}

Rectangles::Rectangles(const Rectangles &other) = default;

Rectangles::Rectangles(Rectangles &&other) noexcept: rectangles(std::move(other.rectangles)) {
}

Rectangles &Rectangles::operator=(const Rectangles &rhs) = default;

Rectangles &Rectangles::operator=(Rectangles &&other) noexcept {
    rectangles = move(other.rectangles);

    return *this;
}

size_t Rectangles::size() const {
    return rectangles.size();
}

Rectangle &Rectangles::operator[](size_t i) {
    assert(i >= 0 && i < size());

    return rectangles[i];
}

const Rectangle &Rectangles::operator[](size_t i) const {
    assert(i >= 0 && i < size());

    return rectangles[i];
}

bool Rectangles::operator==(const Rectangles &rhs) {
    if (rectangles.size() != rhs.rectangles.size()) {
        return false;
    }

    for (size_t i = 0; i < rectangles.size(); ++i) {
        if (!(rectangles[i] == rhs.rectangles[i])) {
            return false;
        }
    }

    return true;
}

Rectangles &Rectangles::operator+=(const Vector &rhs) {
    for (auto &rectangle : rectangles) {
        rectangle += rhs;
    }

    return *this;
}

Rectangles::~Rectangles() = default;

static bool horizontally_possible(const Rectangle &rect1, const Rectangle &rect2) {
    if (rect1.pos() + Vector(0, rect1.height()) == rect2.pos()
        && rect1.width() == rect2.width()) {

        return true;
    }

    return false;
}

static bool vertically_possible(const Rectangle &rect1, const Rectangle &rect2) {
    if (rect1.pos() + Vector(rect1.width(), 0) == rect2.pos()
        && rect1.height() == rect2.height()) {

        return true;
    }

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

Rectangle merge_all(const Rectangles &rectangles) {
    assert(rectangles.size() > 0);

    Position pos = rectangles[0].pos();
    int height = rectangles[0].height();
    int width = rectangles[0].width();

    for (size_t i = 1; i < rectangles.size(); i++) {
        if (width == rectangles[i].width() && pos + Vector(0, height) == rectangles[i].pos()) {
            height += rectangles[i].height();
        } else if (height == rectangles[i].height() && pos + Vector(width, 0) == rectangles[i].pos()) {
            width += rectangles[i].width();
        } else {
            assert(1 == 0);
        }
    }

    return Rectangle(width, height, pos);
}

Rectangles operator+(const Rectangles &recs, const Vector &vec) {
    return (Rectangles) (recs) += vec;
}

Rectangles operator+(const Vector &vec, const Rectangles &recs) {
    return (Rectangles) (recs) += vec;
}

Rectangles operator+(Rectangles &&recs, const Vector &vec) {
    return move(recs) += vec;
}

Rectangles operator+(const Vector &vec, Rectangles &&recs) {
    return move(recs) += vec;
}