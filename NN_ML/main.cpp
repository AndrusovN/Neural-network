#include "matrix.h"
#include "readCSV.h"
#include "CostFunction.h"
#include "GradientDescent.h"
#include "prediction.h"
#include "threshold.h"
#include "Evaluation.h"
#include <iostream>
#include <chrono>
#include "ImageOpener.h"

using namespace chrono;
using namespace std;


int main() {
	
	chrono::high_resolution_clock timer;
	auto start = timer.now();
	const int inputLayerSize = 400;
	const int outputLayerSize = 52;
	const int hiddenLayerSize = 50;
	const int hiddenLayerCount = 1;
	const int M = 2288;
	double A[M][inputLayerSize+outputLayerSize];
	readCSV::read<M, inputLayerSize+outputLayerSize>((char *)"D:\\Dropbox_old\\никита\\Программы (1)\\c++\\NN_ML\\Data.csv", A);
	
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < inputLayerSize+outputLayerSize; j++)
		{
			//cout << A[i][j] << " ";
		}
		//cout << endl;
	}
	double y[M][outputLayerSize] = { 0.94f, 0.25f, 0.64f, 0.1f, 0.33f, 0.476f };
	double X[M][inputLayerSize] = { 0 };

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < inputLayerSize; j++)
		{
			X[i][j] = A[i][j];
		}

		for (int j = 0; j < outputLayerSize; j++)
		{
			y[i][j] = A[i][j + inputLayerSize];
		}
	}

	double grad[(inputLayerSize + 1) * hiddenLayerSize + (hiddenLayerSize + 1) * outputLayerSize] = { 0 };
	double J = 0;
	double params[(inputLayerSize + 1) * hiddenLayerSize + (hiddenLayerSize + 1) * outputLayerSize][1] = { 0 };
	//cout << endl;
	for (int i = 0; i < (inputLayerSize + 1) * hiddenLayerSize + (hiddenLayerSize + 1) * outputLayerSize; i++)
	{
		double f = rand();
		double s = rand();
		if (f > s) {
			params[i][0] = s / f;
		}
		else
		{
			params[i][0] = f / s;
		}
	}
	//cout << endl;
	
	double lambda = -0.1f;
	double alpha = -0.5f;
	double _alpha = -0.002f;
	Optimize<inputLayerSize + 1, hiddenLayerSize + 1, outputLayerSize, M>(X, y, params, lambda, alpha, _alpha, 100);

	double pred[M][outputLayerSize];
	int q = 0;
	Predict<inputLayerSize + 1, hiddenLayerSize + 1, outputLayerSize, M>(X, params[0], pred);
	
	double treshold[outputLayerSize] = { 0 };
	auto f = timer.now();

	cout << "Time : " << (double)duration_cast<duration<double>>(f - start).count() * 1000 << " milliseconds" << endl;
	for (int i = 0; i < outputLayerSize; i++)
	{
		double current_prediction[M][1] = { 0 };
		double current_y[M][1] = { 0 };
		for (int j = 0; j < M; j++)
		{
			current_prediction[j][0] = pred[j][i];
			current_y[j][0] = y[j][i];
		}
		findThreshold<M>(current_prediction, current_y, &(treshold[i]));

	}
	int quality = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < outputLayerSize; j++)
		{
			//cout << pred[i][j] << " // " << y[i][j] << "; ";
			if ((round(y[i][j]) == 1) && ((pred[i][j] > treshold[j]))) {
				quality++;
			}
			if ((int)(pred[i][j] > treshold[j]) == round(y[i][j])) {
				q++;
			}
		}
		//cout << endl;
	}
	cout << endl << "Training accuracy : " << (double)q / ((double)M * outputLayerSize) * 100 << "%" << endl;
	cout << endl << "Training quality : " << (double)quality / ((double)M) * 100 << "%" << endl;
	const int mT = 100;
	double AT[mT][inputLayerSize + outputLayerSize];
	readCSV::read<mT, inputLayerSize + outputLayerSize>((char*)"D:\\Dropbox_old\\никита\\Программы (1)\\c++\\NN_ML\\Data.csv", AT);

	for (int i = 0; i < mT; i++)
	{
		for (int j = 0; j < inputLayerSize + outputLayerSize; j++)
		{
			//cout << AT[i][j] << " ";
		}
		//cout << endl;
	}
	double yT[mT][outputLayerSize] = { 0.94f, 0.25f, 0.64f, 0.1f, 0.33f, 0.476f };
	double XT[mT][inputLayerSize] = { 0 };

	for (int i = 0; i < mT; i++)
	{
		for (int j = 0; j < inputLayerSize; j++)
		{
			XT[i][j] = AT[i][j];
		}

		for (int j = 0; j < outputLayerSize; j++)
		{
			yT[i][j] = AT[i][j + inputLayerSize];
		}
	}

	int qT = 0;
	int qualityT = 0;
	Predict<inputLayerSize + 1, hiddenLayerSize + 1, outputLayerSize, mT>(XT, params[0], pred);
	for (int i = 0; i < mT; i++)
	{
		for (int j = 0; j < outputLayerSize; j++)
		{
			if ((round(yT[i][j]) == 1) && ((pred[i][j] > treshold[j]))) {
				qualityT++;
			}
			//cout << pred[i][j] << " // "  << (int)(pred[i][j] > treshold) << " // " << yT[i][j] << "; ";
			if ((int)(pred[i][j] > treshold[j]) == round(yT[i][j])) {
				qT++;
			}
		}
		//cout << endl;
	}
	cout << endl;
	for (int i = 0; i < (inputLayerSize + 1) * hiddenLayerSize + (hiddenLayerSize + 1) * outputLayerSize; i++)
	{
		//cout << params[i][0] << " \\ ";
	}
	cout << endl;
	cout << "Test accuracy : " << (double)qT / ((double)mT * outputLayerSize) * 100 << "%" << endl;
	cout << endl << "Test quality : " << (double)qualityT / ((double)mT) * 100 << "%" << endl;
	cout << "Treshold : " << endl;
	for (int i = 0; i < outputLayerSize; i++)
	{
		cout << "[" << i << "] - " << treshold[i] << endl;
	}
	auto finish = timer.now();

	cout << "Time : " << (double)duration_cast<duration<double>>(finish - start).count() * 1000 << " milliseconds" << endl;
	double precision = 0;
	double recall = 0;
	EvaluationMatrix<mT, inputLayerSize+1, outputLayerSize>(XT, yT, pred, treshold, &precision, &recall);
	cout << "Precision : " << precision << endl << "Recall : " << recall << endl;
	int n;
	std::cin >> n;
}