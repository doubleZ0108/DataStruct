#include <limits.h>        /* for CHAR_BIT */
#include <stdio.h>
#include <string.h>
#define MAX 10000

//bit����Ķ���
#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)

int main(void)
{
	//��������ΪMAX��bit����
	char bitarray[BITNSLOTS(MAX)];
	int i, j;

	memset(bitarray, 0, BITNSLOTS(MAX));

	for (i = 2; i < MAX; i++) 
	{
		if (!BITTEST(bitarray, i)) 
		{
			printf("%d\n", i);
			for (j = i + i; j < MAX; j += i)
				//����λ�����е�ĳһλ
				BITSET(bitarray, j);
		}
	}

	system("pause");
	return 0;
}