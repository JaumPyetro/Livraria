#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char Titulo[50];
  char Autor[50];
  int NumReg;
  double Preco;
} Livro;

typedef struct node {
  Livro livro;
  struct node *next;
} Node;

Livro GetLivro();
void PrintLivro(Livro livro);
Node *InserirLivro(Node *head, Livro livro);
Node *RemoverLivro(Node *head, int numReg);
Node *PesquisarLivro(Node *head, int opcao);
void MostrarLista(Node *head, char filtro);
void LiberarMemoria(Node *head);
void SalvarListaEmArquivo(Node *head);
Node *CarregarListaDoArquivo();
Node *AdicionarLivroNoFinal(Node *head, Livro livro);

int main(void) {
  Node *head = CarregarListaDoArquivo();
  char resp;

  do {
    printf("\n1. Inserir Livro\n");
    printf("2. Remover Livro\n");
    printf("3. Pesquisar Livro por Titulo\n");
    printf("4. Pesquisar Livro por Número de Registro\n");
    printf("5. Mostrar Lista\n");
    printf("6. Salvar Mudanças\n");
    printf("7. Sair\n");
    printf("Escolha uma opcao: ");
    scanf(" %c", &resp);

    switch (resp) {
    case '1':
      head = InserirLivro(head, GetLivro());
      break;
    case '2':
      if (head != NULL) {
        int numReg;
        printf("\nDigite o numero de registro do livro a ser removido: ");
        scanf("%d", &numReg);
        head = RemoverLivro(head, numReg);
      } else {
        printf("\nA lista esta vazia.\n");
      }
      break;
    case '3':
      PesquisarLivro(head, 1);
      break;
    case '4':
      PesquisarLivro(head, 2);
      break;
    case '5':
      puts("\n\nLISTA DE LIVROS DO ARQUIVO ");
      puts("==================================");
      MostrarLista(head, 'a');
      break;
    case '6':
      SalvarListaEmArquivo(head);
      break;
    case '7':
      LiberarMemoria(head);
      break;
    default:
      printf("\nOpção invalida. Tente novamente.\n");
    }
  } while (resp != '7');

  return 0;
}

void SalvarListaEmArquivo(Node *head) {
  FILE *arquivo;
  arquivo = fopen("livros.dat", "wb");

  if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo para escrita.\n");
    return;
  }

  Node *current = head;
  while (current != NULL) {
    fwrite(&(current->livro), sizeof(Livro), 1, arquivo);
    current = current->next;
  }

  fclose(arquivo);
  printf("\nLista salva no arquivo com sucesso!\n");
}

Node *CarregarListaDoArquivo() {
  FILE *arquivo;
  arquivo = fopen("livros.dat", "rb");

  if (arquivo == NULL) {
    printf("\nArquivo 'livros.dat' nao encontrado. Inicializando uma lista "
           "vazia.\n");
    return NULL;
  }

  Node *head = NULL;
  Livro livro;

  while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
    head = AdicionarLivroNoFinal(head, livro);
  }

  fclose(arquivo);
  printf("\nLista carregada do arquivo com sucesso!\n");

  return head;
}

Node *AdicionarLivroNoFinal(Node *head, Livro livro) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->livro = livro;
  temp->next = NULL;

  if (head == NULL) {
    return temp;
  }

  Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = temp;

  return head;
}

Livro GetLivro() {
  Livro livro;
  printf("\n\tDigite o título: ");
  getchar();
  fgets(livro.Titulo, 50, stdin);
  printf("\n\tDigite o nome do autor: ");
  fgets(livro.Autor, 50, stdin);
  printf("\n\tDigite o numr do registro: ");
  scanf("%d", &livro.NumReg);
  printf("\n\tDigite o preço do livro: ");
  scanf("%lf", &livro.Preco);
  rewind(stdin);

  return livro;
}

void PrintLivro(Livro livro) {
  printf("\n\tTitulo: %s", livro.Titulo);
  printf("\tAutor: %s", livro.Autor);
  printf("\tNo.Reg: %d", livro.NumReg);
  printf("\tPreco: %.2lf\n", livro.Preco);
}

Node *InserirLivro(Node *head, Livro livro) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->livro = livro;
  temp->next = head;
  head = temp;
  printf("\nLivro inserido com sucesso!\n");
  return head;
}

Node *RemoverLivro(Node *head, int numReg) {
  Node *current = head;
  Node *prev = NULL;

  while (current != NULL && current->livro.NumReg != numReg) {
    prev = current;
    current = current->next;
  }

  if (current == NULL) {
    printf("\nLivro com número de registro %d não encontrado.\n", numReg);
  } else {
    if (prev == NULL) {
      head = current->next;
    } else {
      prev->next = current->next;
    }
    free(current);
    printf("\nLivro removido com sucesso!\n");
  }

  return head;
}

Node *PesquisarLivro(Node *head, int opcao) {
  if (head == NULL) {
    printf("\nA lista esta vazia.\n");
    return head;
  }

  char termo[50];
  int numReg;

  printf("\nDigite o título do livro desejado: ");
  getchar();
  fgets(termo, 50, stdin);

  Node *current = head;
  int encontrado = 0;

  switch (opcao) {
  case 1: // Pesquisa por título
    while (current != NULL) {
      if (strstr(current->livro.Titulo, termo) != NULL) {
        PrintLivro(current->livro);
        encontrado = 1;
      }
      current = current->next;
    }
    break;
  case 2: // Pesquisa por número de registro
    printf("\nDigite o numero de registro: ");
    scanf("%d", &numReg);
    while (current != NULL) {
      if (current->livro.NumReg == numReg) {
        PrintLivro(current->livro);
        encontrado = 1;
        break;
      }
      current = current->next;
    }
    break;
  default:
    printf("\nOpcao invalida.\n");
  }

  if (!encontrado) {
    printf("\nNenhum livro encontrado com o título de pesquisa.\n");
  }
  return head;
}

void MostrarLista(Node *head, char filtro) {
  if (head == NULL) {
    printf("\nA lista esta vazia.\n");
    return;
  }

  Node *tempHead = NULL;
  Node *current = head;
  while (current != NULL) {
    tempHead = AdicionarLivroNoFinal(tempHead, current->livro);
    current = current->next;
  }

  Node *i, *j;
  for (i = tempHead; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (strcmp(i->livro.Titulo, j->livro.Titulo) > 0) {
        Livro temp = i->livro;
        i->livro = j->livro;
        j->livro = temp;
      }
    }
  }

  current = tempHead;
  while (current != NULL) {
    if (filtro == 'a' || filtro == 'A') {
      if (current->livro.Titulo[0] >= 'a' && current->livro.Titulo[0] <= 'z') {
        PrintLivro(current->livro);
      }
    } else {
      PrintLivro(current->livro);
    }
    current = current->next;
  }

  LiberarMemoria(tempHead);
}

void LiberarMemoria(Node *head) {
  Node *current = head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
  }
  printf("\nMemoria liberada. Saindo do programa.\n");
  exit(0);
}
