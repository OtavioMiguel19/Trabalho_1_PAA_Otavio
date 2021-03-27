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
vector<Ponto> readFileToVector(const string filename, long long &lenght)
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

MaisProximo forca_bruta(const vector<Ponto> pontos, long long n)
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

    combina(A, i, m, t);
}
// ----------------------------------------------------------------------
// FIM MERGE SORT
// ----------------------------------------------------------------------

MaisProximo menorDistancia(MaisProximo mp1, MaisProximo mp2)
{
    if (mp1.distancia < mp2.distancia)
    {
        return mp1;
    }
    return mp2;
}

vector<Ponto> getVecInRange(vector<Ponto> original, float start, float finish)
{
    vector<Ponto> saida;
    for (long long i = 0; i < original.size(); i++)
    {
        float xPoint = stringToFloat(original[i].x);
        if (xPoint >= start && xPoint < finish)
        {
            saida.push_back(original[i]);
        }
    }
    return saida;
}
vector<Ponto> getVecInRange2(vector<Ponto> original, float start, float finish)
{
    vector<Ponto> saida;
    for (long long i = start; i < finish; i++)
    {
        saida.push_back(original[i]);
    }
    return saida;
}

MaisProximo divisao_e_conquista_recursivo(vector<Ponto> v, long n)
{
    MaisProximo proximo = MaisProximo();
    proximo.distancia = 10000000000000;

    if (n <= 3)
    {
        return forca_bruta(v, n);
    }
    else
    {

        long mid = n / 2;

        vector<Ponto> dlVec = getVecInRange2(v, 0, mid);

        MaisProximo dl = divisao_e_conquista_recursivo(dlVec, dlVec.size());

        proximo = menorDistancia(dl, proximo);

        vector<Ponto> drVec = getVecInRange2(v, mid, n);
        MaisProximo dr = divisao_e_conquista_recursivo(drVec, drVec.size());
        proximo = menorDistancia(dr, proximo);

        vector<Ponto> r3Vec;
        Ponto p_central = v[mid-1];

        for (long long index = 0; index < n; index++)
        {
            float absolute = abs(stringToFloat(v[index].x) - stringToFloat(p_central.x));
            if (absolute <= proximo.distancia && absolute > 0)
            {
                r3Vec.push_back(v[index]);
            }
        }

        MaisProximo r3 = divisao_e_conquista_recursivo(r3Vec, r3Vec.size());
        proximo = menorDistancia(r3, proximo);
        return proximo;
    }
}

MaisProximo divisao_e_conquista_declaracao(vector<Ponto> &v, long long n)
{
    // ------------------------------------
    clock_t begin, end;
    begin = clock();
    // ------------------------------------
    mergeSort(v, 0, n - 1);

    MaisProximo maisProximo = divisao_e_conquista_recursivo(v, n);
    // ------------------------------------
    end = clock();
    float time_taken = float(end - begin) / float(CLOCKS_PER_SEC);
    maisProximo.tempo = time_taken;
    // ------------------------------------
    return maisProximo;
}

int main(int argc, char **argv)
{
    if (argv[1])
    {
        string fn = argv[1]; //filename
        long long lenght = 0;
        vector<Ponto> lines = readFileToVector(fn, lenght);
        if (lenght > 0)
        {
            // cout << "distancia - " << fixed << calculaDistancia(lines[0], lines[1]) << setprecision(5) << endl;
            MaisProximo ponto_forca_bruta = forca_bruta(lines, lenght);

            vector<Ponto> pontos = lines;
            MaisProximo ponto_divisao_e_conquista = divisao_e_conquista_declaracao(pontos, lenght);

            cout << "\n\n\n\n\n";
            cout << fixed << ponto_forca_bruta.tempo << setprecision(5) << " " << ponto_forca_bruta.distancia;
            cout << " " << ponto_forca_bruta.a.x << " " << ponto_forca_bruta.a.y;
            cout << " " << ponto_forca_bruta.b.x << " " << ponto_forca_bruta.b.y;

            cout << " ------ ";

            cout << " " << fixed << ponto_divisao_e_conquista.tempo << setprecision(5) << " " << ponto_divisao_e_conquista.distancia;
            cout << " " << ponto_divisao_e_conquista.a.x << " " << ponto_divisao_e_conquista.a.y;
            cout << " " << ponto_divisao_e_conquista.b.x << " " << ponto_divisao_e_conquista.b.y;
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
