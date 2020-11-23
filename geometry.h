#include <vector>

#ifndef GEOMETRY_H

class Position;

class Rectangle;

class Vector {
    int my_x;
    int my_y;

public:
    Vector() = delete;

    Vector(int a, int b);

    //konstruktor kopiujący
    explicit Vector(const Position &pos);

    bool operator==(const Vector &other) const;

    Vector &operator+=(const Vector &vec);

    Vector reflection() const;

    int x() const;

    int y() const;

    Rectangle operator+(const Rectangle &rhs) const;

    void wypisz();
};

class Position {
    int my_x;
    int my_y;

public:
    Position() = delete;

    Position(int a, int b);

    //konstruktor kopiujący
    explicit Position(const Vector &vec);

    bool operator==(const Position &other) const;

    Position &operator+=(const Vector &vec);

    Position reflection() const;

    int x() const;

    int y() const;

    static const Position &origin();

    void wypisz();
};

class Rectangle {
    Position recPosition;
    int recWidth;
    int recHeight;

public:
    Rectangle(int width, int height);

    Rectangle(int width, int height, Position pos);

    bool operator==(const Rectangle &rhs);

    int width() const;

    int height() const;

    Position pos() const;

    Rectangle reflection() const;

    int_fast64_t area() const;

    Rectangle &operator+=(const Vector &rhs);

    Rectangle operator+(const Vector &rhs) const;
};

class Rectangles {
    std::vector<Rectangle> rectangles;

public:
    Rectangles();

    Rectangles(std::initializer_list<Rectangle> rectanglesList);

    Rectangles(Rectangles &&other);

    Rectangles &operator=(Rectangles &&other);

    Rectangle &operator[](size_t i);

    const Rectangle &operator[](size_t i) const;

    bool operator==(const Rectangles &rhs);

    Rectangles &operator+=(const Vector &rhs);

    size_t size() const;
};

Position operator+(const Position &pos, const Vector &vec);

Position operator+(const Vector &vec, const Position &pos);

Vector operator+(const Vector &vec1, const Vector &vec2);

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_all(const Rectangles &rects);

#endif /* GEOMETRY_H */