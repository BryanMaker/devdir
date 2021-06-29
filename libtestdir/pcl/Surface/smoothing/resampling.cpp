#include <iostream>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>

int main()
{
    // Load input filter into a PointCloud<T> with an appropriate type
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
    // Load bun0.pcd -- should be available with the PCL archive in test
    if (pcl::io::loadPCDFile("../../data/bowl_1_0.pcd", *cloud) == -1)
    {
        std::cout << "Failed to open pcd file" << std::endl;
    }

    // Create a KD-Tree
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);

    // Output has the PointNormal type order to store the normals calculated by MLS(移动最小二乘)
    pcl::PointCloud<pcl::PointNormal> mls_points; // 法线点云(法线参数)

    // Init object (second point type is for the normal, even if unused)
    // mls对象
    pcl::MovingLeastSquares<pcl::PointXYZ, pcl::PointNormal> mls;
    mls.setComputeNormals (true); // 设置算法是否还应存储计算的法线
    // set parameters
    mls.setInputCloud(cloud);
    mls.setPolynomialOrder (2); // 设置多项式阶
    mls.setSearchMethod(tree);
    mls.setSearchRadius(0.03); // 设置搜索半径

    // Reconstruct
    mls.process(mls_points);
    // Save output
    pcl::io::savePCDFile("../../data/bowl_1_0-mls.pcd", mls_points);

    return 0;
}
