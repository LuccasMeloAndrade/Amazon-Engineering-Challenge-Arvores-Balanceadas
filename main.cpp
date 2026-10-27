#include <iostream>
#include <string>
#include "avltree.hpp"
#include "rubronegro.hpp"
#include "testeautomatizado.hpp"

template <typename TipoArvore>
void executarMenuInterativo(TipoArvore& arvore, const std::string& nomeArvore) {
    int opcao;
    do {
        std::cout << "\n--- Menu " << nomeArvore << " ---\n";
        std::cout << "1. Inserir Pacote (ID)\n";
        std::cout << "2. Remover Pacote (ID)\n";
        std::cout << "3. Buscar Pacote (ID)\n";
        std::cout << "4. Percurso Em Ordem\n";
        std::cout << "5. Visualizar Árvore\n";
        std::cout << "6. Exibir Métricas (Altura e Rotações)\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        int id;
        switch (opcao) {
            case 1:
                std::cout << "Digite o ID do pacote: ";
                std::cin >> id;
                if (arvore.inserir(id)) {
                    std::cout << "-> Sucesso: Pacote " << id << " inserido.\n";
                } else {
                    std::cout << "-> Erro: Pacote " << id << " já existe na árvore!\n";
                }
                break;
            case 2:
                std::cout << "Digite o ID a remover: ";
                std::cin >> id;
                if (arvore.remover(id)) {
                    std::cout << "-> Sucesso: Pacote " << id << " removido.\n";
                } else {
                    std::cout << "-> Erro: Pacote " << id << " não encontrado!\n";
                }
                break;
            case 3:
                std::cout << "Digite o ID a buscar: ";
                std::cin >> id;
                if (arvore.buscar(id)) {
                    std::cout << "-> Pacote " << id << " ENCONTRADO no sistema.\n";
                } else {
                    std::cout << "-> Pacote " << id << " NÃO ENCONTRADO.\n";
                }
                break;
            case 4:
                std::cout << "Pacotes Cadastrados (Em Ordem): ";
                arvore.emOrdem();
                break;
            case 5:
                std::cout << "\nEstrutura Atual da Árvore:\n";
                arvore.imprimirArvore();
                break;
            case 6:
                std::cout << "Altura Atual: " << arvore.obterAltura() << "\n";
                std::cout << "Total de Rotações Realizadas: " << arvore.obterContadorRotacoes() << "\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}

int main() {
    int opcaoPrincipal;
    ArvoreAVL<int> arvoreAVL;
    ArvoreRubroNegra<int> arvoreRubroNegra;

    do {
        std::cout << "\n======================================================\n";
        std::cout << "    AMAZON LOGISTICS - SYSTEM PACKAGE TRACKING       \n";
        std::cout << "======================================================\n";
        std::cout << "1. Operar com Árvore AVL\n";
        std::cout << "2. Operar com Árvore Rubro-Negra\n";
        std::cout << "3. Executar Bateria de Testes Comparativos Automatizados\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcaoPrincipal;

        switch (opcaoPrincipal) {
            case 1:
                executarMenuInterativo(arvoreAVL, "Árvore AVL");
                break;
            case 2:
                executarMenuInterativo(arvoreRubroNegra, "Árvore Rubro-Negra");
                break;
            case 3:
                executarTestesComparativos();
                break;
            case 0:
                std::cout << "Encerrando o sistema...\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
    } while (opcaoPrincipal != 0);

    return 0;
}