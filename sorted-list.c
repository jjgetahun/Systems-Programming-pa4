#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorted-list.h"

/*
 * Creates the sorted list, allocating space for it, CompareFuncT,
 * DestructFuncT, the head of the list, and "next". It also initializes
 * head, next, and numPtr.
 */
SortedListPtr SLCreate(CompareFuncT cf) {
    SortedListPtr SL = (SortedListPtr)malloc(sizeof(SortedList));
    //SL->CompareFuncT = (CompareFuncT)malloc(sizeof(CompareFuncT));
    SL->CompareFuncT = cf;
    SL->headWord = NULL;
    SL->headFile = NULL;
    SL->nextWord = NULL;
    SL->nextFile = NULL;
    SL-> word = NULL;
    SL-> file = NULL;
    SL-> count = 0; 
    return SL;
}

SortedListPtr SLCreateWord(char* word, CompareFuncT cf) {
    SortedListPtr SL = (SortedListPtr)malloc(sizeof(SortedList));
    //SL->CompareFuncT = (CompareFuncT)malloc(sizeof(CompareFuncT));
    SL->CompareFuncT = cf;
    SL->headWord = NULL;
    SL->headFile = NULL;
    SL->nextWord = NULL;
    SL->nextFile = NULL;
    SL -> word = (char *) malloc(strlen(word) + 1);
    strcpy(SL -> word,word);
    //SL-> word = word;
    SL-> file = NULL;
    SL-> count = 0; 
    return SL;
}

SortedListPtr SLCreateFile(char* file) {
    SortedListPtr SL = (SortedListPtr)malloc(sizeof(SortedList));
    //SL->CompareFuncT = (CompareFuncT)malloc(sizeof(CompareFuncT));
    SL->CompareFuncT = NULL;
    SL->headWord = NULL;
    SL->headFile = NULL;
    SL->nextWord = NULL;
    SL->nextFile = NULL;
    //SL -> word = (char *) malloc(strlen(word) + 1);
    //strcpy(SL -> word,word);
    SL-> word = NULL;
    SL -> file = (char *) malloc(strlen(file) + 1);
    strcpy(SL -> file, file);
    //SL-> file = NULL;
    SL-> count = 1; 
    return SL;
}
/*
 * Will insert nodes into sorted list, or create a head for new sorted
 * list. Return 1 if successful, 0 if any other case. The sorted list is
 * in descending order.
 */
void SLInsertFile(SortedListPtr list, char* file) {
    //SortedListPtr temp = (SortedListPtr) malloc(sizeof(SortedList));
    //SortedListPtr temp = (SortedListPtr) malloc(sizeof(SortedList));
    //SortedListPtr temp = SLCreateWord(word);
    //temp -> word = (char *) malloc(strlen(word) + 1);
    //strcpy(temp -> word,word);
    
    if (list -> headFile == NULL) {                             //No word inserted yet.
        SortedListPtr temp = SLCreateFile(file);
        list -> headFile = temp;
        return;     
    }
    else {
        int comp = list->CompareFuncT((void*)file, (void*)list->headFile->file);
        if (comp < 0) {                             /*If the new word is less than the head's data*/
            SortedListPtr temp = SLCreateFile(file);
            temp->nextFile = list->headFile;
            list->headFile = temp;
            return;
        }
        else if (comp == 0) {
            list -> headFile -> count+=1;
            return;
        }                                    
        else if (list->headFile->nextFile == NULL) {    /*If the head's word is less than the new object and there is nothing after the word*/
            SortedListPtr temp = SLCreateFile(file);
            list->headFile->nextFile = temp;
            return;
        }
        else {
            SortedListPtr curr = list->headFile;                            /*Points to the headWord of the list*/
            SortedListPtr prev = NULL;                                      /*Initializes prev pointer*/
            while (curr->nextFile != NULL) {                                /*While the pointer is not null*/
                comp = list->CompareFuncT(file, curr->nextFile->file);  /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                prev = curr;                    /*Makes the previous pointer the current pointer*/
                if (comp < 0) {                 /*If word is smaller than curr->nextWord*/
                    SortedListPtr temp = SLCreateFile(file);
                    temp->nextFile = prev->nextFile;
                    prev->nextFile = temp;
                    return;
                }
                else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                    curr -> nextFile -> count +=1;
                    return;             //Temporary - JCaverly
                }
                else {                                  /*If curr->nextWord's word is smaller than the new word*/
                    if (curr->nextFile->nextFile == NULL) {     /*If curr->next->next is null*/
                        SortedListPtr temp = SLCreateFile(file);
                        curr->nextFile->nextFile = temp;        /*curr->next->next is temp*/
                        return;
                    }
                    else {                      /*If curr->next->next is not null*/
                        curr = curr->nextFile;      /*Moves on to the next pointer and continues the loop*/
                    }
                }
            }
            return;
        }
    }
}

