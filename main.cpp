#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <stdio.h>


using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

struct Adresat {
    int id;
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

string wczytajLinieBezDodatkowychZnakow() {
    bool prawidlowyTekst = false;
    string linia = "";

    do {
        cin.clear();
        cin.sync();
        getline(cin, linia);
        for (unsigned int i = 0; i < linia.length(); i++) {
            if (linia[i] == '|' || linia[i] == ' ') {
                prawidlowyTekst = false;
                cout << endl << "Linia zawiera niedozwolony znak '|' lub spacje" << endl;
                cout << "Wprowadz tekst ponownie: " << endl;
                break;
            } else {
                prawidlowyTekst = true;
            }
        }
    } while(!prawidlowyTekst);
    return linia;
}

void wyswietlMenuGlowne() {
    cout << "Menu programu:" << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz program" << endl;
}

void wyswietlMenuUzytkownika(Uzytkownik zalogowanyUzytkownik) {
    cout << "Zalogowany uzytkownik: " << zalogowanyUzytkownik.nazwa << endl << endl;
    cout << "Menu uzytkownika:" << endl;
    cout << "1. Dodaj nowego adresata" << endl;
    cout << "2. Wyszukaj adresata po imieniu" << endl;
    cout << "3. Wyszukaj adresata po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj dane adresata" << endl;
    cout << "7. Zmiana hasla" << endl;
    cout << "8. Wyloguj" << endl;
    cout << "9. Zakoncz program" << endl;
    cout << "Menu programu:" << endl;
}

void wczytajUzytkownikow(vector<Uzytkownik>& uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    int numerZnaku = 0;
    string linia = "";
    string tekstRoboczy = "";

    fstream plik;
    plik.open("Uzytkownicy.txt",ios::in);
    if (!plik.good()) {
    } else {
        while(getline(plik, linia)) {

            for(unsigned int i = 0; i <= linia.length(); i++) {
                if(linia[i] == '|') {
                    switch(numerZnaku) {
                    case 0:
                        nowyUzytkownik.id = atoi(tekstRoboczy.c_str());
                        break;
                    case 1:
                        nowyUzytkownik.nazwa = tekstRoboczy;
                        break;
                    case 2:
                        nowyUzytkownik.haslo = tekstRoboczy;
                        break;
                    }
                    tekstRoboczy = "";
                    numerZnaku++;
                    i++;
                }
                tekstRoboczy += linia[i];
            }
            uzytkownicy.push_back(nowyUzytkownik);
            tekstRoboczy = "";
            numerZnaku = 0;
        }
        plik.close();
    }
}

void dodajAdresata(vector<Adresat>& adresaci, Uzytkownik zalogowanyUzytkownik, int idNowegoAdresata) {

    Adresat nowyAdresat;

    cout << "1. Dodaj nowego adresata" << endl << endl;
    nowyAdresat.id = idNowegoAdresata;
    cout << "Podaj imie adresata:     ";
    nowyAdresat.imie = wczytajLinieBezDodatkowychZnakow();
    cout << "Podaj nazwisko adresata: ";
    nowyAdresat.nazwisko = wczytajLinieBezDodatkowychZnakow();
    cout << "Podaj telefon adresata:  ";
    nowyAdresat.telefon = wczytajLinie();
    cout << "Podaj email adresata:    ";
    nowyAdresat.email = wczytajLinieBezDodatkowychZnakow();
    cout << "Podaj adres adresata:    ";
    nowyAdresat.adres = wczytajLinie();

    fstream plik;
    plik.open("Ksiazka Adresowa.txt", ios::out | ios::app);
    plik << nowyAdresat.id << "|" << zalogowanyUzytkownik.id << "|" << nowyAdresat.imie << "|" << nowyAdresat.nazwisko << "|" << nowyAdresat.telefon << "|"
         << nowyAdresat.email << "|" << nowyAdresat.adres << "|" << endl;
    plik.close();

    adresaci.push_back(nowyAdresat);

    cout << endl << "Adresat zostal dodany prawidlowo!" << endl << endl;
    system("pause");
    system("cls");
}

int wczytajAdresatow(vector<Adresat>& adresaci, Uzytkownik zalogowanyUzytkownik) {
    int idUzytkownika;
    Adresat nowyAdresat;
    nowyAdresat.id = 0;
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
                        idUzytkownika = atoi(tekstRoboczy.c_str());
                        break;
                    case 2:
                        nowyAdresat.imie = tekstRoboczy;
                        break;
                    case 3:
                        nowyAdresat.nazwisko = tekstRoboczy;
                        break;
                    case 4:
                        nowyAdresat.telefon = tekstRoboczy;
                        break;
                    case 5:
                        nowyAdresat.email = tekstRoboczy;
                        break;
                    case 6:
                        nowyAdresat.adres = tekstRoboczy;
                        break;
                    }
                    tekstRoboczy = "";
                    numerZnaku++;
                    i++;
                }
                tekstRoboczy += linia[i];
            }
            if(idUzytkownika == zalogowanyUzytkownik.id) {
                adresaci.push_back(nowyAdresat);
            }
            tekstRoboczy = "";
            numerZnaku = 0;
        }
        plik.close();
    }
    return nowyAdresat.id + 1;
}

