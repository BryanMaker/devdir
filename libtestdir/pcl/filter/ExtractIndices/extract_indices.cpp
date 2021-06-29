#include <iostream>
#include <sstream>
#include <pcl/ModelCoefficients.h> // 模型参数
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h> // 样本共识
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h> // sac(样本共识)分割
#include <pcl/filters/voxel_grid.h> // 网格过滤器
#include <pcl/filters/extract_indices.h> // 提取索引
#include <thread>
#include "../../tools/PCLPCDViewer.h"

using namespace std::literals::chrono_literals;

int main()
{
    // 原始点云
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloudIntensity (new pcl::PointCloud<pcl::PointXYZI>);
    // 将采样过点云
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZI>);
    // 用于保存分割出的平面的点云
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_p (new pcl::PointCloud<pcl::PointXYZI>);
    // 用于保存分割出的平面的补集的点云,用其替换剩余点云以继续处理
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZI>);

    // Open PCD file
    if (pcl::io::loadPCDFile<pcl::PointXYZI>("../../data/room.pcd", *cloudIntensity) == -1)
    {
        std::cout << "Failed to open pcd file" << std::endl;
        return -1;
    }
    // 展示原始点云
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudRGB (new pcl::PointCloud<pcl::PointXYZRGB>);
    CloudIntensityToRGB(cloudIntensity, cloudRGB);
    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = rgbVis(cloudRGB);
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }
    
    // Create the filtering object: downsample the dataset using a leaf size of 5cm
    pcl::VoxelGrid<pcl::PointXYZI> sor;
    sor.setInputCloud(cloudIntensity);
    sor.setLeafSize(0.05f, 0.05f, 0.05f);
    sor.filter(*cloud_filtered);

    // 展示过滤后点云
    cloudRGB = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
    CloudIntensityToRGB(cloud_filtered, cloudRGB);
    viewer = rgbVis(cloudRGB);
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZI> seg;
    // Optional可选项
    seg.setOptimizeCoefficients(true); // 设置优化参数
    // Mandatory强制项
    seg.setModelType(pcl::SACMODEL_PLANE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setMaxIterations(1000); // 设置最大迭代次数
    seg.setDistanceThreshold(0.01); // 设置距离阈值

    // 用于记录从点云中分割出的平面的模型系数和索引
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients()); // 模型系数
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices()); // 点云索引
    
    // Create the filtering object
    pcl::ExtractIndices<pcl::PointXYZI> extract; // 按索引过滤器

    int i = 0, nr_points = (int)cloud_filtered->size();
    // while 30% of the original cloud is still there
    // 结束条件为处理后原始点云剩余30%
    while (cloud_filtered->size() > 0.3 * nr_points)
    {
        // Segment the largest planar component from the remaining cloud
        // 分割剩余点云中的最大平面
        seg.setInputCloud(cloud_filtered);
        seg.segment(*inliers, *coefficients);
        if (inliers->indices.size() == 0)
        {
            std::cerr << "Could not estimate a planar model for the given dataset." << std::endl;
            break;
        }

        // Extract the inliers
        // 从索引中分割点云
        extract.setInputCloud(cloud_filtered);
        extract.setIndices(inliers);
        extract.setNegative(false);
        extract.filter(*cloud_p);
        // 展示分割出的点云
        std::cout << "planar id:" << i << std::endl;
        cloudRGB = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>);
        CloudIntensityToRGB(cloud_p, cloudRGB);
        viewer = rgbVis(cloudRGB);
        while (!viewer->wasStopped())
        {
            viewer->spinOnce(100);
            std::this_thread::sleep_for(100ms);
        }

        // Create the filtering object
        extract.setNegative(true);
        extract.filter(*cloud_f);
        cloud_filtered.swap(cloud_f);

        i++;
    }
    
    return 0;
}

