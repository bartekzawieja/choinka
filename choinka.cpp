#include <iostream>
#include <vector>

using namespace std;

enum TYP {
    PYT, ZAM
};

struct KROTKA {
    TYP typ;
    int x;
    int y;
};

struct Kolorowanie{
    long long kolorA;
    long long kolorB;
    long long liczbaA;

    Kolorowanie() {
      kolorA = 0,
      kolorB = 0,
      liczbaA = 0;
    }

    Kolorowanie(long long _kolorA, long long _kolorB, long long _liczbaA) {
      kolorA = _kolorA,
      kolorB = _kolorB,
      liczbaA = _liczbaA;
    }
};

vector<vector<long long>> tablica2d;
vector<long long> preorder;
vector<long long> kolejnosc;
vector<long long> koniecPoddrzewa;


vector<KROTKA> zapytania;


long long liczbaLisci = 1;
long long lewyCel;
long long prawyCel;


void zmienKolor(Kolorowanie drzewo[], long long lisc, const long long k) {
  lisc = lisc + liczbaLisci;
  drzewo[lisc] = {k, 0, 1};
  while (lisc > 1) {
    lisc = lisc/2;

    if(drzewo[lisc*2].kolorA == -1 || drzewo[lisc*2 + 1].kolorA == -1) {
      drzewo[lisc] = {-1, -1, -1};
      continue;
    } else if(drzewo[lisc*2].kolorA == 0) {
    drzewo[lisc] = drzewo[lisc*2 + 1];
    continue;
    } else if(drzewo[lisc*2 + 1].kolorA == 0) {
      drzewo[lisc] = drzewo[lisc*2];
      continue;
    }
    
    if(drzewo[lisc*2].kolorA == drzewo[lisc*2 + 1].kolorA){

    if(drzewo[lisc*2 + 1].kolorB == 0) {
      drzewo[lisc] = {drzewo[lisc*2].kolorA, drzewo[lisc*2].kolorB, drzewo[lisc*2].liczbaA + drzewo[lisc*2 + 1].liczbaA};
      continue;
    } else if(drzewo[lisc*2].kolorB == 0) {
      drzewo[lisc] = {drzewo[lisc*2].kolorA, drzewo[lisc*2 + 1].kolorB, drzewo[lisc*2].liczbaA + drzewo[lisc*2 + 1].liczbaA};
      continue;
    } else {
      drzewo[lisc] = {-1, -1, -1};
      continue;
    }

  } else {

    if(drzewo[lisc*2].kolorA == drzewo[lisc*2 + 1].kolorB){
      if(drzewo[lisc*2].kolorB == 0 && drzewo[lisc*2 + 1].liczbaA == 1) {
        drzewo[lisc] = {drzewo[lisc*2].kolorA, drzewo[lisc*2 + 1].kolorA, drzewo[lisc*2].liczbaA + 1};
        continue;
      } else {
        drzewo[lisc] = {-1, -1, -1};
        continue;
      }
    }
    if(drzewo[lisc*2].kolorB == drzewo[lisc*2 + 1].kolorA){
      if(drzewo[lisc*2 + 1].kolorB == 0 && drzewo[lisc*2].liczbaA == 1) {
        drzewo[lisc] = {drzewo[lisc*2 + 1].kolorA, drzewo[lisc*2].kolorA, drzewo[lisc*2 + 1].liczbaA + 1};
        continue;
      } else {
        drzewo[lisc] = {-1, -1, -1};
        continue;
      }
    }
    if(drzewo[lisc*2].kolorB == 0 && drzewo[lisc*2 + 1].kolorB == 0){
      if(drzewo[lisc*2].liczbaA == 1) {
        drzewo[lisc] = {drzewo[lisc*2 + 1].kolorA, drzewo[lisc*2].kolorA, drzewo[lisc*2 + 1].liczbaA};
        continue;
      } else if(drzewo[lisc*2 + 1].liczbaA == 1) {
        drzewo[lisc] = {drzewo[lisc*2].kolorA, drzewo[lisc*2 + 1].kolorA, drzewo[lisc*2].liczbaA};
        continue;
      }else {
        drzewo[lisc] = {-1, -1, -1};
        continue;
      }
    }

    drzewo[lisc] = {-1, -1, -1};
    continue;
  }
  }
}

