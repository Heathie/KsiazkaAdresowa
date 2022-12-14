#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdio>

using namespace std;

const char NAZWA_PLIKU_TYMCZASOWEGO[] = "KsiazkaAdresowaTymczasowy.txt";
const char NAZWA_PLIKU_ORYGINALNEGO[] = "KsiazkaAdresowa.txt";

struct Uzytkownik {
    int idUzytkownika=0;
    string login="", haslo="";
};

struct Przyjaciel {
    int id=0, idUzytkownika;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

vector<Przyjaciel> wczytajPrzyjaciolZBazy (int idUzytkownika, int& idOstatniegoAdresata) {
    vector<Przyjaciel> przyjaciele;
    int nr_pola = 1;
    string linia;
    string temp;

    Przyjaciel kumpel;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", fstream::in );

    if (!plik.good()) {
        plik<<"\n";
    } else if (plik.good()) {
        while(!plik.eof()) {
            getline(plik, linia);

            for (int i = 0; i < (int) linia.length(); i++) {
                if (linia[i] == '|') {
                    switch(nr_pola) {
                    case 1:
                        kumpel.id = atoi(temp.c_str());
                        break;
                    case 2:
                        kumpel.idUzytkownika = atoi(temp.c_str());
                        break;
                    case 3:
                        kumpel.imie = temp;
                        break;
                    case 4:
                        kumpel.nazwisko = temp;
                        break;
                    case 5:
                        kumpel.numerTelefonu = temp;
                        break;
                    case 6:
                        kumpel.email = temp;
                        break;
                    case 7:
                        kumpel.adres = temp;
                        break;
                    }

                    if (nr_pola == 7) {
                        nr_pola = 1;
                        if (kumpel.idUzytkownika==idUzytkownika) {
                            przyjaciele.push_back(kumpel);
                        }
                    } else {
                        nr_pola++;
                    }

                    temp = "";
                } else {
                    temp.push_back(linia.at(i));
                }
            }
        }
    }
    plik.close();

    idOstatniegoAdresata=kumpel.id;

    return przyjaciele;
};

void dodajPrzyjacielaDoPliku(Przyjaciel kumpel, fstream& plik) {
    plik<<kumpel.id<<"|";
    plik<<kumpel.idUzytkownika<<"|";
    plik<<kumpel.imie<<"|";
    plik<<kumpel.nazwisko<<"|";
    plik<<kumpel.numerTelefonu<<"|";
    plik<<kumpel.email<<"|";
    plik<<kumpel.adres<<"|";
    plik<<endl;
}

int dodawaniePrzyjacielaDoBazy (vector<Przyjaciel>& przyjaciele, int idUzytkownika, int& idOstatniegoAdresata) {
    string imie, nazwisko, numerTelefonu, email, adres;
    while (true) {
        bool juzIstnieje=false;

        cout << "Podaj imie: ";
        cin>>imie;

        cout << "Podaj nazwisko: ";
        cin>>nazwisko;

        cout << "Podaj numer telefonu: ";
        cin.sync();
        getline(cin, numerTelefonu);

        cout << "Podaj email: ";
        cin>>email;

        cout<< "Podaj adres: ";
        cin.ignore();
        getline(cin,adres);


        for (int i=0; i<(int) przyjaciele.size(); i++) {
            if (
                przyjaciele[i].idUzytkownika==idUzytkownika &&
                przyjaciele[i].imie==imie &&
                przyjaciele[i].nazwisko==nazwisko &&
                przyjaciele[i].numerTelefonu==numerTelefonu &&
                przyjaciele[i].email==email &&
                przyjaciele[i].adres==adres
            ) {
                cout << "Taki adresat jest juz w bazie" << endl;
                juzIstnieje=true;
                break;
            }
        }

        if (!juzIstnieje) {
            Przyjaciel nowyPrzyjaciel;
            idOstatniegoAdresata++;
            nowyPrzyjaciel.id = idOstatniegoAdresata;
            nowyPrzyjaciel.idUzytkownika = idUzytkownika;
            nowyPrzyjaciel.imie=imie;
            nowyPrzyjaciel.nazwisko=nazwisko;
            nowyPrzyjaciel.numerTelefonu=numerTelefonu;
            nowyPrzyjaciel.email=email;
            nowyPrzyjaciel.adres=adres;
            przyjaciele.push_back(nowyPrzyjaciel);

            fstream plik;
            plik.open("KsiazkaAdresowa.txt",fstream::out | fstream::app);
            if (plik.good()) {
                dodajPrzyjacielaDoPliku(nowyPrzyjaciel, plik);
                plik.close();

                cout << "Adresat dodany"<<endl;
                system ("pause");

            } else {
                cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt do rejestracji adresatow" << endl;
            }

            return idOstatniegoAdresata;
        }
    }
}

vector<Uzytkownik> wczytajUzytkownikowZBazy () {
    vector<Uzytkownik> uzytkownicy;
    int nr_pola = 1;
    string linia;
    string temp;

    Uzytkownik user;

    fstream plik;
    plik.open("Uzytkownicy.txt",fstream::in);

    if (!plik.good()) {
        plik<<"\n";
    } else if (plik.good()) {
        while(!plik.eof()) {
            getline(plik, linia);

            for (int i = 0; i < (int) linia.length(); i++) {
                if (linia[i] == '|') {
                    switch(nr_pola) {
                    case 1:
                        user.idUzytkownika = atoi(temp.c_str());
                        break;
                    case 2:
                        user.login = temp;
                        break;
                    case 3:
                        user.haslo = temp;
                        break;
                    }

                    if (nr_pola == 3) {
                        nr_pola = 1;
                        uzytkownicy.push_back(user);
                    } else {
                        nr_pola++;
                    }

                    temp = "";
                } else {
                    temp.push_back(linia.at(i));
                }
            }
        }
    }
    plik.close();

    return uzytkownicy;
}

int logowanieUzytkownika (vector<Uzytkownik> uzytkownicy) {
    string login, haslo;

    cout<< "Podaj login: ";
    cin>>login;

    for (int i=0; i < (int) uzytkownicy.size(); i++) {

        if (uzytkownicy[i].login == login)  {
            for (int proby = 0; proby<3; proby++) {
                cout<< "Podaj haslo. Pozostalo prob "<< 3-proby << " : ";
                cin>>haslo;
                if (uzytkownicy[i].haslo==haslo) {
                    cout<<"Zalogowales sie"<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<< "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba."<<endl;
            Sleep(3000);
            return -1;
        }
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    system("pause");
    return -1;
}

void dodajUzytkownikaDoPliku(Uzytkownik user, fstream& plik) {
    plik<<user.idUzytkownika<<"|";
    plik<<user.login<<"|";
    plik<<user.haslo<<"|";
    plik<<endl;
}

int dodawanieUzytkownikaDoBazy (vector<Uzytkownik>& uzytkownicy) {
    string login,haslo;
    while (true) {
        bool juzIstnieje=false;

        cout << "Podaj login: ";
        cin>>login;

        cout << "Podaj haslo: ";
        cin>>haslo;

        for (int i=0; i<(int) uzytkownicy.size(); i++) {
            if (
                uzytkownicy[i].login==login
            ) {
                cout << "Taki uzytkownik jest juz w bazie" << endl;
                juzIstnieje=true;
                break;
            }
        }

        if (!juzIstnieje) {
            Uzytkownik nowyUzytkownik;
            nowyUzytkownik.idUzytkownika = uzytkownicy.size() > 0 ? uzytkownicy[uzytkownicy.size()-1].idUzytkownika + 1 : 1;
            nowyUzytkownik.login=login;
            nowyUzytkownik.haslo=haslo;
            uzytkownicy.push_back(nowyUzytkownik);

            fstream plik;
            plik.open("Uzytkownicy.txt",fstream::in |fstream::out | fstream::app);
            if (plik.good()) {
                dodajUzytkownikaDoPliku(nowyUzytkownik, plik);
                plik.close();

                cout << "Uzytkownik dodany"<<endl;
                system ("pause");

            } else {
                cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt do rejestracji adresatow" << endl;
            }
            return uzytkownicy.size()+1;
        }
    }
}

void zmienHaslo (vector<Uzytkownik>& uzytkownicy, int zalogowanyUzytkownik) {
    string haslo="", hasloPowtorka="-";
    int indeksUzytkownika;
    for(int i=0; i<=zalogowanyUzytkownik; i++) {
        if(zalogowanyUzytkownik==uzytkownicy[i].idUzytkownika) {
            indeksUzytkownika=i;
            break;
        }
    }
    while(haslo!=hasloPowtorka) {
        cout<< "Podaj nowe haslo: ";
        cin>>haslo;
        if(haslo==uzytkownicy[indeksUzytkownika].haslo) {
            cout<<"Nowe haslo nie moze byc takie samo jak stare haslo. Podaj ponownie nowe haslo."<<endl;
            continue;
        }
        cout<< "Podaj ponownie nowe haslo: ";
        cin>> hasloPowtorka;

        if (haslo!=hasloPowtorka) {
            cout<<"Podane hasla roznia sie. Podaj ponownie nowe haslo."<<endl;
            continue;
        }
        uzytkownicy[indeksUzytkownika].haslo = haslo;
        cout <<"Haslo zmienione"<<endl;
    }

    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out | ios::trunc);
    if (plik.good()) {
        for (int i=0; i< (int) uzytkownicy.size(); i++) {
            dodajUzytkownikaDoPliku(uzytkownicy[i], plik);
        }
        plik.close();
    }
    system ("pause");
    return;
}

void wypiszPrzyjaciela (Przyjaciel przyjaciel) {
    cout<<"----------------------------"<<endl;
    cout<<"ID adresata: "<<przyjaciel.id<<endl;
    cout<<"Imie: "<< przyjaciel.imie <<endl;
    cout<< "Nazwisko: " << przyjaciel.nazwisko <<endl;
    cout<<"Numer Telefonu: " << przyjaciel.numerTelefonu <<endl;
    cout<<"Email: " << przyjaciel.email <<endl;
    cout<<"Adres " << przyjaciel.adres << endl;
}

void wyszukajPoImieniu (vector<Przyjaciel> przyjaciele, int idUzytkownika) {
    bool czyZnaleziono=false;
    string imie;
    cout<<"Podaj imie: ";
    cin>>imie;

    for (int i=0; i < (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].imie==imie && przyjaciele[i].idUzytkownika==idUzytkownika) {
            wypiszPrzyjaciela(przyjaciele[i]);
            czyZnaleziono=true;
        }
    }
    if (!czyZnaleziono) {
        cout << "W bazie nie ma adresata o takim imieniu" << endl;
    }
    system ("pause");

}

void wyszukajPoNazwisku (vector<Przyjaciel> przyjaciele, int idUzytkownika) {
    bool czyZnaleziono=false;
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;

    for (int i=0; i < (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].nazwisko==nazwisko && przyjaciele[i].idUzytkownika==idUzytkownika) {
            wypiszPrzyjaciela(przyjaciele[i]);
            czyZnaleziono=true;
        }
    }
    if (!czyZnaleziono) {
        cout << "W bazie nie ma adresata o takim nazwisku" << endl;

    }
    system ("pause");
}

void wyswietlWszystko(vector<Przyjaciel> przyjaciele, int idUzytkownika) {
    if(przyjaciele.size() == 0) {
        cout<<"Brak adresatow w bazie"<<endl;
    } else {
        system("cls");
        for(int i=0; i< (int) przyjaciele.size(); i++) {
            if(przyjaciele[i].idUzytkownika==idUzytkownika) {
                wypiszPrzyjaciela (przyjaciele[i]);
            }
        }
    }
    system ("pause");
}

void zastapPlikOryginalny (vector<Przyjaciel> przyjaciele, int idUzytkownika) {
    int nr_pola = 1;
    string linia;
    string temp;
    Przyjaciel kumpel;
    int indeks = 0;
    fstream plik;
    fstream plikTymczasowy;

    plik.open(NAZWA_PLIKU_ORYGINALNEGO,ios::in);
    plikTymczasowy.open(NAZWA_PLIKU_TYMCZASOWEGO,ios::out | ios::trunc);

    if (!plikTymczasowy.good()) {
        plikTymczasowy<<"\n";
    } else if (plik.good()) {
        while(!plik.eof()) {
            getline(plik, linia);

            if (plik.eof()) {
                break;
            }

            for (int i = 0; i < (int) linia.length(); i++) {
                if (linia[i] == '|') {
                    switch(nr_pola) {
                    case 1:
                        kumpel.id = atoi(temp.c_str());
                        break;
                    case 2:
                        kumpel.idUzytkownika = atoi(temp.c_str());
                        break;
                    case 3:
                        kumpel.imie = temp;
                        break;
                    case 4:
                        kumpel.nazwisko = temp;
                        break;
                    case 5:
                        kumpel.numerTelefonu = temp;
                        break;
                    case 6:
                        kumpel.email = temp;
                        break;
                    case 7:
                        kumpel.adres = temp;
                        break;
                    }

                    if (nr_pola == 7) {
                        nr_pola = 1;
                    } else {
                        nr_pola++;
                    }

                    temp = "";
                } else {
                    temp.push_back(linia.at(i));
                }
            }

            if (kumpel.idUzytkownika!=idUzytkownika) {
                plikTymczasowy<<linia<<endl;
            } else {
                if (indeks < (int) przyjaciele.size() && kumpel.id==przyjaciele[indeks].id) {
                    dodajPrzyjacielaDoPliku(przyjaciele[indeks], plikTymczasowy);
                    indeks++;
                }
            }

        }
    }
    plik.close();
    plikTymczasowy.close();

    std::remove(NAZWA_PLIKU_ORYGINALNEGO);

    if (rename(NAZWA_PLIKU_TYMCZASOWEGO, NAZWA_PLIKU_ORYGINALNEGO) != 0) {
        perror("Error renaming file");
    }
    system ("pause");
    return;
}

void usunAdresata (vector<Przyjaciel>& przyjaciele, int idUzytkownika) {
    string id;
    int indeksGosciaDoUsuniecia=-1;
    char potwierdzenie;
    cout << "Podaj ID adresata: ";
    cin>>id;

    for (int i=0; i< (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].id==atoi(id.c_str())) {
            if(przyjaciele[i].idUzytkownika!=idUzytkownika) {
                break;
            }
            indeksGosciaDoUsuniecia=i;
            break;
        }
    }

