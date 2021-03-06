## 基本思想
- 以关键字 `key` 为自变量, 通过一个特定的函数 `h(散列函数)` 计算出对应的函数值 `h(key)`, 作为数据对象的存储地址   
- 可能不同的关键字会映射到同一个散列地址上, 即`h(key1) = h(key2) [key1!=key2]`, 会发生冲突   
   
如果没有溢出(冲突?): T_查询 = T_插入 = T_删除 = O(1)   
   
## 构造散列函数
#### 数字关键词
1. 直接定址法:   
&emsp;取关键词的线性函数数值作为散列地址   
&emsp;h(key) = a*key + b   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-b5a3cbb9fea87ff9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

2. 除留余数法:   
&emsp;散列函数为: h(key) = key mod p   
&emsp;- p 一般为表的大小 TableSize   
&emsp;- p取素数   
&emsp; > 为什么p要取素数?   
&emsp; > 素数的因子只有1和它本身，而合数至少有除1和其本身之外的另一个因子；如果处理的数据是以合数的某一因子为间隔的话，哈希值会不断的重复即冲突加剧。例如，数据是{3,6,9,12,15,18}如果除数取6，哈希值是{3,0,3,0,3,0};如果取5，哈希值为{3,1,4,2,0,3}就没有冲突发生。   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-1b5dbb6a122cc1ae.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

3. 数字分析法:   
&emsp;分析数字关键字在各位上的变化情况, 取比较随机的位作为散列地址   
&emsp;- 11位手机号码在同一地区前面都差不多, 可取key的后4位作为地址   
&emsp;&emsp;散列函数为: h(key) = atoi(key +7)   其中key是字符串的指针, key+7即偏移到倒数第四位, 将后面的4位字符串转换为整形   
&emsp;- 身份证号   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-b3cf813f5cafb8c5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

4. 折叠法:   
&emsp;把关键词分割成为尾数相同的几个部分, 然后叠加   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-d4851c9d8c2b3cce.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

5. 平方取中法:   
&emsp;希望key中的每一位都对哈希映射结果有影响   
&emsp;- 如果取平方的最后一位, 则只首原key的最后一位的影响   
&emsp;- 取中间的话, 可以受尽量多key的位数影响   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-0ec2e8566d47e96b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 字符关键词
1. ASCII码加权法:   
&emsp;h(key) = (∑ key[i]) mod TableSize   
&emsp;- 冲突较严重   
&emsp;- ASCII用7位表示字符, 共128种值    
&emsp;&emsp;10位的字符串才有1280种映射方法, 但是10位的字符串变化种类很多很多, 会导致结果较聚集   

2. 前3个字符移位法:
&emsp;h(key) = (key[0]*27^2 + key[1]*27 + key[2]) mod TableSize   
&emsp;- 选27是因为 27 = 26个字母 + 一个空格   
&emsp;- 但是仍有很多冲突: string, street, strong, structure等等前三位都一样   
&emsp;- 空间浪费: 3000/26^3 ~= 30% &emsp;(前三位的变化大概有3000种)   

3. 移位法:
&emsp;把关键词的所有n个字符都考虑进去, 并且分布的很好   
![image.png](https://upload-images.jianshu.io/upload_images/12014150-bb0386e70fc614f6.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/12014150-3a130fd9181f5bad.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 冲突解决方法
1. 开放地址法:    
&emsp;换个位置, 一旦发生冲突, 就按某种规则去寻找另一个空地址   
&emsp;- hi(key) = (h(key) + di) mod TableSize     第i次冲突, 就在原地址基础上增加一个di, 再看看新地址冲不冲突   
&emsp; - 线性探测: di = i, 如果冲突则一个个的往后探测 => 会造成聚集现象  
![image.png](https://upload-images.jianshu.io/upload_images/12014150-cd7031159f3aac2b.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

&emsp; - 平方探测: di = +- i^2     (有冲突先去h+1^2, 还有冲突去h-i^2, 还有去h+2^2...)   
&emsp;&emsp;平方探测可能会一直找不到空位, 即使有空位,但是因为是跳着找的,可能就是找不到; 但是避免了聚集问题
> 如果散列表长度TableSize是某个4k+3形式的素数(7,11,19等), 平方探测法就可以探测到整个散列表孔家

&emsp; - 双散列: di = i*h2(key) 再设计一个散列函数      
> h2(key) = p - (key mod p)效果较好    p是素数
2. 链地址法: 把同一位置的冲突对象组织在一起

3. 当散列元素过多时, alpha过大, 查找效率就会下降

> 实用的装填因子一般取   0.5 <= alpha <= 0.85

当装填因子过大是, 解决方法是"再散列 Rehashing", 扩大散列表, 并将原来装入的元素*重新装入*


#### 散列表的性能分析
1. 散列函数是否均匀
2. 处理冲突的方法
3. 装填因子alpha

![image.png](https://upload-images.jianshu.io/upload_images/12014150-636cf0a2a48a046c.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/12014150-18263ad5956f8944.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![image.png](https://upload-images.jianshu.io/upload_images/12014150-3adcda4c68e0a473.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 散列法的查找与问题规模无关, 效率期望是O(1)
- 也使用与直接比较计算量大的问题 (如字符串的比较)
- 但它是以较小的alpha为前提的, 是空间换时间
- 不适用于范围查找, 或最大值最小值查找
