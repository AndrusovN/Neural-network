#ifndef MATRIX
#define MATRIX

namespace matrices {

	template <class T, int a_s, int b_s, int mid_s>
	void multiply(T a[a_s][mid_s], T b[mid_s][b_s], T res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = 0;
			}
		}
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				for (int k = 0; k < mid_s; k++)
				{
					res[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}


	template <class T, class type = double, class resultT = T, int a_s, int b_s>
	void numberMult(T a[a_s][b_s], type number, resultT res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = a[i][j] * number;
			}
		}
	}


	template <class T, class type = double, class resultT = T, int a_s, int b_s>
	void numberDiv(T a[a_s][b_s], type number, resultT res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = number / a[i][j];
			}
		}
	}

	template <class T, int a_s, int b_s>
	void transpose(T a[a_s][b_s], T res[b_s][a_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[j][i] = a[i][j];
			}
		}
	}


	template <class T, int a_s, int b_s>
	void sum(T a[a_s][b_s], T num, T res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = a[i][j] + num;
			}
		}
	}

	template <class T, int a_s, int b_s>
	void sum(T a[a_s][b_s], T b[a_s][b_s], T res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = a[i][j] + b[i][j];
			}
		}
	}


	template <class T, int a_s, int b_s>
	void multEach(T a[a_s][b_s], T b[a_s][b_s], T res[a_s][b_s]) {
		for (int i = 0; i < a_s; i++)
		{
			for (int j = 0; j < b_s; j++)
			{
				res[i][j] = a[i][j] * b[i][j];
			}
		}
	}


	template <class T, int a_s, int b_s, int both_s>
	void conquatinate(T a[a_s][both_s], T b[b_s][both_s], T res[a_s + b_s][both_s]) {
		for (int i = 0; i < both_s; i++)
		{
			for (int j = 0; j < a_s; j++)
			{
				res[j][i] = a[j][i];
			}

			for (int j = 0; j < b_s; j++)
			{
				res[j + a_s][i] = b[j][i];
			}
		}
	}

	template <class T, int a_s, int b_s, int both_s>
	void conquatinate(T a[both_s][a_s], T b[both_s][b_s], T res[both_s][a_s + b_s]) {
		for (int i = 0; i < both_s; i++)
		{
			for (int j = 0; j < a_s; j++)
			{
				res[i][j] = a[i][j];
			}

			for (int j = 0; j < b_s; j++)
			{
				res[i][j + a_s] = b[i][j];
			}
		}
	}

	template <int xDim, int yDim>
	void ones(double source[xDim][yDim]) {
		for (int i = 0; i < xDim; i++)
		{
			for (int j = 0; j < yDim; j++)
			{
				source[i][j] = 1;
			}
		}
	}

}
#endif
