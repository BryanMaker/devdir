### 该过滤算法将点云投影到特定模型上



使用pcl的ModelCoefficients创建特定模型参数

对于平面:

```cpp
pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
```

设置投影类型:

```cpp
proj.setModelType(pcl::SACMODEL_PLANE);
```

设置输入点云和模型参数:

```cpp
proj.setInputCloud(cloud);
proj.setModelCoefficients(coefficients);
```
