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

MaisProximo forca_bruta(const vector<Ponto> pontos, int lenght)
{
    // ------------------------------------
    clock_t begin, end;
    begin = clock();
    // ------------------------------------
    MaisProximo maisProximo = MaisProximo();
    maisProximo.distancia = 10000000000000;
    for (long long i(0); i < lenght - 1; ++i)
    {
        for (long long j(i + 1); j < lenght; j++)
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

void divisao_e_conquista(const vector<Ponto> v, string &ponto, int lenght)
{
    for (long long i(0); i < lenght; ++i)
    {
        Ponto p = v[i];
        cout << "x " << p.x << " || "
             << "y " << p.y << endl;
        ponto = to_string(lenght);
    }
}

int main(int argc, char **argv)
{
    if (argv[1])
    {
        clock_t begin, end;
        begin = clock();

        string fn = argv[1]; //filename
        int lenght = 0;
        vector<Ponto> lines = readFileToVector(fn, lenght);
        if (lenght > 0)
        {
            // cout << "distancia - " << fixed << calculaDistancia(lines[0], lines[1]) << setprecision(5) << endl;
            MaisProximo ponto_forca_bruta = forca_bruta(lines, lenght);
            // divisao_e_conquista(lines, ponto2, lenght);

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