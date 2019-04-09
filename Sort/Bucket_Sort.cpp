/*
假设有N个学生(N很大), 成绩是0~100分的整数, 于是成绩有M=101种取值
在线性时间内对数据排序
*/
void Bucket_Sort(ElementType student[], int N)
{
	/* 创建M个桶*/
	int Bucket[M] = { 0 };		//初始化为0

	for (int i = 0; i < N; ++i)
	{
		将第i个学生 插入 Bucket[student[i].grade]链表中;
	}

	for (int i = 0; i < M; ++i)
	{
		if (Bucket[i])	//如果桶里有元素
		{
			输出整个Bucket[i]链表
		}
	}
}
