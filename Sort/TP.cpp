#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>
using namespace std;

#define CUTOFF 10
typedef int ElementType;



int main(void)
{
	srand(time(NULL));

	const int N = 100;
	ElementType arr[N];

	/*Init arr[]*/
	for_each(arr, arr + N, [](ElementType &buf) {buf = rand(); });
	
	///////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////


	/*Test if sorted & Print*/
	cout << arr[0] << ' ';
	for(int i = 1; i < N; ++i)
	{
		if (arr[i] < arr[i - 1]) 
		{ 
			cerr << endl << "*** " << "Sort Failed!" << " ***" << endl; 
			system("pause");
			return 0; 
		}
		else
		{
			cout << arr[i] << ' ';
		}
	}
	cout << endl;
	cout << "Sort Success!" << endl;
	
	system("pause");
	return 0;
}
