#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>

using namespace std;

struct Adresat {
    int id = 0;
    string imie, nazwisko, telefon, email, adres;
};

string wczytajLinie() {
    bool prawidlowyTekst = false;
    string linia = "";

    do {
        cin.clear();
        cin.sync();
        getline(cin, linia);
        for (unsigned int i = 0; i < linia.length(); i++) {
            if (linia[i] == '|') {
                prawidlowyTekst = false;
                cout << endl << "Linia zawiera niedozwolony znak '|'" << endl;
                cout << "Wprowadz tekst ponownie: ";
                break;
            } else {
                prawidlowyTekst = true;
            }
        }
    } while(!prawidlowyTekst);
    return linia;
}

void wyswietlMenu() {
    cout << "Menu programu:" << endl;
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "9. Zakoncz program" << endl;
}

void dodajUzytkownika(vector<Adresat>& uzytkownicy) {

    Adresat nowyAdresat;

    cout << "1. Dodaj nowego adresata" << endl << endl;
    if (uzytkownicy.size() == 0) {
        nowyAdresat.id = 1;
    } else {
        nowyAdresat.id = uzytkownicy[uzytkownicy.size() - 1].id + 1;
    }
    cout << "Podaj imie adresata:     ";
    nowyAdresat.imie = wczytajLinie();
    cout << "Podaj nazwisko adresata: ";
    nowyAdresat.nazwisko = wczytajLinie();
    cout << "Podaj telefon adresata:  ";
    nowyAdresat.telefon = wczytajLinie();
    cout << "Podaj email adresata:    ";
    nowyAdresat.email = wczytajLinie();
    cout << "Podaj adres adresata:    ";
    nowyAdresat.adres = wczytajLinie();

    fstream plik;
    plik.open("Ksiazka Adresowa.txt", ios::out | ios::app);
    plik << nowyAdresat.id << "|" << nowyAdresat.imie << "|" << nowyAdresat.nazwisko << "|" << nowyAdresat.telefon << "|"
         << nowyAdresat.email << "|" << nowyAdresat.adres << "|" << endl;
    plik.close();

    uzytkownicy.push_back(nowyAdresat);

    cout << endl << "Adresat zostal dodany prawidlowo!" << endl << endl;
    system("pause");
    system("cls");
}

void zapisUzytkownikow(vector<Adresat>& uzytkownicy) {

    fstream plik;
    plik.open("Ksiazka Adresowa.txt", ios::out);

    for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
        plik << uzytkownicy[i].id << "|" << uzytkownicy[i].imie << "|" << uzytkownicy[i].nazwisko << "|" << uzytkownicy[i].telefon << "|"
             << uzytkownicy[i].email << "|" << uzytkownicy[i].adres << "|" << endl;
    }
    plik.close();
}

void wczytajUzytkownikow(vector<Adresat>& uzytkownicy) {
    Adresat nowyAdresat;
    int numerZnaku = 0;
    string linia = "";
    string tekstRoboczy = "";

    fstream plik;
    plik.open("Ksiazka Adresowa.txt",ios::in);
    if (!plik.good()) {
    } else {
        while(getline(plik, linia)) {

            for(unsigned int i = 0; i <= linia.length(); i++) {
                if(linia[i] == '|') {
                    switch(numerZnaku) {
                    case 0:
                        nowyAdresat.id = atoi(tekstRoboczy.c_str());
                        break;
                    case 1:
                        nowyAdresat.imie = tekstRoboczy;
                        break;
                    case 2:
                        nowyAdresat.nazwisko = tekstRoboczy;
                        break;
                    case 3:
                        nowyAdresat.telefon = tekstRoboczy;
                        break;
                    case 4:
                        nowyAdresat.email = tekstRoboczy;
                        break;
                    case 5:
                        nowyAdresat.adres = tekstRoboczy;
                        break;
                    }
                    tekstRoboczy = "";
                    numerZnaku++;
                    i++;
                }
                tekstRoboczy += linia[i];
            }
            uzytkownicy.push_back(nowyAdresat);
            tekstRoboczy = "";
            numerZnaku = 0;
        }
        plik.close();
    }
}

