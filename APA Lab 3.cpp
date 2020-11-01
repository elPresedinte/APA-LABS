#include <iostream>
#include <time.h>
#include <chrono>


using namespace std;

class List
{
private:
    long int* lista = nullptr;
    int marime = 0;
    void afisareIntern( int * arr,int marime)
    {
        cout << endl;
        for (int i = 0; i < marime; i++)
        {
            cout << arr[i] << endl;
        }
    }
    void merge( int * arr,int s,int m,int d)
    {
        int n1 = m - s + 1;
        int n2 = d - m;

        long int* S = new long int[n1];
        long int* D = new long int[n2];

        for (int i = 0; i < n1; i++) 
        {
            S[i] = arr[s + i];
        };
        for (int j = 0; j < n2; j++)
        {
            D[j] = arr[m + 1 + j];
        };

        int i = 0;
        int j = 0;
        int k = s;

        while(i < n1&& j < n2)
        {
            if (S[i] <= D[j])
            {
                arr[k] = S[i];
                i++;
            }
            else
            {
                arr[k] = D[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = S[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = D[j];
            j++;
            k++;
        }

        delete[] S;
        delete[] D;

    }
    void mergeImp( int * arr,int s, int d)
    {
        
        if (s < d)
        {
            int m = s + (d - s) / 2;
            mergeImp(arr,s,m);
            mergeImp(arr,m+1,d);

            merge(arr,s,m,d);

        }
    }
    int partial(int* arr, int s, int d)
    {
        int pivot = arr[d];

        int i = s;

        for (int j = s; j < d; j++)
        {
            if (arr[j] < pivot)
            {
                int c = arr[i];
                arr[i] = arr[j];
                arr[j] = c;
                i++;
            };
        }
        int c = arr[i];
        arr[i] = arr[d];
        arr[d] = c;

        return i;
    }
    void quick(int* arr, int s, int d)
    {
        if (s < d)
        {
            int part = partial(arr, s, d);

            quick(arr, s, part - 1);
            quick(arr, part + 1, d);
        }
    }
    void shell(int * arr, int n)
    {
        for (int gap = n / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                {
                    arr[j] = arr[j - gap];
                   
                };
                arr[j] = temp;
            }
        }
    }
public:
    List(int marime)
    {
        this->marime = marime;
        lista = new long int[marime];
        for (int i = 0; i < marime; i++)
        {
            int sign = 1;
            if (rand() % 3 == 0)
            {
                sign = -1;
            }
            lista[i] = (rand() % 100000) * sign;
        }
    }
    void afisare()
    {
        cout << endl;
        for (int i = 0; i < marime; i++)
        {
            cout  << lista[i] << endl;
        }
    }
    void sortareMerge()
    {
        int* lista1 = new int[marime];
        for (int i = 0; i < marime; i++)
        {
            lista1[i] =lista[i];
        }
        auto start = chrono::high_resolution_clock::now();
        mergeImp(lista1,0,marime-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Durata MergeSort: " << duration.count() << " microsecunde" << endl;

        //mergeImp(lista1, 0, marime - 1);
        //cout << endl << "Rezultatele pentru Merge Sort: ";
        //afisareIntern(lista1, marime);

        delete[] lista1;

    }
    void sortareQuick()
    {
        int* lista1 = new int[marime];
        for (int i = 0; i < marime; i++)
        {
            lista1[i] = lista[i];
        }
        auto start = chrono::high_resolution_clock::now();
        quick(lista1,0,marime-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Durata QuickSort: "<<duration.count() <<" microsecunde"<< endl;

        //quick(lista1, 0, marime - 1);
        //cout << endl << "Rezultatele pentru Quick Sort: ";
        //afisareIntern(lista1, marime);

        delete[] lista1;
    }
    void sortareShell()
    {
        int* lista1 = new int[marime];
        for (int i = 0; i < marime; i++)
        {
            lista1[i] = lista[i];
        }
        auto start = chrono::high_resolution_clock::now();
        shell(lista1,marime);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Durata ShellSort: " << duration.count() << " microsecunde" << endl;
        
        //shell(lista1, marime);
        //cout << endl << "Rezultatele pentru Shell Sort: ";
        //afisareIntern(lista1, marime);

        delete[] lista1;
    }
};

int main()
{
    srand(time(0));
    int n;
    cin >> n;
    List* lista = new List(n);
    cout << endl << "N= " << n<<endl;
    //lista->afisare();
    lista->sortareMerge();
    lista->sortareQuick();
    lista->sortareShell();
}