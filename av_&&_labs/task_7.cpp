#include <iostream>
#include <cmath>
using namespace std;
class Triangle
{
private:
    float a;
    float b;
    float c;

public:
    Triangle(float _a, float _b, float _c)
    {
        a = _a;
        b = _b;
        c = _c;
    }
    float perimetar()
    {
        return a + b + c;
    }
    float getA()
    {
        return a;
    }

    float ploshtina()
    {
        float s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    ~Triangle()
    {
    }
};

int main()
{
    float a, b, c;
    cin >> a >> b >> c;
    Triangle t1(a, b, c);
    cout << t1.perimetar() << " " << t1.ploshtina() << endl;

    return 0;
}
