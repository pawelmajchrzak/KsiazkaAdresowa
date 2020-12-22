#include <iostream>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Kontakt
{
    int id, idUzytkownika;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

int wczytajIloscUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    string linia;
    int nr_linii = 1;
    int iloscUzytkownikow = 0;
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::in);

    if(plik.good()==false)
    {
        return 0;
    }
    else
    {
        while (getline(plik,linia))
        {
            if (linia=="")
            {
                iloscUzytkownikow--;
                break;
            }
            int poczatekDanej=0;
            string tymczasowaKieszen[3];
            int nrZmiennej=0;
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                {
                    tymczasowaKieszen[nrZmiennej] = linia.substr(poczatekDanej,i-poczatekDanej);
                    nrZmiennej++;
                    poczatekDanej = i+1;
                }
            }
            uzytkownicy.push_back (nowyUzytkownik);
            uzytkownicy[iloscUzytkownikow].id = atoi(tymczasowaKieszen[0].c_str());
            uzytkownicy[iloscUzytkownikow].nazwa = tymczasowaKieszen[1];
            uzytkownicy[iloscUzytkownikow].haslo = tymczasowaKieszen[2];
            iloscUzytkownikow++;
        }
        if (iloscUzytkownikow == -1)
            iloscUzytkownikow++;
    }
    plik.close();
    return iloscUzytkownikow;
}

void zapiszUzytkownikaDoPliku(string nazwa,string haslo,int iloscUzytkownikow)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out|ios::app);
    plik<<iloscUzytkownikow+1<< "|";
    plik<<nazwa<< "|";
    plik<<haslo<< "|"<< endl;
    plik.close();
}

int rejestracja (vector <Uzytkownik> &uzytkownicy,int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i=0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;
    zapiszUzytkownikaDoPliku(nazwa, haslo, iloscUzytkownikow);
    uzytkownicy[iloscUzytkownikow].nazwa = nazwa;
    uzytkownicy[iloscUzytkownikow].haslo = haslo;
    uzytkownicy[iloscUzytkownikow].id = iloscUzytkownikow+1;
        cout << "Konto zalozone" << endl;
    Sleep(1000);
    return iloscUzytkownikow+1;

}

int logowanie(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i=0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proba = 0; proba < 3; proba++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proba << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i=0; i<iloscUzytkownikow; i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}

void logowanieIRejestracja(vector <Uzytkownik> &uzytkownicy,int &idZalogowanegoUzytkownika,int &iloscUzytkownikow)
{


        char wybor;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                Uzytkownik nowyUzytkownik;
                uzytkownicy.push_back (nowyUzytkownik);
                iloscUzytkownikow = rejestracja (uzytkownicy,iloscUzytkownikow);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }
        else
        {
            return;
        }
    }
}

int wczytajIloscKontaktowZPliku(vector <Kontakt> &kontakty, Kontakt nowaOsoba, int idZalogowanegoUzytkownika, int &IdOstatniegoKontaktu)
{
    string linia;
    int nr_linii = 1;
    int iloscOsob = 0;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);

    if(plik.good()==false)
    {
        return 0;
    }
    else
    {
        while (getline(plik,linia))
        {
            if (linia=="")
            {
                iloscOsob--;
                break;
            }
            int poczatekDanej=0;
            string tymczasowaKieszen[7];
            int nrZmiennej=0;
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                {
                    tymczasowaKieszen[nrZmiennej] = linia.substr(poczatekDanej,i-poczatekDanej);
                    nrZmiennej++;
                    poczatekDanej = i+1;
                }
            }
            if (atoi(tymczasowaKieszen[1].c_str()) == idZalogowanegoUzytkownika)
            {
                kontakty.push_back (nowaOsoba);
                kontakty[iloscOsob].id = atoi(tymczasowaKieszen[0].c_str());
                kontakty[iloscOsob].idUzytkownika = atoi(tymczasowaKieszen[1].c_str());
                kontakty[iloscOsob].imie = tymczasowaKieszen[2];
                kontakty[iloscOsob].nazwisko = tymczasowaKieszen[3];
                kontakty[iloscOsob].numerTelefonu = tymczasowaKieszen[4];
                kontakty[iloscOsob].email = tymczasowaKieszen[5];
                kontakty[iloscOsob].adres = tymczasowaKieszen[6];
                iloscOsob++;
            }
            IdOstatniegoKontaktu = atoi(tymczasowaKieszen[0].c_str());
        }
        if (iloscOsob == -1)
            iloscOsob++;
    }
    plik.close();
    return iloscOsob;
}


