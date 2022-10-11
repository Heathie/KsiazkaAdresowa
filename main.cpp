#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct Przyjaciel {
    int id=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

int dodawaniePrzyjacielaDoBazy (vector<Przyjaciel>& przyjaciele) {
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
            nowyPrzyjaciel.id = przyjaciele.size() > 0 ? przyjaciele[przyjaciele.size()-1].id + 1 : 1;
            nowyPrzyjaciel.imie=imie;
            nowyPrzyjaciel.nazwisko=nazwisko;
            nowyPrzyjaciel.numerTelefonu=numerTelefonu;
            nowyPrzyjaciel.email=email;
            nowyPrzyjaciel.adres=adres;
            przyjaciele.push_back(nowyPrzyjaciel);

            fstream plik;
            plik.open("KsiazkaAdresowa.txt",fstream::out | fstream::app);
            if (plik.good()) {
                plik<<nowyPrzyjaciel.id<<"|";
                plik<<nowyPrzyjaciel.imie<<"|";
                plik<<nowyPrzyjaciel.nazwisko<<"|";
                plik<<nowyPrzyjaciel.numerTelefonu<<"|";
                plik<<nowyPrzyjaciel.email<<"|";
                plik<<nowyPrzyjaciel.adres<<"|";
                plik<<endl;
                plik.close();

                cout << "Adresat dodany"<<endl;
                system ("pause");

            } else {
                cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt do rejestracji adresatow" << endl;
            }

            return przyjaciele.size()+1;
        }
    }
}

vector<Przyjaciel> wczytajPrzyjaciolZBazy () {
    vector<Przyjaciel> przyjaciele;
    int nr_pola = 1;
    string linia;
    string temp;

    Przyjaciel kumpel;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", fstream::in | fstream::out | fstream::app);

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
                        kumpel.imie = temp;
                        break;
                    case 3:
                        kumpel.nazwisko = temp;
                        break;
                    case 4:
                        kumpel.numerTelefonu = temp;
                        break;
                    case 5:
                        kumpel.email = temp;
                        break;
                    case 6:
                        kumpel.adres = temp;
                        break;
                    }

                    if (nr_pola == 6) {
                        nr_pola = 1;
                        przyjaciele.push_back(kumpel);
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

    return przyjaciele;
}

void dodajPrzyjacielaDoPliku(Przyjaciel kumpel, fstream& plik){
            plik<<kumpel.id<<"|";
            plik<<kumpel.imie<<"|";
            plik<<kumpel.nazwisko<<"|";
            plik<<kumpel.numerTelefonu<<"|";
            plik<<kumpel.email<<"|";
            plik<<kumpel.adres<<"|";
            plik<<endl;
}

void wypiszPrzyjaciela (Przyjaciel przyjaciel) {
    cout<< przyjaciel.imie << " " << przyjaciel.nazwisko <<" " << przyjaciel.numerTelefonu <<" " << przyjaciel.email <<" " << przyjaciel.adres << endl;
}

void wyszukajPoImieniu (vector<Przyjaciel> przyjaciele) {
    bool czyZnaleziono=false;
    string imie;
    cout<<"Podaj imie: ";
    cin>>imie;

    for (int i=0; i < (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].imie==imie) {
            wypiszPrzyjaciela(przyjaciele[i]);
            czyZnaleziono=true;
        }
    }
    if (!czyZnaleziono) {
        cout << "W bazie nie ma adresata o takim imieniu" << endl;
    }
    system ("pause");

}

void wyszukajPoNazwisku (vector<Przyjaciel> przyjaciele) {
    bool czyZnaleziono=false;
    string nazwisko;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;

    for (int i=0; i < (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].nazwisko==nazwisko) {
            wypiszPrzyjaciela(przyjaciele[i]);
            czyZnaleziono=true;
        }
    }
    if (!czyZnaleziono) {
        cout << "W bazie nie ma adresata o takim nazwisku" << endl;

    }
    system ("pause");
}

