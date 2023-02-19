#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int NUM_NOLEGGIATORI = 5;

int pos;
bool possiedeChiavi[NUM_NOLEGGIATORI];
pthread_t noleggiatori[NUM_NOLEGGIATORI];

int schermoMenu();
int leggiInteroLimitato(int min, int max, string messaggio);
void inizializzaBooleanArrayFalse(bool booleanArray[NUM_NOLEGGIATORI]);
void creaThread(pthread_t noleggiatori[NUM_NOLEGGIATORI], int* numeroChiavi);
void stampaStatoNoleggiatore(int pos, string messaggio);
void* prendiChiave(void* numeroChiavi);
void wait(int& s);
void signal(int& s);

int main() {
    int scelta = schermoMenu();
    if (scelta == 1) {
        int numeroChiavi = NUM_NOLEGGIATORI;
        inizializzaBooleanArrayFalse(possiedeChiavi);
        while (true) {
            creaThread(noleggiatori, &numeroChiavi);
        }
    }
    return 0;
}

int schermoMenu() {
    system("clear");
    cout << " ________________________________________________________________________________________________________________ " << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|                                                   BENVENUTO                                                    |" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|    Quest'applicazione gestisce il problema del noleggio di auto.                                               |" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|    Si hanno:                                                                                                   |" << endl;
    cout << "|    - Cinque noleggiatori;                                                                                      |" << endl;
    cout << "|    - Cinque chiavi.                                                                                            |" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|    Cinque persone dovendo fare un viaggio, noleggiano un auto rivolgendosi ad una società di noleggio;         |" << endl;
    cout << "|    Si suppone che il viaggio sia diviso in fasi alterne guidare/riposare;                                      |" << endl;
    cout << "|    Ogni persona deve guidare per un po' e poi andare a riposare sul sedile posteriore,                         |" << endl;
    cout << "|    lasciando guidare la persona seduta alla sua destra.                                                        |" << endl;
    cout << "|    Inoltre, ognuno deve prendere una chiave alla volta, e per guidare, il noleggiatore,                        |" << endl;
    cout << "|    deve utilizzare due chiavi, una per mettere in moto l’automobile,                                           |" << endl;
    cout << "|    l’altra per disattivare il sistema d’antifurto.                                                             |" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|________________________________________________________________________________________________________________|" << endl;
    cout << " ________________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|                                                      MENU                                                      |" << endl;
    cout << "|                                                                                                                |" << endl;
    cout << "|    1. Avvia applicazione                                                                                       |" << endl;
    cout << "|    0. Esci                                                                                                     |" << endl;
    cout << "|________________________________________________________________________________________________________________|" << endl << endl;
    int scelta = leggiInteroLimitato(0, 1, "Inserire scelta: ");
    return scelta;
}

int leggiInteroLimitato(int min, int max, string messaggio) {
    int num;
    cout << messaggio;
    cin >> num;
    cout << endl;
    while ((num < min) || (num > max)) {
        cout << "ERRORE: Il numero inserito deve essere compreso tra: " << min << " e " << max << endl;
        cout << messaggio;
        cin >> num;
        cout << endl;
    }
    return num;
}

void inizializzaBooleanArrayFalse(bool booleanArray[NUM_NOLEGGIATORI]) {
    for (int i = 0; i < NUM_NOLEGGIATORI; i++) {
        possiedeChiavi[i] = false;
    }
}

void creaThread(pthread_t noleggiatori[NUM_NOLEGGIATORI], int* numeroChiavi) {
    for(pos = 0; pos < NUM_NOLEGGIATORI; pos++){
        sleep(1);
        int thread = pthread_create(&noleggiatori[pos], NULL, prendiChiave, (void*)numeroChiavi);
        pthread_join(noleggiatori[pos], 0);
    }
}

void stampaStatoNoleggiatore(int pos, string messaggio) {
    cout << endl << "Il noleggiatore n." << pos + 1 << " " << messaggio << endl;
}

void* prendiChiave(void* numeroChiavi) {
    int n = NUM_NOLEGGIATORI / 2;
    pthread_join((long unsigned int)noleggiatori[pos], 0);
    if ((*(int*)numeroChiavi >= n) && (possiedeChiavi[pos] == false)) {
        wait(*(int*)numeroChiavi);
        possiedeChiavi[pos] = true;
        stampaStatoNoleggiatore(pos, "HA PRESO LA CHIAVE");
        cout << "Numero chiavi: " << *(int*)numeroChiavi << endl;
        pthread_join(noleggiatori[pos],0);
        pthread_exit(0);
    } else if ((*(int*)numeroChiavi < n) && (possiedeChiavi[pos] == true)) {
        stampaStatoNoleggiatore(pos, "STA GUIDANDO");
        possiedeChiavi[pos] = false;
        signal(*(int*)numeroChiavi);
        cout << "Numero chiavi: " << *(int*)numeroChiavi << endl;
        pthread_exit(0);
    } else if ((*(int*)numeroChiavi < n) && (possiedeChiavi[pos] == false)) {
        stampaStatoNoleggiatore(pos, "STA RIPOSANDO");
        pthread_exit(0);
    }
    pthread_exit(0);
}

void wait(int& s) {
    while (s < 0) {
        pthread_exit(0);
    }
    s--;
}

void signal(int& s) {
    s++;
}
