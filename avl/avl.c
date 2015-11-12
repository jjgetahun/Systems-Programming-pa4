#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int height(node * n) {
    if (n == NULL)
        return -1;
    else
        return n->height;
}

int max(int num1, int num2) {
    if (num1 > num2)
        return num1;
    else
        return num2;
}

node * singleLeftRotation(node * n) {
    node * m = NULL;

    m = n->leftChild;
    n->leftChild = m->rightChild;
    m->rightChild = n;

    n->height = max(height(n->leftChild), height(n->rightChild))+1;
    m->height = max(height(m->leftChild), n->height)+1;

    return m;
}

node * singleRightRotation(node * n) {
    node * m = NULL;

    m = n->rightChild;
    n->rightChild = m->leftChild;
    m->leftChild = n;

    n->height = max(height(n->leftChild), height(n->rightChild))+1;
    m->height = max(height(m->rightChild), n->height)+1;

    return m;
}

node * doubleLeftRotation(node * n) {
    n->leftChild = singleRightRotation(n->leftChild);

    return singleLeftRotation(n);
}

node * doubleRightRotation(node * n) {
    n->rightChild = singleLeftRotation(n->rightChild);

    return singleRightRotation(n);
}

/*node * createNode (char * word, char * filename) {
    node * n = (node *)malloc(sizeof(node));
    n->name = (char *)malloc(strlen(word)+1);
    n->name = word;
    n->height = 0;
    n->leftChild = NULL;
    n->rightChild = NULL;
        
    n->head = (node *)malloc(sizeof(node));
    n->head->name = (char *)malloc(strlen(filename)+1);
    n->head->name = filename;
    n->head->count = 1;
    n->head->height = 0;
    n->head->leftChild = NULL;
    n->head->rightChild = NULL;

    return n;

}*/

node * insert(char * word,/* char * filename,*/ node * root) {
    if (root == NULL) { /*If the node does not exist*/
        root = (node *)malloc(sizeof(node));
        root->name = (char *)malloc(strlen(word)+1);
        root->name = word;
        root->height = 0;
        root->leftChild = NULL;
        root->rightChild = NULL;

        /*root->head = (node *)malloc(sizeof(node));
        root->head->name = (char *)malloc(strlen(filename)+1);
        root->head->name = filename;
        root->head->count = 1;
        root->head->height = 0;
        root->head->leftChild = NULL;
        root->head->rightChild = NULL;*/

        //return createNode(word, filename);

        //printf("%s:\n", root->name);
        //return root;
    }
    else if (strcmp(root->name, word) > 0) { /*If the word is less than the node's word*/
        root->leftChild = insert(word,/* filename,*/ root->leftChild);
        if (height(root->leftChild) - height(root->rightChild) == 2) {
            if (strcmp(root->leftChild->name, word) > 0/* && root->leftChild != NULL*/)
                root = singleLeftRotation(root);
            else {
                /*if (root->leftChild != NULL && root->leftChild->rightChild != NULL)*/
                    root = doubleLeftRotation(root);
            }
        }
        //return root->leftChild;
    }
    else if (strcmp(root->name, word) < 0) { /*If the word is greater than the node's word*/
        root->rightChild = insert(word,/* filename,*/ root->rightChild);
        if (height(root->rightChild) - height(root->leftChild) == 2) {
            if (strcmp(root->rightChild->name, word) < 0/* && root->rightChild != NULL*/)
                root = singleRightRotation(root);
            else
                root = doubleRightRotation(root);
        }
        //return root->rightChild;
    }
    //else { /*If the word is equal to the node's word*/
        //root->height = max(height(root->leftChild), height(root->rightChild))+1;
        /*if (strcmp(root->head->name, filename) > 0) { /*If the file name is less than the node's head's file name*/
            /*root->head->leftChild = insertMoreNodes(filename, root->head->leftChild);
            if (height(root->head->leftChild) - height(root->head->rightChild) == 2) {
                if (strcmp(root->head->leftChild->name, filename) > 0)
                    root->head = singleLeftRotation(root->head);
                else
                    root->head = doubleLeftRotation(root->head);
            }
        }
        else if (strcmp(root->head->name, filename) < 0) { /*If the file name is greater than the node's head's file name*/
            //root->head->rightChild = insertMoreNodes(filename, root->head->rightChild);
            /*if (height(root->head->rightChild) - height(root->head->leftChild) == 2) {
                if (strcmp(root->head->rightChild->name, filename) < 0)
                    root->head = singleRightRotation(root->head);
                else
                    root->head = doubleRightRotation(root->head);
            }
        }
        else { /*If the file name is equal to the node's head's file name*/
           /* root->head->count++;
        }*/
        //printf("\t%s: %d\n", root->head->name, root->head->count);
        //return root;
    //}
    root->height = max(height(root->leftChild), height(root->rightChild))+1;
    return root;
}

node * insertMoreNodes(char * filename, node * root) {
    if (root == NULL) { /*If the node does not exist*/
        root = (node *)malloc(sizeof(node));
        root->name = (char *)malloc(strlen(filename)+1);
        root->name = filename;
        root->count = 1;
        root->height = 0;
        root->leftChild = NULL;
        root->rightChild = NULL;
    }
    else if (strcmp(root->name, filename) > 0) { /*If the file name is less than the node's file name*/
        root->leftChild = insertMoreNodes(filename, root->leftChild);
        if (height(root->leftChild) - height(root->rightChild) == 2) {
            if (strcmp(root->leftChild->name, filename) > 0)
                root = singleLeftRotation(root);
            else
                root = doubleLeftRotation(root);
        }
    }
    else if (strcmp(root->name, filename) < 0) { /*If the file name is greater than the node's file name*/
        root->rightChild = insertMoreNodes(filename, root->rightChild);
        if (height(root->rightChild) - height(root->leftChild) == 2) {
            if (strcmp(root->rightChild->name, filename) < 0)
                root = singleRightRotation(root);
            else
                root = doubleRightRotation(root);
        }
    }
    else { /*If the file name is equal to the node's file name*/
        root->count++;
        //printf("\t%s: %d\n", root->name, root->count);
        //return root;
    }
    root->height = max(height(root->leftChild), height(root->rightChild))+1;
    return root;
}

void print(node * n) {
    if (n == NULL)
        return;
    
    printf("%s, ", n->name);
    printf("Height: %d\n", n->height);

    if (n->leftChild != NULL)
        printf("L: %s\n", n->leftChild->name);
    if (n->rightChild != NULL)
        printf("R: %s\n", n->rightChild->name);
    
    //printf("%s\n", n->name);
    print(n->leftChild);
    //printf("%s\n", n->name);
    print(n->rightChild);
}
