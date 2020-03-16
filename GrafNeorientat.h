#include<iostream>
#include<vector>
using namespace std;

class Node {
private:
    int val;
    Node* next;
public:
    int getVal() {
        return val;
    }
    Node* getNext() {
        return next;
    }
    void setVal(int x) {
        val = x;
    }
    void setNext(Node* x) {
        next = x;
    }
};

class Edge {
// clasa folosita in constructorul de initializare
private:
    int x;
    int y;
public:
    void setX(int value) {
        x = value;
    }
    int getX() {
        return x;
    }
    void setY(int value) {
        y = value;
    }
    int getY() {
        return y;
    }
};

class Graph {
private:
    int V;
    Node** g;
public:
    static void citireNobiecte(int, vector<Graph>&); // cerinta comuna tuturor temelor
    Node* insertEdge(int, int, Node*); // functie pentru inserarea unei muchii
    Graph(); // constructor de initializare
    Graph(int, Edge e[], int); // constructor de initializare
    Graph(const Graph&); // constructor de copiere
    ~Graph(); // destructor
    friend ostream& operator<<(ostream &, const Graph&); // supraincarc <<
    friend istream& operator>>(istream &, Graph&); // supraincarc >>
    void BFS(int, bool verif = false) const; // parcurgerea in latime
    void DFS(int) const; // parcurgerea in adancime
    void DFSutil(int, bool used[], bool afis = true, Node** p = NULL) const; // parcurgerea in adancime
    void compConexe() const; // functia care determina componentele conexe ale grafului
    void matriceaDrumurilor() const; // functia care afiseaza matricea drumurilor
    void esteConex(int) const; // functia care verifica daca graful este conex
    const Graph operator+(const Graph &) const; // functia care supraincarca op. +
};
