#ifndef ARVORE_RUBRO_NEGRA_HPP
#define ARVORE_RUBRO_NEGRA_HPP

#include <iostream>
#include <string>
#include <algorithm>

enum Cor { VERMELHO, PRETO };

template <typename T>
class ArvoreRubroNegra {
private:
    struct No {
        T dado;
        Cor cor;
        No *esquerda, *direita, *pai;

        No(const T& val, Cor c, No* nil) : dado(val), cor(c), esquerda(nil), direita(nil), pai(nil) {}
    };

    No* SENTINELA; // No NULO / NIL
    No* raiz;
    size_t contadorRotacoes;

    void rotacionarEsquerda(No* x) {
        No* y = x->direita;
        x->direita = y->esquerda;
        if (y->esquerda != SENTINELA) y->esquerda->pai = x;
        y->pai = x->pai;

        if (x->pai == SENTINELA) raiz = y;
        else if (x == x->pai->esquerda) x->pai->esquerda = y;
        else x->pai->direita = y;

        y->esquerda = x;
        x->pai = y;
        contadorRotacoes++;
    }

    void rotacionarDireita(No* x) {
        No* y = x->esquerda;
        x->esquerda = y->direita;
        if (y->direita != SENTINELA) y->direita->pai = x;
        y->pai = x->pai;

        if (x->pai == SENTINELA) raiz = y;
        else if (x == x->pai->direita) x->pai->direita = y;
        else x->pai->esquerda = y;

        y->direita = x;
        x->pai = y;
        contadorRotacoes++;
    }

    void corrigirInsercao(No* k) {
        No* tio;
        while (k->pai->cor == VERMELHO) {
            if (k->pai == k->pai->pai->direita) {
                tio = k->pai->pai->esquerda;
                if (tio->cor == VERMELHO) {
                    tio->cor = PRETO;
                    k->pai->cor = PRETO;
                    k->pai->pai->cor = VERMELHO;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->esquerda) {
                        k = k->pai;
                        rotacionarDireita(k);
                    }
                    k->pai->cor = PRETO;
                    k->pai->pai->cor = VERMELHO;
                    rotacionarEsquerda(k->pai->pai);
                }
            } else {
                tio = k->pai->pai->direita;
                if (tio->cor == VERMELHO) {
                    tio->cor = PRETO;
                    k->pai->cor = PRETO;
                    k->pai->pai->cor = VERMELHO;
                    k = k->pai->pai;
                } else {
                    if (k == k->pai->direita) {
                        k = k->pai;
                        rotacionarEsquerda(k);
                    }
                    k->pai->cor = PRETO;
                    k->pai->pai->cor = VERMELHO;
                    rotacionarDireita(k->pai->pai);
                }
            }
            if (k == raiz) break;
        }
        raiz->cor = PRETO;
    }

    void trasplantar(No* u, No* v) {
        if (u->pai == SENTINELA) raiz = v;
        else if (u == u->pai->esquerda) u->pai->esquerda = v;
        else u->pai->direita = v;
        v->pai = u->pai;
    }

    No* minimo(No* no) const {
        while (no->esquerda != SENTINELA) no = no->esquerda;
        return no;
    }

    void corrigirRemocao(No* x) {
        No* irmao;
        while (x != raiz && x->cor == PRETO) {
            if (x == x->pai->esquerda) {
                irmao = x->pai->direita;
                if (irmao->cor == VERMELHO) {
                    irmao->cor = PRETO;
                    x->pai->cor = VERMELHO;
                    rotacionarEsquerda(x->pai);
                    irmao = x->pai->direita;
                }
                if (irmao->esquerda->cor == PRETO && irmao->direita->cor == PRETO) {
                    irmao->cor = VERMELHO;
                    x = x->pai;
                } else {
                    if (irmao->direita->cor == PRETO) {
                        irmao->esquerda->cor = PRETO;
                        irmao->cor = VERMELHO;
                        rotacionarDireita(irmao);
                        irmao = x->pai->direita;
                    }
                    irmao->cor = x->pai->cor;
                    x->pai->cor = PRETO;
                    irmao->direita->cor = PRETO;
                    rotacionarEsquerda(x->pai);
                    x = raiz;
                }
            } else {
                irmao = x->pai->esquerda;
                if (irmao->cor == VERMELHO) {
                    irmao->cor = PRETO;
                    x->pai->cor = VERMELHO;
                    rotacionarDireita(x->pai);
                    irmao = x->pai->esquerda;
                }
                if (irmao->direita->cor == PRETO && irmao->esquerda->cor == PRETO) {
                    irmao->cor = VERMELHO;
                    x = x->pai;
                } else {
                    if (irmao->esquerda->cor == PRETO) {
                        irmao->direita->cor = PRETO;
                        irmao->cor = VERMELHO;
                        rotacionarEsquerda(irmao);
                        irmao = x->pai->esquerda;
                    }
                    irmao->cor = x->pai->cor;
                    x->pai->cor = PRETO;
                    irmao->esquerda->cor = PRETO;
                    rotacionarDireita(x->pai);
                    x = raiz;
                }
            }
        }
        x->cor = PRETO;
    }

    void emOrdem(No* no) const {
        if (no == SENTINELA) return;
        emOrdem(no->esquerda);
        std::cout << no->dado << " ";
        emOrdem(no->direita);
    }

    void imprimirArvore(No* no, std::string prefixo, bool ehEsquerda) const {
        if (no == SENTINELA) return;
        std::string textoCor = (no->cor == VERMELHO) ? "\033[31m[VERMELHO]\033[0m" : "\033[30;1m[PRETO]\033[0m";
        std::cout << prefixo << (ehEsquerda ? "├── " : "└── ") << no->dado << " " << textoCor << "\n";
        imprimirArvore(no->esquerda, prefixo + (ehEsquerda ? "│   " : "    "), true);
        imprimirArvore(no->direita, prefixo + (ehEsquerda ? "│   " : "    "), false);
    }

    int obterAltura(No* no) const {
        if (no == SENTINELA) return 0;
        return 1 + std::max(obterAltura(no->esquerda), obterAltura(no->direita));
    }

    void limpar(No* no) {
        if (no == SENTINELA) return;
        limpar(no->esquerda);
        limpar(no->direita);
        delete no;
    }

