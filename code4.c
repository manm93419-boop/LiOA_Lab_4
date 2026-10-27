#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция вставки с защитой от дубликатов и проверки памяти
struct Node* insert(struct Node* root, int data, int* success) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Ошибка: не удалось выделить память!\n");
            *success = 0;
            return NULL;
        }
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        *success = 1;
        return newNode;
    }

    if (data < root->data) {
        root->left = insert(root->left, data, success);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data, success);
    }
    else {
        printf("Ошибка: элемент %d уже существует в дереве.\n", data);
        *success = 0;
    }

    return root;
}

// Поиск значения
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// Подсчет числа вхождений
int count_occurrences(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    int count = (root->data == key) ? 1 : 0;

    if (key < root->data) {
        count += count_occurrences(root->left, key);
    }
    else if (key > root->data) {
        count += count_occurrences(root->right, key);
    }
    else {
        count += count_occurrences(root->left, key) + count_occurrences(root->right, key);
    }

    return count;
}

// Визуализация дерева
void print_tree(struct Node* r, int l) {
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
void free_tree(struct Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    // Подключение русской локали для корректного ввода/вывода в консоли
    setlocale(LC_ALL, "Russian");

    struct Node* root = NULL;
    int val;

    printf("=== Построение дерева (-1 для окончания ввода) ===\n");
    while (1) {
        printf("Введите число: ");

        // Защита от некорректного ввода (буквы, символы вместо чисел)
        if (scanf("%d", &val) != 1) {
            printf("Ошибка: введено не целое число. Попробуйте снова.\n");
            while (getchar() != '\n'); // Очистка буфера ввода
            continue;
        }

        if (val == -1) {
            printf("Построение дерева окончено.\n\n");
            break;
        }

        int success = 0;
        root = insert(root, val, &success);
    }

    if (root == NULL) {
        printf("Дерево пустое.\n");
        return 0;
    }

    printf("Визуализация дерева (корень слева):\n");
    print_tree(root, 0);
    printf("\n");

    // Поиск
    printf("=== Поиск элемента ===\n");
    printf("Введите значение для поиска: ");
    if (scanf("%d", &val) == 1) {
        struct Node* found = search(root, val);
        if (found != NULL) {
            printf("Элемент %d найден в дереве.\n", val);
        }
        else {
            printf("Элемент %d НЕ найден в дереве.\n", val);
        }
    }
    else {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }

    // Подсчет вхождений
    printf("\n=== Подсчет вхождений ===\n");
    printf("Введите значение для подсчета: ");
    if (scanf("%d", &val) == 1) {
        int count = count_occurrences(root, val);
        printf("Количество вхождений элемента %d в дерево: %d\n", val, count);
    }
    else {
        printf("Ошибка ввода.\n");
        while (getchar() != '\n');
    }

    free_tree(root);
    return 0;
}
