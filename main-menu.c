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

void createRoot(Data **roots, int *numRoots, int id, char *nama) {
  (*numRoots)++;
  
  *roots = (Data *)realloc(*roots, ((*numRoots) + 1) * sizeof(Data));

  (*roots)[(*numRoots) - 1] = createNode(id, nama);
  (*roots)[(*numRoots)] = NULL;
}

int main(int argc, char const *argv[]) {
  int pilihan = -1, numRoots = 0;
  Data *roots = (Data *)malloc((numRoots + 1) * sizeof(Data));
  roots[numRoots] = NULL;

  while (1) {
    system("cls");
    if (pilihan == 404) printf("Pilihan tidak tersedia\n");

    if (roots[0] != NULL) {
      for (int i = 0; i < numRoots; i++) {
        printf("%d %s\n", roots[i]->id, roots[i]->nama);
      }
    }

    printf("\n1. Create root\n2. Insert child\n3. Cari Mahasiswa\n4. Traverse preorder");
    printf("\n5. Traverse inorder\n6. Traverse postorder\n0. Keluar\nPilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
      case 1:
        int id;
        char nama[50];

        printf("Masukkan id prodi: ");
        scanf("%d", &id);
        printf("Masukkan nama prodi: ");
        scanf(" %[^\n]s", &nama);

        createRoot(&roots, &numRoots, id, nama);
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 0:
        exit(0);
        break;
      default:
        pilihan = 404;
        break;
    }
  }

  return 0;
}
