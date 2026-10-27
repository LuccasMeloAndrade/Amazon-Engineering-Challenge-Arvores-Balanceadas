#include "avltree.hpp"
#include "rubronegro.hpp"
#include "testeautomatizado.hpp"
#include <iostream>
#include <vector>
#include <string>

void executarTestesComparativos() {
    std::cout << "\n======================================================\n";
    std::cout << "         TESTE COMPARATIVO AUTOMATIZADO              \n";
    std::cout << "======================================================\n";

    std::vector<int> dadosCrescentes = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::vector<int> dadosDecrescentes = {100, 90, 80, 70, 60, 50, 40, 30, 20, 10};
    std::vector<int> dadosDesordenados = {50, 20, 70, 10, 30, 60, 90, 5, 15, 25};

    auto executarCenario = [](const std::string& titulo, const std::vector<int>& dados) {
        ArvoreAVL<int> avl;
        ArvoreRubroNegra<int> arn;

        for (int elemento : dados) {
            avl.inserir(elemento);
            arn.inserir(elemento);
        }

        std::cout << "\n--- Cenário: " << titulo << " ---\n";
        std::cout << "AVL         -> Altura: " << avl.obterAltura() << " | Rotações: " << avl.obterContadorRotacoes() << "\n";
        std::cout << "Rubro-Negra -> Altura: " << arn.obterAltura() << " | Rotações: " << arn.obterContadorRotacoes() << "\n";
    };

    executarCenario("Inserção Crescente (10 a 100)", dadosCrescentes);
    executarCenario("Inserção Decrescente (100 a 10)", dadosDecrescentes);
    executarCenario("Inserção Desordenada", dadosDesordenados);

    std::cout << "\n======================================================\n\n";
}