void zapiszAdresatow(vector<Adresat>& adresaci, Uzytkownik zalogowanyUzytkownik, int idEdytowanegoUzytkownika, int idUsuwanegoUzytkownika) {

    string linia = "";
    string tekstRoboczy = "";
    int idAdresata;

    fstream nowyPlik;
    fstream staryPlik;

    nowyPlik.open("Ksiazka Adresowa_temp.txt", ios::out);
    staryPlik.open("Ksiazka Adresowa.txt",ios::in);

    if (!staryPlik.good()) {
    } else {
        while(getline(staryPlik, linia)) {
            for(unsigned int i = 0; i <= linia.length(); i++) {
                if(linia[i] == '|') {
                    idAdresata = atoi(tekstRoboczy.c_str());
                    tekstRoboczy = "";
                    break;
                }
                tekstRoboczy += linia[i];
            }
            if(idAdresata == idEdytowanegoUzytkownika) {
                for(unsigned int i = 0; i < adresaci.size(); i++) {
                    if( adresaci[i].id == idEdytowanegoUzytkownika) {
                        nowyPlik << adresaci[i].id << "|" << zalogowanyUzytkownik.id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].telefon << "|"
                                 << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
                        break;
                    }
                }

            } else if(idAdresata == idUsuwanegoUzytkownika) {
            } else {
                nowyPlik << linia << endl;
            }
        }
    }
    nowyPlik.close();
    staryPlik.close();
    remove( "Ksiazka Adresowa.txt" );
    rename("Ksiazka Adresowa_temp.txt", "Ksiazka Adresowa.txt");

}

void wyswietlAdresatow(vector<Adresat>& adresaci) {
    for (unsigned int i = 0; i < adresaci.size(); i++) {
        cout << "Numer ID:       " << adresaci[i].id << endl;
        cout << "Imie:           " << adresaci[i].imie << endl;
        cout << "Nazwisko:       " << adresaci[i].nazwisko << endl;
        cout << "Numer telefonu: " << adresaci[i].telefon << endl;
        cout << "Email:          " << adresaci[i].email << endl;
        cout << "Adres:          " << adresaci[i].adres << endl << endl;
    }
}

void wyszukajAdresatow(vector<Adresat>& adresaci, string dane) {
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
    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if (imieUzytkownika == adresaci[i].imie || nazwiskoUzytkownika == adresaci[i].nazwisko) {
            wyszukiwanie = true;
            cout << "Numer ID:       " << adresaci[i].id << endl;
            cout << "Imie:           " << adresaci[i].imie << endl;
            cout << "Nazwisko:       " << adresaci[i].nazwisko << endl;
            cout << "Numer telefonu: " << adresaci[i].telefon << endl;
            cout << "Email:          " << adresaci[i].email << endl;
            cout << "Adres:          " << adresaci[i].adres << endl << endl;
        }
    }
    if (!wyszukiwanie) {
        cout << endl << "W ksiazce adresowej nie znaleziono wskazanego uzytkownika." << endl;
    }
}

