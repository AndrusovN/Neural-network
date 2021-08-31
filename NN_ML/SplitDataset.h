#ifndef SPLIT_DATASET
#define SPLIT_DATASET

template<int M, int ILS, int OLS, int ST>
void Split(int[M][ILS] X, int[M][OLS] y, int[ST][ILS] X_train, int [ST][OLS] y_train, int[M-ST][ILS] X_CV, int[M-ST][OLS] y_CV) {
	for (int i = 0; i < ST; i++)
	{
		for (int j = 0; j < ILS; j++)
		{
			X_train[i][j] = X[i][j];
		}

		for (int k = 0; k < OLS; k++)
		{
			y_train[i][j] = y[i][j];
		}
	}

	for (int i = 0; i < M-ST; i++)
	{
		for (int j = 0; j < ILS; j++)
		{
			X_CV[i][j] = X[i+ST][j];
		}

		for (int k = 0; k < OLS; k++)
		{
			y_CV[i][j] = y[i+ST][j];
		}
	}
}

#endif // !SPLIT_DATASET

