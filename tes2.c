#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct node *Data;
struct node {
  int item;
  char nama[50];
  int child_count;
  Data *children;
};

Data createNode(int id, char *nama) {
  Data node = (Data)malloc(sizeof(struct node));

  node->item = id;
  strcpy(node->nama, nama);
  node->child_count = 0;
  node->children = NULL;

  return node;
}

void insertNode(Data parent, int item, char *nama) {
  Data node = createNode(item, nama);

  parent->child_count++;
  parent->children = (Data*)realloc(parent->children, parent->child_count * sizeof(Data));
  parent->children[parent->child_count - 1] = node;
}

Data findNode(Data root, int id) {
    if (root == NULL) return NULL;
    if (root->item == id) return root;
    Data result = NULL;
    for (int i = 0; i < root->child_count; i++) {
        result = findNode(root->children[i], id);
        if (result != NULL) return result;
    }
  return NULL;
}

void printInorder(Data root, int level) {
  if (root == NULL) return;
  if (root->child_count > 0) printInorder(root->children[0], level + 1);

  printf("%*s%d %s (Level %d)\n", level * 2, "", root->item, root->nama, level);

  for (int i = 1; i < root->child_count; i++) {
      printInorder(root->children[i], level + 1);
  }
}

void printPreorder(Data root, int level) {
  if (root == NULL) {
    printf("Masih Kosong\n");
    return;
  }

  printf("%*s%d %s (Level %d)\n", level * 2, "", root->item, root->nama, level);

  for (int i = 0; i < root->child_count; i++) {
    printPreorder(root->children[i], level + 1);
  }
}

void printPostorder(Data root, int level) {
  if (root == NULL) return;

  for (int i = 0; i < root->child_count; i++) {
    printPostorder(root->children[i], level + 1);
  }

  printf("%*s%d %s (Level %d)\n", level * 2, "", root->item, root->nama, level);
}

void freeTree(Data root) {
  if (root == NULL) return;

  if (root->children) {
    for (int i = 0; i < root->child_count; i++) {
      freeTree(root->children[i]);
    }
    free(root->children);
  }

  free(root);
}

int main() {
  Data root = NULL;
  int pilihan; // Masukan User
  int value, parentId, count; // Awal Cabang/Cabang yang mau di hubungkan
  char nama[50];
  
  while (1){
    system("cls");
    printPreorder(root, 0);
    printf("1. Buat Node\n2. Masukkan Node Baru ke Cabang\n3. Menu Traverse\n4. Exit\nMasukkan Pilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan){
      case 1:
        printf("Masukkan Root dan Nama: ");
        scanf("%d %[^\n]s", &value, nama);
        root = createNode(value, nama);
        break;
      case 2:
        if (root == NULL) {
          printf("\nRoot belum dibuat.\n");
          break;
        }

        printf("\nJumlah Cabang: ");
        scanf("%d", &count);
        
        printf("Masukkan ID Parent(format: parent_id): ");
        scanf("%d", &parentId);
        Data parent = findNode(root, parentId);
        if (parent != NULL){
          printf("Masukkan Nama Cabang Baru (format: id nama): ");
          for (int i = 0; i < count; i++){
            scanf("%d %[^\n]s", &value, nama);
            insertNode(parent, value, nama);
          }
        } else{
          printf("Parent dengan ID %d tidak ditemukan.\n", parentId);
        }
        break;
      case 3:
        if (root == NULL){
          printf("Tree masih kosong.\n");
          break;
        }

        printf("\n1. InOrder\n2. PreOrder(30 Hari)\n3. PostOrder\nPilihan: ");
        scanf("%d", &pilihan);

        if (pilihan == 1) printInorder(root, 0);
        if (pilihan == 2) printPreorder(root, 0);
        if (pilihan == 3) printPostorder(root, 0);

        break;
      case 4:
        printf("Exit. . .\n");
        freeTree(root);
        
        system("cls");
        return 0;
      default:
        printf("Pilihan tidak valid.\n");
        break;
    }
    system("pause");
    system("cls");
  }
  
  // printf("\nMencetak tree secara inorder dengan level:\n");
  // printInorder(root, 0);

  // printf("\nMencetak tree secara preorder dengan level:\n");
  // printPreorder(root, 0);

  // printf("\nMencetak tree secara postorder dengan level:\n");
  // printPostorder(root, 0);

  return 0;
}

// insertNode(root, 2, "Sea of Quantum");
// insertNode(root, 3, "Sea of Data");
// insertNode(root, 4, "Time Travel");
// insertNode(root->children[0], 5, "Kallen");
// insertNode(root->children[0], 6, "Bayu");
// insertNode(root->children[1], 7, "Bambang");
// insertNode(root->children[2], 8, "Agung Hapsah");