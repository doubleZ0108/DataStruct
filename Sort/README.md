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


---
#### 归并排序(稳定)
##### 递归算法
> 其实只有Merge中才真正用到tmp数组, 为什么不在Merge中声明tmp呢?
> > 在接口函数中直接开辟一个大的空间, 比Merge中一次一次声明小空间要合算的多

**接口函数中开辟只用一个大数组就好**
**Merge中反复开辟空间↓**
![Merge中反复开辟空间](https://upload-images.jianshu.io/upload_images/12014150-ceb521989c012450.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 非递归算法
不用每次都开辟一个n的空间
其实只需要一个额外的空间就行, arr和tmp来回用
![归并排序非递归算法](https://upload-images.jianshu.io/upload_images/12014150-35cd64ac5fb898c8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> 但是你只用两个导来导去, 最后一次不定是在arr中还是在tmp中
> > 在每次循环中做两次MergePass, 最后可以保证最后的结果存在arr中(其实就是如果是奇数次的话, 多执行了一次tmp直接导给arr的操作)

**归并排序在外排序中很常用, 内排序中基本不用**

#### 快速排序(不稳定)
> 快的很重要一个原因是: 调完划分, 每次得到的pivot的位置都是该元素最终的位置
> 向插入排序, 很多元素本轮的位置在下一轮都会发生变化的, 导致很慢

> 子集划分中, 如果正好有元素等于pivot时该怎么办?
> 考虑极端情况, 初始序列全是1
> - 如果遇到相同元素就停下来: left指针在第一个位置就停下来了, right指针在最后一个位置也停下来了, 二者交换, 不停的重复
>   做了很多很多没用的交换, 但是好处在于, 最后pivot的位置大致正好处于序列的中间, 子问题变为N/2的规模
> - 如果遇到相同元素不管他, 继续往后移指针的话: left指针第一轮就一直往后移一直往后移, 直接越过了right, 划分终止
>   省去了很多次无谓的交换, 但是pivot的位置处于该段序列倒数第二的位置, 子问题基本变为N-1的规模
> 还是选择第一个方法要好一点, 第二个方法时间复杂度一下子变成O(N^2)最坏的排序算法情况了

**快速排序小规模数据的处理**
![快速排序小规模数据的处理](https://upload-images.jianshu.io/upload_images/12014150-58f997e4d2ca2258.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 表排序
> 待排序列的数据类型很庞大(比如一部电影), 这时交换两个数据的时间不可以忽略不计了
> 此时我们不改变数据的物理地址, 只是改变指向这些数据的指针顺序以达到排序的目的

![表排序](https://upload-images.jianshu.io/upload_images/12014150-86665b1ada255d88.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如果最终还是必须要对所有数据进行一次物理排序
则可以按照一个环一个环的处理
**复杂度分析**
![复杂度分析](https://upload-images.jianshu.io/upload_images/12014150-021338cdfa12e6cd.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
