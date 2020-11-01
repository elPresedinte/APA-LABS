#include <iostream>
#include<chrono>

using namespace std;
using namespace std::chrono;

void Afisare(unsigned int* arr, unsigned int n)
{
	cout << endl<<1;
	for (unsigned int i = 0; i < n; i++)
	{
		cout << " " << arr[i];
	}
}

void PrimeIter(unsigned int n, unsigned int* arr, unsigned int& pos)
{

	for (unsigned int i = 2; i < n+1; i++)
	{
		bool isP = true;
		for (unsigned int j = 2; j < i-1; j++)
		{
			if (i%j==0)
			{
				isP = false;
				break;
			};
		}
		if (isP)
		{
			arr[pos] = i;
			pos++;
		}
	}
}

void PrimeBetter(unsigned int n, unsigned int* arr, unsigned int& pos)
{
	if (n < 3) {
		for (unsigned int i = 0; i < n-1; i++)
		{
			arr[i] = i + 2;
			pos++;
		}

	}
	else
	{
		for (unsigned int i = 0; i < 2; i++)
		{
			arr[i] = i + 2;
			pos++;
		}
		for (unsigned int i = 4; i < n + 1; i++)
		{
			bool isT = true;
			for (unsigned int j = 0; j < pos && arr[j] <= sqrt(i); j++)
			{
				if (i % arr[j] == 0)
				{
					isT = false;
					break;
				};
			}
			if (isT)
			{
				arr[pos] = i;
				pos++;
			}
		}
	};
}

void Ciorul(unsigned int nMAX, unsigned int & cantPrimCior,bool * toateNr,unsigned int* nrPrimeCior)
{
	for (int i = 0; i < nMAX; i++)
	{
		toateNr[i] = false;
	}
	toateNr[0] = toateNr[1] = true;
	for (int j = 4; j <= nMAX; j += 2)
	{
		toateNr[j] = true;
	};
	for (int i = 3; i * i <= nMAX; i += 2)
	{
		if (!toateNr[i])
		{
			for (int j = i * i; j <= nMAX; j += 2 * i)
			{
				toateNr[j] = true;
			};
		};
	};
	nrPrimeCior[0] = 2;
	cantPrimCior = 1;
	for (int i = 1; i <= nMAX; i += 2)
	{
		if (!toateNr[i])
		{
			nrPrimeCior[cantPrimCior] = i;
			cantPrimCior++;
		};
	};
}

int main()
{
	unsigned int nMAX;
	cin >> nMAX;

	unsigned int cantPrimIt = 0;
	unsigned int* nr_PrimeIt = new unsigned int[nMAX];

	auto start = high_resolution_clock::now();
	PrimeIter(nMAX, nr_PrimeIt, cantPrimIt);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Timp utilizat Iter " << duration.count() << " microseconds" << endl;

	unsigned int cantPrim = 0;
	unsigned int* nr_Prime = new unsigned int[nMAX];
	
	start = high_resolution_clock::now();
	PrimeBetter(nMAX, nr_Prime, cantPrim);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Timp utilizat Better "<< duration.count() << " microseconds" << endl;

	
	
	bool* toateNr = new bool[nMAX+1];
	unsigned int* nrPrimeCior = new unsigned int[nMAX+1];
	unsigned int cantPrimCior = 0;

	start = high_resolution_clock::now();
	Ciorul(nMAX+1, cantPrimCior,toateNr, nrPrimeCior);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Timp utilizat Cior " << duration.count() << " microseconds" << endl;

	
	Afisare(nr_PrimeIt, cantPrimIt);
	Afisare(nr_Prime, cantPrim);
	Afisare(nrPrimeCior, cantPrimCior);

	return 0;
}