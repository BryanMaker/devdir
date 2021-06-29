#include <iostream>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>

int main()
{
    // 多边形法线为多边形逆时针右手定则方向，平面有正反
    vtkNew<vtkPoints> points1;
    points1->InsertNextPoint(0.0, 0.0, 0.0);
    points1->InsertNextPoint(3.0, 0.0, 0.0);
    points1->InsertNextPoint(3.0, 0.0, 2.0);
    points1->InsertNextPoint(0.0, 0.0, 2.0);

    vtkNew<vtkPolygon> polygon1;
    polygon1->GetPoints()->DeepCopy(points1.Get());
    polygon1->GetPointIds()->SetNumberOfIds(4);
    polygon1->GetPointIds()->SetId(0, 0);
    polygon1->GetPointIds()->SetId(1, 1);
    polygon1->GetPointIds()->SetId(2, 2);
    polygon1->GetPointIds()->SetId(3, 3);

    vtkNew<vtkPoints> points2;
    points2->InsertNextPoint(0.0, 0.0, 0.0);
    points2->InsertNextPoint(3.0, 0.0, 0.0);
    points2->InsertNextPoint(3.0, 2.0, 0.0);
    points2->InsertNextPoint(0.0, 2.0, 0.0);

    vtkNew<vtkPolygon> polygon2;
    polygon2->GetPoints()->DeepCopy(points2.Get());
    polygon2->GetPointIds()->SetNumberOfIds(4);
    polygon2->GetPointIds()->SetId(0, 0);
    polygon2->GetPointIds()->SetId(1, 1);
    polygon2->GetPointIds()->SetId(2, 2);
    polygon2->GetPointIds()->SetId(3, 3);

    double  tolerance = 0.001; // 均方误差
    double p0[3];
    double p1[3];
    bool isTheyIntersect;
    isTheyIntersect = vtkPolygon::IntersectConvex2DCells(polygon1.Get(), polygon2.Get(), tolerance, p0, p1);
    if (isTheyIntersect)
    {
        std::cout << "Intersected with line: p1(" 
            << p0[0] << "," << p0[1] << "," << p0[2] << 
            "), p2(" << p1[0] << "," << p1[1] << "," << p1[2] <<
            ")" << std::endl;
    }
  
  return 0;
}

