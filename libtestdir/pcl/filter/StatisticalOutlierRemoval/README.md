### 该算法使用统计分析从点云中删除嘈杂的测量值，例如离群值

算法主要需要设置两个参数

```cpp
sor.setMeanK(50) // 要分析的近邻点数
sor.setStddevMulThresh(1.0) // 设置标准差倍数
// 如果一个点的距离超出平均距离一个标准差以上, 将被删除
```

平均距离:

$$
u=(x1+x2+...+xn)/n
$$

方差(数据的离散程度):

$$
S^2=((x1-u)^2+(x2-u)^2+...+(xn-u)^2)/n)
$$

标准差:

$$
\sigma=sqrt(s^2)
$$

平均值、标准差、方差讲解:

[平均值(Mean)、方差(Variance)、标准差(Standard Deviation) （转）_weixin_30362083的博客-CSDN博客](https://blog.csdn.net/weixin_30362083/article/details/99830789)
