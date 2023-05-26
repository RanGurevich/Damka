#pragma once
#include "utills.h"

void makeEmptyListSingleSource(SingleSourceMovesList* lst);
bool isEmptyListSingleSource(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewListNodeSingleSource(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertDataToEndListSingleSource(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertNodeToEndListSingleSource(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail);

#include <stdio.h>
#include <stdlib.h>

typedef struct checkersPos {
    char row;
    char col;
} checkersPos;

typedef struct Board {
    // Define your Board structure here
} Board;

typedef struct _SingleSourceMovesTreeNode {
    Board board;
    checkersPos* pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode* next_move[2];
} SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
    SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree;

// Helper function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the height of a binary tree
int findHeight(SingleSourceMovesTreeNode* root) {
    if (root == NULL)
        return 0;

    int leftHeight = findHeight(root->next_move[0]);
    int rightHeight = findHeight(root->next_move[1]);

    return max(leftHeight, rightHeight) + 1;
}

// Function to find the deepest path in a binary tree
void findDeepestPath(SingleSourceMovesTreeNode* root, int currentHeight, int targetHeight, SingleSourceMovesTreeNode** currentPath, SingleSourceMovesTreeNode** deepestPath) {
    if (root == NULL)
        return;

    currentPath[currentHeight] = root;

    if (currentHeight == targetHeight) {
        // Update the deepest path
        for (int i = 0; i <= targetHeight; i++) {
            deepestPath[i] = currentPath[i];
        }
        return;
    }

    findDeepestPath(root->next_move[0], currentHeight + 1, targetHeight, currentPath, deepestPath);
    findDeepestPath(root->next_move[1], currentHeight + 1, targetHeight, currentPath, deepestPath);
}

int main() {
    // Create a SingleSourceMovesTree
    SingleSourceMovesTree tree;
    tree.source = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
    tree.source->board = /* Initialize your board */;
    tree.source->pos = /* Initialize your checkersPos */;
    tree.source->total_captures_so_far = 0;
    tree.source->next_move[0] = /* Initialize the left child */;
    tree.source->next_move[1] = /* Initialize the right child */;

    // Find the height of the tree
    int height = findHeight(tree.source);

    // Create an array to store the current path and deepest path
    SingleSourceMovesTreeNode** currentPath = (SingleSourceMovesTreeNode**)malloc(height * sizeof(SingleSourceMovesTreeNode*));
    SingleSourceMovesTreeNode** deepestPath = (SingleSourceMovesTreeNode**)malloc(height * sizeof(SingleSourceMovesTreeNode*));

    // Find the deepest path
    findDeepestPath(tree.source, 0, height - 1, currentPath, deepestPath);

    // Print the deepest path
    printf("Deepest path: ");
    for (int i = 0; i < height; i++) {
        printf("(%d, %d) ", deepestPath[i]->pos->row, deepestPath[i]->pos->col);
    }

    // Clean up memory
    free(currentPath);
    free(deepestPath);

    return 0;
}