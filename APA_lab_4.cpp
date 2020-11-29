#include <iostream>
#include <utility>
#include<time.h>
#include <chrono> 

using namespace std;


class Kruskal
{
private:
    int** graph;
    int length;
    pair<int, int> min(int** graph, int v)
    {
        pair<int, int> p;
        int min = 100;
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (min > graph[i][j] && graph[i][j] > 0)
                {
                    min = graph[i][j];
                    p.first = i;
                    p.second = j;
                }
            }
        }
        return p;
    }
    bool cycle(int** graph, int n, int v, int* ocupied)
    {
        bool cucle=false;
        ocupied[n]++;
        if (ocupied[n] > 1)
        {
            cucle = true;
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                if (i != v && graph[n][i] > 0)
                {
                    bool isT = cycle(graph, i, n, ocupied);
                    if (isT)
                    {
                        cucle = true;
                        break;
                        
                    }
                }
            };
        }
        return cucle;
    }
    bool startCycle(int** graph, int n)
    {
        bool isT;
        int* ocupied = new int[length];
        for (int i = 0; i < length; i++)
        {
            ocupied[i] = 0;
        }
        isT = cycle(graph, n, n, ocupied);
        delete[] ocupied;
        ocupied = nullptr;
        return isT;
    }
public:
    Kruskal(int **g, int v)
    {
        graph = new int* [v];
        for (int i = 0; i < v; i++)
        {
            graph[i] = new int[v];
        }
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                graph[i][j] = g[i][j];
            }
        }
        length = v;
    };
    static void afisare(int** g, int v)
    {
        cout << endl;
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                cout << " " << g[i][j];
            }
            cout << endl;
        }
    }
    void Acoperire()
    {
        int** graphSchimb = new int* [length];
        for (int i = 0; i < length; i++)
        {
            graphSchimb[i] = new int[length];
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                graphSchimb[i][j] = graph[i][j];
            }
        }

        int **graphNou = new int* [length];
        for (int i = 0; i < length; i++)
        {
            graphNou[i] = new int[length];
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                graphNou[i][j] = 0;
            }
        }

        int* ocupied = new int[length];
        for (int i = 0; i < length; i++)
        {
            ocupied[i] = 0;
        }

        int numberArcs = 0;

        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                if (graphSchimb[i][j] > 0)
                {
                    numberArcs++;
                }
            }
        }
        cout << endl <<"Numarul de arce pina: "<< numberArcs;

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < numberArcs; i++)
        {
            pair<int, int> p = min(graphSchimb, length);
            graphNou[p.first][p.second] = graphSchimb[p.first][p.second];
            graphNou[p.second][p.first] = graphSchimb[p.second][p.first];
            graphSchimb[p.first][p.second] = 0;
            graphSchimb[p.second][p.first] = 0;
            if (ocupied[p.first]>0 && ocupied[p.second]>0 && startCycle(graphNou,p.first))
            {
                graphNou[p.first][p.second] = 0;
                graphNou[p.second][p.first] = 0;
               
            }
            ocupied[p.first]++;
            ocupied[p.second]++;
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout <<endl<<"Durata metodei Kruskal este: "<< duration.count()<<" millisecunde" << endl;

        numberArcs = 0;
        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                if (graphNou[i][j] > 0)
                {
                    numberArcs++;
                }
            }
        }
        cout << endl << "Numarul de arce dupa: " << numberArcs;
        int lungime = 0;
        for (int i = 1; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                lungime += graphNou[i][j];
            }            
        }
        cout << endl << "Cost: " << lungime;
        Kruskal::afisare(graphNou, length);
        for (int i = 0; i < length; i++)
        {
            delete[] graphNou[i];
            delete[] graphSchimb[i];
        }
        delete[] graphNou;
        delete[] graphSchimb;

        graphNou = nullptr;
        graphSchimb = nullptr;
    }
};
class Prim
{
private:
    int** graph;
    int length;
    pair<int, int> min(int** graph, int v, int * acoperit)
    {
        pair<int, int> p;
        int min = 100;
        for (int i = 0; i < v; i++)
        {
            if (acoperit[i] > 0)
            {
                for (int j = 0; j < v; j++)
                {
                    if (acoperit[j]==0 && min > graph[i][j] && graph[i][j] > 0)
                    {
                        min = graph[i][j];
                        p.first = i;
                        p.second = j;
                    }
                }
            }
        }
        return p;
    }
public:
    Prim(int** g, int v)
    {
        graph = new int* [v];
        for (int i = 0; i < v; i++)
        {
            graph[i] = new int[v];
        }
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                graph[i][j] = g[i][j];
            }
        }
        length = v;
    };
    void Acoperire()
    {
        int** graphSchimb = new int* [length];
        for (int i = 0; i < length; i++)
        {
            graphSchimb[i] = new int[length];
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                graphSchimb[i][j] = graph[i][j];
            }
        }

        int** graphNou = new int* [length];
        for (int i = 0; i < length; i++)
        {
            graphNou[i] = new int[length];
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                graphNou[i][j] = 0;
            }
        }

        int* ocupied = new int[length];
        for (int i = 0; i < length; i++)
        {
            ocupied[i] = 0;
        }

        int numberArcs = 0;

        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                if (graphSchimb[i][j] > 0)
                {
                    numberArcs++;
                }
            }
        }
        ocupied[0]++;
        cout << endl << "Numarul de arce pina: " << numberArcs;

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < length; i++)
        {
            pair<int, int> p = min(graphSchimb, length,ocupied);
            graphNou[p.first][p.second] = graphSchimb[p.first][p.second];
            graphNou[p.second][p.first] = graphSchimb[p.second][p.first];
            graphSchimb[p.first][p.second] = 0;
            graphSchimb[p.second][p.first] = 0;
            if (ocupied[p.first] > 0 && ocupied[p.second] > 0)
            {
                graphNou[p.first][p.second] = 0;
                graphNou[p.second][p.first] = 0;

            }
            ocupied[p.first]++;
            ocupied[p.second]++;
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout <<endl<< "Durata metodei Prim este: " << duration.count() << " millisecunde" << endl;

        numberArcs = 0;
        for (int i = 0; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                if (graphNou[i][j] > 0)
                {
                    numberArcs++;
                }
            }
        }
        cout << endl << "Numarul de arce dupa: " << numberArcs;
        int lungime = 0;
        for (int i = 1; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                lungime += graphNou[i][j];
            }        
        }
        cout << endl << "Cost: " << lungime;
        Kruskal::afisare(graphNou, length);
        for (int i = 0; i < length; i++)
        {
            delete[] graphNou[i];
            delete[] graphSchimb[i];
        }
        delete[] graphNou;
        delete[] graphSchimb;


        graphNou = nullptr;
        graphSchimb = nullptr;

    }
};

int ** generateMatrix(int V)
{
    int** graphP = new int* [V];
    for (int i = 0; i < V; i++)
    {
        graphP[i] = new int[V];
    }
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graphP[i][j] = 0;
        }
    }

    srand(time(0));
    for (int i = 0; i < V - 1; i++)
    {
        graphP[i][i + 1] = rand() % 20 + 1;
        graphP[i + 1][i] = graphP[i][i + 1];
    }

    cout << "Dati numarul de arce aditionare> ";
    int nr_arce;
    cin >> nr_arce;

    while (nr_arce > 0)
    {
        int i = rand() % V;
        int j = rand() % V;

        if (i != j && abs(i - j) != 1 && graphP[i][j] == 0)
        {
            graphP[i][j] = rand() % 20 + 1;
            graphP[j][i] = graphP[i][j];
            nr_arce--;
        }
    }
    return graphP;
}

int main()
{
    int V;
    cout << endl << "Dati numarul de virfuri:";
    cin >> V;
    int** graphP=generateMatrix(V);
    Kruskal::afisare(graphP, V);
    Kruskal krusk(graphP,V);
    krusk.Acoperire();
    Prim prim(graphP,V);
    prim.Acoperire();
    return 0;
}
