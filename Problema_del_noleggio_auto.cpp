#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

const int NUM_NOLEGGIATORI = 5;

bool possiedeChiavi[NUM_NOLEGGIATORI];

int schermoMenu();
int leggiInteroLimitato(int min, int max, string messaggio);
void inizializzaBooleanArrayFalse(bool booleanArray[NUM_NOLEGGIATORI]);

int main() {
    int scelta = schermoMenu();
    if (scelta == 1) {
        int numeroChiavi = NUM_NOLEGGIATORI;
        inizializzaBooleanArrayFalse(possiedeChiavi);
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