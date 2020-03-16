/*
    BANCIU HORIA - ADRIAN
    GRUPA 132 - SEMIGRUPA 1
    TEMA 1 - POO - PROBLEMA 16 ( GRAF NEORIENTAT )
*/

#include<iostream>
#include<vector>
#include"GrafNeorientat.h"
#define MAX_EDGES 100
using namespace std;

int main() {
    /*
        Grafurile se vor citi astfel :
        numarul de varfuri   numarul de muchii ( pe prima linie )
        pe urmatoarele linii se vor afla muchiile grafului
    */
    vector<Graph> v;
    int n, len;
    cout << "Introduceti nr de grafuri care vor fi citite : ";
    cin >> n;
    Graph::citireNobiecte(n, v); // cerinta comuna tuturor temelor
    len = v.size();
    for(int i = 0; i < len; i++) {
        cout << "Graful " << 1 + i << "\n";
        v[i].BFS(1);
        v[i].DFS(1);
        v[i].compConexe();
        v[i].matriceaDrumurilor();
        v[i].esteConex(1);
    }

       //!!! Pentru testarea functiei care supraincarca operatorul +*/
        //cout << v[0] + v[1]; //unde v[0] si v[1] sunt doua obiecte de tip graf
        //Pot fi alese oricare doua obiecte din vectorul


    /*Constructorul de copiere :
    Graph A(v[0]);
    cout << A;
    */


    //Constructorul de initializare ( care primeste ca parametru si o lista de muchii )
        /*Edge e[MAX_EDGES];
        int nrv, nrm, x, y, cnt;
        cout << "Numarul de varfuri ale grafului este : \n";
        cin >> nrv;
        cout << "Introduceti numarul de muchii ale grafului : ";
        cin >> nrm;
        cnt = 0;
        for(int i = 0; i < nrm; ++i) {
            cin >> x >> y;
            e[cnt].setX(x);
            e[cnt].setY(y);
            ++cnt;
        }
        Graph B(nrv, e, nrm);
        cout << B;*/

    return 0;
}
