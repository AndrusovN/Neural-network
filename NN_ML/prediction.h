#include "matrix.h"
#include "sigmoid.h"
#include <iostream>
using namespace std;

#ifndef PREDICTION
#define PREDICTION

//A prediction function
//ILS - is Input Layer Size
//HLS - is Hidden Layer Size
//OLS - is Output Layer Size
//X - data for learning
//params - parameters for learning (also weights)
//prediction - is a vector of predicted values
template <int ILS, int HLS, int OLS, int m>
void Predict(double X[m][ILS - 1], double params[ILS * (HLS - 1) + HLS * OLS], double prediction[m][OLS]) {
	//"Unrolling" Theta1 and Theta2 from 'params'
	double Theta1[ILS][HLS - 1];
	double Theta2[HLS][OLS];
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS - 1; j++)
		{
			Theta1[i][j] = params[i * (HLS - 1) + j];
		}
	}

	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			Theta2[i][j] = params[(HLS - 1) * ILS + i * OLS + j];
		}
	}

	//std::cout << "Theta2:" << endl;
	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			//std::cout << Theta2[i][j] << " ";
		}
		//std::cout << endl;
	}

	//std::cout << "Theta1:" << endl;
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS - 1; j++)
		{
			//std::cout << Theta1[i][j] << " ";
		}
		//std::cout << endl;
	}
	//The matrix of 1 values
	double ONE[m][1] = { 0 };
	matrices::ones<m, 1>(ONE);

	//adding bias neuron
	double xNew[m][ILS] = { 0 };
	matrices::conquatinate<double, 1, ILS - 1, m>(ONE, X, xNew);

	//Computing unactivated values for the Hidden layer
	double A[m][HLS - 1] = { 0 };
	matrices::multiply<double, m, HLS - 1, ILS>(xNew, Theta1, A);

	//activation of Hidden layer values
	double H1[m][HLS - 1] = { 0 };
	Sigmoid::sigmoid<m, HLS - 1>(A, H1);

	//Same for Theta2
	double ONE_1[m][1] = { 0 };
	matrices::ones<m, 1>(ONE_1);

	double xNew_1[m][HLS] = { 0 };
	matrices::conquatinate<double, 1, HLS - 1, m>(ONE_1, H1, xNew_1);

	double A1[m][OLS] = { 0 };
	matrices::multiply<double, m, OLS, HLS>(xNew_1, Theta2, A1);

	Sigmoid::sigmoid<m, OLS>(A1, prediction);

	/*double min = 1;
	double max = 0;

	for (int i = 0; i < m; i++)
	{
		if (prediction[i][0] > max) {
			max = prediction[i][0];
		}
		if (prediction[i][0] < min) {
			min = prediction[i][0];
		}

	}

	for (int i = 0; i < m; i++)
	{
		prediction[i][0] -= (max + min) / 2.0f;
		prediction[i][0] *= 1.0f / (max - min);
		prediction[i][0] += 0.5f;
	}*/
}

#endif
