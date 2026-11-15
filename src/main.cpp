#include <iostream>
#include <string>
#include <vector>

#include "BST.h"
#include "DFS.h"

using namespace std;

namespace {

void printVec(const string& label, const vector<int>& v) {
    cout << label;
    for (size_t i = 0; i < v.size(); ++i) {
        cout << (i ? " " : "") << v[i];
    }
    cout << "\n";
}

void printPath(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << (i ? " -> " : "") << path[i];
    }
}

void section(const string& title) {
    cout << "\n==================================================\n"
         << title
         << "\n==================================================\n";
}

void testPathSum(Node* root, int K) {
    vector<int> path;
    cout << "K = " << K << ": ";
    if (findPathWithSum(root, K, path)) {
        cout << "SI existe -> ";
        printPath(path);
        long long s = 0;
        for (int x : path) s += x;
        cout << "  (suma = " << s << ")\n";
    } else {
        cout << "NO existe camino raiz-hoja con esa suma\n";
    }
}

}

int main() {
    vector<int> sorted;
    for (int i = 1; i <= 20; ++i) sorted.push_back(i);

    section("EJERCICIO 1: BST iterativo");
    const vector<int> data = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35,
                              45, 55, 65, 75, 90, 5, 15, 28, 42, 85};
    BST bst;
    for (int x : data) bst.insert(x);

    printVec("Insertados (20):  ", data);
    printVec("In-order:         ", bst.inorder());
    printVec("Pre-orden:        ", bst.preorder());
    cout << "Altura:           " << bst.height() << "\n";

    cout << "\nEliminar 30 (nodo con dos hijos) -> "
         << (bst.remove(30) ? "ok" : "no existe") << "\n";
    cout << "Eliminar 5  (hoja)               -> "
         << (bst.remove(5) ? "ok" : "no existe") << "\n";

    printVec("In-order (stack): ", bst.inorder());
    printVec("Pre-orden:        ", bst.preorder());
    cout << "Altura final:     " << bst.height() << "\n";

    section("EJERCICIO 1: Degradacion con datos ordenados");
    BST degenerate;
    for (int x : sorted) degenerate.insert(x);
    const long long n = static_cast<long long>(sorted.size());

    printVec("Insertados 1..20: ", sorted);
    printVec("Pre-orden:        ", degenerate.preorder());
    cout << "Altura BST (ordenado):   " << degenerate.height()
         << "   (= n = " << n << ")\n";
    cout << "Altura BST (aleatorio):  " << bst.height()
         << "   (mismo tamano aprox.)\n";
    cout << "Comparaciones insertando ordenado: " << degenerate.comparisons()
         << "   (teoria n(n-1)/2 = " << n * (n - 1) / 2 << ")\n";

    section("PROBLEMA 3: DFS iterativo - camino raiz-hoja con suma K");
    printVec("Arbol (pre-orden): ", bst.preorder());
    testPathSum(bst.root(), 50 + 35 + 20 + 10 + 15);
    testPathSum(bst.root(), 50 + 70 + 80 + 90 + 85);
    testPathSum(bst.root(), 50 + 70 + 60 + 55);
    testPathSum(bst.root(), 999);
    testPathSum(bst.root(), 50 + 35);
    testPathSum(degenerate.root(), 210);
    testPathSum(nullptr, 0);

    return 0;
}
