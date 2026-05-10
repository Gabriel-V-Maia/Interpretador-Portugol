# Interpretador Portugol
<div align="center">
  <img src="https://raw.githubusercontent.com/Gabriel-V-Maia/portugol-docs/refs/heads/main/overrides/assets/LOGO.png" width=150>
</div>

<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-blue?style=for-the-badge&logo=c">
  <img src="https://img.shields.io/badge/status-em%20desenvolvimento-yellow?style=for-the-badge">
  <img src="https://img.shields.io/badge/licença-MIT-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/plataforma-Linux%20%7C%20Windows-lightgrey?style=for-the-badge">
</p>

Projeto focado no desenvolvimento de um interpretador e compilador para a linguagem Portugol, escrito inteiramente em C. O sistema realiza o processamento completo do código, desde a análise inicial até a geração de uma Árvore de Sintaxe Abstrata (AST) com suporte para transpilação para C.

A sintaxe é inspirada com o padrão do Portugol-Webstudio, porém sofreu modificações.

A logo foi criada por [Willian Guedes](https://github.com/Willian-Guedes)

## Exemplos de Código

### Sequência de Fibonacci
```portugol
programa {
  inteiro funcao fib(inteiro n) {
    se (n <= 1) {
      retorne n
    }
    retorne fib(n - 1) + fib(n - 2)
  }

  nulo funcao inicio() {
    escreva("${fib(10)}\n")
  }
}
```

### Cálculo de Fatorial
```portugol
programa {
  inteiro funcao fat(inteiro n) {
    se (n == 0) {
      retorne 1
    }
    retorne n * fat(n - 1)
  }

  nulo funcao inicio() {
    escreva("${fat(5)}\n")
  }
}
```

## Instruções de Uso

Para compilar o projeto e executar os exemplos:

```bash
# Compilação do interpretador
make

# Execução de um script Portugol
./build/portugol examples/fibbonaci.por

# Execução com visualização de logs e AST
./build/portugol -d examples/fatorial.por
```

## Organização de Diretórios

* build: Arquivos binários e resultados de compilação.
* examples: Scripts de teste em linguagem Portugol.
* libs: Bibliotecas padrão e módulos externos.
* src: Código fonte organizado por módulos (Lexer, Parser, Codegen).
* src/include: Definições de cabeçalhos e interfaces.

## Metas de Implementação

* Finalização do Parser para suporte total à gramática.
* Estabilização do sistema de importação de arquivos.
* Integração automática com o GCC para compilação final.
* Criação de biblioteca padrão para entrada e saída de dados.
* Implementação de suite de testes automatizados para a AST.

## Licença

Este software é distribuído sob a Licença MIT. Desenvolvido por Gabriel Vinícius da Maia.
```