void wyswietlUzytkownikow(vector<Adresat>& uzytkownicy) {
    for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
        cout << "Numer ID:       " << uzytkownicy[i].id << endl;
        cout << "Imie:           " << uzytkownicy[i].imie << endl;
        cout << "Nazwisko:       " << uzytkownicy[i].nazwisko << endl;
        cout << "Numer telefonu: " << uzytkownicy[i].telefon << endl;
        cout << "Email:          " << uzytkownicy[i].email << endl;
        cout << "Adres:          " << uzytkownicy[i].adres << endl << endl;
    }
}

void wyszukajUzytkownikow(vector<Adresat>& uzytkownicy, string dane) {
    string imieUzytkownika, nazwiskoUzytkownika;
    bool wyszukiwanie = false;

    if( dane == "imie") {
        cout << "2. Wyszukaj adresata po imieniu" << endl << endl;
        cout << "Podaj imie uzytkownika: ";
        imieUzytkownika = wczytajLinie();
    } else if (dane == "nazwisko") {
        cout << "3. Wyszukaj adresata po nazwisku" << endl;
        cout << "Podaj nazwisko uzytkownika: ";
        nazwiskoUzytkownika = wczytajLinie();
    }
    for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
        if (imieUzytkownika == uzytkownicy[i].imie || nazwiskoUzytkownika == uzytkownicy[i].nazwisko) {
            wyszukiwanie = true;
            cout << "Numer ID:       " << uzytkownicy[i].id << endl;
            cout << "Imie:           " << uzytkownicy[i].imie << endl;
            cout << "Nazwisko:       " << uzytkownicy[i].nazwisko << endl;
            cout << "Numer telefonu: " << uzytkownicy[i].telefon << endl;
            cout << "Email:          " << uzytkownicy[i].email << endl;
            cout << "Adres:          " << uzytkownicy[i].adres << endl << endl;
        }
    }
    if (!wyszukiwanie) {
        cout << endl << "W ksiazce adresowej nie znaleziono wskazanego uzytkownika." << endl;
    }
}

void edytujUzytkownikow(vector<Adresat>& uzytkownicy) {
    bool edytowanieUzytkownika = false;
    int idAdresata, daneUzytkownika;

    cout << "6. Edytuj dane adresata:" << endl << endl;
    wyswietlUzytkownikow(uzytkownicy);
    cout << "Podaj ID uzytkownika: ";
    cin >> idAdresata;

    for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].id == idAdresata) {
            edytowanieUzytkownika = true;
            system("cls");
            cout << "6. Edytuj dane adresata" << endl << endl;
            cout << "1. Imie:           " << uzytkownicy[i].imie << endl;
            cout << "2. Nazwisko:       " << uzytkownicy[i].nazwisko << endl;
            cout << "3. Numer telefonu: " << uzytkownicy[i].telefon << endl;
            cout << "4. Email:          " << uzytkownicy[i].email << endl;
            cout << "5. Adres:          " << uzytkownicy[i].adres << endl;
            cout << "6. Powrot do menu  " << endl << endl;
            do {
                cout << "Wybierz numer, aby edytowac odpowiednie dane: ";
                cin >> daneUzytkownika;
            } while ((daneUzytkownika < 1) || (6 < daneUzytkownika));
            system("cls");
            switch(daneUzytkownika) {
            case 1:
                cout << "Imie:               " << uzytkownicy[i].imie << endl;
                cout << "Wprowadz nowe dane: ";
                uzytkownicy[i].imie = wczytajLinie();
                break;
            case 2:
                cout << "Nazwisko:           " << uzytkownicy[i].nazwisko << endl;
                cout << "Wprowadz nowe dane: ";
                uzytkownicy[i].nazwisko  = wczytajLinie();
                break;
            case 3:
                cout << "Numer telefonu:     " << uzytkownicy[i].telefon << endl;
                cout << "Wprowadz nowe dane: ";
                uzytkownicy[i].telefon  = wczytajLinie();
                break;
            case 4:
                cout << "Email:              " << uzytkownicy[i].email << endl;
                cout << "Wprowadz nowe dane: ";
                uzytkownicy[i].email = wczytajLinie();
                break;
            case 5:
                cout << "Adres:              " << uzytkownicy[i].adres << endl << endl;
                cout << "Wprowadz nowe dane: ";
                uzytkownicy[i].adres  = wczytajLinie();
                break;
            case 6:
                edytowanieUzytkownika = false;
                break;
            }
            if (edytowanieUzytkownika) {
                zapisUzytkownikow(uzytkownicy);
                cout << endl << "Adresat zostal prawidlowo edytowany!" << endl << endl;
                system("pause");
                system("cls");
            }
        }
    }
    if (!edytowanieUzytkownika) {
        cout << "Nie znaleziono uzytkownika o wskazanym ID lub anulowano operacje!" << endl << endl;
        system("pause");
        system("cls");
    }
}