void wyswietlWszystko(vector<Przyjaciel> przyjaciele) {
    if(przyjaciele.size() == 0) {
        cout<<"Brak adresatow w bazie"<<endl;
    } else {
        for(int i=0; i< (int) przyjaciele.size(); i++) {
            wypiszPrzyjaciela (przyjaciele[i]);
        }
    }
    system ("pause");
}

void usunAdresata (vector<Przyjaciel>& przyjaciele) {
    string id;
    int indeksGosciaDoUsuniecia=-1;
    char potwierdzenie;
    cout << "Podaj ID adresata: ";
    cin>>id;

    for (int i=0; i< (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].id==atoi(id.c_str())) {
            indeksGosciaDoUsuniecia=i;
            break;
        }
    }

    if (indeksGosciaDoUsuniecia==-1) {
        cout<<"Nie ma takiego adresata w bazie"<<endl;
        return;
    }
    cout << "Usunac adresata?" << endl;
    cin>>potwierdzenie;

    if (potwierdzenie == 't') {
        przyjaciele.erase(przyjaciele.begin()+indeksGosciaDoUsuniecia);
    }

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::trunc);
    if (plik.good()) {
        for (int i=0; i< (int) przyjaciele.size(); i++) {
            dodajPrzyjacielaDoPliku(przyjaciele[i], plik);
        }
        plik.close();
        cout <<"Adresat usuniety"<<endl;
    }
    system ("pause");
    return;
}

void edytujAdresata (vector<Przyjaciel>& przyjaciele) {
    string id;
    char wybor;
    string dane;
    cout<<"Podaj ID adresata"<<endl;
    cin>>id;

    for (int i=0; i< (int) przyjaciele.size(); i++) {
        if (przyjaciele[i].id==atoi(id.c_str())) {
            cout<<"1.Imie"<<endl;
            cout<<"2.Nazwisko"<<endl;
            cout<<"3.Numer telefonu"<<endl;
            cout<<"4.Email"<<endl;
            cout<<"5.Adres"<<endl;
            cout<<"6.Powrot do menu"<<endl;
            cin>>wybor;
            cin.ignore();
            getline(cin,dane);

            switch(wybor) {
            case '1':
                przyjaciele[i].imie=dane;
                break;
            case '2':
                przyjaciele[i].nazwisko=dane;
                break;
            case '3':
                przyjaciele[i].numerTelefonu=dane;
                break;
            case '4':
                przyjaciele[i].email=dane;
                break;
            case '5':
                przyjaciele[i].adres=dane;
                break;
            case '6':
                return;
                break;
            }
            cout <<"Adresat zedytowany"<<endl;
            break;
        }
    }

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::trunc);
    if (plik.good()) {
        for (int i=0; i< (int) przyjaciele.size(); i++) {
            dodajPrzyjacielaDoPliku(przyjaciele[i], plik);
        }
        plik.close();
    }
    system ("pause");
    return;
}

int main() {
    vector<Przyjaciel> przyjaciele = wczytajPrzyjaciolZBazy();
    char wybor;

    while (1) {
        system ("cls");
        cout << "1. Dodawanie" << endl;
        cout << "2. Wyszukiwanie po imieniu" << endl;
        cout << "3. Wyszukiwanie po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz dzialanie" << endl;
        cin >> wybor;

        switch(wybor) {
        case '1':
            dodawaniePrzyjacielaDoBazy (przyjaciele);
            break;
        case '2':
            wyszukajPoImieniu (przyjaciele);
            break;
        case '3':
            wyszukajPoNazwisku (przyjaciele);
            break;
        case '4':
            wyswietlWszystko (przyjaciele);
            break;
        case '5':
            usunAdresata (przyjaciele);
            break;
        case '6':
            edytujAdresata (przyjaciele);
            break;
        case '9':
            exit(0);
        }
    }

    return 0;
}
