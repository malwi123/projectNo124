#include<iostream>
#include<conio.h>
#include <Windows.h>

using namespace std;

const int SZER_MAX = 79;	//max wymiary figury
const int WYS_MAX = 24;
const int SZER_MIN = 4;
const int WYS_MIN = 4;

void intro();
char czytajZnak();
void czytajRozmiar(int &szerokosc, int &wysokosc);
void rysuj(char znak, int szerokosc, int wysokosc, int Xstart, int Ystart);
void akcja(int &szerokosc, int &wysokosc, int &Xstart, int &Ystart);

int main()
{
	intro(); 
	_getch();
	system("cls");

	char znak;
	znak=czytajZnak();

	int szer = 0, wys = 0;		//szerokoœc i wysokoœæ figury
	czytajRozmiar(szer, wys);
	system("cls");

	int X=1, Y=1;				//po³o¿enie punktu startowego
	while (true)
	{
		rysuj(znak, szer, wys, X, Y);
		akcja(szer, wys, X, Y);
		system("cls");
	}
	_getch();
}

void intro()
{
	cout << "Autor: Malwina Jeglinska, nr studenta: s16277" << endl;
	cout << "Projekt Nr 124" << endl << endl;
	cout << "Program rysowania znakiem ASCII ponizszej figury:" << endl<<endl;
	cout << "		M       *" << endl;
	cout << "		M M   M M" << endl;
	cout << "		M   M   M" << endl;
	cout << "		M       M" << endl;
	cout << "		M       M" << endl;
	cout << "		M       M" << endl << endl;
	cout << "Uwaga: punktem poczatkowym jest gwiazdka." << endl << endl;
	cout << "Program umozliwia:" << endl;
	cout << "-wybor znaku kodu ASCII;"<<endl;
	cout << "-wczytanie poczatkowych rozmiarow figury;"<<endl;
	cout << "-przesuwanie figury strzalkami;" << endl;
	cout << "-powiekszanie oraz zmniejszanie rozmiaru figury za pomoca klawiszy + i - ;" << endl;
	cout << "-ograniczenie przesuwania i rozmiarow figury do obszaru ekranu;" << endl << endl;
	cout << "nacisnij dowolny klawisz aby kontynuowac" << endl;

}

char czytajZnak()
{
	char znak;
	cout << "Podaj znak typu ASCII, a wypisze figure: ";
	cin >> znak;
	cout << "Wartosc tego znaku w kodzie ASCII wynosi: " << (int)znak << endl << endl;
	cin.clear(); // usun pozostale znaki jesli uzytkownik poda³ wiecej niz jeden
	std::cin.ignore(256, '\n');
	return znak;
}

void czytajRozmiar(int &szerokosc, int &wysokosc)
{
	bool czytajPonownie = false;
	do
	{
		czytajPonownie = false;
		cout << "podaj szerokosc figury w zakresie 4-79: ";
		cin >> szerokosc;

		if (!cin || szerokosc > SZER_MAX || szerokosc < SZER_MIN)
		{
			
			cout << "bledny zakres wartosci" << endl;
			cin.clear();
			std::cin.ignore(256, '\n');
			czytajPonownie = true;
		}
	} while (czytajPonownie);

	do
	{
		czytajPonownie = false;
		cout << "podaj wysokosc figury w zakresie 4-24: ";
		cin >> wysokosc;
		if (!cin || wysokosc > WYS_MAX || wysokosc < WYS_MIN)
		{
			cout << "bledny zakres wartosci" << endl;
			cin.clear();
			std::cin.ignore(256, '\n');
			czytajPonownie = true;
		}
	} while (czytajPonownie);
}

