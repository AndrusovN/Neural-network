#include "prediction.h"

#ifndef EVALUATION
#define EVALUATION

template <int M, int ILS, int OLS>
void EvaluationMatrix(double X[M][ILS - 1], double y[M][OLS], double pred[M][OLS], double treshold[OLS], double * precision, double * recall) {
	int tp = 0;
	int fp = 0;
	int tn = 0;
	int fn = 0;

	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			if ((int)(pred[i][j] > treshold[j]) == y[i][j]) {
				if ((int)(pred[i][j] > treshold[j]) == 1) {
					tp++;
				}
				else
				{
					fn++;
				}
			}
			else
			{
				if ((int)(pred[i][j] > treshold[j]) == 1) {
					tn++;
				}
				else
				{
					fp++;
				}
			}
		}
	}

	*precision = (double)tp / (double)(tp + tn);
	*recall = (double)tp / (double)(tp + fp);
}

#endif // !EVALUATION

