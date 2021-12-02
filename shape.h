#ifndef PONG_SHAPE_H
#define PONG_SHAPE_H

#include <math.h>
#include <string>

struct point {

    double x;
    double y;

    point();
    point(double x, double y);

};

struct color {

    double red;
    double green;
    double blue;
    double alpha;

    color();
    color(double r, double g, double b);
    color (double r, double g, double b, double a);

};

class Shape {

protected:

    point center;
    color fill;

public:

    Shape();
    explicit Shape(color fill);
    explicit Shape(point center);
    Shape(point center, color fill);

    virtual ~Shape() = default;

    color getColor() const;
    void setColor(color fill);
    point getCenter() const;
    void setCenter(point center);
    double getCenterX() const;
    double getCenterY() const;
    void setCenterX(double x);
    void setCenterY(double y);
    virtual double getLeftX() const = 0;
    virtual double getRightX() const = 0;
    virtual double getTopY() const = 0;
    virtual double getBottomY() const = 0;

    void move(double deltaX, double deltaY);
    virtual void draw() const = 0;

};


#endif //PONG_SHAPE_H