void zapiszKontaktdoPliku(string imie,string nazwisko,string numerTelefonu,string email,string adres,int IdOstatniegoKontaktu, int idZalogowanegoUzytkownika)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out|ios::app);
    plik<<IdOstatniegoKontaktu+1<< "|";
    plik<<idZalogowanegoUzytkownika<< "|";
    plik<<imie<< "|";
    plik<<nazwisko<< "|";
    plik<<numerTelefonu<< "|";
    plik<<email<< "|";
    plik<<adres<< "|"<< endl;
    plik.close();
}



int dodanieNowegoKontaktu (vector <Kontakt> &kontakty,int iloscKontaktow, Kontakt nowaOsoba, int &IdOstatniegoKontaktu, int idZalogowanegoUzytkownika)
{
    system("cls");
    cout << "Tworzenie nowego kontaku"<< endl<< endl;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.clear();
    cin.sync();
    getline(cin,numerTelefonu);
    cout << "Podaj numer email: ";
    cin >> email;
    cout << "Podaj adres zamieszkania: ";
    cin.clear();
    cin.sync();
    getline(cin,adres);

    zapiszKontaktdoPliku(imie, nazwisko, numerTelefonu, email, adres, IdOstatniegoKontaktu, idZalogowanegoUzytkownika);

    kontakty.push_back (nowaOsoba);
    kontakty[iloscKontaktow].imie = imie;
    kontakty[iloscKontaktow].nazwisko = nazwisko;
    kontakty[iloscKontaktow].numerTelefonu = numerTelefonu;
    kontakty[iloscKontaktow].email = email;
    kontakty[iloscKontaktow].adres = adres;
    kontakty[iloscKontaktow].id = IdOstatniegoKontaktu+1;
    kontakty[iloscKontaktow].idUzytkownika = idZalogowanegoUzytkownika;
    cout <<endl<< "Nowy kontakt zostal dodany do ksiazki adresowej!"<<endl;
    Sleep (1500);
    IdOstatniegoKontaktu++;
    return iloscKontaktow+1;
}


void wyswietlKontakt (vector <Kontakt> kontakty,int numerKontaktu)
{
    cout << "Id: ";
    cout << kontakty[numerKontaktu].id<< "| ";
    cout << kontakty[numerKontaktu].idUzytkownika<< "| ";
    cout << kontakty[numerKontaktu].imie<< " ";
    cout << kontakty[numerKontaktu].nazwisko<< " tel. ";
    cout << kontakty[numerKontaktu].numerTelefonu<< " ";
    cout << kontakty[numerKontaktu].email<< " ";
    cout << kontakty[numerKontaktu].adres<< endl;
}


void szukanieKontaktu(vector <Kontakt> kontakty,int iloscKontaktow);

void szukaniePoImieniu(vector <Kontakt> kontakty,int iloscKontaktow)
{
    string imie;
    int parametrIstnieniaOsobODanymImieniu = 0;

    system("cls");
    cout << "Wyszukiwarka kontaktow"<< endl<< endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << endl;

    for (int i=0; i<=iloscKontaktow; i++)
    {
        if(kontakty[i].imie == imie)
        {
            wyswietlKontakt (kontakty,i);
            parametrIstnieniaOsobODanymImieniu++;
        }
    }

    if (parametrIstnieniaOsobODanymImieniu == 0)
    {
        cout << "Brak Wynikow" << endl ;
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zmien dane wyszukiwania" << endl;

        char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        szukanieKontaktu(kontakty,iloscKontaktow);
    }
}


void szukaniePoNazwisku(vector <Kontakt> kontakty,int iloscKontaktow)
{
    string nazwisko;
    int parametrIstnieniaOsobODanymNazwisku = 0;

    system("cls");
    cout << "Wyszukiwarka kontaktow"<< endl<< endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << endl;

    for (int i=0; i<=iloscKontaktow; i++)
    {
        if(kontakty[i].nazwisko == nazwisko)
        {
            wyswietlKontakt (kontakty,i);
            parametrIstnieniaOsobODanymNazwisku++;
        }
    }

    if (parametrIstnieniaOsobODanymNazwisku == 0)
    {
        cout << "Brak Wynikow" << endl ;
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zmien dane wyszukiwania" << endl;

    char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        szukanieKontaktu(kontakty,iloscKontaktow);
    }
}


void szukanieKontaktu(vector <Kontakt> kontakty,int iloscKontaktow)
{
    system("cls");
    cout << "1. Szukaj po imieniu" << endl;
    cout << "2. Szukaj po nazwisku" << endl << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";

    char wybor;

    while (1)
    {
        cin >> wybor;
        if (wybor == '1')
        {
            szukaniePoImieniu(kontakty,iloscKontaktow);
            return;
        }
        else if (wybor == '2')
        {
            szukaniePoNazwisku(kontakty,iloscKontaktow);
            return;
        }
        else if (wybor == '0')
        {
            return;
        }
        else
            cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
    }
}


