# Amazon Engineering Challenge: Árvores Balanceadas (AVL e Rubro-Negra)

**Disciplina:** Estruturas de Dados Básicas II   
**Aluno:** Luccas Melo de Andrade  

---

## 📋 Sobre o Projeto

Este projeto consiste em um protótipo de sistema para registro, localização e remoção de identificadores de pacotes logísticos para a **Amazon** durante o evento de alta demanda da **Black Friday**. 

Devido ao risco de degeneração de desempenho em Árvores de Busca Binária (ABB) tradicionais diante de entradas de dados em ordem específica, o sistema foi construído utilizando duas estruturas de dados auto-balanceadas implementadas do zero em C++17:
* **Árvore AVL:** Balanceamento rigoroso baseado na altura dos nós.
* **Árvore Rubro-Negra (Red-Black Tree):** Balanceamento baseado na coloração dos nós e altura-preta, otimizada para menor custo de reestruturação em atualizações frequentes.

---

## 🛠️ Funcionalidades Implementadas

* **Operações Básicas:**
  * Inserção de identificadores (IDs de pacotes).
  * Remoção de identificadores (com tratamento de nós folha, com 1 filho e com 2 filhos).
  * Busca eficiente de pacotes (O(log n)).
  * Percurso em ordem, exibindo os elementos de forma crescente.
* **Visualização Estrutural:**
  * Exibição visual da árvore em formato de hierarquia textual.
  * Indicação visual de cores para a Árvore Rubro-Negra (`[VERMELHO]` e `[PRETO]`).
* **Tratamento de Exceções e Casos de Borda:**
  * Rejeição e notificação em tentativas de inserção de IDs duplicados.
  * Mensagens claras ao buscar ou remover elementos inexistentes.
  * Operações seguras sobre árvores vazias ou com elemento único.
* **Métricas de Desempenho e Benchmarking:**
  * Contabilização dinâmica da altura da árvore.
  * Contagem total do número de rotações efetuadas para rebalanceamento.
  * Módulo de testes comparativos automatizados (*Benchmark*) para avaliação dos cenários de inserção crescente, decrescente e desordenada.

---

## 📁 Estrutura do Repositório

```text
.
├── avltree.hpp              # Classe da Árvore AVL
├── rubronegro.hpp           # Classe da Árvore Rubro-Negra
├── testesautomatizado.hpp   # Cabeçalho da suíte de benchmarking
├── testesautomatizado.cpp   # Implementação dos cenários comparativos
├── main.cpp                 # Menu interativo principal e interface com usuário
├── Makefile                 # Automação de compilação
└── README.md                # Documentação do projeto
```

---

## 🔧 Compilação e Execução

### Pré-requisitos
* Compilador C++ com suporte ao padrão **C++17** (ex: `g++` 7.0 ou superior).
* Utilitário `make` instalado no ambiente (Linux/macOS ou WSL no Windows).

### Instruções passo a passo

1. **Clonar o repositório:**
   ```bash
   git clone https://github.com/LuccasMeloAndrade/Amazon-Engineering-Challenge-rvores-Balanceadas.git

2. **Compilar o projeto:**
   ```bash
   make
   ```

3. **Executar a aplicação:**
   ```bash
   ./amazon_tracking
   ```

4. **Limpar arquivos compilados (`.o` e executável):**
   ```bash
   make clean
   ```

---

## 💻 Exemplo de Uso (Menu Principal)

Ao iniciar o programa, o menu interativo oferece acesso às operações em cada árvore ou à bateria automatizada:

```text
======================================================
    AMAZON LOGISTICS - SYSTEM PACKAGE TRACKING       
======================================================
1. Operar com Árvore AVL
2. Operar com Árvore Rubro-Negra
3. Executar Bateria de Testes Comparativos Automatizados
0. Sair
Escolha uma opção: 
```

Ao selecionar a **opção 3**, o sistema executa automaticamente os testes e apresenta as métricas comparativas:

```text
--- Cenário: Inserção Crescente (10 a 100) ---
AVL         -> Altura: 4 | Rotações: 6
Rubro-Negra -> Altura: 5 | Rotações: 5
```

---

## 📊 Principais Conclusões Técnicas

* **Árvore AVL:** Garante uma altura ligeiramente menor devido ao seu critério rigoroso de fator de balanceamento ($|FB| \le 1$), tornando-a ideal para sistemas focados predominantemente em **consultas/leituras**.
* **Árvore Rubro-Negra:** Apresenta maior eficiência em sistemas com **gravações intensivas (inserções e remoções)**, como o ambiente de logística durante a Black Friday. O critério de coloração aceita pequenas variações de altura em troca de uma frequência reduzida de rotações de rebalanceamento.

---
