#include <vector>

#ifndef GEOMETRY_H

class Position;

class Rectangle;

class Vector {
    int my_x;
    int my_y;

public:
    ~Vector();

    Vector(int a, int b);

    explicit Vector(const Position &pos);

    bool operator==(const Vector &other) const;

    Vector &operator+=(const Vector &vec);

    Rectangle operator+(const Rectangle &rhs) const;

    Vector reflection() const;

    int x() const;

    int y() const;
};

class Position {
    int my_x;
    int my_y;

public:
    ~Position();

    Position(int a, int b);

    explicit Position(const Vector &vec);

    bool operator==(const Position &other) const;

    Position &operator+=(const Vector &vec);

    Position reflection() const;

    int x() const;

    int y() const;

    static const Position &origin();
};

class Rectangle {
    Position recPosition;
    int recWidth;
    int recHeight;

public:
    ~Rectangle();

    Rectangle(int width, int height);

    Rectangle(int width, int height, const Position &pos);

    bool operator==(const Rectangle &rhs) const;

    Rectangle &operator+=(const Vector &rhs);

    Rectangle operator+(const Vector &rhs) const;

    int width() const;

    int height() const;

    Position pos() const;

    Rectangle reflection() const;

    size_t area() const;
};

class Rectangles {
    std::vector<Rectangle> rectangles;

public:
    ~Rectangles();

    Rectangles();

    Rectangles(std::initializer_list<Rectangle> rectanglesList);

    Rectangles(const Rectangles &other);

    Rectangles(Rectangles &&other) noexcept;

    Rectangles &operator=(const Rectangles &rhs);

    Rectangles &operator=(Rectangles &&other) noexcept;

    Rectangle &operator[](size_t i);

    const Rectangle &operator[](size_t i) const;

    bool operator==(const Rectangles &rhs);

    Rectangles &operator+=(const Vector &rhs);

    size_t size() const;
};

Position operator+(const Position &pos, const Vector &vec);

Position operator+(const Vector &vec, const Position &pos);

Vector operator+(const Vector &vec1, const Vector &vec2);

Rectangles operator+(const Rectangles &recs, const Vector &vec);

Rectangles operator+(const Vector &vec, const Rectangles &recs);

Rectangles operator+(Rectangles &&recs, const Vector &vec);

Rectangles operator+(const Vector &vec, Rectangles &&recs);

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2);

Rectangle merge_all(const Rectangles &rectangles);

#endif /* GEOMETRY_H */