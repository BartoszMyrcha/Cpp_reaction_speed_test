#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;

struct wynik
{
	double czas_odp;
	int poprawnosc;
	int figura;
	wynik* nastepny;
	wynik();
};

wynik::wynik()	{
	nastepny=0;
}

struct lista {
    wynik* pierw;
    void dodaj_wynik (double czas_odp, int poprawnosc, int figura);
    void wyswietl_liste ();
    lista();
};

lista::lista() {
    pierw = 0;
}


void lista::dodaj_wynik(double czas_odp, int poprawnosc, int figura)
{
    wynik *nowy = new wynik;

    nowy->czas_odp = czas_odp;
    nowy->poprawnosc = poprawnosc;
    nowy->figura = figura;
 
    if (pierw==0)
    {
        pierw = nowy;
    }
 
    else
    {
        wynik *temp = pierw;
 
        while (temp->nastepny)
        {
            temp = temp->nastepny;
        }
 
        temp->nastepny = nowy;
        nowy->nastepny = 0; 
    }
}

void lista::wyswietl_liste()
{
    wynik *temp = pierw;
 
    while (temp)
    {
        cout << "imie: " << temp->czas_odp<<endl;
        temp=temp->nastepny;
    }
}

void trojkat(char);
void kwadrat(char);
void romb(char);
void kolo(char);
char zamiana(int, int);
void kolor(int);
void wykres(double, int, double, int, double, int, double, int);

////


int main(){
	int kol, wyb, znak_int, ok=0, nok=0, ile_pytan=0, tr=0, kw=0, ro=0, ko=0;
	char litera, odp;
	double wyniki_temp[3], czas_start=clock(), czas_pyt, max, min;
	double pr, czas_tr=0, czas_kw=0, czas_ro=0, czas_ko=0;
	
	lista *wyniki = new lista;
	
	cout<<"\tTEST BADAJACY SZYBKOSC REAKCJI.\n\nZostana wyswietlone figury. Zadanie polega na jak najszybszym\nwprowadzeniu litery odpowiadajacej figurze."<<endl;
	cout<<"Na kazda odpowiedz przeznaczone sa 4 sekundy. \nJesli odpowiedz nie padnie po tym czasie, zostanie uznana za zla.\nTrojkat - w\nKwadrat - s\nRomb - a\nKolo - d\n\nAby zaczac test wcisnij dowolny klawisz.";
	getch();
	system("cls");
	srand(clock());
	
	double pozostaly_czas=60;
	
	while(pozostaly_czas>0)
	{
		ile_pytan++;
		czas_pyt=clock();
		wyb=1+rand()%4; //losowanie figury
		znak_int=1+rand()%4; //losowanie znaku
		kol=1+rand()%7; //losowanie koloru
		kolor(kol);		//ustawianie koloru
		system("cls");
		cout<<"Pozostaly czas testu: "<<pozostaly_czas<<"s.\n\n";
		cout<<ile_pytan<<")\tTrojkat - w\tKwadrat - s\tRomb - a\tKolo - d\n";
		
		litera=zamiana(wyb, znak_int);	//ustalanie odpowiedzi (litery) dla wylosowanej figury oraz zdefiniowanie znaku
		cout<<"\nCzas pozostaly na odpowiedz: ";
	
		int timer=4000;
		while(timer>0)
		{
			if (timer%1000==0 || timer==10) cout<<timer/1000<<" ";
			if (kbhit())
				{
					odp=getch();	
					break;
				}
			Sleep(10);
			timer-=10;
		};
		
		wyniki_temp[2]=wyb;
		
		if (difftime(clock(), czas_pyt)/1000<=4)	wyniki_temp[0]=difftime(clock(), czas_pyt)/1000; else wyniki_temp[0]=4;
		pozostaly_czas=pozostaly_czas-wyniki_temp[0];
		if (wyniki_temp[0]>=4) {nok++; cout<<"Za pozno!"; wyniki_temp[1]=0;} else
		{ 
			if (odp!=litera) {cout<<"ZLA ODPOWIEDZ!\n\n"; nok++; wyniki_temp[1]=0;}
			else {cout<<"DOBRA ODPOWIEDZ!\n\n"; ok++; wyniki_temp[1]=1;};
		};
		wyniki->dodaj_wynik(wyniki_temp[0], wyniki_temp[1], wyniki_temp[2]);
	}

	kolor(-1);
	system("cls");
	cout<<"Liczba dobrych odpowiedzi: "<<ok<<endl;
	cout<<"Liczba zlych odpowiedzi: "<<nok<<endl;
	cout<<"Ilosc pytan: "<<ile_pytan<<endl;
	pr=ok;
	cout<<"Wynik procentowy dobrych odpowiedzi: "<<setprecision(4)<<(pr*100)/ile_pytan<<"%\n\n";
	cout<<"Tabela wynikow poszczegolnych pytan:\n\n";
	cout<<"Pytanie\t|\tCzas\t|\tOdpowiedz  |\tFigura";
	cout<<"\n________________________________________________________";
	
	
	max=wyniki_temp[0];
	min=wyniki_temp[0];
	
	int i=1;
	
	wynik *temp = wyniki->pierw;
 
    while (temp)
    {
        cout<<"\n"<<i<<")\t|\t"<<temp->czas_odp<<" s\t|\t";
        if (temp->poprawnosc==1) cout<<"DOBRA\t|\t"; else cout<<"ZLA\t|\t";
		switch(temp->figura){
			case 1 : {cout<<"Trojkat"; tr++; czas_tr+=temp->czas_odp; break;}
			case 2 : {cout<<"Kwadrat"; kw++; czas_kw+=temp->czas_odp; break;}
			case 3 : {cout<<"Romb"; ro++; czas_ro+=temp->czas_odp; break;}
			case 4 : {cout<<"Kolo"; ko++; czas_ko+=temp->czas_odp; break;}
		}
		cout<<"\n--------------------------------------------------------";
		
		if (temp->czas_odp>max) max=temp->czas_odp;
		if (temp->czas_odp<min) min=temp->czas_odp;
        
        
        temp=temp->nastepny;
        
        i++;
    }
    
    delete wyniki;
	
	cout<<"\nNajkrotszy czas rozpoznawania: "<<min<<"s";
	cout<<"\nNajdluzszy czas rozpoznawania: "<<max<<"s";
	cout<<"\nSredni czas rozpoznawania: "<<60./ile_pytan<<"s\n\n";
	wykres(czas_tr, tr, czas_kw, kw, czas_ro, ro, czas_ko, ko);
	cout<<"\n\n\n";
	
	system("PAUSE");
	return 0;
}

