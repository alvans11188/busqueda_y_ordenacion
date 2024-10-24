#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

void ordenarDirecto(int[],int);
void ordenacionLogaritmica(int[],int);
int nuevosDatos(int[]);
void copia(int[],int[],int);

int main(){
    int n=0,op;
    const int MAX_SIZE=1000000;  
    
    int*a=new int[MAX_SIZE];
    int*b=new int[MAX_SIZE];
    double duracion;
    srand(static_cast<unsigned int>(time(0)));

    do{
        cout<<"Ingrese cuantos datos desea (max "<<MAX_SIZE<<"): ";
        cin>>n;
        if(n<1||n>MAX_SIZE){
            cout<<"Por favor, ingrese un número entre 1 y "<<MAX_SIZE<<": ";
        }
    }while(n<1||n>MAX_SIZE);

    for(int i=0;i<n;i++){
        a[i]=rand()%10000+1;
    }

    do{
        system("cls");
        cout<<"=== COMPARACION DE METODOS DE ORDENACION ===\n\n";
        cout<<"1. Metodo Directo\n";
        cout<<"2. Metodo Logaritmico (Shell Sort)\n";
        cout<<"3. Elija la cantidad de datos\n";
        cout<<"4. SALIR\n\n";
        cout<<"Escoja el metodo de ordenacion: ";
        cin>>op;

        switch(op){
            case 1:
                copia(a,b,n);
                {
                    clock_t inicio=clock();
                    ordenarDirecto(b,n);
                    clock_t fin=clock();
                    duracion=double(fin-inicio)/CLOCKS_PER_SEC;
                    cout<<"La funcion tardo "<<duracion<<" segundos en ejecutarse.\n";
                }
                break;
            case 2:
                copia(a,b,n);
                {
                    clock_t i=clock();
                    ordenacionLogaritmica(b,n);
                    clock_t f=clock();
                    duracion=double(f-i)/CLOCKS_PER_SEC;
                    cout<<"La funcion tardo "<<duracion<<" segundos en ejecutarse.\n";
                }
                break;
            case 3:
                n=nuevosDatos(a);
                break;
            case 4:
                cout<<"Saliendo del programa...\n";
                break;
            default:
                cout<<"Elija una opcion valida\n";
                break;
        }
        system("pause");
    }while(op!=4);

    return 0;
}

void ordenarDirecto(int a[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(a[j]>a[j+1]){
            	int aux=a[j+1];
            	a[j+1]=a[j];
            	a[j]=aux;
            }
        }
    }
}

void ordenacionLogaritmica(int a[],int n){
    int k,i,cen;
    k=n;
    while(k>0){
        k=k/2;
        cen=1;
        while(cen==1){
            cen=0;
            i=0;
            while(i+k<n){
                if(a[i+k]<a[i]){
                    int aux=a[i+k];
                    a[i+k]=a[i];
                    a[i]=aux;
                    cen=1;
                }
                i++;
            }
        }
    }   
}

int nuevosDatos(int a[]){
    int m;
    cout<<"Ingrese cuantos datos desea: ";
    cin>>m;
    while(m<1||m>1000000){
        cout<<"Por favor, ingrese un número entre 1 y 1000000: ";
        cin>>m;
    }
    for(int i=0;i<m;i++){
        a[i]=rand()%100000+1;
    }
    return m;
}

void copia(int source[],int dest[],int n){
    for(int i=0;i<n;i++){
		dest[i]=source[i];
    }
}
