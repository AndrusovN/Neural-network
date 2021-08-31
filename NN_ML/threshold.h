template<int m>
void sort(double arr[m][2]) {
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m-i-1; j++)
		{
			if (arr[j][0] > arr[j + 1][0]) {
				double buf = arr[j][0];
				arr[j][0] = arr[j + 1][0];
				arr[j + 1][0] = buf;
				
				buf = arr[j][1];
				arr[j][1] = arr[j + 1][1];
				arr[j + 1][1] = buf;
			}
		}
	}
}

#include "matrix.h"
#ifndef THRESHOLD
#define THRESHOLD

template <int m>
void findThreshold(double prediction[m][1], double y[m][1], double* threshold) {
	double conc[m][2] = { 0 };
	matrices::conquatinate<double, 1, 1, m>(prediction, y, conc);
	sort<m>(conc);

	int min1 = m;
	int max0 = -1;
	for (int i = 0; i < m; i++)
	{
		if (conc[i][1] == 1 && min1 == m) {
			min1 = i;
		}

		if (conc[i][1] == 0) {
			max0 = i;
		}
	}
	int nulls = 0;
	for (int i = min1; i <= max0; i++)
	{
		if (conc[i][1] == 0) {
			nulls++;
		}

	}

	bool flag = false;
	int J = nulls;
	int minJ = nulls;
	int minIdx = min1;
	for (int i = min1; i <= max0; i++)
	{
		if (!flag) {
			flag = true;
		}
		if (conc[i][1] == 0) {
			J--;
		}
		else
		{
			J++;
		}

		if (J < minJ) {
			minJ = J;
			minIdx = i;
		}

	}
	if (!flag) {
		*threshold = (conc[min1][0] + conc[max0][0]) / 2.0f;
	}
	else
	{
		if(minIdx != m-1){
			*threshold = (conc[minIdx][0] + conc[minIdx + 1][0]) / 2.0f;
		}
		else
		{
			*threshold = conc[minIdx][0];
		}
		
	}
}

#endif

