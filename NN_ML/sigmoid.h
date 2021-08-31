#include <cmath>
#include <iostream>
#ifndef SIGMOID
#define SIGMOID

namespace Sigmoid {

	template <int xDim, int yDim>
	void sigmoid(double matrix[xDim][yDim], double res[xDim][yDim]) {
		long double e = 2.718281828459045f;
		for (int i = 0; i < xDim; i++)
		{
			for (int j = 0; j < yDim; j++)
			{
				res[i][j] = 1 / (1 + pow(e, -1 * matrix[i][j]));
				//std::cout << pow(e, -1 * matrix[i][j]) << " " << -1 * matrix[i][j] << endl;;
			}
		}
	}


	double sigmoid(double value) {
		double e = 2.718281828f;
		return(1 / (1 + pow(e, -1 * value)));
	}

	template <int xDim, int yDim>
	void sigmoidDerivative(double matrix[xDim][yDim], double res[xDim][yDim]) {
		long double e = 2.718281828f;
		for (int i = 0; i < xDim; i++)
		{
			for (int j = 0; j < yDim; j++)
			{
				long double ePowUnX = pow(e, -1 * matrix[i][j]);
				res[i][j] = ePowUnX / ((1 + ePowUnX) * (1 + ePowUnX));
			}
		}
	}

	double sigmoidDerivative(double value) {
		long double e = 2.718281828f;
		long double ePowUnX = pow(e, -1 * value);
		return(ePowUnX / ((1 + ePowUnX) * (1 + ePowUnX)));
	}

}
#endif