void usunUzytkownikow(vector<Adresat>& uzytkownicy) {
    bool usuniecieAdresata = false;
    int idAdresata;

    cout << "5. Usun adresata:" << endl << endl;
    wyswietlUzytkownikow(uzytkownicy);
    cout << "Podaj ID uzytkownika: ";
    cin >> idAdresata;

    for(unsigned int i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].id == idAdresata) {
            uzytkownicy.erase(uzytkownicy.begin()+i);
            usuniecieAdresata = true;
            break;
        }
    }
    if(usuniecieAdresata) {
        zapisUzytkownikow(uzytkownicy);
        cout << "Adresat zostal usuniety." << endl;
    } else if(!usuniecieAdresata) {
        cout << "Adresat nie zostal odnaleziony!" << endl;
    }
    system("pause");
    system("cls");
}

int main() {
    char wybor = '0';
    vector<Adresat> uzytkownicy;

    wczytajUzytkownikow(uzytkownicy);
    do {
        wyswietlMenu();
        wybor = getch();
        system("cls");

        switch(wybor) {
        case '1':
            dodajUzytkownika(uzytkownicy);
            break;
        case '2':
            if (uzytkownicy.size() > 0) {
                wyszukajUzytkownikow(uzytkownicy, "imie");
                system("pause");
                system("cls");
            } else {
                cout << "Ksiazka adresowa jest pusta!" << endl;
                system("pause");
                system("cls");
            }
            break;
        case '3':
            if (uzytkownicy.size() > 0) {
                wyszukajUzytkownikow(uzytkownicy, "nazwisko");
                system("pause");
                system("cls");
            } else {
                cout << "Ksiazka adresowa jest pusta!" << endl;
                system("pause");
                system("cls");
            }
            break;
        case '4':
            if (uzytkownicy.size() > 0) {
                cout << "4. Wyswietl wszystkich adresatow:" << endl << endl;
                wyswietlUzytkownikow(uzytkownicy);
                system("pause");
                system("cls");
            } else {
                cout << "Ksiazka adresowa jest pusta!" << endl;
                system("pause");
                system("cls");
            }
            break;
        case '5':
            if (uzytkownicy.size() > 0) {
                usunUzytkownikow(uzytkownicy);
            } else {
                cout << "Ksiazka adresowa jest pusta!" << endl;
                system("pause");
                system("cls");
            }
            break;
        case '6':
            if (uzytkownicy.size() > 0) {
                edytujUzytkownikow(uzytkownicy);
            } else {
                cout << "Ksiazka adresowa jest pusta!" << endl;
                system("pause");
                system("cls");
            }
            break;
        }
    } while(wybor != '9');
    return 0;
}