void wyswietlenieWszystkichKontaktow(vector <Kontakt> kontakty,int iloscKontaktow)
{
    cout << endl;
    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }

    cout << endl << "1. Powrot do menu glownego" << endl;
    cout << "2. Zakonczenie programu" << endl << endl;
    cout << "Twoj wybor: ";
    char wybor;
    cin >> wybor;

    if (wybor == '1')
    {
        return;
    }
    else if (wybor == '2')
    {
        exit(0);
    }
}

int edytujDaneOsoby(vector <Kontakt> &kontakty,int iloscKontaktow,int &numerKontaktu)
{
    system("cls");
    int Id;
    cout << "Podaj nr Id osoby, ktora chcesz edytowac";

    cout << endl<< endl<< "Spis kontaktow:"<< endl;

    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }

    cout << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";

    while (1)
    {

    cin >> Id;
    if (Id == 0)
        return Id;

    for (int j=0; j<iloscKontaktow; j++)
    {
        if (Id == kontakty[j].id)
            numerKontaktu = j;
    }
    if (numerKontaktu == -1)
        cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
    else
        break;
    }
    system("cls");

    wyswietlKontakt (kontakty,numerKontaktu);

    cout << endl << "Co chcialbys zmienic:" << endl;

    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu" << endl;

    string zmienionaDana;
    char wybor;
    while(1)
    {
        cin >> wybor;
        switch (wybor)
        {
        case '1':
            cout << "Podaj nowe imie: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].imie = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return Id;
            break;
        case '2':
            cout << "Podaj nowe nazwisko: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].nazwisko = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return Id;
            break;
        case '3':
            cout << "Podaj nowy numer telefonu: ";
            cin.clear();
            cin.sync();
            getline(cin,zmienionaDana);
            kontakty[numerKontaktu].numerTelefonu = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return Id;
            break;
        case '4':
            cout << "Podaj nowy email: ";
            cin >> zmienionaDana;
            kontakty[numerKontaktu].email = zmienionaDana;
            cout << endl << "Zmiana zosta³a zapisana!";
            Sleep (1500);
            return Id;
            break;
        case '5':
            cout << "Podaj nowy adres: ";
            cin.clear();
            cin.sync();
            getline(cin,zmienionaDana);
            kontakty[numerKontaktu].adres = zmienionaDana;
            cout << endl << "Zmiana zostala zapisana!";
            Sleep (1500);
            return Id;
            break;
        case '6':
            return Id;
            break;
        default:
            cout << "Nie ma takiej opcji w menu!" << endl;
            cout << "Wybierz liczbe w zakresu od 1 do 6" << endl;
        }
    }
    return Id;
}

void zapiszZmianyDoPliku(vector <Kontakt> kontakty,int iloscKontaktow, int numerOsoby, int numerKontaktu)
{
    ifstream input("KsiazkaAdresowa.txt");
    ofstream output("TymczasowaKsiazkaAdresowa.txt");
    string linia;
    int nrIdZPliku = 0;

    if(!input.good() || !output.good())
    {
        return;
    }
    else
    {
        while(getline(input,linia))
        {
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                {
                    nrIdZPliku = atoi(linia.substr(0,i).c_str());
                    break;
                }
            }

            if (nrIdZPliku == numerOsoby)
            {
                output << kontakty[numerKontaktu].id << "|";
                output << kontakty[numerKontaktu].idUzytkownika << "|";
                output << kontakty[numerKontaktu].imie << "|";
                output << kontakty[numerKontaktu].nazwisko << "|";
                output << kontakty[numerKontaktu].numerTelefonu << "|";
                output << kontakty[numerKontaktu].email << "|";
                output << kontakty[numerKontaktu].adres << "|" << endl;
            }
            else
                output << linia << endl;
        }
    }
    input.close();
    output.close();
    remove ("KsiazkaAdresowa.txt");
    rename("TymczasowaKsiazkaAdresowa.txt","KsiazkaAdresowa.txt");
    return;
}

