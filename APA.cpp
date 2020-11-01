#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int repetari = 0;;

int Fib(int n)
{
	repetari++;
	if (n < 2)
		return n;
	else
	{
		int m = Fib(n - 1) + Fib(n - 2);
		return m;
	}
}

double Phi()
{
	return (sqrtf(5) + 1.0f) / 2.0f;
}

int Fib1(int n)
{
	int m = (pow(Phi(), n) - pow((-1 * Phi()), -1 * n)) / sqrtf(5);
	return m;
}

int Fib2(int k)
{
	int j = 0; int n = 1;
	for (int i = 1; i <= k; i++)
	{
		n = n + j;
		j = n - j;
	};
	return j;
}

int repetari1 = 0;

int Fib3(int n)
{
	int i = 1; int j = 0; int k = 0; int h = 1;
	while (n > 0)
	{
		repetari1++;
		if (n % 2 != 0)
		{
			repetari1++;
			int t = j * h;
			j = i * h + j * k + t;
			i = i * k + t;
		};
		int t = pow(h, 2);
		h = 2 * k * h + t;
		k = pow(k, 2) + t;
		n = n / 2;
	};
	return j;
}



int main()
{
	int n;
	cout << endl << "INtroduceti n: " << endl;
	cin >> n;
	cout << endl;

	auto start1 = high_resolution_clock::now();
	cout << endl;
	cout << endl << "Raspunsul e " << Fib(n);
	cout << endl << "Nr de iteratii este: " << repetari << endl;
	auto stop1 = high_resolution_clock::now();
	auto duration1 = duration_cast<microseconds>(stop1 - start1);
	cout << "Durata Fib(recursia) este: " << duration1.count() << " microseconds" << endl;

	auto start = high_resolution_clock::now();
	cout << endl << "Raspunsul e " << Fib1(n);
	cout << endl << "Nr de iteratii este: " << 1 << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Durata Fib1(formula lui Binet) este: " << duration.count() << " microseconds" << endl;


	start = high_resolution_clock::now();
	cout << endl << "Raspunsul e " << Fib2(n);
	cout << endl << "Nr de iteratii este: " << n << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Durata Fib2(for) este: " << duration.count() << " microseconds" << endl;

	start = high_resolution_clock::now();
	cout << endl << "Raspunsul e " << Fib3(n);
	cout << endl << "Nr de iteratii este: " << repetari1 << endl;
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Durata Fib3(imparitm la 2) este: " << duration.count() << " microseconds" << endl;
	return 0;
}
