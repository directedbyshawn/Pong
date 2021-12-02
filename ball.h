#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "shape.h"

const double PI = 3.14159265358979323846;

struct positionVector {

    double x;
    double y;

    positionVector();
    positionVector(double x, double y);

};

class Ball : public Shape {

private:

    double radius;
    positionVector v;

public:

    Ball();
    explicit Ball(double radius);
    Ball(double radius, point center);
    Ball(point center, double radius, positionVector v);
    Ball(point center, color fill, double radius);
    Ball(point center, color fill, double radius, positionVector v);

    virtual ~Ball() = default;

    double getRadius() const;
    void setRadius(double radius);
    positionVector getVector() const;
    void setVector(double x, double y);
    void setVectorX(double x);
    void setVectorY(double y);
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    void draw() const override;


};

#endif //PONG_BALL_H