int usunKontakt(vector <Kontakt> &kontakty,int &iloscKontaktow,int &numerKontaktu)
{
    system("cls");
    int Id;
    //int numerKontaktu = -1;
    cout << "Wybierz nr Id osoby, ktora chcesz usunac";

    cout << endl<< endl<< "Spis kontaktow:"<< endl;
    for (int i=0; i<iloscKontaktow; i++)
    {
            wyswietlKontakt (kontakty,i);
    }
    cout << endl;
    cout << "0. Powrot do menu glownego" << endl << endl;
    cout << "Twoj wybor: ";
    while (1)
    {
        cin >> Id;
        if (Id == 0)
        return Id;

        for (int i=0; i<iloscKontaktow; i++)
        {
            if (Id == kontakty[i].id)
                numerKontaktu = i;
        }
        if (numerKontaktu == -1)
            cout << endl << "Blad wyboru! Sprobuj jeszcze raz: ";
        else
            break;

    }
    system("cls");

    wyswietlKontakt (kontakty,numerKontaktu);
    cout << endl<< endl<< "Czy napewno chcesz ten kontakt usunac? (t/n)"<< endl;
    string wybor;
    while (1)
    {
    cin >> wybor;
    transform(wybor.begin(),wybor.end(),wybor.begin(),::tolower);
    if ( wybor == "t")
    {
        for (int j=numerKontaktu; j<iloscKontaktow-1; j++)
        {
            kontakty[j].imie            = kontakty[j+1].imie;
            kontakty[j].nazwisko        = kontakty[j+1].nazwisko;
            kontakty[j].numerTelefonu   = kontakty[j+1].numerTelefonu;
            kontakty[j].email           = kontakty[j+1].email;
            kontakty[j].adres           = kontakty[j+1].adres;
            kontakty[j].id              = kontakty[j+1].id;
        }
        kontakty.pop_back();
        iloscKontaktow--;
        cout << "Usunieto kontakt!";
        Sleep (1500);
        return Id;
    }
    else if ( wybor == "n")
        return Id;
    else
        cout << "Wybierz t lub n" << endl;
    }
}

void usunZPliku(vector <Kontakt> kontakty,int iloscKontaktow, int numerOsoby, int numerKontaktu)
{
    ifstream input("KsiazkaAdresowa.txt");
    ofstream output("TymczasowaKsiazkaAdresowa.txt");
    string linia;
    int nrIdZPliku = 0;

    if(!input.good() || !output.good())
    {
        return;
    }
    else
    {
        while(getline(input,linia))
        {
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                {
                    nrIdZPliku = atoi(linia.substr(0,i).c_str());
                    break;
                }
            }

            if (nrIdZPliku == numerOsoby)
            {

            }
            else
                output << linia << endl;
        }
    }
    input.close();
    output.close();
    remove ("KsiazkaAdresowa.txt");
    rename("TymczasowaKsiazkaAdresowa.txt","KsiazkaAdresowa.txt");
    return;
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = wczytajIloscUzytkownikowZPliku(uzytkownicy);

    logowanieIRejestracja(uzytkownicy,idZalogowanegoUzytkownika,iloscUzytkownikow);
    while(1)
    {
        vector <Kontakt> kontakty;
        Kontakt nowaOsoba;
        int idWyswietlonegoKontaktu = 0;
        int IdOstatniegoKontaktu = 0;
        int iloscKontaktow = wczytajIloscKontaktowZPliku(kontakty,nowaOsoba,idZalogowanegoUzytkownika, IdOstatniegoKontaktu);
        int numerOsoby = 0;
        char wybor;

        while(1)
        {
            system("cls");
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukaj kontakt" << endl;
            cout << "3. Wyswietl wszyskie moje kontakty" << endl;
            cout << "4. Edytuj kontakt" << endl;
            cout << "5. Usun kontakt" << endl;
            cout << "6. Zmiana hasla" << endl;
            cout << "9. Wylogowanie" << endl <<endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                kontakty.push_back (nowaOsoba);
                iloscKontaktow = dodanieNowegoKontaktu (kontakty, iloscKontaktow, nowaOsoba, IdOstatniegoKontaktu, idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {
                szukanieKontaktu(kontakty,iloscKontaktow);
            }
            else if (wybor == '3')
            {
                system ("cls");
                wyswietlenieWszystkichKontaktow(kontakty,iloscKontaktow);
            }
            else if (wybor == '4')
            {
                int numerKontaktu = -1;
                numerOsoby=edytujDaneOsoby(kontakty,iloscKontaktow,numerKontaktu);
                zapiszZmianyDoPliku(kontakty,iloscKontaktow,numerOsoby,numerKontaktu);
            }
            else if (wybor == '5')
            {
                int numerKontaktu = -1;
                numerOsoby=usunKontakt(kontakty,iloscKontaktow,numerKontaktu);
                usunZPliku(kontakty,iloscKontaktow,numerOsoby,numerKontaktu);
            }
            else if (wybor == '6')
            {
                zmianaHasla(uzytkownicy,iloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                idZalogowanegoUzytkownika=0;
                logowanieIRejestracja(uzytkownicy,idZalogowanegoUzytkownika,iloscUzytkownikow);
                break;
            }
        }

    }
    return 0;
}
