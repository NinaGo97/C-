#include <iostream>

using namespace std;
#include <fstream>
#include "string.h"
#include <string>

int main()
{

    fstream ausgabe("neueDatei.xml"); //neue Datei erstellen
    fstream eingabe; // xml Datei

    char zeichen;
    char puffer [100]; //Zwischenspeicher
    int zaehler;
    char id[4];
    char test ='a'; // Test, dass an die richtige Stelle was geschrieben wird in der neuen Datei
    enum zustand {start, iderwarte, idverarbeite,idend,einsetzen};
    enum zustand zustand = start;

    fstream eingabetxt; // txt Datei

    char zeichentxt;
    char puffertxt [100]; //Zwischenspeicher
    int zaehlertxt;
    char idtxt[4][50];  //ID's der Txt Datei werden hier reingeschrieben
    int idzaehlertxt = 0;
    char birthtxt[15][50]; //Geb.Datum reingeschrieben
    int birthzaehlertxt=0;

    enum zustandtxt {idvontxt, gebtxt};
    enum zustandtxt zustandtxt = idvontxt;
   // char aktion; //Eingabe ob suchen oder konvertieren
    //enum zustand{Tagname,ID, Vorname, Nachname};



    //Einlesen XML
    eingabe.open("nameList1.xml");

    //Kontrolle ob einlesen funktionert
    if(!eingabe) cout << "error" << endl;
                         else cout << "jaaaaa"<< endl;

    //Einlesen txt
    eingabetxt.open("nameList2.txt");

    //Kontrolle ob einlesen funktionert
    if(!eingabetxt) cout << "errortxt" << endl;
                         else cout << "jaaaaatxt"<< endl;

    //Einlesen neue Datei
    ausgabe.open("neueDatei.xml",ios::in | ios::out | ios::trunc);

    //Kontrolle ob einlesen funktionert
    if(!ausgabe) cout << "errorausgabe" << endl;
                         else cout << "jaaaaaausgabe"<< endl;



    //txt Datei unterscheidet zwischen ID und Geb
     for(eingabetxt.get(zeichentxt);!eingabetxt.eof();eingabetxt.get(zeichentxt)){
         switch (zeichentxt) {
         case ' ':

             puffertxt[zaehlertxt]='\0';
             zaehlertxt= 0;

                if (zustandtxt == idvontxt){
                    strcpy(idtxt[idzaehlertxt],puffertxt);
                    cout << idtxt[idzaehlertxt]<< endl;
                    idzaehlertxt ++;
                    zustandtxt = gebtxt;
                }

            break;

         case '\n':
             puffertxt[zaehlertxt]='\0';
             zaehlertxt=0;
             if (zustandtxt == gebtxt){
                 strcpy(birthtxt[birthzaehlertxt],puffertxt);
             cout << birthtxt[birthzaehlertxt] << endl;
             }



                 zustandtxt = idvontxt;

             break;


         //  \n (zeilenumbruch) Dann kommt eine ID
         // nach ' ' kommt Geb.
         default:
             puffertxt[zaehlertxt]=zeichentxt;
             zaehlertxt++;

             break;
         }


     };



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


           puffer[zaehler]= '\0';
           zaehler = 0;

           if(!strcmp(puffer,"/persName")){
            ausgabe << test << endl;

           /*if(id==idtxt[idzaehlertxt]){
            ausgabe << birthtxt << endl;


            };*/





           };

           ausgabe << zeichen;

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
             //zustand= idend;
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
     eingabetxt.close();
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

    cout<< "Wollen Sie suchen[s] oder konvertieren[k]?"<< endl;
    cin >> aktion;
    switch (aktion) {
    case 's':

        break;

    case 'k':

        break;
    default:

        cout << "Was meinen Sie mit " << aktion  << "?" << endl;
        break;
    }
*/
