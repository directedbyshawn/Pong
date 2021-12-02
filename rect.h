#ifndef PONG_RECT_H
#define PONG_RECT_H

#include "shape.h"

struct dimensions {

    double width;
    double height;

    dimensions();
    dimensions(double width, double height);

};

class Rect : public Shape {

private:

    dimensions size;
    // didn't have time to implement paddle speed, hopefully
    // will be able to add soon.
    int speed;

public:

    Rect();
    explicit Rect(dimensions size);
    explicit Rect(color fill);
    explicit Rect(point center);
    Rect(dimensions size, color fill);
    Rect(dimensions size, color fill, point center);

    virtual ~Rect() = default;

    dimensions getSize() const;
    void setSize(double width, double height);
    double getWidth() const;
    void setWidth(double width);
    double getHeight() const;
    void setHeight(double height);
    void changeWidth(double deltaW);
    void changeHeight(double deltaH);
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;
    int getSpeed() const;
    void setSpeed(int speed);

    void draw() const override;

};

#endif //PONG_RECT_H
