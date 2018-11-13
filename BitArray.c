#include <limits.h>        /* for CHAR_BIT */
#include <stdio.h>
#include <string.h>
#define MAX 10000

//bit数组的定义
#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

int main(void)
{
	//声明长度为MAX的bit数组
	char bitarray[BITNSLOTS(MAX)];
	int i, j;

	memset(bitarray, 0, BITNSLOTS(MAX));

	for (i = 2; i < MAX; i++) 
	{
		if (!BITTEST(bitarray, i)) 
		{
			printf("%d\n", i);
			for (j = i + i; j < MAX; j += i)
				//设置位数组中的某一位
				BITSET(bitarray, j);
		}
	}

	system("pause");
	return 0;
}