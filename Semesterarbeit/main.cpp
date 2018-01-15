//Semesterarbeit von Anita Wichert und Nina Gollwig, 15.01.2018


#include <iostream>

using namespace std;
#include <fstream>
#include "string.h"
#include <string>

int main()
{
    char zeichen;
    char puffer [10000]; //Zwischenspeicher
    int zaehler;
    char id[4];
    string ausgabename;

    enum zustand {start, iderwarte, idverarbeite,idend,einsetzen};
    enum zustand zustand = start;

    fstream eingabetxt; // txt Datei

    char zeichentxt;
    char puffertxt [10000]; //Zwischenspeicher
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

    /*Kontrolle ob einlesen funktionert
    if(!eingabetxt) cout << "errortxt" << endl;
    else cout << "jaaaaatxt"<< endl; */


    cout<< "----------------------------Herzlich Willkommen!-------------------------------" << endl
        << "-------------------Wollen Sie suchen[s] oder konvertieren[k]?------------------"<< endl
        << "                                  ";
    cin >> aktion;

    cout << "----------Wie soll die neue Datei heissen? Bitte mit .xml am Schluss-----------"<< endl
         << "                                  ";
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

    fstream eingabe; // xml Datei
    //Einlesen XML
    eingabe.open("nameList1.xml");

    /*Kontrolle ob einlesen funktionert
    if(!eingabe) cout << "erroreingabe" << endl;
    else cout << "jaaaaaeingabe"<< endl;*/

    fstream ausgabe(ausgabename); //neue Datei erstellen nachdem nach Name gefragt wird
    //Einlesen neue Datei
    ausgabe.open(ausgabename,ios::in | ios::out | ios::trunc);

   /*Kontrolle ob einlesen funktionert
    if(!ausgabe) cout << "errorausgabe" << endl;
    else cout << "jaaaaaausgabe"<< endl;*/


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

     if(aktion =='s'){



     int zaehleraus;
     char pufferaus[10000];
     char zeichenaus;

     char vornameaus[100][100];
     char nachnameaus[100][100];
     char birthaus[50][50];
     char idaus[50][50];
     int zaehlersucheaus=0;

     enum zustandaus{erwarteidaus, verarbeiteidaus, erwartebirthaus, verarbeitebirthaus};
     enum zustandaus zustandaus = erwarteidaus;

     enum zustandname {startaus, verarbeitevornameaus, tagaus, verarbeitenachnameaus};
     enum zustandname zustandname = startaus;

     ausgabe.open(ausgabename);


          for(ausgabe.get(zeichenaus);!ausgabe.eof();ausgabe.get(zeichenaus)){

              switch (zeichenaus) {
              case '<':
                  pufferaus[zaehleraus]= '\0';
                  zaehleraus = 0;

                    if(zustandname==verarbeitevornameaus) {
                        pufferaus[0] = tolower(pufferaus[0]); // erster Buchstabe klein
                        strcpy(vornameaus[zaehlersucheaus], pufferaus);

                    } else if(zustandname == verarbeitenachnameaus){
                        pufferaus[0] = tolower(pufferaus[0]);
                        strcpy(nachnameaus[zaehlersucheaus], pufferaus);

                    }
                  break;

              case '>':
                  pufferaus[zaehleraus]= '\0';
                  zaehleraus = 0;

                  if(!strcmp("forename", pufferaus)){
                      zustandname = verarbeitevornameaus;
                  } else if (!strcmp("surname", pufferaus)){
                      zustandname = verarbeitenachnameaus;
                  } else{
                      zustandname = tagaus;

                  }


                  break;

              case '"':
                  pufferaus[zaehleraus]= '\0';
                  zaehleraus = 0;

                  switch (zustandaus) {
                  case erwarteidaus:
                      zustandaus = verarbeiteidaus;

                      break;
                  case verarbeiteidaus:
                      zustandaus = erwartebirthaus;

                      strcpy(idaus[zaehlersucheaus],pufferaus);


                      break;
                  case erwartebirthaus:
                      zustandaus = verarbeitebirthaus;

                      break;
                  case verarbeitebirthaus:
                      zustandaus = erwarteidaus;
                      pufferaus[0] = tolower(pufferaus[0]);
                      strcpy(birthaus[zaehlersucheaus],pufferaus);
                      zaehlersucheaus ++;



                      break;
                  default:
                      break;
                  } // switch zu

                  break;

              default:
                  pufferaus[zaehleraus]=zeichenaus;
                  zaehleraus++;


                  break;
              } // switch zu
          } //for schleife zu

          char kategorie [50];
          char suchbegriff[100];
          bool on=true;


        while(on==true){
            bool treffer = false;

          cout << "-Welche Kategorie wollen Sie suchen? (id, vorname, nachname, geburtstag, exit)-" << endl
               << "                                  ";
          cin >> kategorie;
          kategorie[0] = tolower(kategorie[0]);
          if(!strcmp(kategorie, "exit")){

                        return 0;

                    }
          if(strcmp(kategorie,"vorname") && strcmp(kategorie,"nachname")
                  && strcmp(kategorie,"id")&& strcmp(kategorie,"geburtstag")){
              cout << "------------------Ungültige Eingabe. Versuchen Sie es nochmal-------------------"<< endl<< endl;
              continue;
          }

          cout << "---Bitte Suchbegriff eingeben. Es reicht, wenn die Eingabe nur ein Teil ist.---" << endl
               << "                                  ";
          cin >> suchbegriff;
          suchbegriff[0] = tolower(suchbegriff[0]);

          if(!strcmp(kategorie, "id")){

              for(int z=0; z<=zaehlersucheaus; z++){

                  char *subid;
                  subid = strstr(idaus[z], suchbegriff);
                  if (subid){
                      cout << "--------------------------------Ergebis gefunden--------------------------------" << endl
                           << "                                  Id: " << idaus[z] << endl
                           << "                             Vorname: " << vornameaus[z]  << endl
                           << "                            Nachname: " << nachnameaus[z] << endl
                           << "                          Geburtstag: " << birthaus[z] <<endl << endl;
                      treffer = true;
                  }

              }

          } else if(!strcmp(kategorie, "vorname")){
              for(int z=0; z<=zaehlersucheaus; z++){

                  char *subvorname;
                  subvorname = strstr(vornameaus[z], suchbegriff);
                  if (subvorname){
                      cout << "--------------------------------Ergebis gefunden--------------------------------" << endl
                           << "                                  Id: " << idaus[z] << endl
                           << "                             Vorname: " << vornameaus[z]  << endl
                           << "                            Nachname: " << nachnameaus[z] << endl
                           << "                          Geburtstag: " << birthaus[z] <<endl << endl;
                      treffer = true;


                  }
              }



          } else if(!strcmp(kategorie, "nachname")){
              for(int z=0; z<=zaehlersucheaus; z++){

                  char *subnachname;
                  subnachname= strstr(nachnameaus[z], suchbegriff);
                  if (subnachname){
                      cout << "--------------------------------Ergebis gefunden--------------------------------" << endl
                           << "                                  Id: " << idaus[z] << endl
                           << "                             Vorname: " << vornameaus[z]  << endl
                           << "                            Nachname: " << nachnameaus[z] << endl
                           << "                          Geburtstag: " << birthaus[z] <<endl << endl;
                      treffer = true;


                  }
              }



          } else if (!strcmp(kategorie, "geburtstag")){

              for(int z=0; z<=zaehlersucheaus; z++){
                  char *subbirth;
                  subbirth = strstr(birthaus[z], suchbegriff);
                  if (subbirth){
                      cout << "--------------------------------Ergebis gefunden--------------------------------" << endl
                           << "                                  Id: " << idaus[z] << endl
                           << "                             Vorname: " << vornameaus[z]  << endl
                           << "                            Nachname: " << nachnameaus[z] << endl
                           << "                          Geburtstag: " << birthaus[z] <<endl << endl;
                      treffer = true;


                  }
              }


          }
          if(treffer==false){
              cout << "-----------------Leider kein Treffer, Versuchen Sie es nochmal!-----------------" << endl; //45
          }

     }//while
     }//if aktion


eingabetxt.close();
eingabe.close();

ausgabe.close();


    return 0;
}

