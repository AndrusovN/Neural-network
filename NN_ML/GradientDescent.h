#include "CostFunction.h"
#include "matrix.h"
#include "prediction.h"
#include "sigmoid.h"
#include <iostream>
using namespace std;

#ifndef GRADIENT_DESCENT
#define GEADIENT_DESCENT

template <int ILS, int HLS, int OLS, int m>
void Optimize(double X[m][ILS - 1], double y[m][OLS], double params[ILS * (HLS - 1) + HLS * OLS][1], double lambda, double alpha, double _alpha, int maxIter) {
	double oldGradient[ILS * (HLS - 1) + HLS * OLS][1] = { 0 };
	int iter = 0;
	int itr = maxIter / 100;
	/*for (int i = 0; i < ILS * (HLS - 1) + HLS * OLS; i++)
	{
		//cout << params[i][0] << " ";
		params_copy[i][0] = params[i][0];
	}*/
	for (maxIter; maxIter > 0; maxIter--)
	{
		
		double params_copy[ILS * (HLS - 1) + HLS * OLS][1] = { 0 };
		double gradient[ILS * (HLS - 1) + HLS * OLS][1] = { 0 };
		double cost = 0;
		for (int i = 0; i < ILS * (HLS - 1) + HLS * OLS; i++)
		{
			//cout << params[i][0] << " ";
			params_copy[i][0] = params[i][0];
		}
		//cout << "PARAMS " << params[0][0] << " " << params[1][0] << endl;
		CostFunction<ILS, HLS, OLS, m>(X, y, params_copy[0], lambda, &cost, gradient[0]);
		for (int i = 0; i < ILS * (HLS - 1) + HLS * OLS; i++)
		{
			//cout << params[i][0] << " ";
			params_copy[i][0] = params[i][0];
		}
		matrices::numberMult< double, double, double, ILS* (HLS - 1) + HLS * OLS, 1>(gradient, -1 * alpha, gradient);
		matrices::numberMult< double, double, double, ILS* (HLS - 1) + HLS * OLS, 1>(oldGradient, -1 * _alpha, oldGradient);
		matrices::sum<double, ILS* (HLS - 1) + HLS * OLS, 1>(gradient, oldGradient, gradient);
		for (int i = 0; i < ILS * (HLS - 1) + HLS * OLS; i++)
		{
			//cout << params_copy[i][0] << " ";
		}
		matrices::sum<double, ILS* (HLS - 1) + HLS * OLS, 1>(gradient, params_copy, params);

		for (int i = 0; i < ILS * (HLS - 1) + HLS * OLS; i++)
		{
			oldGradient[i][0] = gradient[i][0];
		}
		
		//
		iter++;
		if (iter % itr == 0) {
			cout << iter / itr << "% completed" << endl;
			cout << "Iteration : " << maxIter << " cost function is " << cost << endl;
		}
		
	}
		
}

#endif
