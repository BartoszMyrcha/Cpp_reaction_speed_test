#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <windows.h>
using namespace std;


void trojkat(int sp=20, int zn=1){
	for(int i=0; i<20; i++)
	{
		cout<<"\t\t";
	    for(int j=0; j<sp; j++)
			cout<<" ";
		for(int k=0; k<zn; k++)
			cout<<"#";
		for(int l=0; l<sp; l++)
			cout<<" ";
		cout<<"\t\t";
		cout<<"\n";
		sp--;
		zn+=2;
	}
}


void kwadrat(void){
	for (int i=0; i<20; i++)
	{
		cout<<"\t\t";
		for (int j=0; j<20; j++)
			cout<<"##";
		cout<<"\t\t";
		cout<<endl;
	}
}


void romb(void){
	int sp=10, zn=1;
	for(int i=0; i<10; i++)
	{
		cout<<"\t\t\t";
	    for(int k=0; k<sp; k++)
			cout<<" ";
		for(int l=0; l<zn; l++)
			cout<<"#";
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
		cout<<"#";
	cout<<"\t\t\t\t";
	cout<<"\n";
	
	for(int i=0; i<10; i++)
	{
		cout<<"\t\t\t";
	    for(int k=sp; k>0; k--)
			cout<<" ";
		for(int l=zn; l>0; l--)
			cout<<"#";
		for(int m=sp; m>0; m--)
			cout<<" ";
		cout<<"\t\t\t\t";
		cout<<"\n";
		sp++;
		zn-=2;
	}
}

void kolo(void){
	for (int y = 0; y < 20; y++ )
	{
		cout<<"\t\t\t";
		for (int x = 0; x < 20; x++)
			if ( (y-10)*(y-10) + (x-10)*(x-10) < 50 ) cout<<"#"; else	cout<<" ";
		cout<<"\t\t\t";
		cout <<endl;
	}
}


char zamiana(int n){
	char l;
	switch(n){
			case 1 : {trojkat(); l='w';	break;}
			case 2 : {kwadrat(); l='s';	break;}
			case 3 : {romb(); l='a';	break;}
			case 4 : {kolo(); l='d';  break;}
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



int main(){
	int czas_start=time(0), czas_pyt, kol, wyb, ok=0, nok=0, ile_pytan=0, pozostaly_czas, ile, max, min, tr=0, kw=0, ro=0, ko=0;
	char litera, odp;
	int wyniki[100][3];
	double pr, czas_tr=0, czas_kw=0, czas_ro=0, czas_ko=0;
	
	cout<<"\tTEST BADAJACY SZYBKOSC REAKCJI.\n\nZostana wyswietlone figury. Zadanie polega na jak najszybszym\nwprowadzeniu litery odpowiadajacej figurze."<<endl;
	cout<<"Na kazda odpowiedz przeznaczone sa 4 sekundy. \nJesli odpowiedz nie padnie po tym czasie, zostanie uznana za zla.\nTrojkat - w\nKwadrat - s\nRomb - a\nKolo - d\n\nAby zaczac test wcisnij dowolny klawisz.";
	getch();
	system("cls");
	srand(time(0));
	
	pozostaly_czas=60;
	while(pozostaly_czas>0)
	{
		cout<<"Pozostaly czas testu: "<<pozostaly_czas<<"s.\n\n";
		ile_pytan++;
		czas_pyt=time(0);
		wyb=1+rand()%4;
		cout<<ile_pytan<<")\tTrojkat - w\tKwadrat - s\tRomb - a\tKolo - d\n";
		kol=1+rand()%7;
		kolor(kol);
		litera=zamiana(wyb);
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
		ile=ile_pytan;
		
		wyniki[ile_pytan-1][2]=wyb;
		
		if (difftime(time(0), czas_pyt)<=4)	wyniki[ile_pytan-1][0]=difftime(time(0), czas_pyt); else wyniki[ile_pytan-1][0]=4;
		pozostaly_czas=pozostaly_czas-wyniki[ile_pytan-1][0];
		if (wyniki[ile_pytan-1][0]>=4) {nok++; cout<<"Za pozno!"; wyniki[ile_pytan-1][1]=0;} else
		{ 
			if (odp!=litera) {cout<<"ZLA ODPOWIEDZ!\n\n"; nok++; wyniki[ile_pytan-1][1]=0;}
			else {cout<<"DOBRA ODPOWIEDZ!\n\n"; ok++; wyniki[ile_pytan-1][1]=1;};
		};
		system("cls");
	}

	
	cout<<"Liczba dobrych odpowiedzi: "<<ok<<endl;
	cout<<"Liczba zlych odpowiedzi: "<<nok<<endl;
	cout<<"Ilosc pytan: "<<ile_pytan<<endl;
	pr=ok;
	cout<<"Wynik procentowy dobrych odpowiedzi: "<<setprecision(4)<<(pr*100)/ile_pytan<<"%\n\n";
	cout<<"Tabela wynikow poszczegolnych pytan:\n\n";
	cout<<"Pytanie\t|\tCzas\t|\tOdpowiedz  |\tFigura";
	cout<<"\n________________________________________________________";
	max=wyniki[0][0];
	min=wyniki[0][0];
	for(int i=0; i<ile_pytan; i++)
	{
		cout<<"\n"<<i+1<<")\t|\t"<<wyniki[i][0]<<" s\t|\t";
		if (wyniki[i][1]==1) cout<<"DOBRA\t|\t"; else cout<<"ZLA\t|\t";
		switch(wyniki[i][2]){
			case 1 : {cout<<"Trojkat"; tr++; czas_tr+=wyniki[i][0]; break;}
			case 2 : {cout<<"Kwadrat"; kw++; czas_kw+=wyniki[i][0]; break;}
			case 3 : {cout<<"Romb"; ro++; czas_ro+=wyniki[i][0]; break;}
			case 4 : {cout<<"Kolo"; ko++; czas_ko+=wyniki[i][0]; break;}
		}
		cout<<"\n--------------------------------------------------------";
	};
	
	for (int i=0; i<ile_pytan-1; i++)
	{
		if (wyniki[i+1][0]>max) max=wyniki[i+1][0];
		if (wyniki[i+1][0]<min) min=wyniki[i+1][0];
	}
	
	cout<<"\nNajkrotszy czas rozpoznawania: "<<min<<"s";
	cout<<"\nNajdluzszy czas rozpoznawania: "<<max<<"s";
	cout<<"\nSredni czas rozpoznawania: "<<60./ile_pytan<<"s\n\n";
	wykres(czas_tr, tr, czas_kw, kw, czas_ro, ro, czas_ko, ko);
	cout<<"\n\n\n";
	
	system("PAUSE");
	return 0;
}
