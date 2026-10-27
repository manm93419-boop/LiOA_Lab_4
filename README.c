#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Функция вставки элемента в бинарное дерево поиска.
// Задание (*): Исключает добавление дубликатов.
struct Node* insert(struct Node *root, int data) {
    if (root == NULL) {
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка выделения памяти!\n");
            exit(1);
        }
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        // Условие задания (*): если элемент уже есть, повторно не добавляем
        printf("Элемент %d уже существует в дереве и не будет добавлен.\n", data);
    }

    return root;
}

// Задание 1: Поиск значения в бинарном дереве поиска
struct Node* search(struct Node *root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Задание 2: Подсчет числа вхождений заданного элемента в дерево
// (Для классического BST с уникальными узлами результат 0 или 1, 
// но функция честно обходит дерево для любого формата)
int count_occurrences(struct Node *root, int key) {
    if (root == NULL) {
        return 0;
    }

    int count = (root->data == key) ? 1 : 0;

    if (key < root->data) {
        count += count_occurrences(root->left, key);
    } else if (key > root->data) {
        count += count_occurrences(root->right, key);
    } else {
        count += count_occurrences(root->left, key) + count_occurrences(root->right, key);
    }

    return count;
}

// Вывод дерева на экран (повернуто на 90 градусов)
void print_tree(struct Node *r, int l) {
    if (r == NULL) {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf("   ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

// Освобождение памяти
void free_tree(struct Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    setlocale(LC_ALL, "");

    struct Node *root = NULL;
    int val;

    printf("=== Построение дерева (-1 для окончания ввода) ===\n");
    while (1) {
        printf("Введите число: ");
        if (scanf("%d", &val) != 1) break;

        if (val == -1) {
            printf("Построение дерева окончено.\n\n");
            break;
        }
        root = insert(root, val);
    }

    printf("Визуализация дерева (корень слева):\n");
    print_tree(root, 0);
    printf("\n");

    // Тест поиска (Задание 1)
    printf("=== Поиск элемента ===\n");
    printf("Введите значение для поиска: ");
    scanf("%d", &val);
    struct Node *found = search(root, val);
    if (found != NULL) {
        printf("Элемент %d найден в дереве.\n", val);
    } else {
        printf("Элемент %d НЕ найден в дереве.\n", val);
    }

    // Тест подсчета вхождений (Задание 2)
    printf("\n=== Подсчет вхождений ===\n");
    printf("Введите значение для подсчета вхождений: ");
    scanf("%d", &val);
    int count = count_occurrences(root, val);
    printf("Количество вхождений элемента %d в дерево: %d\n", val, count);

    free_tree(root);
    return 0;
}
