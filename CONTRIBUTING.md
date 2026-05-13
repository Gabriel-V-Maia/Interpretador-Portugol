# Fazendo contribuições

Obrigado por querer contribuir com o Interpretador Portugol! Este guia explica como o projeto está organizado e como submeter contribuições.

---

## Pré-requisitos

- `gcc` e `make` instalados
- Conhecimento básico de C
- (Opcional) Familiaridade com compiladores (Lexer, parser, etc...)

---

## Configurando o ambiente

```bash
git clone https://github.com/Gabriel-V-Maia/Interpretador-Portugol.git
cd Interpretador-Portugol
make
```

Para testar se tudo está funcionando:

```bash
./build/portugol.out examples/fibbonaci.por
```

Para rodar com logs e visualização da AST:

```bash
./build/portugol.out -d examples/fatorial.por
```

---

## Estrutura do projeto

```
src/
├── lexer.c / include/lexer.h       # Análise léxica (tokens)
├── parser.c / include/parser.h     # Análise sintática (AST)
├── AST.c / include/AST.H           # Definição e inicialização dos nós da AST
├── token.c / include/token.h       # Tipos de tokens
├── main.c                          # Ponto de entrada
├── codegen/                        # Transpilação para C
├── semantic/                       # Análise semântica
├── preprocessor/                   # Pré-processamento e importações
├── diagnostics/                    # Erros e mensagens
├── debugger/                       # Logs internos (-d)
└── helpers/                        # Utilitários

examples/       # Scripts .por de exemplo
libs/           # Biblioteca padrão em Portugol
tests/          # Testes automatizados (via zest.h)
```

---

## Fluxo de contribuição

1. **Abra uma issue** antes de começar e descreva o bug ou a feature
2. Faça um fork e crie uma branch descritiva:
   ```bash
   git checkout -b fix/parser-para-loop
   git checkout -b feat/operador-modulo
   ```
3. Faça suas alterações
4. Adicione ou atualize testes em `tests/`
5. Confirme que o build passa:
   ```bash
   make clean && make
   ```
6. Abra um Pull Request para a branch `main`

> [!NOTE]
> Para bugs pequenos e correções simples, abra direto o PR. Para features novas ou mudanças maiores, abra uma issue primeiro pra alinhar antes de codar.

---

## Adicionando testes

Os testes ficam em `tests/` e usam a biblioteca `zest.h`. O padrão é rodar o binário com `popen` e verificar a saída:

```c
ZEST_TEST(test_minha_feature) {
    FILE *f = popen("./build/portugol.out examples/meu_exemplo.por", "r");
    ZEST_ASSERT_NOTNULL(f);
    char output[64];
    fgets(output, sizeof(output), f);
    pclose(f);
    ZEST_ASSERT_STR_EQ(output, "resultado esperado\n");
}
```

Registre o teste em `tests/main.c`:

```c
ZEST_RUN("tests/", 1, "tests.log",
    ZEST_ENTRY(test_fib_output),
    ZEST_ENTRY(test_minha_feature)   // <-- adicione aqui
);
```

---

## Adicionando suporte a novos tokens ou construções

| Etapa | Arquivo |
|---|---|
| 1. Definir o token | `src/include/token.h` |
| 2. Reconhecer no lexer | `src/lexer.c` |
| 3. Parsear a construção | `src/parser.c` |
| 4. Definir o nó da AST | `src/include/AST.H` e `src/AST.c` |
| 5. Gerar o código C | `src/codegen/codegen.c` |
| 6. Checar semântica | `src/semantic/semantic.c` |

---

## Convenções de código

- Nomes de funções e variáveis em `snake_case`
- Prefixo do módulo nas funções públicas: `parser_`, `lexer_`, `codegen_`, etc.
- Mensagens de erro em português (via `diagnostic_error`)
- Sem warnings, o projeto compila com `-Wall -Wextra`

---

## Dúvidas

Abra uma issue com a label `pergunta`. A documentação da linguagem está em:  
https://gabriel-v-maia.github.io/portugol-docs/
