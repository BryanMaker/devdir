#include <pcl/ModelCoefficients.h> // 模型参数
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h> // 样本共识方法
#include <pcl/sample_consensus/model_types.h> // 样本共识模型
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/sac_segmentation.h> // 样本共识分割
//#include <pcl/surface/concave_hull.h> // 凹多边形
#include <pcl/surface/convex_hull.h> // 凸多边形
#include <pcl/filters/project_inliers.h>
#include <thread>
#include "../../tools/PCLPCDViewer.h"

using namespace std::literals::chrono_literals;

int main ()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>),
        cloud_projected(new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile("../../data/table_scene_lms400.pcd", *cloud) == -1)
    {
        std::cout << "Failed to open pcd file" << std::endl;
    }

    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    
    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    // Optional
    seg.setOptimizeCoefficients(true);
    // Mandatory
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setDistanceThreshold(0.01);
    
    seg.setInputCloud(cloud);
    seg.segment(*inliers, *coefficients);

    // Project the model inliers
    pcl::ProjectInliers<pcl::PointXYZ> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    // proj.setIndices(inliers);
    proj.setInputCloud(cloud);
    proj.setModelCoefficients(coefficients);
    proj.filter(*cloud_projected);

    // Create a convex Hull representation of the projected inliers
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_hull(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::ConvexHull<pcl::PointXYZ> chull;
    chull.setInputCloud(cloud_projected);
    chull.reconstruct(*cloud_hull);

    std::cout << "cloud_hull size:" << cloud_hull->size() << std::endl;

    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = simpleVis(cloud);
    pcl::visualization::PCLVisualizer::Ptr viewer1;
    viewer1 = simpleVis(cloud_hull);

    while (!viewer->wasStopped()
            && !viewer1->wasStopped())
    {
        viewer->spinOnce(100);
        viewer1->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }
}
