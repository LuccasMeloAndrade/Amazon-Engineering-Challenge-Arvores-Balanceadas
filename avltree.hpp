#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include <iostream>
#include <algorithm>
#include <string>

template <typename T>
class ArvoreAVL {
private:
    struct No {
        T dado;
        int altura;
        No* esquerda;
        No* direita;

        No(const T& valor) : dado(valor), altura(1), esquerda(nullptr), direita(nullptr) {}
    };

    No* raiz;
    size_t contadorRotacoes;

    int obterAltura(No* no) const {
        return no ? no->altura : 0;
    }

    int obterFatorBalanceamento(No* no) const {
        return no ? obterAltura(no->esquerda) - obterAltura(no->direita) : 0;
    }

    void atualizarAltura(No* no) {
        if (no) {
            no->altura = 1 + std::max(obterAltura(no->esquerda), obterAltura(no->direita));
        }
    }

    No* rotacionarDireita(No* y) {
        No* x = y->esquerda;
        No* T2 = x->direita;

        x->direita = y;
        y->esquerda = T2;

        atualizarAltura(y);
        atualizarAltura(x);

        contadorRotacoes++;
        return x;
    }

    No* rotacionarEsquerda(No* x) {
        No* y = x->direita;
        No* T2 = y->esquerda;

        y->esquerda = x;
        x->direita = T2;

        atualizarAltura(x);
        atualizarAltura(y);

        contadorRotacoes++;
        return y;
    }

    No* balancearNo(No* no) {
        atualizarAltura(no);
        int balanceamento = obterFatorBalanceamento(no);

        // Caso Esquerda-Esquerda
        if (balanceamento > 1 && obterFatorBalanceamento(no->esquerda) >= 0) {
            return rotacionarDireita(no);
        }
        // Caso Esquerda-Direita
        if (balanceamento > 1 && obterFatorBalanceamento(no->esquerda) < 0) {
            no->esquerda = rotacionarEsquerda(no->esquerda);
            return rotacionarDireita(no);
        }
        // Caso Direita-Direita
        if (balanceamento < -1 && obterFatorBalanceamento(no->direita) <= 0) {
            return rotacionarEsquerda(no);
        }
        // Caso Direita-Esquerda
        if (balanceamento < -1 && obterFatorBalanceamento(no->direita) > 0) {
            no->direita = rotacionarDireita(no->direita);
            return rotacionarEsquerda(no);
        }

        return no;
    }

    No* inserir(No* no, const T& valor, bool& inserido) {
        if (!no) {
            inserido = true;
            return new No(valor);
        }

        if (valor < no->dado) {
            no->esquerda = inserir(no->esquerda, valor, inserido);
        } else if (valor > no->dado) {
            no->direita = inserir(no->direita, valor, inserido);
        } else {
            inserido = false; // Trata tentativa de inserir elemento duplicado
            return no;
        }

        return balancearNo(no);
    }

    No* obterMenorNo(No* no) const {
        No* atual = no;
        while (atual && atual->esquerda) {
            atual = atual->esquerda;
        }
        return atual;
    }

    No* remover(No* no, const T& valor, bool& removido) {
        if (!no) {
            removido = false;
            return nullptr;
        }

        if (valor < no->dado) {
            no->esquerda = remover(no->esquerda, valor, removido);
        } else if (valor > no->dado) {
            no->direita = remover(no->direita, valor, removido);
        } else {
            removido = true;
            if (!no->esquerda || !no->direita) {
                No* temp = no->esquerda ? no->esquerda : no->direita;
                delete no;
                return temp;
            }
            No* temp = obterMenorNo(no->direita);
            no->dado = temp->dado;
            no->direita = remover(no->direita, temp->dado, removido);
        }

        return balancearNo(no);
    }

    bool buscar(No* no, const T& valor) const {
        if (!no) return false;
        if (valor == no->dado) return true;
        if (valor < no->dado) return buscar(no->esquerda, valor);
        return buscar(no->direita, valor);
    }

    void emOrdem(No* no) const {
        if (!no) return;
        emOrdem(no->esquerda);
        std::cout << no->dado << " ";
        emOrdem(no->direita);
    }

    void imprimirArvore(No* no, std::string prefixo, bool ehEsquerda) const {
        if (!no) return;
        std::cout << prefixo << (ehEsquerda ? "├── " : "└── ") << no->dado << " (h:" << no->altura << ")\n";
        imprimirArvore(no->esquerda, prefixo + (ehEsquerda ? "│   " : "    "), true);
        imprimirArvore(no->direita, prefixo + (ehEsquerda ? "│   " : "    "), false);
    }

    void limpar(No* no) {
        if (!no) return;
        limpar(no->esquerda);
        limpar(no->direita);
        delete no;
    }

public:
    ArvoreAVL() : raiz(nullptr), contadorRotacoes(0) {}
    ~ArvoreAVL() { limpar(raiz); }

    bool inserir(const T& valor) {
        bool inserido = false;
        raiz = inserir(raiz, valor, inserido);
        return inserido;
    }

    bool remover(const T& valor) {
        bool removido = false;
        raiz = remover(raiz, valor, removido);
        return removido;
    }

    bool buscar(const T& valor) const {
        return buscar(raiz, valor);
    }

    void emOrdem() const {
        emOrdem(raiz);
        std::cout << "\n";
    }

    void imprimirArvore() const {
        if (!raiz) {
            std::cout << "(Árvore Vazia)\n";
            return;
        }
        imprimirArvore(raiz, "", false);
    }

    int obterAltura() const {
        return obterAltura(raiz);
    }

    size_t obterContadorRotacoes() const {
        return contadorRotacoes;
    }

    void resetarContadorRotacoes() {
        contadorRotacoes = 0;
    }
};

#endif