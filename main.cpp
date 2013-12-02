#include <iostream>
#include <cstdio>
/*
Programm zum Umrechnen von Dualzahlen
nach Dezimalzahlen
*/

using namespace std;

const string text = "Ein Konsoleprogramm zum Umrechnen von Dualzahlen nach Dezimalzahlen.\n\n"
"Die Eingabe erfolgt Byte - weise.\n"
"Als Duale Werte sind die Ziffern 0 und 1 erlaubt.\n"
"Pro Byte koennen nicht mehr als 8 bit eingegeben werden.\nAndernfalls erscheint eine Fehlermeldung oder es\n"
"werden die zuerst eingegebenen Bits geloescht.";

//! wieviel bit unterstützt das System
unsigned int berechneStellen();

//! Buffer für die Dualzahl mit nullen initialisieren
void initBuffer(unsigned int dualzahl[],unsigned int laenge);

//! Eingabe der Dualzahl
bool eingabeBits(unsigned int dualzahl[],int count);

//! Anzeige der Eingabe
void printEingabe(unsigned int dualzahl[],unsigned int laenge);

unsigned long berechneErgebniss(unsigned int dualzahl[],unsigned int laenge,int basis = 2);

void printErgebnis(unsigned long dezi);


int main()
{
    unsigned int laenge = berechneStellen();
    unsigned int dualzahl[laenge];
    bool nocheinmal = false, mehrBits = false, eingabeOk;
    cout << text << endl << endl;

    do{//! Noch ein Programmdurchlauf?
        unsigned int bitcount = 0;
        initBuffer(dualzahl,laenge);
        do{//! eingabe OK
            //eingabeOk = true;
            do{//! mehr Bits
                mehrBits = 0;
                eingabeOk = eingabeBits(dualzahl,bitcount);
                if(eingabeOk){
                    printEingabe(dualzahl,laenge);
                    bitcount++;
                    if(bitcount < laenge/8){
                        cout << "moechten Sie ein " << bitcount+1 << ".tes Byte eingeben (Ja = 1)" << endl;
                        cin >> mehrBits;
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(BUFSIZ, '\n');
                            mehrBits = 0;
                        }
                    }
                }
                else{
                    cout << "Eingabefehler!" << endl;
                }
            }while(mehrBits ==1);

        }while(!eingabeOk);
        printErgebnis(berechneErgebniss(dualzahl,laenge));
        cout << "moechten sie noch eine Berechung durchfuehren? (Ja = 1)" << endl;
        cin >> nocheinmal;
        if(cin.fail()){
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            nocheinmal = 0;
        }
    }while(nocheinmal == 1);
}


unsigned int berechneStellen()
{
    unsigned int stellen =  sizeof(unsigned long)*8;
    return  stellen;
}


void initBuffer(unsigned int dualzahl[],unsigned int laenge){
    for (unsigned int i=0;i<laenge;i++){
        dualzahl[i] = 0;
    }
}


//#define NEUE_EINGABE
#ifndef NEUE_EINGABE
bool eingabeBits(unsigned int dualzahl[],int count){
    unsigned long letzte =0;
    bool eingabeOk = true;
    unsigned long zahl =0;
    do{
        cout << "Geben  Sie das "<< count+1 << ".te Byte ein: (niederwertigstes Bit zuerst)" << endl;
        cin >> zahl;

        if(zahl > 11111111 || cin.fail() ){
            eingabeOk = false;
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            return false;
        }
        else{
            eingabeOk = true;
        }
    }while(!eingabeOk);
    //cout << "zahl: " << zahl << endl;
    int i=0;
    do{
        letzte = zahl%10;
        if(letzte < 0 || letzte > 1){
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            for(int y = 0;y<i;i++){
                dualzahl[y+count*8] = 0;
            }
            return false;
        }
        else{
            zahl /=10;
            //cout << "  durchlauf: " << i <<endl;
            dualzahl[i+count*8] = letzte;
        }
        i++;
        }while(i<8);
    return eingabeOk;
}
#else
bool eingabeBits(unsigned int dualzahl[],int count){

        unsigned int byte[8];
        unsigned long zahl =0;
        unsigned int bit = 0;
        for (int i=0;i<8;i++){
            cout << "geben sie Bit "<< i+count*8 <<" ein:" << endl;
            bool nochmal = false;
            do{
                cin >> bit;
                if(bit == 1 || bit == 0){
                    byte[i] = bit;
                    nochmal = false;
                }
                else{
                    cout << "\nFalsche Eingabe. Ein Bit kann nur den Wert 0 oder 1 annehmen!\nEingabe Wiederholen:" << endl;
                    cin.clear();
                    cin.ignore(BUFSIZ, '\n');
                    nochmal = true;
                }
            }while(nochmal);
        }
        /*
        for(unsigned int i= 0;i<8;i++){
            unsigned int z = 8 - i;
            unsigned long dezistelle = 1;
            while(z<8){
                dezistelle *= 10;
                z++;
            }
            zahl += dezistelle*byte[i];
        }
        */
        zahl = berechneErgebniss(byte,8,10);
        //cout << "zahl: " << zahl << endl;
        int i=0;
        unsigned long letzte =0;
        do{
            letzte = zahl%10;
            //cout << "zahl: " << zahl << " letzte: " << letzte;
            zahl = zahl/10;
            //cout << "  durchlauf: " << i <<endl;
            dualzahl[i+count*8] = letzte;
            i++;
        }while(i<8);
        return true;
}
#endif




void printEingabe(unsigned int dualzahl[],unsigned int laenge){
    cout << endl <<"Ihre Eingabe: " << endl;
    for (int i=laenge-1;i>=0;i--){
        cout << dualzahl[i];
        if (i % 4 == 0) cout << " ";
        if (i % 8 == 0) cout << "  ";
        if (i % 16 == 0) cout << "\n";
    }
    cout << endl;
}

unsigned long berechneErgebniss(unsigned int dualzahl[],
                                unsigned int laenge,
                                int basis){

    unsigned long ergebnis = 0;
    //unsigned int n = laenge-1;
    for(unsigned int i= 0;i<laenge;i++){
            unsigned int z = laenge - i;
            unsigned long dezistelle = 1;
            while(z<laenge){
                dezistelle *= basis;
                z++;
            }
        ergebnis += dezistelle*dualzahl[i];
    }
    return ergebnis;
}

void printErgebnis(unsigned long dezi){
    cout << endl<< "Die Dezimalzahl lautet: " << dezi << endl << endl;
}
