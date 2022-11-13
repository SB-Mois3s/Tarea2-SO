#include<pthread.h>
#include<stdio.h>
#include<iostream>
#include<fstream>

using namespace std;
pthread_mutex_t mutex;

//Función que le el contenido del txt y obtiene la cantidad de lineas equivalentes al número de IPs.
void leer_archivo();

//Función que a través de un parámetro dado, muestra los ms de esa dirección ip.
void obtener_ping(string ip);

//variable global, cantidad de lineas equivalentes al número de IPs.
int nlineas=-1;

//Función de prueba
void * funcion(void * arg) {
    for (int i = 0; i < nlineas; i++) {
        pthread_mutex_lock(&mutex);
        cout <<i+1<<endl;
        pthread_mutex_unlock(&mutex);
    }
}

//Función main
int main(int argc, char const *argv[]){
leer_archivo();
pthread_t hilo[nlineas];

ifstream archivo;
string texto;
string *A;
archivo.open("ips.txt",ios::in);
A = new string[nlineas];//Se guarda una copia de la dirección de memoria de un arreglo.

//Se crean n hilos equivalentes a la cantidad de IPs en un archivo txt
for(int i=0; i<nlineas && !archivo.eof(); i++){
    pthread_create(&hilo[i], NULL, &funcion, NULL);
    cout<<"Hilo numero: "<<i+1<<endl;
    getline(archivo,texto);
    A[i]=texto;
    pthread_join(hilo[i], NULL);
}
archivo.close();

for(int i=0; i<nlineas; i++){
    cout<<endl<<"valor de: A["<<i<<"]: "<<A[i]<<endl;
    obtener_ping(A[i]);
}

cout<<"Numero de lineas del archivo: "<<nlineas<<endl;
return 0;
}

void leer_archivo(){
    ifstream archivo;
    string texto;

    archivo.open("ips.txt",ios::in);
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo ";
        exit(1);
    }
    while(!archivo.eof()){
        getline(archivo,texto);
        cout<<texto<<endl;
        nlineas++;
    }
    archivo.close();//Se cierra el archivo

}

void obtener_ping(string ip) {
    string comando="ping " + ip + " -q -c2";
    string nombre_txt = ip;
    cout<<" "<<endl;
    system(comando.c_str());
}