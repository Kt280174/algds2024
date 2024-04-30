#ifndef _Lab2_h
#include <stdio.h>
#include <stdlib.h>

// Определяет цвет узел
#define RED 0
#define BLACK 1

struct Node {
    int data;
    int color;  // Цвет узел (КРАСНЫЙ или ЧЕРНЫЙ)
    struct Node* parent;
    struct Node* left;
    struct Node* right;
};

// Инициализируем новый узел
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED;  // По умолчанию новый узел красного цвета
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция поворота влево
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Функция поворота вправо
void rightRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Функция для изменения цвета узла и его дочерних элементов
void swapColors(struct Node* x1, struct Node* x2) {
    int temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}



// Функция для изменения порядка дерева после вставки нового узла
void fixInsertRBTree(struct Node** root, struct Node* x) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;

    while ((x != *root) && (x->color != BLACK) && (x->parent->color == RED)) {
        parent = x->parent;
        grandparent = parent->parent;

        // Случай 1: отец x — левый сын дедушки x
        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;

            // Случай 1А: Дядя красный, просто нужно сменить цвет
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            }
            else {
                // Случай 1B: x является правым дочерним элементом своего родителя, его необходимо повернуть влево
                if (x == parent->right) {
                    leftRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }
                // Случай 1C: x является левым дочерним элементом своего родителя, его необходимо повернуть вправо и изменить цвет
                rightRotate(root, grandparent);
                swapColors(parent, grandparent);
                x = parent;
            }
        }
        else {
            // Случай 2: отец x — правый ребенок дедушки x
            struct Node* uncle = grandparent->left;

            // Случай 2А: Дядя красный, просто нужно сменить цвет
            if ((uncle != NULL) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            }
            else {
                // Случай 2B: x является левым дочерним элементом своего родителя, его необходимо повернуть вправо
                if (x == parent->left) {
                    rightRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }
                // Случай 2C: x является правым дочерним элементом своего родителя, его необходимо повернуть влево и изменить цвет
                leftRotate(root, grandparent);
                swapColors(parent, grandparent);
                x = parent;
            }
        }
    }

    // Убедитесь, что корневой узел всегда черный
    (*root)->color = BLACK;
}

// Вставляем новый узел в красно-черное дерево
void insertRBTree(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* parent = NULL;
    struct Node* x = *root;

    // Находим позицию для вставки нового узла
    while (x != NULL) {
        parent = x;
        if (data < x->data)
            x = x->left;
        else if (data > x->data)
            x = x->right;
        else {
            free(newNode);
            return;  // Узел уже существует в дереве, больше не вставляйте
        }
    }

    // Назначаем родителя новому узлу
    newNode->parent = parent;

    // Обработка случая пустого дерева
    if (parent == NULL)
        *root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Переупорядочиваем дерево, чтобы сохранить свойства красно-черного дерева
    fixInsertRBTree(root, newNode);
}




// Функция для поиска узла с наименьшим значением в дереве
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}


void fixDeleteRBTree(struct Node** root, struct Node* x, struct Node* parent) {
    struct Node* sibling;

    while ((x != *root) && ((x == NULL) || (x->color == BLACK))) {
        if (x == parent->left) {
            sibling = parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                sibling = parent->right;
            }

            if (((sibling->left == NULL) || (sibling->left->color == BLACK)) &&
                ((sibling->right == NULL) || (sibling->right->color == BLACK))) {
                sibling->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                if ((sibling->right == NULL) || (sibling->right->color == BLACK)) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = parent->right;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, parent);
                x = *root;
            }
        }
        else {
            sibling = parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rightRotate(root, parent);
                sibling = parent->left;
            }

            if (((sibling->right == NULL) || (sibling->right->color == BLACK)) &&
                ((sibling->left == NULL) || (sibling->left->color == BLACK))) {
                sibling->color = RED;
                x = parent;
                parent = x->parent;
            }
            else {
                if ((sibling->left == NULL) || (sibling->left->color == BLACK)) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = parent->left;
                }

                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, parent);
                x = *root;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}
// Функция удаления узла из дерева
void deleteNode(struct Node** root, int data) {
    struct Node* z = NULL;
    struct Node* x, * y;
    struct Node* parent = NULL;

    // Tìm nút cần xóa
    z = *root;
    while (z != NULL) {
        if (data == z->data)
            break;
        parent = z;
        if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL) {
        printf("Khong tim thay gia tri can xoa.\n");
        return;
    }


    if ((z->left == NULL) || (z->right == NULL)) {
        y = z;
    }
    else {
        y = minValueNode(z->right);
    }


    if (y->left != NULL) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    if (x != NULL) {
        x->parent = y->parent;
    }

    if (y->parent == NULL) {
        *root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    if (y != z) {
        z->data = y->data;
    }


    if (y->color == BLACK) {
        fixDeleteRBTree(root, x, y->parent);
    }

    free(y);
}


void print2DUtil(struct Node* root, int space) {
    if (root == NULL)
        return;
    int count = 5;
    space += count;

    print2DUtil(root->right, space);
    printf("\n");
    for (int i = count; i < space; i++)
        printf(" ");
    if (root->color == RED)
        printf("%d(R)\n", root->data);
    else
        printf("%d(B)\n", root->data);
    print2DUtil(root->left, space);
}
void print2D(struct Node* root) {
    print2DUtil(root, 0);
}
#endif