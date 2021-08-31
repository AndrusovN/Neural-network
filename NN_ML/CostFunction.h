#include "matrix.h"
#include "sigmoid.h"
#include <iostream>
#ifndef COST_FUNCTION
#define COST_FUNCTION


//A cost function and a gradient computing for it
//ILS - is Input Layer Size
//HLS - is Hidden Layer Size
//OLS - is Output Layer Size
//X - data for learning
//y - answers for data
//params - parameters for learning (also weights)
//lambda - regularization coefficient
//J - the variable to write cost function value
//grad - the variable to write partial gradient for this parameters
template <int ILS, int HLS, int OLS, int m>
void CostFunction(double X[m][ILS-1], double y[m][OLS], double params[ILS * (HLS-1) + HLS * OLS], double lambda, double * J, double grad[ILS * HLS + HLS * OLS]) {
	
	//"Unrolling" Theta1 and Theta2 from 'params'
	double Theta1[ILS][HLS-1];
	double Theta2[HLS][OLS];
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS-1; j++)
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
	//std::cout << "Theta1_01 " << params[0] << " " << params[1];
	/*std::cout << "Theta2:" << endl;
	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			std::cout << Theta2[i][j] << " ";
		}
		std::cout << endl;
	}
	
	std::cout << "Theta1:" << endl;
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS-1; j++)
		{
			std::cout << Theta1[i][j] << " ";
		}
		std::cout << endl;
	}*/
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

	double H2[m][OLS] = { 0 };
	
	Sigmoid::sigmoid<m, OLS>(A1, H2);


	//Counting J(Theta) - cost function
	*J = 0;
	for (int i = 0; i < OLS; i++)
	{
		for (int j = 0; j < m; j++)
		{
			*J -= (1.0f / m) * ((y[j][i] * log(H2[j][i])) + ((1 - y[j][i]) * log(1 - H2[j][i])));
			//std::cout << (1.0 / m) * ((y[j][i] * log(H2[j][i])) + ((1 - y[j][i]) * log(1.0 - H2[j][i]))) << endl;
		}
	}
	//std::cout << "J " << *J << endl;
	//Implementing regularization
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS-1; j++)
		{
			*J += Theta1[i][j] * Theta1[i][j] * (lambda / (2.0f * m));
			//std::cout << Theta1[i][j] * (lambda / (2 * m)) << " ";
		}
	}
	//std::cout << endl << "J' " << *J << endl;
	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			*J += Theta2[i][j] * Theta2[i][j] * (lambda / (2 * m));
		}
	}
	//std::cout << "J'' " << *J << endl;
	//Computing partial gradient 
	double Theta1Grad[ILS][HLS-1] = { 0 };
	double Theta2Grad[HLS][OLS] = { 0 };

	//Setting to zero
	for (int i = 0; i < ILS; i++)
	{
		for (int j = 0; j < HLS-1; j++)
		{
			Theta1Grad[i][j] = 0;
		}
	}

	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			Theta2Grad[i][j] = 0;
		}
	}

	//main computations
	for (int i = 0; i < m; i++)
	{
		//delta3 - delta of Output layer
		double delta3[OLS][1] = { 0 };
		for (int j = 0; j < OLS; j++)
		{
			delta3[j][0] = H2[i][j] - y[i][j];
		}

		//Computing delta2 - delta of Hidden layer
		//The formula in Octave is:
			// (Theta2' * delta3')(2:hidden_layer_size+1, :) .* sigmoidGradient(z2(i, :))';
		//Try to understand this
		double Theta2XDelta3[HLS][1] = { 0 };
		matrices::multiply<double, HLS, 1, OLS>(Theta2, delta3, Theta2XDelta3);
		double gradCutted[HLS - 1][1] = { 0 };
		for (int j = 1; j < HLS; j++)
		{
			gradCutted[j-1][0] = Theta2XDelta3[j][0];
		}
		//Now count the gradient
		double A_new[1][HLS - 1] = { 0 };
		//I tried this: A_new[0] = A[i];, but it does'n work, so... 
		for (int j = 0; j < HLS-1; j++)
		{
			A_new[0][j] = A[i][j];
		}

		//Multiply with sigmoid derivative
		Sigmoid::sigmoidDerivative<1, HLS - 1>(A_new, A_new);
		double A_new_h[HLS - 1][1] = { 0 };
		matrices::transpose<double, 1, HLS - 1>(A_new, A_new_h);

		double resGrad[HLS - 1][1] = { 0 };
		matrices::multEach<double, HLS - 1, 1>(gradCutted, A_new_h, resGrad);

		//Multiply with X to find the partial derivative
		double X_chosen[1][ILS-1] = { 0 };
		for (int j = 0; j < ILS-1; j++)
		{
			X_chosen[0][j] = X[i][j];
		}
		double X_added[1][ILS] = { 0 };

		double _one[1][1] = { {1} };
		matrices::conquatinate<double, 1, ILS - 1, 1>(_one, X_chosen, X_added);

		double GRAD_Th1[HLS-1][ILS] = { 0 };
		matrices::multiply<double, HLS-1, ILS, 1>(resGrad, X_added, GRAD_Th1);

		//Transpose the matrix to sum with Theta1_Gradient
		double Grad_Th1_T[ILS][HLS-1] = { 0 };
		matrices::transpose<double, HLS-1, ILS>(GRAD_Th1, Grad_Th1_T);
		matrices::numberMult<double, double, double, ILS, HLS-1>(Grad_Th1_T, -1.0f / (double)m, Grad_Th1_T);
		
		matrices::sum<double, ILS, HLS-1>(Theta1Grad, Grad_Th1_T, Theta1Grad);
		
		//The same for delta3
		double H_chosen[1][HLS - 1] = { 0 };
		for (int j = 0; j < HLS - 1; j++)
		{
			H_chosen[0][j] = H1[i][j];
		}
		double H_added[1][HLS] = { 0 };

		matrices::conquatinate<double, 1, HLS - 1, 1>(_one, H_chosen, H_added);

		double GRAD_Th2[OLS][HLS] = { 0 };
		matrices::multiply<double, OLS, HLS, 1>(delta3, H_added, GRAD_Th2);

		double Grad_Th2_T[HLS][OLS] = { 0 };
		matrices::transpose<double, OLS, HLS>(GRAD_Th2, Grad_Th2_T);

		matrices::numberMult<double, double, double, HLS, OLS>(Grad_Th2_T, -1.0f / (double)m, Grad_Th2_T);

		matrices::sum<double, HLS, OLS>(Theta2Grad, Grad_Th2_T, Theta2Grad);
	}

	//There also should be regularization implemetnation, but I'm too lazy...

	double _grad[OLS * HLS + (HLS - 1) * ILS][1] = { 0 };

	//Now "Roll" Theta1Grad and Theta2Grad to 'grad' variable
	for (int i = 0; i < ILS; i++)
	{
		
		for (int j = 0; j < HLS-1; j++)
		{
			//cout << i * (HLS - 1) + j << endl;
			_grad[i * (HLS-1) + j][0] = Theta1Grad[i][j];
		}
	}
	//cout << "Grad : ";
	for (int i = 0; i < HLS; i++)
	{
		for (int j = 0; j < OLS; j++)
		{
			//cout << i * OLS + j + (ILS* (HLS - 1)) << endl;
			_grad[i * OLS + j + (ILS * (HLS-1))][0] = Theta2Grad[i][j];
			//cout << _grad[i * OLS + j + (ILS * (HLS-1))][0] << " ";
		}

	}

	double _regularization_grad[OLS * HLS + (HLS - 1) * ILS][1];
	double _params[OLS * HLS + (HLS - 1) * ILS][1] = { 0 };
	for (int i = 0; i < OLS * HLS + (HLS - 1) * ILS; i++)
	{
		_params[i][0] = params[i];
	}
	matrices::numberMult<double, double, double, OLS* HLS + (HLS - 1)* ILS, 1>(_params, lambda / m, _regularization_grad);

	matrices::sum<double, OLS* HLS + (HLS - 1)* ILS, 1>(_grad, _regularization_grad, _grad);

	for (int i = 0; i < OLS * HLS + (HLS - 1) * ILS; i++)
	{
		grad[i] = _grad[i][0];
	}


	//cout << endl;
}
#endif