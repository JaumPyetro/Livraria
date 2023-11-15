# README

## Executando o Código por Linha de Comando

Para executar o código `main.c` por linha de comando, siga as instruções abaixo:

1. Abra um terminal no diretório onde o arquivo `main.c` está localizado.

2. Compile o código utilizando um compilador C. Por exemplo, para compilar com o GCC, use o seguinte comando:

    ```bash
    gcc -o programa_seu_nome main.c
    ```

    Substitua `programa_seu_nome` pelo nome desejado para o executável.

3. Execute o programa gerado:

    ```bash
    ./programa_seu_nome
    ```

    O programa será executado e seguirá as instruções do menu.

## Mudanças Realizadas no Código Original

- Adicionada a capacidade de inserir, remover e pesquisar livros em uma lista encadeada.
- Criada a função `SalvarListaEmArquivo` para salvar as mudanças feitas na lista encadeada em um arquivo chamado "livros.dat".
- Adicionada a função `CarregarListaDoArquivo` para carregar os dados do arquivo "livros.dat" de volta para a lista encadeada.
- Modificada a função `MostrarLista` para exibir os livros em ordem alfabética crescente, filtrando por título.
- Atualizada a estrutura do código para fornecer um menu interativo com opções para o usuário.
- Adicionada a função `AdicionarLivroNoFinal` para adicionar um livro no final da lista encadeada.
- Adicionada a função `LiberarMemoria` para liberar a memória alocada para a lista encadeada.
- Adicionada uma opção no menu principal para o usuário escolher salvar ou não as mudanças feitas na lista encadeada no arquivo "livros.dat".
- Adicionada verificação de erro ao abrir o arquivo "livros.dat" para escrita e leitura.
- Modificadas as funções `GetLivro` e `PrintLivro` para melhorar a entrada e exibição de dados.
