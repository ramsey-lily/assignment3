#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}
struct Node* bst_construct(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) {
        return NULL;
    }

    struct Node* root = createNode(postorder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex = findIndex(inorder, inStart, inEnd, root->data);

    root->right = bst_construct(inorder, postorder, inIndex + 1, inEnd, postIndex);
    root->left = bst_construct(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}


void bfs_traversal(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}

int main() {
    int inorder[] = {5, 10, 15, 20, 25, 30, 45};
    int postorder[] = {5, 15, 10, 25, 45, 30, 20};
    int size = sizeof(inorder) / sizeof(inorder[0]);

    int postIndex = size - 1;
    struct Node* root = bst_construct(inorder, postorder, 0, size - 1, &postIndex);

    printf("BFS (DFS) traversal of constructed BST: ");
    bfs_traversal(root);
    printf("\n");

    return 0;
}
