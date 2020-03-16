#include<iostream>
#include<cstdlib>
#include"GrafNeorientat.h"
using namespace std;

Node* Graph::insertEdge(int x, int y, Node* head) {
    /* -adauga nodul y in lista de adiacenta a nodului x
     - inserarea se face la inceput*/
    Node* elem = new Node;
    elem->setVal(y);
    elem->setNext(head);
    return elem;
}

Graph::Graph() {
    // constructor de initializare
    V = 0;
    g = NULL;
}

Graph::Graph(int nrv, Edge v[], int vcomp) {
    // constructor de initializare
    // initializeaza graful cu lista muchiilor v[]
    int i, x1, x2;
    V = nrv;
    g = new Node*[nrv + 1];
    for(i = 0; i <= nrv; ++i)
        g[i] = NULL;

    for(i = 0; i < vcomp; i++) {
        try {
            x1 = v[i].getX();
            x2 = v[i].getY();
            if(x1 <= 0 || x1 > V || x2 <= 0 || x2 > V)
                throw("Ati introdus o muchie invalida");
        } catch(const char * s) {
            cout << s << "\n";
            exit(1);
        }
        Node* newNode = insertEdge(x1, x2, g[x1]);
        g[x1] = newNode;
        newNode = insertEdge(x2, x1, g[x2]);
        g[x2] = newNode;
    }
}

Graph::Graph(const Graph& a) {
    // constructor de copiere
    Node* p;
    Node* newNode;
    int i;
    V = a.V;
    g = new Node*[V + 1]; // aloc memorie
    for(i = 0; i <= V; ++i)
        g[i] = NULL; // initializez listele de adiacenta cu NULL
    for(i = 1; i <= V; ++i) {
        p = a.g[i]; // parcurg fiecare lista de adiacenta
        while(p != NULL) {
            newNode = insertEdge(i, p->getVal(), g[i]);
            g[i] = newNode;
            p = p->getNext();
        }
    }
}

Graph::~Graph() {
    // destructor
    for(int i = 0; i <= V; ++i) {
        delete[] g[i];
    }
    delete[] g;
}

istream & operator>>(istream & in, Graph & G) {
    /* Pe prima linie se vor afla numarul de noduri si numarul de muchii
    Pe urmatoarele m linii se afla lista muchiilor */
    int edges, a, b, i;
    Node* newNode;
    in >> G.V >> edges;
    G.g = new Node*[G.V + 1];
    for(i = 0; i <= G.V; ++i)
        G.g[i] = NULL;
    for(i = 1; i <= edges; ++i) {
        try {
            in >> a >> b; // citim o muchie
            if(a <= 0 || a > G.V || b <= 0 || b > G.V)
                throw("Ati introdus o muchie invalida");
        } catch(const char * s) {
            cout << s << "\n";
            exit(1);
        }
        newNode = G.insertEdge(a, b, G.g[a]);
        G.g[a] = newNode;
        newNode = G.insertEdge(b, a, G.g[b]);
        G.g[b] = newNode;
    }
    return in;
}

ostream & operator<<(ostream &out, const Graph &G) {
    // supraincarc operatorul << pentru afisarea grafului
    bool used[G.V + 1];
    int i, j;
    Node* p;
    out << "Reprezentarea prin liste de adiacenta este : \n";
    for(i = 1; i <= G.V; ++i) {
        out << i << " : ";
        p = G.g[i];
        while(p != NULL) {
            out << p->getVal() << " ";
            p = p->getNext();
        }
        out << "\n";
    }
    out << "\nReprezentarea prin matricea de adiacenta este : \n";
    for(i = 1; i <= G.V; ++i) {
        for(j = 1; j <= G.V; ++j)
            used[j] = 0;
        p = G.g[i];
        while(p != NULL) {
            used[p->getVal()] = 1;
            p = p->getNext();
        }
        for(j = 1; j <= G.V; ++j)
            out << used[j] << " ";
        out << "\n";
    }
    out << "\n";
    return out;
}

void Graph::BFS(int source, bool verif) const {
    // parcurgerea in latime a grafului
    // parametrul verif ne spune daca trebuie sa verificam conexitatea grafului
    bool ok;
    try {
        ok = ((source > 0 && source <= V)? true : false);
        if(!ok)
            throw("Apelati parcurgerea BFS dintr-un nod invalid!");
    } catch(const char * s) {
        cout << s << "\n";
        exit(1);
    }
    Node* p;
    int prim, ultim, i, node;
    int q[V + 1], dist[V + 1];
    for(i = 1; i <= V; i++)
        dist[i] = -1; // initial, toate nodurile sunt nevizitate
    dist[source] = 0; // setez distanta pana la nodul sursa, adica 0
    prim = ultim = 0;
    q[prim] = source; // adaug nodul de start in coada
    if(!verif)
        cout << "Parcurgerea in latime a grafului este : ";
    while(prim <= ultim) {
        node = q[prim++]; // extrag un nod din coada
        if(!verif)
            cout << node << " ";
        p = g[node]; // urmeaza sa-i parcurg vecinii
        while(p != NULL) {
            if(dist[p->getVal()] == -1) { // vecin nevizitat
                dist[p->getVal()] = 1 + dist[node]; // actualizez distanta pana la el
                q[++ultim] = p->getVal(); // adaug nodul in coada
            }
            p = p->getNext(); // trec la urmatorul vecin
        }
    }
    if(!verif) {
        cout << "\nVectorul de distante minime ( ca nr de muchii ) este : ";
        for(i = 1; i <= V; i++)
            cout << dist[i] << " ";
    } else {
        bool conex = true;
        for(i = 1; i <= V && conex; ++i)
            if(dist[i] == -1) // daca un nod este inaccesibil din oricare altul, graful nu e conex
                conex = false;
        if(conex)
            cout << "Graful este conex\n";
        else cout << "Graful nu este conex\n";
    }
    cout << "\n";
}

