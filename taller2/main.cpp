#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void extraer(char[], char[], char[]);
void agregarcantidad(char[], char[]);

int main() {
    char linea1[120];   //una linea de trx_taller.csv
    char barcode[25];   //codigo
    char quantity[25];  //cantidad 

    //se abre trx_taller.csv 
    ifstream fe("trx_taller.csv"); 
    

    //creamos archivo de salida
    ofstream fs("resultado.csv");
    char primeralinea[120]="'barcode';'name';'volume';'quantity'";
    fs << primeralinea <<endl;

    char linea2[120];

    char aux[120];
    fe.getline(aux, 120);

    //abrimos products_taller.csv
    ifstream fi("products_taller.csv");
    

    //recorremos trx_taller.csv
    while(!fe.eof()) 
    {   
        //extrae una linea de .csv 
        fe.getline(linea1, 120);
        extraer(linea1, barcode, quantity);
        //abrimos products_taller.csv
        ifstream fi("products_taller.csv");
        while(!fi.eof())
        {
            fi.getline(linea2,120);
            if(strstr(linea2, barcode) != NULL)
            {   
                agregarcantidad(linea2, quantity);
                fs << linea2 << endl;
                break;
            }
        }
        fi.close();
    }
   
    //cerramos ficheros
    fe.close();
    fs.close();

   return 0;
}

//extrae codigo y cantidad de linea
void extraer(char linea[], char barcode[], char quantity[])
{
    int i, q=0, p=0;
    char aux[25];
    char aux2[25];
    for(i=0; i<strlen(linea); i++)
    {
        if(linea[i]==';')q=q+1;
        if(q==0)
        {
            aux[i]=linea[i];
        }
        if(q==1)
        {
            aux2[p]=linea[i];
            p++;
        }
    }
    int c=0;
    for(i=1; i<strlen(aux);i++)
    {
        if(aux[i]=='"')c++;
        if(c<1)
        {
            barcode[i-1]=aux[i];
        }
    }

    for(i=0; i<4; i++)
    {
        quantity[i]=aux2[i];
    }
}

//agrega cantidad al final de linea
void agregarcantidad(char linea[], char cantidad[])
{
    strcat(linea, cantidad);
}

