#include <iostream>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h> // 按照坐标轴过滤
#include <pcl/segmentation/min_cut_segmentation.h> // 最小剪切细分
// 需要待分割对象中心点,不能使用点云质心取代
#include <Eigen/Core>
#include <pcl/common/transforms.h> // 计算点云质心
#include "../../tools/PCLPCDViewer.h"
#include <thread>

using namespace std::literals::chrono_literals;

int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("../../data/min_cut_segmentation_tutorial.pcd", *cloud))
    {
        std::cout << "Failed to open pcd file" << std::endl;
        return -1;
    }

    // 沿z轴裁剪(非必需,此处用于证明MinCutSegmentation可以使用索引)
    pcl::IndicesPtr indices(new std::vector<int>);
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    pass.filter(*indices);

    // 最小剪切分割对象
    pcl::MinCutSegmentation<pcl::PointXYZ> seg;
    seg.setInputCloud(cloud);
    seg.setIndices(indices); // 设置子集索引(非必需)

    Eigen::Vector4f centroid; // 需要待分割对象的中心点,不能使用点云质心取代
    pcl::compute3DCentroid(*cloud, centroid);
    pcl::PointCloud<pcl::PointXYZ>::Ptr foreground_points(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointXYZ point;
    /*
    point.x = 68.97;
    point.y = -18.55;
    point.z = 0.57;
    */
    point.x = centroid(0);
    point.y = centroid(1);
    point.z = centroid(2);
    foreground_points->points.push_back(point);
    seg.setForegroundPoints(foreground_points);

    seg.setSigma(0.25);
    seg.setRadius(3.0433856);
    seg.setNumberOfNeighbours(14);
    seg.setSourceWeight(0.8);
    std::vector<pcl::PointIndices> clusters;
    seg.extract(clusters);


    std::cout << "Maximum flow is " << seg.getMaxFlow() << std::endl;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud = seg.getColoredCloud();
    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = rgbVis(colored_cloud);
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    return 0;
}
