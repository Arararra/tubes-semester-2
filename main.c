#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data *Data;
struct data {
  int id;
  char nama[50];
  Data parent;
  Data *childs;
  Data sibling;
};

Data createNode(int id, char *nama) {
  Data node = (Data)malloc(sizeof(struct data));
  node->id = id;
  strcpy(node->nama, nama);
  node->parent = NULL;
  node->childs = NULL;
  node->sibling = NULL;
  return node;
}

void insertNode(Data parent, int id, char *nama) {
  Data node = createNode(id, nama);
  node->parent = parent;

  int numChilds = 0;
  if (parent->childs != NULL) {
    while (parent->childs[numChilds] != NULL) {
      numChilds++;
    }
  }

  parent->childs = (Data *)realloc(parent->childs, (numChilds + 2) * sizeof(Data));
  parent->childs[numChilds] = node;
  parent->childs[numChilds + 1] = NULL;

  if (numChilds > 0) {
    parent->childs[numChilds - 1]->sibling = node;
  }
}

void printTree(Data node, int level) {
  if (node == NULL) return;

  for (int i = 0; i < level; i++) {
    printf("  ");
  }

  printf("%d %s\n", node->id, node->nama);

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      printTree(node->childs[i], level + 1);
    }
  }
}

void inOrderTraversal(Data node, int level) {
  if (node == NULL) return;

  if (node->childs && node->childs[0]) {
    inOrderTraversal(node->childs[0], level + 1);
  }

  for (int i = 0; i < level; i++) {
    printf("  ");
  }

  printf("%d %s\n", node->id, node->nama);
  
  if (node->childs) {
    for (int i = 1; node->childs[i] != NULL; i++) {
      inOrderTraversal(node->childs[i], level + 1);
    }
  }
}

void postOrderTraversal(Data node, int level) {
  if (node == NULL) return;

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      postOrderTraversal(node->childs[i], level + 1);
    }
  }

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  
  printf("%d %s\n", node->id, node->nama);
}

void freeTree(Data node) {
  if (node == NULL) return;

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      freeTree(node->childs[i]);
    }
    free(node->childs);
  }

  free(node);
}

int main(int argc, char const *argv[]) {
    Data root = createNode(1, "Informatika");

    insertNode(root, 2, "Aljabar Linear");
    insertNode(root, 3, "Pemrograman Lanjut");
    insertNode(root, 4, "Basis Data");
    insertNode(root->childs[0], 5, "Rama");
    insertNode(root->childs[0], 6, "Bayu");
    insertNode(root->childs[1], 7, "Bambang");

    printf("Tree Structure:\n");
    printTree(root, 0);

    printf("\nInorder Traversal:\n");
    inOrderTraversal(root, 0);

    printf("\nPostorder Traversal:\n");
    postOrderTraversal(root, 0);

    freeTree(root);

    return 0;
}
