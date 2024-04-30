#include <stdio.h>
#include <stdlib.h>
#include "Lab2.h"
// Định nghĩa màu của các nút

int main() {
    struct Node* root = NULL;

    insertRBTree(&root, 1);
    insertRBTree(&root, 2);
    insertRBTree(&root, 0);
    deleteNode(&root, 0);

    printf("Cay 2D:\n");
    print2D(root);
    deleteNode(&root, 5);
    print2D(root);
    return 0;
}