void rysuj(char znak, int szerokosc, int wysokosc, int Xstart, int Ystart)
{
	int i;
	for (i = 1; i < (wysokosc+Ystart); i++)		//obszar rysowania, zakres wierszy
	{
		int j;
		for (j = 1; j < (szerokosc + Xstart);j++)		//obszar rysowania, zakres kolumn 
		{
			if(i >= Ystart && i<(wysokosc + Ystart) && j==Xstart) 	// linia pionowa lewa
			{
				cout << znak;
			}
			else
			{
				if (i >= Ystart && i < (wysokosc + Ystart) && j == (szerokosc + Xstart) - 1)		// linia pionowa prawa
				{
					cout << znak;
				}
				else
				{
					if (i >= Ystart && j>=Xstart && j < (szerokosc/2 + Xstart) &&  i-Ystart == (int)( ((double)wysokosc/(double)szerokosc) *(j - Xstart))) //linia ukoœna w dó³
					{
						cout << znak;
					}
					else
					{
						if (i >= Ystart &&  j>= (szerokosc / 2 + Xstart) && 
							i - Ystart == (int)(((double)wysokosc / (double)szerokosc)*(szerokosc -j + Xstart - 1)))		//linia ukoœna w górê
						{
							cout << znak;
						}
							else
							{
								cout << ' ';
							}
					}
				}
			}
		}
		cout << endl;
	}
}

void akcja(int &szerokosc, int &wysokosc, int &Xstart, int &Ystart)
{
	int pobranieZnaku = _getch();
		switch (pobranieZnaku)
		{
		case 224:
		{
			pobranieZnaku = _getch();
			switch (pobranieZnaku)
			{
			case 75:
			{
				if(Xstart >= 2)
				{
					Xstart--;	// strza³ka w lewo, przesuniêcie
				}
				break;
			}
			case 72:
			{
				if (Ystart >= 2)
				{
					Ystart--;	//strza³ka w górê, przesuniêcie
				}
				break;
			}
			case 77:
			{
				if (Xstart <= (SZER_MAX- szerokosc))
				{
					Xstart++;	//strza³ka w prawo, przesuniêcie
				}
				break;
			}
			case 80:
			{
				if (Ystart <= (WYS_MAX - wysokosc))
				{
					Ystart++;	//strza³ka w dó³, przesuniêcie
				}
				break;
			}
			break;
			}
			break;
		}
		case 43:	//'+', powiêkszenie
		{
			if (Xstart > 1 && Ystart <= (WYS_MAX - wysokosc))
			{
				szerokosc++;
				wysokosc++;
				Xstart--; //bo prawy gory naroznik ma zostac w tym samym punkcie
			}
			break;
		}
		case 45:	//'-', pomniejszenie
		{
			if (szerokosc > 4 && wysokosc > 4)
			{
				szerokosc--;
				wysokosc--;
				Xstart++; //bo prawy gory naroznik ma zostac w tym samym punkcie
			}
			break;
		}
		}
}

//int main() {
//	unsigned char ascii;
//	int numer;
//	cout << "Podaj znak typu ASCII: ";
//	cin >> ascii;
//	cout << "Wartosc tego znaku wynosi: " << (unsigned int)ascii << endl;
//	cout << "Podaj numer znaku ASCII od 33-255: ";
//	cin >> numer;
//	cout << "Znak typu ASCII odpowiadajacy numerowi " << numer << " to " << (unsigned char)numer;
//	_getch();
//	return 0;
//}

//void rysowanieFigury(char znak, int szerokosc, int wysokosc)
//{
//	int i;
//	for (i = 0; i < wysokosc; i++)
//	{
//		int j;
//		for (j = 0; j < szerokosc;j++)
//		{
//			cout << znak;
//		}
//		cout << endl;
//	}
//}

//void rysowanieFigury2(char znak, int Xstart, int Ystart)
//{
//	int i;
//	for (i = 0; i < Ystart; i++)
//	{
//		int j;
//		for (j = 0; j < Xstart;j++)
//		{
//			if(j==Xstart-1 && i==Ystart-1 )
//			{
//				cout << znak;
//			}
//			else
//			{
//				cout << " ";
//			}
//		}
//		cout << endl;
//	}
//}

//void rysowanieFigury2(char znak, int szerokosc, int wysokosc, int Xstart, int Ystart)
//{
//	int i;
//	for (i = 1; i <= wysokosc; i++)
//	{
//		int j;
//		for (j = 1; j <= szerokosc;j++)
//		{
//			if (j == Xstart && i == Ystart)
//			{
//				cout << znak;
//			}
//			else
//			{
//				cout << " ";
//			}
//		}
//		cout << endl;
//	}
//}