void Graph::DFSutil(int node, bool used[], bool afis, Node** a) const {
    // parcurgerea in adancime a grafului
    // functia este folosita in 2 scopuri :
    // pentru parcurgerea efectiva, dar si pentru determinarea componentelor conexe
    Node* p;
    used[node] = 1;
    if(afis) // afisam efectiv nodul din parcurgere
        cout << node << " ";
    else { // doar memoram nodul intr-o lista ( pentru componentele conexe )
        Node* x = new Node;
        x->setVal(node);
        x->setNext(*a);
        *a = x;
    }
    p = g[node]; // iterez prin toti vecinii nodului
    while(p != NULL) {
        if(!used[p->getVal()]) // daca nodul e nevizitat, apelam functia DFSutil()
            DFSutil(p->getVal(), used, afis, a);
        p = p->getNext();
    }
}

void Graph::DFS(int node) const {
    bool ok;
    try {
        ok = ((node > 0 && node <= V)? true : false);
        if(!ok)
            throw("Apelati parcurgerea DFS dintr-un nod invalid!");
    } catch(const char * s) {
        cout << s << "\n";
        exit(1);
    }
    bool used[V];
    for(int i = 1; i <= V; ++i)
        used[i] = 0;
    cout << "\nParcurgerea in adancime a grafului este : ";
    DFSutil(node, used);
    cout << "\n";
}

void Graph::compConexe() const {
    // functia determina componentele conexe ale grafului
    // acestea vor fi retinute in vectorul de liste comp
    // cand apelam functia DFSutil, ii trimitem si adresa campului in care urmeaza sa inseram
    Node* p;
    int i, cnt;
    bool used[V + 1];
    Node* comp[V + 1]; // graful poate avea cel mult V componente conexe
    for(i = 0; i <= V; ++i) {
        used[i] = 0;
        comp[i] = NULL;
    }
    cnt = 0;
    for(i = 1; i <= V; ++i) {
        if(!used[i]) {
            DFSutil(i, used, 0, &comp[cnt]);
            ++cnt;
        }
    }
    cout << "\nGraful are " << cnt << " componente conexe\n";
    for(i = 0; i < cnt; ++i) {
        cout << "Componenta conexa " << 1 + i << " : ";
        p = comp[i];
        while(p != NULL) {
            cout << p->getVal() << " ";
            p = p->getNext();
        }
        cout << "\n";
    }
}

void Graph::matriceaDrumurilor() const {
    bool used[V + 1];
    Node* p;
    int i, j;
    cout << "\nMatricea drumurilor este : \n";
    for(i = 1; i <= V; ++i) {
        for(j = 1; j <= V; ++j)
            used[j] = 0;
        p = g[i];
        while(p != NULL) {
            used[p->getVal()] = 1;
            p = p->getNext();
        }
        for(j = 1; j <= V; ++j)
            cout << used[j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void Graph::esteConex(int source) const {
    // folosim parcurgerea in latime pentru a verifica daca graful este conex
    // parametrul verif va fi true de data aceasta
    BFS(source, true);
}

const Graph Graph::operator+(const Graph& G) const {
    bool ok;
    try {
        ok = (V == G.V? true : false);
        if(!ok)
            throw("Cele doua grafuri nu au acelasi numar de noduri");
    } catch(const char * s) {
        cout << s << "\n";
        exit(1);
    }
    cout << "Graful reuniunii muchiilor celor 2 grafuri este :\n";
    Node* p, *newNode, *l;
    Graph temp;
    bool gasit;
    temp.V = G.V;
    temp.g = new Node*[G.V + 1];
    for(int i = 0; i <= temp.V; ++i)
        temp.g[i] = NULL;
    // copiem obiectul curent in temp
    for(int i = 1; i <= V; ++i) {
        p = g[i];
        while(p != NULL) {
            newNode = temp.insertEdge(i, p->getVal(), temp.g[i]);
            temp.g[i] = newNode;
            p = p->getNext();
        }
    }
    // parcurg listele de adiacente ale celui de-al doilea graf si adaug muchii daca este cazul
    for(int i = 1; i <= temp.V; ++i) {
        p = G.g[i];
        while(p != NULL) {
            l = temp.g[i];
            gasit = false;
            while(l != NULL && !gasit) {
                if(p->getVal() == l->getVal())
                    gasit = true;
                else l = l->getNext();
            }
            if(!gasit) {
                newNode = temp.insertEdge(i, p->getVal(), temp.g[i]);
                temp.g[i] = newNode;
            }
            p = p->getNext();
        }
    }
    return temp;
}

void Graph::citireNobiecte(int n, vector<Graph>& v) {
    // Aceasta este cerinta comuna tuturor temelor
    for(int i = 0; i < n; ++i) {
        cout << "Introduceti datele pentru graful " << 1 + i << "\n";
        Graph P;
        cin >> P;
        v.push_back(P);
    }
    vector<Graph>::iterator it;
    int cnt = 1;
    for(it = v.begin(); it != v.end(); ++it) {
        cout << "Graful " << cnt << "\n";
        cout << *it;
        ++cnt;
    }
}
