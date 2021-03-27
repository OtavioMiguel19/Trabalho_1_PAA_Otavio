#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <math.h>

using namespace std;

class Ponto
{
public:
    string x, y;
};
class MaisProximo
{
public:
    Ponto a, b;
    float distancia;
    float tempo;
};

/** Usado para abrir o arquivo e pegar as linhas **/
vector<Ponto> readFileToVector(const string filename, int &lenght)
{
    ifstream source;
    source.open(filename);
    vector<Ponto> pontos;
    string line;
    bool isFirstLine = true;
    while (getline(source, line))
    {
        if (isFirstLine)
        {
            lenght = stoi(line);
            isFirstLine = false;
        }
        else
        {
            string divider = " ";
            string x = line.substr(0, line.find(divider));
            string y = line.substr(line.find(divider) + 1, line.length());
            Ponto ponto = Ponto();
            ponto.x = x;
            ponto.y = y;
            pontos.push_back(ponto);
        }
    }
    return pontos;
}

float stringToFloat(string s)
{
    return stof(s);
}

float calculaDistancia(Ponto a, Ponto b)
{
    float d1 = (stringToFloat(a.x) - stringToFloat(b.x));
    float d2 = (stringToFloat(a.y) - stringToFloat(b.y));
    return sqrt((d1 * d1) + (d2 * d2));
}

MaisProximo forca_bruta(const vector<Ponto> pontos, int n)
{
    // ------------------------------------
    clock_t begin, end;
    begin = clock();
    // ------------------------------------
    MaisProximo maisProximo = MaisProximo(); // O(1)
    maisProximo.distancia = 10000000000000;  // O(1)
    for (long long i(0); i < n - 1; ++i)     // O(n)
    {
        for (long long j(i + 1); j < n; j++) // O(n^2)
        {
            Ponto a = pontos[i];
            Ponto b = pontos[j];
            float distancia = calculaDistancia(a, b);
            if (distancia < maisProximo.distancia)
            {
                maisProximo.a = a;
                maisProximo.b = b;
                maisProximo.distancia = distancia;
            }
        }
    }
    // ------------------------------------
    end = clock();
    float time_taken = float(end - begin) / float(CLOCKS_PER_SEC);
    maisProximo.tempo = time_taken;
    // ------------------------------------
    return maisProximo;
}

// ----------------------------------------------------------------------
// MERGE SORT
// ----------------------------------------------------------------------
void combina(vector<Ponto> &A, long long i, long long m, long long t)
{
    vector<Ponto> B, C;
    for (long k = i; k <= m; k++)
    {
        B.push_back(A[k]);
    }
    for (long k = m + 1; k <= t; k++)
    {
        C.push_back(A[k]);
    }
    // cout << "B0 " << B[0].x << endl;
    // cout << "C0 " << C[0].x << endl;

    long sizeB = B.size(), sizeC = C.size();

    long j1 = 0, j2 = 0;
    for (long k = i; k <= t; k++)
    {
        if (j1 < sizeB && ((j2 + i) >= t || j2 >= sizeC || ((j1 + i) <= m && stringToFloat(B[j1].x) <= stringToFloat(C[j2].x))))
        {
            A[k] = B[j1];
            j1++;
        }
        else
        {
            A[k] = C[j2];
            j2++;
        }
    }
}

void mergeSort(vector<Ponto> &A, long long i, long long t)
{
    if (i == t)
    {
        return;
    }
    long m = long((i + t) / 2);
    mergeSort(A, i, m);
    mergeSort(A, m + 1, t);

    // cout << "i " << i << endl;
    // cout << "m " << m << endl;
    // cout << "t " << t << endl;

    combina(A, i, m, t);
}
// ----------------------------------------------------------------------
// FIM MERGE SORT
// ----------------------------------------------------------------------

void divisao_e_conquista_declaracao(vector<Ponto> &v, int n)
{
    mergeSort(v, 0, n - 1);

    // cout << "TERMINOU" << endl;

    // cout << "Menor no x = " << v[0].x << " " << v[0].y << endl;
    // cout << "Maior no x = " << v[v.size() - 1].x << " " << v[v.size() - 1].y << endl;

    divisao_e_conquista_recursivo(v, n, 1);
}

void divisao_e_conquista_recursivo(vector<Ponto> v, int n, int partes)
{
    Ponto beg = v[0];
    Ponto end = v[n - 1];
    float ampl = float(stringToFloat(beg.x) - stringToFloat(end.x));
    MaisProximo proximo = MaisProximo();
    proximo.distancia = 10000000000000;

    for (int i = 0; i < partes; i++) {
        
    }
}

int main(int argc, char **argv)
{
    if (argv[1])
    {
        string fn = argv[1]; //filename
        int lenght = 0;
        vector<Ponto> lines = readFileToVector(fn, lenght);
        if (lenght > 0)
        {
            // cout << "distancia - " << fixed << calculaDistancia(lines[0], lines[1]) << setprecision(5) << endl;
            MaisProximo ponto_forca_bruta = forca_bruta(lines, lenght);

            vector<Ponto> pontos = lines;
            divisao_e_conquista_declaracao(pontos, lenght);

            cout << "\n\n\n\n\n";
            cout << fixed << ponto_forca_bruta.tempo << setprecision(5) << " " << ponto_forca_bruta.distancia;
            cout << " " << ponto_forca_bruta.a.x << " " << ponto_forca_bruta.a.y;
            cout << " " << ponto_forca_bruta.b.x << " " << ponto_forca_bruta.b.y;
            cout << "\n\n\n\n\n";
        }
        else
        {
            cout << "Nenhum ponto informado. Abortando.";
        }
    }
    else
    {
        cout << "Nenhum arquivo informado. Abortando.";
    }
}