#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

class List
{
private:
    int* list = nullptr;
    int length = 0;
    static void afisareIntern(int* arr, int length)
    {
        cout << endl;
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << endl;
        }
    }
    static void merge(int* arr, int start, int medium, int end)
    {
        int n1 = medium - start + 1;
        int n2 = end - medium;

        long int* leftArr = new long int[n1];
        long int* rightArr = new long int[n2];

        for (int i = 0; i < n1; i++)
        {
            leftArr[i] = arr[start + i];
        };
        for (int j = 0; j < n2; j++)
        {
            rightArr[j] = arr[medium + 1 + j];
        };

        int i = 0;
        int j = 0;
        int k = start;

        while (i < n1 && j < n2)
        {
            if (leftArr[i] <= rightArr[j])
            {
                arr[k] = leftArr[i];
                i++;
            }
            else
            {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr[k] = rightArr[j];
            j++;
            k++;
        }

        delete[] leftArr;
        delete[] rightArr;

    }
    static void mergeImp(int* arr, int start, int end)
    {
        if (start < end)
        {
            int medium = start + (end - start) / 2;
            mergeImp(arr, start, medium);
            mergeImp(arr, medium + 1, end);

            merge(arr, start, medium, end);

        }
    }
    static int partial(int* arr, int start, int end)
    {
        int pivot = arr[end];

        int i = start;

        for (int j = start; j < end; j++)
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
        arr[i] = arr[end];
        arr[end] = c;

        return i;
    }
    static void quick(int* arr, int start, int end)
    {
        if (start < end)
        {
            int part = partial(arr, start, end);

            quick(arr, start, part - 1);
            quick(arr, part + 1, end);
        }
    }
    static int partialRand(int* arr, int start, int end)
    {

        if (start - end != 0) {
            int random = start + rand() % (end - start);
            int c = arr[random];
            arr[random] = arr[end];
            arr[end] = c;
        }
        
        return partial(arr,start,end);
    }
    static void quickRand(int* arr, int start, int end)
    {
        if (start < end)
        {
            int part = partialRand(arr, start, end);
            quickRand(arr, start, part - 1);
            quickRand(arr, part + 1, end);
        }
    }
    static void shell(int* arr, int start, int end)
    {
        int n = end - start+1;
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
    int* copy()
    {
        int* list1 = new int[length];
        for (int i = 0; i < length; i++)
        {
            list1[i] = list[i];
        }
        return list1;
    }
    void time(void(*function)(int*, int, int), int* arr,int length, string sortType)
    {
        auto start = chrono::high_resolution_clock::now();
        function(arr, 0, length-1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Durata " << sortType << " : " << duration.count() << " microsecunde" << endl;
    }
    void genRand(int * arr, int length, int range)
    {

        for (int i = 0; i < length; i++)
        {
            int sign = 1;
            if (rand() % 3 == 0)
            {
                sign = -1;
            }
            arr[i] = (rand() % range) * sign;
        }
    }
    void genDescending(int* arr, int length, int range)
    {
        float max = range;
        float step = (rand()%10);
        for (int i = 0; i < length; i++)
        {
            arr[i] = max;
            max -= step;
        }
    }
    void genAscending(int* arr, int length, int range)
    {
        int sign = 1;
        if (rand() % 2 == 0)
        {
            sign = -1;
        }
        float min = 1 * (rand() % 25)*sign;
        float step = ( rand() % 10);
        for (int i = 0; i < length; i++)
        {
            arr[i] = min;
            min += step;
        }
    }
    void genAlmostAscending(int* arr, int length, int range)
    {
        int sign = 1;
        if (rand() % 2 == 0)
        {
            sign = -1;
        }
        float min = 1 * (rand() % 25) * sign;
        float step =(rand() % 10);
        for (int i = 0; i < length; i++)
        {
            arr[i] = min;
            min += step;
        }
        int randN1 = rand() % (length/2-1);
        int randN2 = rand() % (length / 2 - 1);
        int c = arr[length / 2 + randN1];
        arr[length / 2 + randN1] = arr[length / 2 - randN2];
        arr[length / 2 - randN2] = c;
    }
public:
    List(int length, int range,int mode)
    {
        this->length = length;
        list = new int[length];
        switch (mode)
        {
        case 0:
            {
            genRand(list,length,range);
            }
            break;
        case 1:
        {
            genDescending(list, length, range);
        }
        break;
        case 2:
        {
            genAscending(list, length, range);
        }
        break;
        case 3:
        {
            genAlmostAscending(list, length, range);
        }
        break;
        default:
            break;
        }
        
    }
    void afisare()
    {
        cout << endl;
        for (int i = 0; i < length; i++)
        {
            cout << list[i] << endl;
        }
    }
    void sortareMerge()
    {
        int* list1 = copy();
        time(&mergeImp, list1, length, "Merge Sort");

        afisareIntern(list1, length);

        delete[] list1;

    }
    void sortareQuick()
    {
        int* list1 = copy();
        time(&quick, list1, length, "Quick Sort");

        afisareIntern(list1, length);
        
        delete[] list1;
    }
    void sortareRandQuick()
    {
        int* list1 = copy();
        time(&quickRand, list1, length, "Random Quick Sort");

        afisareIntern(list1, length);

        delete[] list1;
    }
    void sortareShell()
    {
        int* list1 = copy();
        time(&shell, list1, length, "Shell Sort");

        afisareIntern(list1, length);

        delete[] list1;
    }
};

int main()
{
    srand(time(0));
    cout << endl << "Give how many random numbers you woud like: ";
    int n=10;
    cin >> n;
    cout << endl << "Give the biggest number you woud like: ";
    int range=20;
    cin >> range;
    cout << endl << "Give mode of generation (0-random; 1-descending; 2-ascending; 3-almost ascending): ";
    int mode=0;
    cin >> mode;
    List* lista = new List(n,range,mode);
    cout << endl << "N= " << n<<" range = "<<range << endl;
    lista->afisare();
    lista->sortareMerge();
    lista->sortareQuick();
    lista->sortareRandQuick();
    lista->sortareShell();
}