    if (indeksGosciaDoUsuniecia==-1) {
        cout<<"Nie ma takiego adresata w bazie"<<endl;
        system("pause");
        return;
    }
    cout << "Usunac adresata? W celu potwierdzenia nacisnij t: ";
    cin>>potwierdzenie;

    if (potwierdzenie == 't') {
        przyjaciele.erase(przyjaciele.begin()+indeksGosciaDoUsuniecia);
        cout<<"Adresat usuniety"<<endl;
    }

    zastapPlikOryginalny (przyjaciele, idUzytkownika);
}

void edytujAdresata (vector<Przyjaciel>& przyjaciele, int idUzytkownika) {
    string id;
    int indeksAdresataDoEdycji=-1;
    char wybor;
    string dane;
    cout<<"Podaj ID adresata: ";
    cin>>id;

    for (int i=0; i< (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].id==atoi(id.c_str())) {
            indeksAdresataDoEdycji=i;
            break;
        }
    }

    if (indeksAdresataDoEdycji==-1) {
        cout<<"Nie ma takiego adresata w bazie"<<endl;
        system("pause");
        return;
    }

    cout<<"----------------------------"<<endl;
    cout<<"1.Imie"<<endl;
    cout<<"2.Nazwisko"<<endl;
    cout<<"3.Numer telefonu"<<endl;
    cout<<"4.Email"<<endl;
    cout<<"5.Adres"<<endl;
    cout<<"6.Powrot do menu"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Twoj wybor: ";
    cin>>wybor;
    cin.ignore();
    getline(cin,dane);

    switch(wybor) {
    case '1':
        przyjaciele[indeksAdresataDoEdycji].imie=dane;
        break;
    case '2':
        przyjaciele[indeksAdresataDoEdycji].nazwisko=dane;
        break;
    case '3':
        przyjaciele[indeksAdresataDoEdycji].numerTelefonu=dane;
        break;
    case '4':
        przyjaciele[indeksAdresataDoEdycji].email=dane;
        break;
    case '5':
        przyjaciele[indeksAdresataDoEdycji].adres=dane;
        break;
    case '6':
        return;
        break;
    }
    cout <<"Adresat zedytowany"<<endl;

    zastapPlikOryginalny (przyjaciele, idUzytkownika);
}

