#include <stdio.h>
#include <stdlib.h>

typedef char *data;
typedef int keyType;

struct tree {
  keyType key;
  data info;
  struct tree *left;
  struct tree *right;
};

/* ������� � ������� ����� */
struct tree *search(keyType key, struct tree *T)
{ if (NULL == T)
    return NULL;
  else if (key < T->key)
    return search(key, T->left);
  else if (key > T->key)
    return search(key, T->right);
  else
    return T;
}

/* ��������� � ������� ����� */
void insertKey(keyType key, data x, struct tree **T)
{ if (NULL == *T) {
    *T = (struct tree *) malloc(sizeof(**T));
    (*T)->key = key;
    (*T)->info = x;
    (*T)->left = NULL;
    (*T)->right = NULL;
  }
  else if (key < (*T)->key)
    insertKey(key, x, &(*T)->left);
  else if (key > (*T)->key)
    insertKey(key, x, &(*T)->right);
  else
    fprintf(stderr, "��������� � ���� � �������!\n");
}

/* ���������� �� ������� ����� � */

/* �������� �� ���������� ������� � ����� */
struct tree *findMin(struct tree *T)
{ while (NULL != T->left) T = T->left;
  return T;
}

void deleteKey(keyType key, struct tree **T)
{ if (NULL == *T) {
    fprintf(stderr, "������, ����� ������ �� �� �������, ������! \n");
  } else {
    if (key < (*T)->key)
      deleteKey(key, &(*T)->left);
    else if (key > (*T)->key)
      deleteKey(key, &(*T)->right);
    else  /* �������� �� ���������� � ������� */
    if ((*T)->left && (*T)->right) {       /* ��������� ��� � ���� � ����� �������� */
      /* ������ �� ������ �� ������� */
      struct tree *replace = findMin((*T)->right);
      (*T)->key = replace->key;
      (*T)->info = replace->info;
      deleteKey((*T)->key, &(*T)->right);    /* ������ �� �������� */
    }
    else {  /* ��������� ��� ���� ��� ���� ���������� */
      struct tree *temp = *T;
      if ((*T)->left)
        *T = (*T)->left;
      else
        *T = (*T)->right;
      free(temp);
    }
  }
}

void printTree(struct tree *T)
{ if (NULL == T) return;
  printf("%d ", T->key);
  printTree(T->left);
  printTree(T->right);
}

int main(void) {
  struct tree *T = NULL, *result;
  int i;

  /* ������� 10 ����� � ���������� ������� */
  for (i = 0; i < 10; i++) {
    int ikey = random(20) + 1;
    printf("������ �� ������� � ���� %d \n", ikey);
    insertKey(ikey, "someinfo", &T);
  }

  printf("�����: ");

  printTree(T);
  printf("\n");

  /* ��������� �� �������� � ���� 5 */
  result = search(5, T);
  printf("������� �: %s\n", result->info);

  /* ������� ���������� 10 ����� �� ������� */
  for (i = 0; i < 10; i++) {
    int ikey = random(20) + 1;
    printf("������� �� �������� � ���� %d \n", ikey);
    deleteKey(ikey, &T);
  }

  printf("�����: ");

  printTree(T);
  printf("\n");
  return 0;
}