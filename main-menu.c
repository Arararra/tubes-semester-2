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
  node->parent = node->sibling = NULL;
  node->childs = NULL;
  return node;
}

Data findNodeById(Data node, int id) {
  if (node == NULL) return NULL;
  if (node->id == id) return node;

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      Data found = findNodeById(node->childs[i], id);
      if (found != NULL) return found;
    }
  }
  return NULL;
}

Data findNodeByName(Data node, char *nama) {
  if (node == NULL) return NULL;
  if (strcmp(node->nama, nama) == 0) return node;

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      Data found = findNodeByName(node->childs[i], nama);
      if (found != NULL) return found;
    }
  }
  return NULL;
}

void createRoot(Data **roots, int *numRoots) {
  int id;
  printf("Masukkan id prodi: ");
  scanf("%d", &id);

  char nama[50];
  printf("Masukkan nama prodi: ");
  scanf(" %[^\n]s", &nama);

  (*numRoots)++;
  *roots = (Data *)realloc(*roots, ((*numRoots) + 1) * sizeof(Data));
  (*roots)[(*numRoots) - 1] = createNode(id, nama);
  (*roots)[(*numRoots)] = NULL;
}

void insertChild(Data *roots, int numRoots) {
  int parentId, childId;
  printf("Masukkan id parent: ");
  scanf("%d", &parentId);

  Data parent = NULL;
  for (int i = 0; i < numRoots; i++) {
    parent = findNodeById(roots[i], parentId);
    if (parent != NULL) break;
  }

  if (parent == NULL) {
    printf("ID parent tidak ditemukan\n");
    system("pause");
    return;
  }

  printf("Masukkan id child: ");
  scanf("%d", &childId);

  int found = 0;
  Data *temp = parent->childs;
  while (temp && *temp) {
    if ((*temp)->id == childId) {
      found = 1;
      break;
    }
    temp++;
  }
  if (found == 1) {
    printf("ID child sudah ada\n");
    system("pause");
    return;
  }

  char nama[50];
  printf("Masukkan nama child: ");
  scanf(" %[^\n]s", &nama);

  Data child = createNode(childId, nama);
  child->parent = parent;

  int numChilds = 0;
  if (parent->childs) {
    while (parent->childs[numChilds] != NULL) numChilds++;
  }

  parent->childs = (Data *)realloc(parent->childs, (numChilds + 2) * sizeof(Data));
  if (numChilds > 0) {
    parent->childs[numChilds - 1]->sibling = child;
  }
  parent->childs[numChilds] = child;
  parent->childs[numChilds + 1] = NULL;
}

void printPreorder(Data node, int level) {
  if (node == NULL) return;

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  printf("%d %s\n", node->id, node->nama);

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      printPreorder(node->childs[i], level + 1);
    }
  }
}

void printInorder(Data node, int level) {
  if (node == NULL) return;

  if (node->childs && node->childs[0]) {
    printInorder(node->childs[0], level + 1);
  }

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  printf("%d %s\n", node->id, node->nama);

  if (node->childs) {
    for (int i = 1; node->childs[i] != NULL; i++) {
      printInorder(node->childs[i], level + 1);
    }
  }
}

void printPostorder(Data node, int level) {
  if (node == NULL) return;

  if (node->childs) {
    for (int i = 0; node->childs[i] != NULL; i++) {
      printPostorder(node->childs[i], level + 1);
    }
  }

  for (int i = 0; i < level; i++) {
    printf("  ");
  }
  printf("%d %s\n", node->id, node->nama);
}

void searchNode(Data *roots, int numRoots) {
  char nama[50];
  printf("Masukkan nama node: ");
  scanf(" %[^\n]s", &nama);

  Data node = NULL;
  for (int i = 0; i < numRoots; i++) {
    node = findNodeByName(roots[i], nama);
    if (node != NULL) break;
  }

  if (node == NULL) {
    printf("Node dengan nama %s tidak ditemukan\n", nama);
  } else {
    printf("ID: %d\n", node->id);
    printf("Nama: %s\n", node->nama);
    if (node->parent != NULL) {
      printf("Parent: %s\n", node->parent->nama);
    } else {
      printf("Parent: None\n");
    }

    printf("Siblings: ");
    int siblingCount = 0;
    if (node->parent != NULL && node->parent->childs != NULL) {
      for (int i = 0; node->parent->childs[i] != NULL; i++) {
        if (node->parent->childs[i] != node) {
          if (siblingCount > 0) printf(", ");
          printf("%s", node->parent->childs[i]->nama);
          siblingCount++;
        }
      }
      if (siblingCount == 0) printf("None");
    } else {
      printf("None");
    }
    printf("\n");

    if (node->childs != NULL) {
      printf("Childs:\n");
      for (int i = 0; node->childs[i] != NULL; i++) {
        printf("  - ID: %d, Nama: %s\n", node->childs[i]->id, node->childs[i]->nama);
      }
    } else {
      printf("Childs: None\n");
    }
  }

  system("pause");
}

int main(int argc, char const *argv[]) {
  int pilihan = -1, numRoots = 0, jenisPrint = 1;
  Data *roots = (Data *)malloc(1 * sizeof(Data));
  roots[0] = NULL;

  while (1) {
    system("cls");
    if (roots[0] != NULL) {
      for (int i = 0; i < numRoots; i++) {
        if (jenisPrint == 1) {
          printPreorder(roots[i], 0);
        } else if (jenisPrint == 2) {
          printInorder(roots[i], 0);
        } else {
          printPostorder(roots[i], 0);
        }
        printf("\n");
      }
      printf("=========================\n\n");
    }

    printf("1. Create root\n2. Insert child\n3. Cari node\n4. Traverse preorder");
    printf("\n5. Traverse inorder\n6. Traverse postorder\n0. Keluar\nPilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
      case 1:
        createRoot(&roots, &numRoots);
        break;
      case 2:
        insertChild(roots, numRoots);
        break;
      case 3:
        searchNode(roots, numRoots);
        break;
      case 4:
        jenisPrint = 1;
        break;
      case 5:
        jenisPrint = 2;
        break;
      case 6:
        jenisPrint = 3;
        break;
      case 0:
        exit(0);
        break;
      default:
        printf("Pilihan tidak tersedia\n");
        system("pause");
        break;
    }
  }

  return 0;
}