void edytujAdresatow(vector<Adresat>& adresaci, Uzytkownik zalogowanyUzytkownik) {
    bool edytowanieUzytkownika = false;
    int idAdresata, daneUzytkownika;

    cout << "6. Edytuj dane adresata:" << endl << endl;
    wyswietlAdresatow(adresaci);
    cout << "Podaj ID uzytkownika: ";
    cin >> idAdresata;

    for (unsigned int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].id == idAdresata) {
            edytowanieUzytkownika = true;
            system("cls");
            cout << "6. Edytuj dane adresata" << endl << endl;
            cout << "1. Imie:           " << adresaci[i].imie << endl;
            cout << "2. Nazwisko:       " << adresaci[i].nazwisko << endl;
            cout << "3. Numer telefonu: " << adresaci[i].telefon << endl;
            cout << "4. Email:          " << adresaci[i].email << endl;
            cout << "5. Adres:          " << adresaci[i].adres << endl;
            cout << "6. Powrot do menu  " << endl << endl;
            do {
                cout << "Wybierz numer, aby edytowac odpowiednie dane: ";
                cin >> daneUzytkownika;
            } while ((daneUzytkownika < 1) || (6 < daneUzytkownika));
            system("cls");
            switch(daneUzytkownika) {
            case 1:
                cout << "Imie:               " << adresaci[i].imie << endl;
                cout << "Wprowadz nowe dane: ";
                adresaci[i].imie = wczytajLinie();
                break;
            case 2:
                cout << "Nazwisko:           " << adresaci[i].nazwisko << endl;
                cout << "Wprowadz nowe dane: ";
                adresaci[i].nazwisko  = wczytajLinie();
                break;
            case 3:
                cout << "Numer telefonu:     " << adresaci[i].telefon << endl;
                cout << "Wprowadz nowe dane: ";
                adresaci[i].telefon  = wczytajLinie();
                break;
            case 4:
                cout << "Email:              " << adresaci[i].email << endl;
                cout << "Wprowadz nowe dane: ";
                adresaci[i].email = wczytajLinie();
                break;
            case 5:
                cout << "Adres:              " << adresaci[i].adres << endl << endl;
                cout << "Wprowadz nowe dane: ";
                adresaci[i].adres  = wczytajLinie();
                break;
            case 6:
                edytowanieUzytkownika = false;
                break;
            }
            if (edytowanieUzytkownika) {
                zapiszAdresatow(adresaci, zalogowanyUzytkownik, idAdresata, 0);
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

void usunAdresata(vector<Adresat>& adresaci, Uzytkownik zalogowanyUzytkownik) {
    bool usuniecieAdresata = false;
    int idAdresata;

    cout << "5. Usun adresata:" << endl << endl;
    wyswietlAdresatow(adresaci);
    cout << "Podaj ID uzytkownika: ";
    cin >> idAdresata;

    for(unsigned int i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].id == idAdresata) {
            adresaci.erase(adresaci.begin()+i);
            usuniecieAdresata = true;
            break;
        }
    }
    if(usuniecieAdresata) {
        zapiszAdresatow(adresaci, zalogowanyUzytkownik, 0, idAdresata);
        cout << "Adresat zostal usuniety." << endl;
    } else if(!usuniecieAdresata) {
        cout << "Adresat nie zostal odnaleziony!" << endl;
    }
    system("pause");
    system("cls");
}