/*
 * Will insert nodes into sorted list, or create a head for new sorted
 * list. Return 1 if successful, 0 if any other case. The sorted list is
 * in descending order.
 */
void SLInsertWord(SortedListPtr list, char* word, char* fileName) {
    //SortedListPtr temp = (SortedListPtr) malloc(sizeof(SortedList));
    //SortedListPtr temp = (SortedListPtr) malloc(sizeof(SortedList));
    //SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
    //temp -> word = (char *) malloc(strlen(word) + 1);
    //strcpy(temp -> word,word);
    
    if (list -> headWord == NULL) {                             //No word inserted yet.
        SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
        list -> headWord = temp;            
        SLInsertFile(list -> headWord,fileName);
        return;     
    }
    else {
        int comp = list->CompareFuncT(word, list->headWord->word);
        if (comp < 0) {                             /*If the new word is less than the head's data*/
            SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
            temp->nextWord = list->headWord;
            list->headWord = temp;
            SLInsertFile(temp,fileName);
            return;
        }
        else if (comp == 0) {
            SLInsertFile(list -> headWord,fileName);                //Look for file count
            return;
        }
        else if (list->headWord->nextWord == NULL) {    /*If the head's word is less than the new object and there is nothing after the word*/
            SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
            list->headWord->nextWord = temp;
            SLInsertFile(temp,fileName);
            return;
        }
        else {
            SortedListPtr curr = list->headWord;                            /*Points to the headWord of the list*/
            SortedListPtr prev = NULL;                                      /*Initializes prev pointer*/
            while (curr->nextWord != NULL) {                                /*While the pointer is not null*/
                comp = list->CompareFuncT(word, curr->nextWord->word);  /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                prev = curr;                    /*Makes the previous pointer the current pointer*/
                if (comp < 0) {                 /*If word is smaller than curr->nextWord*/
                    SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
                    temp->nextWord = prev->nextWord;
                    prev->nextWord = temp;
                    SLInsertFile(temp,fileName);
                    return;
                }
                else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                    SLInsertFile(curr -> nextWord,fileName);
                    return;             //Temporary - JCaverly
                }
                else {                                  /*If curr->nextWord's word is smaller than the new word*/
                    if (curr->nextWord->nextWord == NULL) {     /*If curr->next->next is null*/
                        SortedListPtr temp = SLCreateWord(word, list -> CompareFuncT);
                        curr->nextWord->nextWord = temp;        /*curr->next->next is temp*/
                        SLInsertFile(temp,fileName);
                        return;
                    }
                    else {                      /*If curr->next->next is not null*/
                        curr = curr->nextWord;      /*Moves on to the next pointer and continues the loop*/
                    }
                }
            }
            return;
        }
    }
}

/*void printFiles (SortedListPtr list) {
   list = list -> headFile;
   for (;list != NULL;list = list -> nextFile) {
       if (list -> nextFile == NULL) {
           printf("\t\t{\"%s\" : %d}\n",list -> file, list -> count);
           break;
       }
       printf("\t\t{\"%s\" : %d},\n",list -> file, list -> count);
   }
   return;
}*/

void printFiles(SortedListPtr list, FILE * file) {
    int max = 0;
    SortedListPtr p = list -> headFile;
    max = p->count;
    for (; p != NULL; p = p -> nextFile) {
        if (p->count > max)
            max = p->count;
    }
    if (max == -1)
        return;
    p = list -> headFile;
    for (; p != NULL; p = p -> nextFile) {
        if (p->count == max && p -> nextFile == NULL) {
            fprintf(file, "\t\t{\"%s\" : %d}\n",p -> file, p -> count);
            p->count = -1;
        }
        else if (p->count == max && p -> nextFile != NULL) {
            fprintf(file, "\t\t{\"%s\" : %d},\n",p -> file, p -> count);
            p->count = -1;
        }
        //printFiles(list);
    }
    printFiles(list, file);
    return;
}

void printList(SortedListPtr list, FILE * file) {
    list = list -> headWord;
    for (;list != NULL; list = list -> nextWord) {
        fprintf(file, "\t{\"%s\" : [\n",list -> word);
        printFiles(list, file);
        if (list -> nextWord == NULL) {
        fprintf(file, "\t]}\n");
        break;
        }
        fprintf(file, "\t]},\n");
    }
    return;
}

void cleanFiles(SortedListPtr list) {
    SortedListPtr temp, temp1;
    temp = list -> headFile;
    while (temp != NULL) {
        temp1 = temp;
        temp = temp -> nextFile;
        free (temp1 -> file);
        free(temp1);
    }
    return;
}

void cleanList(SortedListPtr list) {
    SortedListPtr temp, temp1;
    temp = list -> headWord;
    while (temp != NULL) {
        temp1 = temp;
        temp = temp -> nextWord;
        cleanFiles(temp1);
        free(temp1 -> word);
        free (temp1);
    }
    //free (list-> CompareFuncT);
    free (list);
    return;
}
