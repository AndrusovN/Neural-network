#include <fstream>
#include <iostream>
using namespace std;

#ifndef READCSV
#define READCVS

namespace readCSV {

	template <int xDim, int yDim>
	void read(char* path, double source[xDim][yDim]) {
		ifstream file;

		file.open(path, ios_base::in);

		for (int i = 0; i < xDim; i++)
		{
			string buffer;
			file >> buffer;
			int start = -1;
			int idx = 0;
			for (int j = 0; j < buffer.length(); j++)
			{
				if (buffer.c_str()[j] == ';') {
					string buf = "";
					for (int k = start + 1; k < j; k++)
					{
						buf += buffer[k];
					}
					start = j;
					source[i][idx] = atof(buf.c_str());
					idx++;
				}
			}
		}
		file.close();
	}

}
#endif
