#include <iostream>
#include <string>
#include <vector>

const double EPSILON = 0.0000000001;
  // 3D vector
struct Vector3d
{
public:
    double x, y, z;
    Vector3d()
    {
        ;
    }

    ~Vector3d()
    {
        ;
    }

    Vector3d(double dx, double dy, double dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    // 矢量赋值
    void set(double dx, double dy, double dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    // 矢量相加
    Vector3d operator + (const Vector3d& v)const
    {
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }
    // 矢量相减
    Vector3d operator - (const Vector3d& v)const
    {
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }
    // 矢量数乘
    Vector3d Scalar(double c)const
    {
        return Vector3d(c*x, c*y, c*z);
    }
    // 矢量点积
    double Dot(const Vector3d& v)const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    // 矢量叉积
    Vector3d Cross(const Vector3d& v)const
    {
        return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    bool operator == (const Vector3d& v)const
    {
        if (abs(x - v.x) < EPSILON && abs(y - v.y) < EPSILON && abs(z - v.z) < EPSILON)
        {
            return true;
        }
        return false;
    }
};

// 求解一元二次方程ax*x + b*x + c = 0
void SolvingQuadratics(double a, double b, double c, std::vector<double>& t)
{
    ;
}