bool porownanieZnakow(string pierwszyCiagZnakow, string drugiCiagZnakow) {
    if(pierwszyCiagZnakow.length() == drugiCiagZnakow.length()) {
        transform(pierwszyCiagZnakow.begin(), pierwszyCiagZnakow.end(), pierwszyCiagZnakow.begin(), ::tolower);
        transform(drugiCiagZnakow.begin(), drugiCiagZnakow.end(), drugiCiagZnakow.begin(), ::tolower);
        if (pierwszyCiagZnakow == drugiCiagZnakow) {
            return true;
        }
    }
    return false;
}

void rejestracja(vector<Uzytkownik>& uzytkownicy) {
    Uzytkownik nowyUzytkownik;
    bool zajetaNazwaUzytkownika = false;

    cout << "1. Rejestracja" << endl << endl;
    if (uzytkownicy.size() == 0) {
        nowyUzytkownik.id = 1;
    } else {
        nowyUzytkownik.id = uzytkownicy[uzytkownicy.size() - 1].id + 1;
    }
    do {
        cout << "Podaj nazwe uzytkownika: " << endl;
        nowyUzytkownik.nazwa = wczytajLinieBezDodatkowychZnakow();
        zajetaNazwaUzytkownika = false;
        for(unsigned int i = 0; i < uzytkownicy.size(); i++) {
            zajetaNazwaUzytkownika = porownanieZnakow(nowyUzytkownik.nazwa, uzytkownicy[i].nazwa);
            if (zajetaNazwaUzytkownika) {
                cout << endl << "Podana nazwa uzytkownika jest zajeta. Podaj inna nazwe." << endl;
                break;
            }
        }
    } while(zajetaNazwaUzytkownika == true);
    cout << "Podaj haslo uzytkownika: " << endl;
    nowyUzytkownik.haslo = wczytajLinieBezDodatkowychZnakow();

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    plik << nowyUzytkownik.id << "|" << nowyUzytkownik.nazwa << "|" << nowyUzytkownik.haslo << "|" << endl;
    plik.close();

    uzytkownicy.push_back(nowyUzytkownik);

    cout << endl << "Konto zostalo prawidlowo utworzone." << endl << endl;
}

void logowanie(vector<Uzytkownik>& uzytkownicy, Uzytkownik& zalogowanyUzytkownik) {
    bool znalezionaNazwa = false;
    string nazwa, haslo;

    cout << "2. Logowanie" << endl << endl;
    cout << "Podaj nazwe uzytkownika: " << endl;
    nazwa = wczytajLinie();
    unsigned int i = 0;
    while (i < uzytkownicy.size()) {
        if (porownanieZnakow(nazwa, uzytkownicy[i].nazwa)) {
            znalezionaNazwa = true;
            for (int probyLogowania = 0; probyLogowania < 3; probyLogowania++) {
                cout << "Podaj haslo: " << endl;
                haslo = wczytajLinie();
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Uzytkownik zostal zalogowany pomyslnie." << endl;
                    zalogowanyUzytkownik.id = uzytkownicy[i].id;
                    zalogowanyUzytkownik.nazwa = uzytkownicy[i].nazwa;
                    break;
                } else {
                    cout << "Podane haslo jest nieprawidlowe!" << endl;
                    if (probyLogowania >= 2) {
                        cout << endl << "Przekroczono liczbe prob logowania!" << endl << endl;
                    }
                }
            }
        }
        i++;
    }
    if(!znalezionaNazwa) {
        cout << "Nie odnaleziono podanej nazwy uzytkownika!" << endl;
    }
}

