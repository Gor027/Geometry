#include <cassert>
#include "geometry.h"

using namespace std;

Vector::~Vector() = default;

Vector::Vector(int x, int y) {
    vecX = x;
    vecY = y;
}

Vector::Vector(const Position &pos) {
    vecX = pos.x();
    vecY = pos.y();
}

bool Vector::operator==(const Vector &other) const {
    return (vecX == other.vecX && vecY == other.vecY);
}

Vector &Vector::operator+=(const Vector &vec) {
    vecX += vec.vecX;
    vecY += vec.vecY;

    return *this;
}

Vector Vector::reflection() const {
    return Vector(vecY, vecX);
}

int Vector::x() const {
    return vecX;
}

int Vector::y() const {
    return vecY;
}

Position::~Position() = default;

Position::Position(int x, int y) {
    posX = x;
    posY = y;
}

Position::Position(const Vector &vec) {
    posX = vec.x();
    posY = vec.y();
}

bool Position::operator==(const Position &other) const {
    return (posX == other.posX && posY == other.posY);
}

Position &Position::operator+=(const Vector &vec) {
    posX += vec.x();
    posY += vec.y();

    return *this;
}

Position Position::reflection() const {
    return Position(posY, posX);
}

int Position::x() const {
    return posX;
}

int Position::y() const {
    return posY;
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

Rectangle Vector::operator+(const Rectangle &vec) const {
    Rectangle result(vec);
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

bool Rectangle::operator==(const Rectangle &other) const {
    return (recWidth == other.recWidth && recHeight == other.recHeight
            && recPosition == other.recPosition);
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

Rectangle &Rectangle::operator+=(const Vector &vec) {
    recPosition += vec;

    return *this;
}

Rectangle Rectangle::operator+(const Vector &vec) const {
    Rectangle result = *this;
    result += vec;

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

Rectangles &Rectangles::operator=(const Rectangles &other) = default;

Rectangles &Rectangles::operator=(Rectangles &&other) noexcept {
    rectangles = move(other.rectangles);

    return *this;
}

size_t Rectangles::size() const {
    return rectangles.size();
}

Rectangle &Rectangles::operator[](size_t i) {
    assert(i < size());

    return rectangles[i];
}

const Rectangle &Rectangles::operator[](size_t i) const {
    assert(i < size());

    return rectangles[i];
}

bool Rectangles::operator==(const Rectangles &other) {
    return rectangles == other.rectangles;
}

Rectangles &Rectangles::operator+=(const Vector &vec) {
    for (auto &rectangle : rectangles) {
        rectangle += vec;
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
    assert(horizontally_possible(rect1, rect2));

    return Rectangle(rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
    assert(vertically_possible(rect1, rect2));

    return Rectangle(rect1.width() + rect2.width(), rect1.height(), rect1.pos());
}

Rectangle merge_all(const Rectangles &recs) {
    assert(recs.size() > 0);

    Position pos = recs[0].pos();
    int height = (int) (recs[0].height());
    int width = (int) (recs[0].width());

    for (size_t i = 1; i < recs.size(); i++) {
        if (width == recs[i].width() && pos + Vector(0, height) == recs[i].pos()) {
            height += recs[i].height();
        } else if (height == recs[i].height() && pos + Vector(width, 0) == recs[i].pos()) {
            width += recs[i].width();
        } else {
            assert(false);
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