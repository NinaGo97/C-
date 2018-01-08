#include <iostream>

using namespace std;
#include <fstream>
#include "string.h"
#include <string>

int main()
{
    char zeichen;
    char puffer [100]; //Zwischenspeicher
    int zaehler;
    char id[4];
    string ausgabename;

    enum zustand {start, iderwarte, idverarbeite,idend,einsetzen};
    enum zustand zustand = start;

    fstream eingabetxt; // txt Datei

    char zeichentxt;
    char puffertxt [100]; //Zwischenspeicher
    int zaehlertxt;
    char idtxt[50][4];  //ID's der Txt Datei werden hier reingeschrieben     char x [Anzahl der Zeilen][Max Zeilenlänge]
    int idzaehlertxt = 0;
    int birthzaehlertxt=0;

    char daytxt[50][4];
    char monthtxt[50][4];
    char yeartxt[50][8];

    bool hotfix = false; // für > klammer nach persname

    enum zustandtxt {erwarteidtxt, erwartetagtxt, erwartemonattxt, erwartejahrtxt};
    enum zustandtxt zustandtxt = erwarteidtxt;
    char aktion; //Eingabe ob suchen oder konvertieren


    //Einlesen txt
    eingabetxt.open("nameList2.txt");

    //Kontrolle ob einlesen funktionert
    if(!eingabetxt) cout << "errortxt" << endl;
    else cout << "jaaaaatxt"<< endl;
    cout<< "Wollen Sie suchen[s] oder konvertieren[k]?"<< endl;
    cin >> aktion;

    if (aktion=='k'){

    cout << "Wie soll die neue Datei heissen? Bitte mit .xml am Schluss" << endl;
    cin >> ausgabename;


    //txt Datei unterscheidet zwischen ID und Geb
     for(eingabetxt.get(zeichentxt);!eingabetxt.eof();eingabetxt.get(zeichentxt)) {
         switch (zeichentxt) {

         case ' ': //ID
            puffertxt[zaehlertxt]='\0';
            zaehlertxt= 0;
            strcpy(idtxt[idzaehlertxt],puffertxt);
            idzaehlertxt ++;
            zustandtxt = erwartetagtxt;

            break;

         case '\n': //Jahr
             puffertxt[zaehlertxt]='\0';
             zaehlertxt=0;
             strcpy(yeartxt[birthzaehlertxt],puffertxt);
             birthzaehlertxt++;
             zustandtxt = erwarteidtxt;

             break;

         case '.': //Monat und Tag
             puffertxt[zaehlertxt]='\0';
             zaehlertxt=0;

             if (zustandtxt==erwartetagtxt){
                 strcpy(daytxt[birthzaehlertxt],puffertxt);
                 zustandtxt=erwartemonattxt;

             }else if(zustandtxt==erwartemonattxt){
                 strcpy(monthtxt[birthzaehlertxt],puffertxt);
                 zustandtxt = erwartejahrtxt;
             }

             break;

         default:
             puffertxt[zaehlertxt]=zeichentxt;
             zaehlertxt++;
             break;
         }

     }

    eingabetxt.close();


    fstream eingabe; // xml Datei

    //Einlesen XML
    eingabe.open("nameList1.xml");

    //Kontrolle ob einlesen funktionert
    if(!eingabe) cout << "erroreingabe" << endl;
    else cout << "jaaaaaeingabe"<< endl;


    fstream ausgabe(ausgabename); //neue Datei erstellen nachdem nach Name gefragt wird

    //Einlesen neue Datei
    ausgabe.open(ausgabename,ios::in | ios::out | ios::trunc);

    //Kontrolle ob einlesen funktionert
    if(!ausgabe) cout << "errorausgabe" << endl;
    else cout << "jaaaaaausgabe"<< endl;


    // XMl Datei - Wo ist die Id und wo muss das Geb.Datum hingeschrieben werden
     for(eingabe.get(zeichen);!eingabe.eof();eingabe.get(zeichen)){

    // Wir verarbeiten die einzelnen Zeichen in Abhängigkeit davon, welche es sind.
       switch(zeichen)
          {

       case '<':
           puffer[zaehler]= '\0';
           zaehler = 0;
           ausgabe << zeichen;

          break;

       case '>':
           hotfix = true;
           puffer[zaehler]= '\0';
           zaehler = 0;

           if(!strcmp(puffer,"/persName")){

                int k = 0; // zum durchzählen der ID's von idtxt
                for(k=0; k<=idzaehlertxt; k++) {
                    if(!strcmp(id,idtxt[k])){
                        ausgabe << zeichen;
                        ausgabe << endl << "<birth when=\"" << yeartxt[k] << "-" << monthtxt[k] << "-" << daytxt[k] << "\"></birth>";
                        hotfix = false; // damit nicht noch ein > eingefügt wird
                      }
                 }
           }

            if (!hotfix==false){
           ausgabe << zeichen; // > wird eingefügt
            }

          break;

       case '=':
           zustand= iderwarte;
           ausgabe << zeichen;

           break;

       case '"':
           puffer[zaehler]= '\0';
           zaehler = 0;
           if (zustand == iderwarte){
              zustand= idverarbeite;

           }
           else if(zustand==idverarbeite){
             strcpy(id,puffer);
           }

           ausgabe << zeichen;

           break;


        default:
           puffer[zaehler]=zeichen;
           zaehler++;
           ausgabe << zeichen;
           break;

       }
}

     //Dateien werden geschlossen
     ausgabe.close();
     eingabe.close();
    } else {
        cout << "das ist leider momentan nicht verfügbar"<< endl;
    }



    return 0;
}



/*
           //zustand=ID;

    // Wenn wir einen Attributnamen gelesen haben, endet er.
    // Wenn wir einen Attributwert lesen, ist es ein normales Zeichen, das
    // gespeichert wird.
    // Sonst melden wir einen Fehler.
          break;

       default:
           puffer[zaehler]=zeichen;
           zaehler++;
           break;

       }








       case '"':
    // Wenn wir einen Attributwert erwarten, beginnt er.
    // Wenn wir einen Attributwert verarbeiten, endet er.
    // Sonst melden wir einen Fehler.
          break;

       default:
    // Wir speichern das Zeichen, wenn wir innerhalb eines Tags sind.
          break;
        }


    }
*/
