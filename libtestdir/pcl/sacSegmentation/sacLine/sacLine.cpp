#include <iostream>
#include <pcl/ModelCoefficients.h> // 模型参数
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h> // 样本共识
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h> // sac(样本共识)分割
#include <pcl/filters/extract_indices.h> // 提取索引
#include <thread>
#include "../../tools/PCLPCDViewer.h"
#include <math.h>

using namespace std::literals::chrono_literals;

void createLineData(int size, float distance, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudSrc (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudDst (new pcl::PointCloud<pcl::PointXYZ>);
    // 生成数据
    createLineData(100, 0.01, cloudSrc);
    // 显示原始数据
    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = simpleVis(cloudSrc);

    // 用于记录从点云中分割出的平面的模型系数和索引
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients()); // 模型系数
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices()); // 点云索引

    // Create the filtering object
    pcl::ExtractIndices<pcl::PointXYZ> extract; // 按索引过滤器

    // Create the segmentation object
    pcl::SACSegmentation<pcl::PointXYZ> seg;
    // Optional可选项
    seg.setOptimizeCoefficients(true); // 设置优化参数
    // Mandatory强制项
    seg.setModelType(pcl::SACMODEL_LINE);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setMaxIterations(1000); // 设置最大迭代次数
    seg.setDistanceThreshold(0.01); // 设置距离阈值

    seg.setInputCloud(cloudSrc);
    seg.segment(*inliers, *coefficients);
    // 从索引中分割点云
    extract.setInputCloud(cloudSrc);
    extract.setIndices(inliers);
    extract.setNegative(false);
    extract.filter(*cloudDst);

    // 显示直线数据
    pcl::visualization::PCLVisualizer::Ptr viewer1;
    viewer1 = simpleVis(cloudDst);

    while (!viewer->wasStopped()
            && !viewer1->wasStopped())
    {
        viewer->spinOnce(100);
        viewer1->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    return 0;
}

void createLineData(int size, float distance, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{   // x = y = z;
    cloud->push_back(pcl::PointXYZ(0, 0, 0));
    float end = 0;
    for (int i = 0; i < size; i++)
    {
        // 添加直线
        float a = sqrt(pow(distance, 2) / 3) + end;
        end = a;
        float ran1 = 0.1 / (rand() % 100 + 100);
        float ran2 = 0.1 / (rand() % 100 + 100);
        float ran3 = 0.1 / (rand() % 100 + 100);

        float neg1 = rand() % 2;
        float neg2 = rand() % 2;
        float neg3 = rand() % 2;
        ran1 = neg1 ? ran1 : -ran1;
        ran2 = neg2 ? ran2 : -ran2;
        ran3 = neg3 ? ran3 : -ran3;

        cloud->push_back(pcl::PointXYZ(a + ran1, a + ran2, a + ran3));

        // 添加杂讯
        float b = sqrt(pow(distance, 2) / 3) + cloud->at(cloud->size() - 1).x;
        float ran4 = 0.01 * (rand() % 10 + 1);
        float ran5 = 0.01 * (rand() % 10 + 1);
        float ran6 = 0.01 * (rand() % 10 + 1);

        float neg4 = rand() % 2;
        float neg5 = rand() % 2;
        float neg6 = rand() % 2;
        ran4 = neg4 ? ran4 : -ran4;
        ran5 = neg5 ? ran5 : -ran5;
        ran6 = neg6 ? ran6 : -ran6;

        cloud->push_back(pcl::PointXYZ(b + ran4, b + ran5, b + ran6));
    }
}

