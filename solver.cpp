#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void Print(vector<vector<ll> > A){

  for(ll i=1; i<=9; i++){
    for(ll j=1; j<=9; j++)
      cout << A[i][j] << ' ';
    cout << "\n";
  }

  ll a;
  cin >> a;
  exit(0);
}

bool Pr(vector<vector<ll> > B){         //проверка на противоречие введенных данных

    for(ll i=1; i<=9; i++){
        vector<ll> V(10, 0);
        for(ll j=1; j<=9; j++)
            if (B[i][j] > 0)
                if (V[B[i][j]] > 0) return 1;
                else V[B[i][j]] = 1;
    }

    for(ll i=1; i<=9; i++){
        vector<ll> V(10, 0);
        for(ll j=1; j<=9; j++)
            if (B[j][i] > 0)
                if (V[B[j][i]] > 0) return 1;
                else V[B[j][i]] = 1;
    }

    for(ll i=1; i<=9; i+=3)
        for(ll j=1; j<=9; j+=3){
            vector<ll> V(10, 0);
            for(ll a=i; a<i+3; a++)
                for(ll b=j; b<j+3; b++)
                    if (B[a][b] > 0)
                        if (V[B[a][b]] > 0) return 1;
                        else V[B[a][b]] = 1;
        }

    return 0;
}

void F(vector<vector<vector<ll> > > A, vector<vector<ll> > B){
  if (Pr(B)) return;

  ll ans = 0;

  for(ll i=1; i<=9; i++)
    for(ll j=1; j<=9; j++)
        if (B[i][j] == 0) ans++;
  if (ans == 0) Print(B);

  // обработка горизонталей и вертикалей

  for(ll i=1; i<=9; i++)
    for(ll j=1; j<=9; j++){
      ll p = B[i][j];
      if (p)
        for(ll ii=1; ii<=9; ii++){
          A[ii][j][p] = 0;
          A[i][ii][p] = 0;
        }
    }

  // обработка квадратиков

  for(ll i=1; i<=9; i+=3)
    for(ll j=1; j<=9; j+=3){
        vector<ll> V(10, 0);
        for(ll a=i; a<i+3; a++)
            for(ll b=j; b<j+3; b++)
                if (B[a][b])
                    V[B[a][b]] = 1;
        for(ll a=i; a<i+3; a++)
            for(ll b=j; b<j+3; b++)
                for(ll k=1; k<=9; k++)
                    if (V[k] == 1)
                        A[a][b][k] = 0;
    }

  ll m = 10, a, b;

  for(ll i=1; i<=9; i++)  // выбираем оптимальный элемент
    for(ll j=1; j<=9; j++){
      ll siz = 0;
      for(ll k=1; k<=9; k++)
        if (A[i][j][k] == 1) siz++;

      if (B[i][j] == 0 && siz < m && siz != 0) {
        m = siz;
        a = i;
        b = j;
      }
    }

  if (m == 10 || m == 0) return;

  for(ll i=1; i<=9; i++)
    if (A[a][b][i] == 1){
        B[a][b] = i;
        F(A, B);
        B[a][b] = 0;
    }
}

int main(){
  vector<vector<ll> > B (10, vector<ll> (10,0));
  vector<vector<vector<ll> > > A (10, vector<vector<ll> > (10, vector<ll> (10,1)));

  for(ll i=1; i<=9; i++)
    for(ll j=1; j<=9; j++)
      cin >> B[i][j];

  F(A, B);
}