int main() {
    vector<Przyjaciel> przyjaciele;
    vector<Uzytkownik> uzytkownicy = wczytajUzytkownikowZBazy();
    int idOstatniegoAdresata=0;
    char wybor, decyzja;
    int idZalogowanegoUzytkownika=-1;


    while (1) {
        if (idZalogowanegoUzytkownika==-1) {
            system("cls");
            cout<< "     >>>MENU GLOWNE<<<"<<endl;
            cout<<"----------------------------"<<endl;
            cout<<"1. Logowanie"<<endl;
            cout<<"2. Rejestracja" <<endl;
            cout<<"9. Koniec programu" <<endl;
            cout<<"----------------------------"<<endl;
            cout<<"Twoj wybor: ";
            cin>>decyzja;

            switch(decyzja) {
            case '1':
                idZalogowanegoUzytkownika = logowanieUzytkownika (uzytkownicy);
                przyjaciele = wczytajPrzyjaciolZBazy(idZalogowanegoUzytkownika, idOstatniegoAdresata);
                break;
            case '2':
                dodawanieUzytkownikaDoBazy (uzytkownicy);
                break;
            case '9':
                exit(0);
            }
        } else {
            system ("cls");
            cout<< "        >>>MENU<<<"<<endl;
            cout<<"----------------------------"<<endl;
            cout << "1. Dodawanie" << endl;
            cout << "2. Wyszukiwanie po imieniu" << endl;
            cout << "3. Wyszukiwanie po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout<<"----------------------------"<<endl;
            cout<<"Twoj wybor: ";
            cin >> wybor;

            switch(wybor) {
            case '1':
                dodawaniePrzyjacielaDoBazy (przyjaciele, idZalogowanegoUzytkownika, idOstatniegoAdresata);
                break;
            case '2':
                wyszukajPoImieniu (przyjaciele, idZalogowanegoUzytkownika);
                break;
            case '3':
                wyszukajPoNazwisku (przyjaciele, idZalogowanegoUzytkownika);
                break;
            case '4':
                wyswietlWszystko (przyjaciele, idZalogowanegoUzytkownika);
                break;
            case '5':
                usunAdresata (przyjaciele, idZalogowanegoUzytkownika);
                break;
            case '6':
                edytujAdresata (przyjaciele, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmienHaslo (uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '9':
                idZalogowanegoUzytkownika=-1;
            }
        }
    }

    return 0;
}
