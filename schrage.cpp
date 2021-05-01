#include <iostream>
#include <fstream>

using namespace std;

int cmax(int n, int*R, int*P, int *Q, int *X)
{
    int m=0,c=0; // m - moment do ktorego pracuje maszyna, c - moment do ktorego siega najdluzszy ogonek q

    for(int i=0;i<n;i++){
        m = max(m,R[X[i]])+P[X[i]];
        c = max(c,m+Q[X[i]]);
    }
    return c;
}

void Schrage(int n,int*R,int*P,int*Q,int*X) // dane wejsciowe, X - proponowana kolejnosc
{
    int A[100],K[100]; // A - zbior zadan posortowanych po r, z ktorego bedziemy przenosic do kolejki K
    int a=n,k=0,x=0,t=0; // a,k - liczba zadan w A i K; x - l. uszeregowanych zadan; t- aktualny moment
    for(int i=0;i<n;i++) A[i]=i; // przypisanie kolejnosci 0,1,2,3...
    for(int i=0; i<(n-1); i++) // sortowanie malejaco po r
        for(int j=0; j<(n-1); j++)
            if( R[A[j]] < R[A[j+1]] )
                swap(A[j], A[j+1]);
    while(x!=n) // jesli jeszcze nie zakonczono szeregowania
    {
        if(a!=0){ // jesli zbior zadan jest niepusty
            if(R[A[a-1]]<=t) // jesli zadania dojechaly
            {
                K[k]=A[a-1]; // dodajemy do kolejki zadania gotowe do realizacji
                k++; a--; // aktualizacja liczby zadan w kolejce i niedojechanych
                for(int e=k-1;e>0;e--){ // wstawienie nowego zadania na odpowiednie miejsce w kolejce (wg q)
                    if( Q[K[e]] < Q[K[e-1]] )
                        swap(K[e], K[e-1]);
                }
                continue; // powrot do poczatku petli while - sprawdzenie czy nastepne zadanie tez jest gotowe
            }
        }
        if(k!=0) // jesli sa zadania w kolejce
        {
            X[x]=K[k-1]; // przypisanie do kolejnosci zadania z kolejki o najwiekszym q
            k--; x++; // zaktualizowanie liczby zadan uszeregowanych i w kolejce
            t=t+P[X[x-1]]; // aktualizacja aktualnego momentu
            continue;
        }
        if(0==k && R[A[a-1]]>t){ // jesli nie ma zadan w kolejce ani dojechanych to posuwamy czas
            t=R[A[a-1]];
        }
    }
}

int Schrage_zPodzialem(int n,int*R,int*P,int*Q,int*X)
{
    int A[100],K[100];
    int a=n,k=0,x=0,t=0,p=0,l=-1,cmaks=0; // p - czas wykonywania zadania przed przerwaniem; l - wykonywane zadanie
    for(int i=0;i<n;i++) A[i]=i;
    for(int i=0;i<(n-1);i++) for(int j=0;j<(n-1);j++) if(R[A[j]]<R[A[j+1]]) swap(A[j],A[j+1]); // sort r
    while(a!=0 || k!=0){ // kiedy sa jeszcze zadania niedojechane lub w kolejce
  //      cout << "cmaks: " << cmaks << endl;
   //     cout << "t: " << t << endl;
        if(a!=0){
            if(R[A[a-1]]<=t){
                K[k]=A[a-1];
                k++; a--;
                for(int e=k-1;e>0;e--){
                    if( Q[K[e]] < Q[K[e-1]] )
                        swap(K[e], K[e-1]);
                }
                if( l!=-1 && Q[K[k-1]] > Q[l] ) // sprawdzamy czy robimy przerwanie
                {
                    K[k]=l;
                    k++;
                    swap(K[k-1],K[k-2]);
               //     P[K[k-2]] = P[K[k-2]] - p;
                    l=-1;
                }
                continue;
            }
        }
        if(k!=0)
        {
            l=K[k-1];
       //     X[x]=K[k-1];
            k--; x++;
            if(a!=0) {p = min( P[l], R[a-1]-t ); cout << "t: " << t << " a: " <<a<< " R[a-1]: "<<R[a-1] <<endl;}
            else p=P[l];
            t = t + p; // leci czas
            P[l] = P[l] - p;
            if(0==P[l]){
                l=-1;
                cmaks=max(cmaks,t+Q[l]);
            }
            continue;
        }
        if(0==k && a!=0)
            if(R[A[a-1]]>t)
                t=R[A[a-1]];

    }
    return cmaks;
}


int main()
{
    int n,R[100],P[100],Q[100],X[100];

    ifstream plik("data.txt");
    string s; while(s!="data.000:") plik>>s;
    plik >> n;
    for(int i=0;i<n;i++)
        plik >> R[i] >> P[i] >> Q[i];
    plik.close();

   /* Schrage(n,R,P,Q,X);
    cout << "\nKolejnosc:\n"; for(int i=0;i<n;i++) cout << X[i]+1 << " ";
    cout << "\nCmax: " << cmax(n,R,P,Q,X) << endl << endl;*/

 //   cout << "schrpmtn = " << Schrage_zPodzialem(n,R,P,Q,X) << endl;
    Schrage_zPodzialem(n,R,P,Q,X);

    cin.get();

    return 0;
}
