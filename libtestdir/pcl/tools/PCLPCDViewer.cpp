#include "PCLPCDViewer.h"

pcl::visualization::PCLVisualizer::Ptr rgbVis(pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud)
{
    // --------------------------------------------
    // -----Open 3D viewer and add point cloud-----
    // --------------------------------------------
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, rgb, "sample cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();
    return (viewer);
}

void CloudIntensityToRGB(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudIntensity, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudRGB)
{
    uint8_t r, g, b;
    for (size_t i = 0; i < cloudIntensity->size(); i++)
    {
        uint8_t intensity = (uint8_t)cloudIntensity->at(i).intensity;
        // red
        if (intensity < 128)
        {
            r = 0;
        }
        else if (intensity < 192)
        {
            r = 255 / 64 * (intensity - 128);
        }
        else
        {
            r = 255;
        }

        // green
        if (intensity < 64)
        {
            g = 255 / 64 * intensity;
        }
        else if (intensity < 192)
        {
            g = 255;
        }
        else
        {
            g = -255 / 64 * (intensity - 192) + 255;
        }

        // blue
        if (intensity < 64)
        {
            b = 255;
        }
        else if (intensity < 128)
        {
            b = -255 / 64 * (intensity - 64) + 255;
        }
        else
        {
            b = 0;
        }

        pcl::PointXYZRGB point = pcl::PointXYZRGB(r, g, b);
        point.x = cloudIntensity->at(i).x;
        point.y = cloudIntensity->at(i).y;
        point.z = cloudIntensity->at(i).z;
        cloudRGB->push_back(point);
    }
}