void zmianaHasla(vector<Uzytkownik>& uzytkownicy, Uzytkownik zalogowanyUzytkownik) {
    string noweHaslo, noweHasloWeryfikacja;

    do {
        cout << "7. Zmiana hasla uzytkownika " << endl << endl;
        cout << "Wprowadz nowe haslo: " << endl;
        noweHaslo = wczytajLinieBezDodatkowychZnakow();
        cout << "Wprowadz nowe haslo w celu weryfikacji: " << endl;
        noweHasloWeryfikacja = wczytajLinieBezDodatkowychZnakow();
        if(noweHaslo != noweHasloWeryfikacja) {
            cout << "Wprowadzone hasla nie sa zgodne!" << endl;
            system("pause");
            system("cls");
        }
    } while(noweHaslo != noweHasloWeryfikacja);

    for(unsigned int i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].id == zalogowanyUzytkownik.id) {
            uzytkownicy[i].haslo = noweHaslo;
            cout << "Haslo uzytkownika zostalo zmienione." << endl;
            fstream plik;
            plik.open("Uzytkownicy.txt", ios::out);
            for (unsigned int i = 0; i < uzytkownicy.size(); i++) {
                fstream plik;
                plik.open("Uzytkownicy.txt", ios::out | ios::app);
                plik << uzytkownicy[i].id << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << "|" << endl;
            }
            plik.close();
            break;
        }
    }
}

int main() {
    char wybor = '0';
    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;

    bool wczytaniAdresaci = false;
    int idNowegoAdresata = 0;

    Uzytkownik zalogowanyUzytkownik;
    zalogowanyUzytkownik.id = 0;

    wczytajUzytkownikow(uzytkownicy);

    do {
        if(zalogowanyUzytkownik.id == 0) {
            wyswietlMenuGlowne();
            wybor = getch();
            system("cls");

            switch(wybor) {
            case '1':
                rejestracja(uzytkownicy);
                system("pause");
                system("cls");
                break;
            case '2':
                logowanie(uzytkownicy, zalogowanyUzytkownik);
                system("pause");
                system("cls");
                break;
            }
        } else {
            if (wczytaniAdresaci == false) {
                idNowegoAdresata = wczytajAdresatow(adresaci, zalogowanyUzytkownik);
                wczytaniAdresaci = true;
            }
            wyswietlMenuUzytkownika(zalogowanyUzytkownik);
            wybor = getch();
            system("cls");

            switch(wybor) {
            case '1':
                dodajAdresata(adresaci, zalogowanyUzytkownik, idNowegoAdresata);
                idNowegoAdresata++;
                break;
            case '2':
                if (adresaci.size() > 0) {
                    wyszukajAdresatow(adresaci, "imie");
                    system("pause");
                    system("cls");
                } else {
                    cout << "Ksiazka adresowa jest pusta!" << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case '3':
                if (adresaci.size() > 0) {
                    wyszukajAdresatow(adresaci, "nazwisko");
                    system("pause");
                    system("cls");
                } else {
                    cout << "Ksiazka adresowa jest pusta!" << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case '4':
                if (adresaci.size() > 0) {
                    cout << "4. Wyswietl wszystkich adresatow:" << endl << endl;
                    wyswietlAdresatow(adresaci);
                    system("pause");
                    system("cls");
                } else {
                    cout << "Ksiazka adresowa jest pusta!" << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case '5':
                if (adresaci.size() > 0) {
                    usunAdresata(adresaci, zalogowanyUzytkownik);
                } else {
                    cout << "Ksiazka adresowa jest pusta!" << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case '6':
                if (adresaci.size() > 0) {
                    edytujAdresatow(adresaci, zalogowanyUzytkownik);
                } else {
                    cout << "Ksiazka adresowa jest pusta!" << endl;
                    system("pause");
                    system("cls");
                }
                break;
            case '7':
                zmianaHasla(uzytkownicy, zalogowanyUzytkownik);
                system("pause");
                system("cls");
                break;
            case '8':
                zalogowanyUzytkownik.nazwa = "";
                zalogowanyUzytkownik.id = 0;
                wczytaniAdresaci = false;
                adresaci.clear();
                wczytaniAdresaci = false;
                cout << "Uzytkownik zostal wylogowany." << endl;
                system("pause");
                system("cls");
                break;
            }
        }
    } while(wybor != '9');
    cout << "Program zostaje wylaczony." << endl;
    return 0;
}