/* FUNKCJE */
void trojkat(char znak){
	int sp=20, zn=1;
	for(int i=0; i<20; i++)
	{
		cout<<"\t\t";
	    for(int j=0; j<sp; j++)
			cout<<" ";
		for(int k=0; k<zn; k++)
			cout<<znak;
		for(int l=0; l<sp; l++)
			cout<<" ";
		cout<<"\t\t";
		cout<<"\n";
		sp--;
		zn+=2;
	}
}


void kwadrat(char znak){
	for (int i=0; i<20; i++)
	{
		cout<<"\t\t";
		for (int j=0; j<20; j++)
			cout<<znak<<znak;
		cout<<"\t\t";
		cout<<endl;
	}
}


void romb(char znak){
	int sp=10, zn=1;
	for(int i=0; i<10; i++)
	{
		cout<<"\t\t\t";
	    for(int k=0; k<sp; k++)
			cout<<" ";
		for(int l=0; l<zn; l++)
			cout<<znak;
		for(int m=0; m<sp; m++)
			cout<<" ";
		cout<<"\t\t\t\t";
		cout<<"\n";
		sp--;
		zn+=2;
	}
	sp=1;
	zn=19;
	cout<<"\t\t\t";
	for (int i=0; i<21; i++)
		cout<<znak;
	cout<<"\t\t\t\t";
	cout<<"\n";
	
	for(int i=0; i<10; i++)
	{
		cout<<"\t\t\t";
	    for(int k=sp; k>0; k--)
			cout<<" ";
		for(int l=zn; l>0; l--)
			cout<<znak;
		for(int m=sp; m>0; m--)
			cout<<" ";
		cout<<"\t\t\t\t";
		cout<<"\n";
		sp++;
		zn-=2;
	}
}

void kolo(char znak){
	for (int y = 0; y < 20; y++ )
	{
		cout<<"\t\t\t";
		for (int x = 0; x < 20; x++)
			if ( (y-10)*(y-10) + (x-10)*(x-10) < 50 ) cout<<znak; else	cout<<" ";
		cout<<"\t\t\t";
		cout <<endl;
	}
}


char zamiana(int n, int znak_int){
	char l, znak;
	switch(znak_int)
	{
		case 1 : {znak='@'; break;}
		case 2 : {znak='#'; break;}
		case 3 : {znak='$'; break;}
		case 4 : {znak='*';	break;}
	}
	switch(n){
			case 1 : {trojkat(znak); l='w';	break;}
			case 2 : {kwadrat(znak); l='s';	break;}
			case 3 : {romb(znak); l='a';	break;}
			case 4 : {kolo(znak); l='d';  break;}
		}
	return l;
}

void kolor(int n){
	HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (n){
		case 1 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE); break;};
		case 2 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | BACKGROUND_BLUE); break;};
		case 3 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN); break;};
		case 4 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_BLUE | BACKGROUND_RED); break;};
		case 5 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN); break;};
		case 6 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_BLUE |BACKGROUND_BLUE | BACKGROUND_GREEN); break;};
		case 7 : {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE); break;};
		default: {SetConsoleTextAttribute(uchwyt, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);};
	}
}


void wykres(double czas_troj, int troj, double czas_kwad, int kwad, double czas_romb, int romb, double czas_kolo, int kolo){
	double sr_tr, sr_kw, sr_ro, sr_ko;
	sr_tr=czas_troj/troj;
	sr_kw=czas_kwad/kwad;
	sr_ro=czas_romb/romb;
	sr_ko=czas_kolo/kolo;
/*	cout<<"\n\nTrojkat: "<<czas_troj<<"s ,"<<troj<<" sr: "<<sr_tr;
	cout<<"\nKwadrat: "<<czas_kwad<<"s ,"<<kwad<<" sr: "<<sr_kw;
	cout<<"\nRomb: "<<czas_romb<<"s ,"<<romb<<" sr: "<<sr_ro;
	cout<<"\nKolo: "<<czas_kolo<<"s ,"<<kolo<<" sr: "<<sr_ko;		*/
	cout<<"\n\n\nWYKRES SLUPKOWY";
	cout<<"\n\nTrojkat: \t";
	while(sr_tr>0.099){
		cout<<"|";
		sr_tr-=0.1;
	}
	cout<<"\n\nKwadrat: \t";
	while(sr_kw>0.099){
		cout<<"|";
		sr_kw-=0.1;
	}
	cout<<"\n\nRomb:    \t";
	while(sr_ro>0.099){
		cout<<"|";
		sr_ro-=0.1;
	}
	cout<<"\n\nKolo:    \t";
	while(sr_ko>0.099){
		cout<<"|";
		sr_ko-=0.1;
	}
	cout<<"\n\t\t----------------------------------------";
	cout<<"\n\t\t0s\t\t\t\t\t4s\n(Podzialka: | - 0,1s)\n";
}

