#ifndef AVL_H
#define AVL_H

typedef struct node {

    char * name;
    int count;
    int height;
    struct node * head;
    struct node * leftChild;
    struct node * rightChild;

} node;

//node * insert(char * word, char * filename, node * root);
node * insert(char * word, node * root);
node * insertMoreNodes(char * filename, node * root);
void print(node * n);

#endif
