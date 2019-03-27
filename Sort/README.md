## 交换方法
#### 冒泡排序(稳定)
#### 插入排序(稳定)

> 逆序对
> 对于下标i<j, 如果arr[i]>arr[j], 则成(i,j)是一个逆序对

- 交换相邻的两个元素正好消去一个有序对
- 这两个算法的复杂度都是```O(N+逆序对个数)```
- 任意N个不同元素组成的序列平均有N(N-1)/4个逆序对

**要提高算法效率
  => 必须每次消去不止一个逆序对
  => 每次交换相隔较远的两个元素**

#### 希尔排序(不稳定)
> "Dk-间隔"有序的序列, 在执行"Dk-1-间隔"排序后, 仍然是"Dk-间隔"有序的
> 也就是最开始比如做5间隔的排序, 下一趟做3间隔的排序之后, 此时的序列仍然是5间隔有序的
> 也就是逐步缩小gap不会使序列越来越坏

- 原始希尔排序
DM = ⌊N/2⌋, Dk-1 = ⌊Dk/2⌋

**希尔排序坏情况**
![希尔排序坏情况](https://upload-images.jianshu.io/upload_images/12014150-e9d261ea6557d47e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

前几趟增量插入排序根本一点没用, 最后还是靠一趟直接插入排序完成的活, 还不如一开始就直接做直接插入排序呢

**参考的gap取法**
![参考的gap取法](https://upload-images.jianshu.io/upload_images/12014150-026896ae111c0c1a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)