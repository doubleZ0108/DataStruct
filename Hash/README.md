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

