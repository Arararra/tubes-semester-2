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

void preOrderTraversal(Data node, int level) {
  if (node == NULL) return;

  for (int i = 0; i < level; i++) {
    printf("  ");
  }

  printf("%d %s\n", node->id, node->nama);

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      preOrderTraversal(node->childs[i], level + 1);
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

Data searchByName(Data node, char *name) {
  if (node == NULL) return NULL;

  if (strcmp(node->nama, name) == 0) {
    return node;
  }

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      Data result = searchByName(node->childs[i], name);
      if (result != NULL) {
        return result;
      }
    }
  }

  return NULL;
}

void printNodeInfo(Data node) {
  if (node == NULL) {
    printf("Node tidak ditemukan.\n");
    return;
  }

  printf("Node ditemukan:\n");
  printf("ID: %d\n", node->id);
  printf("Nama: %s\n", node->nama);

  if (node->parent) {
    printf("Parent: %s\n", node->parent->nama);
  } else {
    printf("Parent: NULL\n");
  }

  printf("Siblings: ");
  if (node->parent && node->parent->childs) {
    int hasSibling = 0;
    for (int i = 0; node->parent->childs[i] != NULL; i++) {
      if (node->parent->childs[i] != node) {
        printf("%s ", node->parent->childs[i]->nama);
        hasSibling = 1;
      }
    }
    if (!hasSibling) {
      printf("None");
    }
  } else {
    printf("None");
  }
  printf("\n");

  printf("Children: ");
  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      printf("%s ", node->childs[i]->nama);
    }
  } else {
    printf("None");
  }
  printf("\n");
}

int main(int argc, char const *argv[]) {
  Data root = createNode(1, "Informatika");

  insertNode(root, 2, "Aljabar Linear");
  insertNode(root, 3, "Pemrograman Lanjut");
  insertNode(root, 4, "Basis Data");
  insertNode(root->childs[0], 5, "Rama");
  insertNode(root->childs[0], 6, "Bayu");
  insertNode(root->childs[0], 8, "Ahmad");
  insertNode(root->childs[1], 7, "Bambang");

  printf("Preorder Traversal:\n");
  preOrderTraversal(root, 0);

  printf("\nInorder Traversal:\n");
  inOrderTraversal(root, 0);

  printf("\nPostorder Traversal:\n");
  postOrderTraversal(root, 0);

  char nameToSearch[50];
  printf("\nMasukkan nama mahasiswa yang ingin dicari: ");
  scanf(" %[^\n]s", nameToSearch);

  Data foundNode = searchByName(root, nameToSearch);
  printNodeInfo(foundNode);

  return 0;
}
