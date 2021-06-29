#include <pcl/ModelCoefficients.h> // 模型参数
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h> // 提取索引
#include <pcl/filters/voxel_grid.h> // 降采样过滤器
#include <pcl/features/normal_3d.h>
#include <pcl/search/kdtree.h>
#include <pcl/sample_consensus/method_types.h> // 样本共识算法
#include <pcl/sample_consensus/model_types.h> // 样本共识模型
#include <pcl/segmentation/sac_segmentation.h> // 样本共识分割
#include <pcl/segmentation/extract_clusters.h> // 提取团簇
#include <thread>
#include "../../tools/PCLPCDViewer.h"

using namespace std::literals::chrono_literals;

int main()
{
    // Read in the cloud data
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>),
        cloud_f(new pcl::PointCloud<pcl::PointXYZ>);
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("../../data/table_scene_lms400.pcd", *cloud))
    {
        std::cout << "Failed to open pcd file" << std::endl;
        return -1;
    }

    // 降采样
    // Create the filtering object: downsample the dataset using a leaf size of 1cm
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::VoxelGrid<pcl::PointXYZ> vg;
    vg.setInputCloud(cloud);
    vg.setLeafSize(0.01f, 0.01f, 0.01f);
    vg.filter(*cloud_filtered);

    // 平面分割(替除所有平面,为下面团簇提取准备数据)
    // Create the segmentation object for the plannar model and set all the parameters
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane(new pcl::PointCloud<pcl::PointXYZ>);
    seg.setOptimizeCoefficients(true); // 设置优化
    seg.setModelType(pcl::SACMODEL_PLANE); // 平面
    seg.setMethodType(pcl::SAC_RANSAC); // 随机样本共识
    seg.setMaxIterations(100); // 最大迭代次数
    seg.setDistanceThreshold(0.02); // 设置距离阈值

    int nr_points = (int) cloud_filtered->size();
    while (cloud_filtered->size() > 0.3 * nr_points)
    {
        // Segment the largest planar comonent from the remaining cloud
        seg.setInputCloud(cloud_filtered);
        seg.segment(*inliers, *coefficients); // 分割出索引和模型系数
        if (inliers->indices.size() == 0)
        {
            std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
            break;
        }

        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<pcl::PointXYZ> extract;
        extract.setInputCloud(cloud_filtered);
        extract.setIndices(inliers);
        extract.setNegative(false);
        extract.filter(*cloud_plane);

        // Remove the planar inliers, extract the rest
        extract.setNegative(true);
        extract.filter(*cloud_f);
        *cloud_filtered = *cloud_f;
    }
    
    // Creating the KdTree object for the search method of the extraction
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud_filtered);

    std::vector<pcl::PointIndices> cluster_indices; // 用于保存检测到的簇索引
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setClusterTolerance(0.02); // 2cm
    ec.setMinClusterSize(100); // 团簇包含最小点
    ec.setMaxClusterSize(25000); // 团簇包含最大点
    ec.setSearchMethod(tree); // 点云数空间信息
    ec.setInputCloud(cloud_filtered);
    ec.extract(cluster_indices);

    pcl::visualization::PCLVisualizer::Ptr viewer;
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); it++)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        for (const auto& idx : it->indices)
            cloud_cluster->push_back((*cloud_filtered)[idx]);
        cloud_cluster->width = cloud_cluster->size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        viewer = simpleVis(cloud_cluster);
        while (!viewer->wasStopped())
        {
            viewer->spinOnce(100);
            std::this_thread::sleep_for(100ms);
        }
    }

    return 0;
}
