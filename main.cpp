#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>

using namespace std;

/** Usado para abrir o arquivo e pegar as linhas **/
vector<string> readFileToVector(const string filename, int &lenght)
{
    ifstream source;
    source.open(filename);
    vector<string> lines;
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
            lines.push_back(line);
        }
    }
    return lines;
}

void forca_bruta(const vector<string> v, string &ponto, int lenght)
{
    cout << lenght << endl;
    for (long long i(1); i <= lenght; ++i)
    {
        ponto = to_string(lenght);
    }
}

void divisao_e_conquista(const vector<string> v, string &ponto, int lenght)
{
    cout << lenght << endl;
    for (long long i(1); i <= lenght; ++i)
    {
        ponto = to_string(lenght);
    }
}

int main(int argc, char **argv)
{
    if (argv[1])
    {
        clock_t begin, end;
        begin = clock();

        string ponto1, ponto2;
        string fn = argv[1]; //filename
        int lenght = 0;
        vector<string> lines = readFileToVector(fn, lenght);
        if (lenght > 0)
        {
            forca_bruta(lines, ponto1, lenght);
            divisao_e_conquista(lines, ponto2, lenght);
            end = clock();
            double time_taken = double(end - begin) / double(CLOCKS_PER_SEC);

            cout << "\n\n\n\n\n";
            cout << "Pontos - " << ponto1 << ", " << ponto2 << ", " << fixed
                 << time_taken << setprecision(5);
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