Kolorowanie sprawdzKolor(Kolorowanie drzewo[], const  long long lewy,  const long long prawy, const long long i) {
  if (prawy <= prawyCel && lewyCel <= lewy) {
    return drzewo[i];
  }
  long long nowyPrawy = (lewy + prawy) / 2;
  long long nowyLewy = nowyPrawy + 1;
  if (lewyCel <= nowyPrawy && nowyLewy <= prawyCel) {

  Kolorowanie x = sprawdzKolor(drzewo, lewy, nowyPrawy, i*2);
  Kolorowanie y = sprawdzKolor(drzewo, nowyLewy, prawy, i*2 + 1);


  if(x.kolorA == -1 || y.kolorA == -1) {
    return {-1, -1, -1};
  } else if(x.kolorA == 0) {
    return y;
  } else if (y.kolorA == 0) {
    return x;
  }
  
  if(x.kolorA == y.kolorA){
      if(y.kolorB == 0) {
        return {x.kolorA, x.kolorB, x.liczbaA + y.liczbaA};
      } else if(x.kolorB == 0) {
        return {x.kolorA, y.kolorB, x.liczbaA + y.liczbaA};
      } else {
        return {-1, -1, -1};
      }
    } else {
      if(x.kolorA == y.kolorB){

        if(x.kolorB == 0 && y.liczbaA == 1) {
          return {x.kolorA, y.kolorA, x.liczbaA + 1};
        } else {
          return {-1, -1, -1};
        }

      }
      if(x.kolorB == y.kolorA){

        if(y.kolorB == 0 && x.liczbaA == 1) {
          return {y.kolorA, x.kolorA, y.liczbaA + 1};
        } else {
          return {-1, -1, -1};
        }
      }
      if(x.kolorB == 0 && y.kolorB == 0){
        if(x.liczbaA == 1) {
          return {y.kolorA, x.kolorA, y.liczbaA};
        } else if (y.liczbaA == 1) {
          return {x.kolorA, y.kolorA, x.liczbaA};
        } else {
          return {-1, -1, -1};
        }
      }

      return {-1, -1, -1};
    }
  }
    if (lewyCel <= nowyPrawy) {
      return sprawdzKolor(drzewo, lewy, nowyPrawy, i*2);
    }
    else {
      return sprawdzKolor(drzewo, nowyLewy, prawy, i*2 + 1);
    }
  }

long long inicjalizuj(long long aktualny) {
  kolejnosc[aktualny] = preorder.size();
  preorder.push_back(aktualny);

  if (tablica2d[aktualny].empty()) {
    koniecPoddrzewa[kolejnosc[aktualny]] = preorder.size() - 1;
  } else {
    for (long long i = 0; i < tablica2d[aktualny].size(); i ++) {
      koniecPoddrzewa[kolejnosc[aktualny]] = inicjalizuj(tablica2d[aktualny][i]);
    }
  }
  return koniecPoddrzewa[kolejnosc[aktualny]];
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  long long n;
  cin >> n;

  long long q;
  cin >> q;

  tablica2d = vector<vector<long long>>(n);

  kolejnosc = vector<long long>(n);

  koniecPoddrzewa = vector<long long>(n);

  for (int i = 1; i < n; i++) {
    long long pom;
    cin >> pom;
    tablica2d[pom - 1].push_back(i); //ładujemy 1 wiersz input -> ojców cofniętych o 1
  }

  inicjalizuj(0); //dla takich

  while (liczbaLisci < n) {
    liczbaLisci = liczbaLisci*2;
  }

  Kolorowanie drzewo[liczbaLisci*2];

  for (long long i = 0; i < n; i++) {
    long long pom;
    cin >> pom; //ładujemy drugi wiersz inputu - kolory
    zmienKolor(drzewo, kolejnosc[i], pom);
  }


   //ładowanie zapytań -> OD INDEKSU 0:
    for(int i=0; i<q; i++) {
        char pom;
        int _x;
        int _y;
        KROTKA zapytanie = {PYT, 0, 0};
        cin>>pom;
        if(pom == '?') {
            zapytanie.typ = PYT;
            cin>>_x;
            zapytanie.x = _x;
            zapytanie.y = -1;
        } else {
            zapytanie.typ = ZAM;
            cin>>_x;
            cin>>_y;
            zapytanie.x = _x;
            zapytanie.y = _y;
        }
        zapytania.push_back(zapytanie);
    }

    for(int i=0; i<q; i++) {
        if(zapytania[i].typ == PYT) {
          lewyCel = kolejnosc[zapytania[i].x - 1];
          prawyCel = koniecPoddrzewa[kolejnosc[zapytania[i].x - 1]];
          if ((sprawdzKolor(drzewo, 0, liczbaLisci - 1, 1)).kolorA != -1)
            cout << "TAK\n";
          else
            cout << "NIE\n";
        } else {
          zmienKolor(drzewo, kolejnosc[zapytania[i].x - 1], zapytania[i].y );
        }

    }

  return 0;
}