public:
    ArvoreRubroNegra() : contadorRotacoes(0) {
        SENTINELA = new No(T(), PRETO, nullptr);
        SENTINELA->esquerda = SENTINELA;
        SENTINELA->direita = SENTINELA;
        SENTINELA->pai = SENTINELA;
        raiz = SENTINELA;
    }

    ~ArvoreRubroNegra() {
        limpar(raiz);
        delete SENTINELA;
    }

    bool inserir(const T& valor) {
        No* y = SENTINELA;
        No* x = raiz;

        while (x != SENTINELA) {
            y = x;
            if (valor < x->dado) x = x->esquerda;
            else if (valor > x->dado) x = x->direita;
            else return false; // Trata elemento duplicado
        }

        No* z = new No(valor, VERMELHO, SENTINELA);
        z->pai = y;

        if (y == SENTINELA) raiz = z;
        else if (z->dado < y->dado) y->esquerda = z;
        else y->direita = z;

        if (z->pai == SENTINELA) {
            z->cor = PRETO;
            return true;
        }

        if (z->pai->pai == SENTINELA) return true;

        corrigirInsercao(z);
        return true;
    }

    bool remover(const T& chave) {
        No* z = raiz;
        while (z != SENTINELA && z->dado != chave) {
            if (chave < z->dado) z = z->esquerda;
            else z = z->direita;
        }

        if (z == SENTINELA) return false;

        No* y = z;
        No* x;
        Cor corOriginalY = y->cor;

        if (z->esquerda == SENTINELA) {
            x = z->direita;
            trasplantar(z, z->direita);
        } else if (z->direita == SENTINELA) {
            x = z->esquerda;
            trasplantar(z, z->esquerda);
        } else {
            y = minimo(z->direita);
            corOriginalY = y->cor;
            x = y->direita;
            if (y->pai == z) {
                x->pai = y;
            } else {
                trasplantar(y, y->direita);
                y->direita = z->direita;
                y->direita->pai = y;
            }
            trasplantar(z, y);
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
            y->cor = z->cor;
        }
        delete z;

        if (corOriginalY == PRETO) {
            corrigirRemocao(x);
        }
        return true;
    }

    bool buscar(const T& chave) const {
        No* x = raiz;
        while (x != SENTINELA && chave != x->dado) {
            if (chave < x->dado) x = x->esquerda;
            else x = x->direita;
        }
        return x != SENTINELA;
    }

    void emOrdem() const {
        emOrdem(raiz);
        std::cout << "\n";
    }

    void imprimirArvore() const {
        if (raiz == SENTINELA) {
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