#if 0
#define _USE_MATH_DEFINES
#include <cmath>

class Point {
private:
    Point(float x, float y) { this->x = x; this->y = y; }

    class PointFactory {
    private:
        PointFactory() {}
    public:
        static Point NewCartisian(float x, float y) {
            return Point{ x, y };
        }
        static Point NewPolar(float r, float theta) {
            return Point{ r*cos(theta), r*sin(theta) };
        }
    };

public:
    float x, y;
    static PointFactory factory;
};


int main()
{
    auto point1 = Point::factory.NewCartisian(3, 4);
    auto point2 = Point::factory.NewPolar(5, M_PI_4);

    return 0;
}
#endif