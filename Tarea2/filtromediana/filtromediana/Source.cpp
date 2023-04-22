#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/* Función para ordenar un arreglo usando ordenamiento por inserción*/
void ordenamiento(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int arreglo[2000][2000];
int arr[2000][2000];

int main()
{
    int ventana[9], fila = 0, colum = 0, numrows = 0, numcols = 0, MAX = 0;
    ifstream infile("pruebaRuido.pgm");
    stringstream ss;
    string inputLine = "";

    getline(infile, inputLine);
    if (inputLine.compare("P2") != 0) cerr << "Error no es un archivo PGM Version 2 correcto" << endl;
    else cout << "Si es un archivo PGM Version 2 correcto" << inputLine << endl;

    ss << infile.rdbuf();
    ss >> numcols >> numrows >> MAX;

    /*cout << numcols << " columns and " << numrows << " rows" << endl << "Maximum Intensity "<< MAX <<endl;*/

    //Inicializar un nuevo arreglo del mismo tamaño de imagen con 0
    for (fila = 0; fila <= numrows; ++fila)
        arreglo[fila][0] = 0;
    for (colum = 0; colum <= numcols; ++colum)
        arreglo[0][colum] = 0;

    for (fila = 1; fila <= numrows; ++fila)
    {
        for (colum = 1; colum <= numcols; ++colum)
        {
            ss >> arreglo[fila][colum];
        }
    }

    // Se imprime el arreglo
    for (fila = 1; fila <= numrows; ++fila)
    {
        for (colum = 1; colum <= numcols; ++colum)
        {
            ventana[0] = arreglo[fila - 1][colum - 1];
            ventana[1] = arreglo[fila - 1][colum];
            ventana[2] = arreglo[fila - 1][colum + 1];
            ventana[3] = arreglo[fila][colum - 1];
            ventana[4] = arreglo[fila][colum];
            ventana[5] = arreglo[fila][colum + 1];
            ventana[6] = arreglo[fila + 1][colum - 1];
            ventana[7] = arreglo[fila + 1][colum];
            ventana[8] = arreglo[fila + 1][colum + 1];

            ordenamiento(ventana, 9);
            arr[fila][colum] = ventana[4];
        }
    }

    ofstream outfile;

    //generamos nueva imagen de salida
    outfile.open("pruebafiltrada.pgm");
    outfile << "P2" << endl;
    outfile << numcols << " " << numrows << endl;
    outfile << "255" << endl;

    for (fila = 1; fila <= numrows; ++fila)
    {
        for (colum = 1; colum <= numcols; ++colum)
        {
            //guardamos los pixeles resultantes
            outfile << arr[fila][colum] << " ";
        }
    }

    outfile.close();
    infile.close();
    return 0;
}