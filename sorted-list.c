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
        int comp = list->CompareFuncT(file, list->headFile->file);
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

void printFiles (SortedListPtr list) {
   list = list -> headFile;
   for (;list != NULL;list = list -> nextFile) {
        printf("\t\t{\"%s\" : %d},\n",list -> file, list -> count);
   }
   return;
}

void printList(SortedListPtr list) {
    list = list -> headWord;
    for (;list != NULL; list = list -> nextWord) {
        printf("\t{\"%s\" : [\n",list -> word);
        printFiles(list);
        printf("\t]},\n");
    }
    return;
}

void cleanList(SortedListPtr list) {
    SortedListPtr temp, temp1;
    temp = list -> headWord;
    while (temp != NULL) {
        temp1 = temp;
        temp = temp -> nextWord;
        free(temp1 -> word);
        free (temp1);
    }
    //free (list-> CompareFuncT);
    free (list);
    return;
}
    //temp->data = newObj;
    //temp->numPtr+=1;

    //if (list->head == NULL) {
        //list->head = temp;
        //return 1;
    //}
    //else {
        //if (list->CompareFuncT(list->head->data, newObj) < 0) { /*If the new object is greater than the head's data*/
            //temp->next = list->head;
            //list->head = temp;
            //return 1;
        //}
        //else if (list->CompareFuncT(list->head->data, newObj) == 0) {  //Head and newObj is equal no need to insert data
            //return 0;
        //}
        //else if (list->CompareFuncT(list->head->data, newObj) > 0 && list->head->next == NULL) { /*If the head's data is greater than the new object*/
            //list->head->next = temp;
            //return 1;
        //}
        //else {
            //SortedListPtr curr = list->head; /*Points to the head of the list*/
            //SortedListPtr prev = NULL; /*Initializes prev pointer*/
            //while (curr->next != NULL) { /*While the pointer is not null*/
                //int comp = list->CompareFuncT(curr->next->data, newObj); /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                //prev = curr; /*Makes the previous pointer the current pointer*/
                //if (comp < 0) { /*If curr->next's data is less than the new object*/

                    //temp->next = prev->next;
                    //prev->next = temp;
                    //return 1;
                //}
                //else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                    //return 0;
                //}
                //else { /*If curr->next's data is greater than the new object*/
                    //if (curr->next->next == NULL) { /*If curr->next->next is null*/
                        //curr->next->next = temp; /*curr->next->next is temp*/
                        //return 1;
                    //}
                    //else { /*If curr->next->next is not null*/
                        //curr = curr->next; /*Moves on to the next pointer and continues the loop*/
                    //}
                //}
            //}
            //return 0;
        //}
    //}
//}

//*
 //* Will remove nodes from the sorted list if their data matches the data
 //* that is specified. Returns 1 if successful, 0 if any other case.
 //*/
//int SLRemove(SortedListPtr list, void *newObj) {
    //if (list->head == NULL) { /*If the list has nothing in it*/
        //return 0; /*Nothing can be deleted*/
    //}
    //else { /*If the list's head has data*/
        //if (list->CompareFuncT(list->head->data, newObj) < 0) { /*If the head's data is smaller than the new object*/
            //return 0; /*Nothing can be deleted*/
        //}
        //else if (list->CompareFuncT(list->head->data, newObj) == 0) {  /*If the head's data and the new object are equal*/
            //if (list->head->next == NULL) { /*If there is nothing after the head*/
                //if (list->head->numPtr == 1) {      //if head is is only referenced by head
                    //list->DestructFuncT(list->head);
                //}
                //list->head = NULL; /*Makes the head null*/
                //return 1;
            //}
            //else { /*If there is something after the head*/
                //SortedListPtr temp = list->head;
                //list->head = list->head->next; /*Makes the item after the head the new head*/
                //temp->numPtr-=1;
                //if (temp->numPtr == 0) {
                    //list->DestructFuncT(temp);
                //}
                //else {
                    //list->head->numPtr+=1;
                //}
                //return 1;
            //}
        //}
        //else { /*If the head's data is greater than the new object*/
            //if (list->head->next == NULL) { /*If there is nothing after the head*/
                //return 0; /*Nothing can be deleted*/
            //}
            //else { /*If there is something after the head*/
                //SortedListPtr curr = list->head; /*Points to the head of the list*/
                //SortedListPtr prev = NULL; /*Initializes prev pointer*/
                //while (curr->next != NULL) { /*While the pointer is not null*/
                    //int comp = list->CompareFuncT(curr->next->data, newObj); /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                    //SortedListPtr temp = curr->next;
                    //prev = curr; /*Makes the previous pointer the current pointer*/
                    //if (comp < 0) { /*If curr->next's data is less than the new object*/
                        //return 0; /*Nothing can be deleted*/
                    //}
                    //else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                        //prev->next = prev->next->next; /*Makes prev->next->next the item immediately following prev*/
                        //temp->numPtr-=1;
                        //if (temp->numPtr==0) {
                            //list->DestructFuncT(temp);
                        //}
                        //else if (temp->next != NULL) {
                                //temp->next->numPtr+=1;      //if its not null, incrememnt ptr.
                        //}
                        //return 1;
                    //}
                    //else { /*If curr->next's data is greater than the new object*/
                        //if (curr->next->next == NULL) { /*If curr->next->next is null*/
                            //return 0; /*Nothing can be deleted*/
                        //}
                        //else { /*If curr->next->next is not null*/
                            //curr = curr->next; /*Moves on to the next pointer and continues the loop*/
                        //}
                    //}
                //}
            //}
            //return 0;
        //}
    //}
//}

///*
 //* Creates a sorted list iterator, allocating space for it if the sorted
 //* list exists and has a head, and making it point to the head of the list,
 //* incrementing numPtr by 1. It also allocates space for DestructFuncT, which
 //* points to the sorted list's DestructFuncT.
 //*/
//SortedListIteratorPtr SLCreateIterator (SortedListPtr list) {
    //SortedListIteratorPtr iter;
    //if (list == NULL || list->head == NULL)
        //return NULL;
    //else {
        //iter = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
        //iter->DestructFuncT = (DestructFuncT)malloc(sizeof(DestructFuncT));
        //iter->DestructFuncT = list->DestructFuncT;
        //iter->CurrNode = list->head;
        //iter->CurrNode->numPtr+=1;
    //}
    //return iter;
//}

///*
 //* Goes to the node in the list that a given iterator pointing to. If it
 //* doesn't exist, return 0, else return that node's data.
 //*/
//void* SLGetItem(SortedListIteratorPtr iter) {
    //if (iter == NULL)
        //return 0;
    //SortedListPtr temp = iter->CurrNode;
    //if (temp == NULL){
        //return 0;
    //}
    //else {
        //return temp->data;
    //}
//}

//*
 //* Goes to the node in the list that follows the node that a given iterator
 //* is pointing to. If it exists, the iterator will point to that node, and
 //* numPtr for that node will increase by one. numPtr for the node that the
 //* iterator was previously pointing to will decrease by 1, and if the
 //* resulting numPtr is 0, then that node will be destroyed. numPtr for the
 //* current node will decrease by 1, and its data will be returned. If the
 //* node does not exist, the iterator will point to nothing, and numPtr for
 //* the node that it was previously pointing to will decrease by 1. If the
 //* resulting numPtr is 0, then that node will be destroyed. NULL is returned.
 //*/
//void * SLNextItem(SortedListIteratorPtr iter) {
    //SortedListPtr temp = iter->CurrNode;
    //if (temp->next == NULL) {
        //iter->CurrNode = NULL;
        //temp->numPtr-=1;
        //if (temp->numPtr == 0)
            //iter->DestructFuncT(temp);
        //return NULL;
    //}
    //else {
        //iter->CurrNode = temp->next;
        //iter->CurrNode->numPtr+=1;
        //temp->numPtr-=1;
        //if (temp->numPtr == 0){
            //iter->CurrNode->numPtr-=1;
            //iter->DestructFuncT(temp);
        //}
        //return iter->CurrNode->data;
    //}
//}

//*
 //* Destroys a sorted list when called.
 //*/
//void SLDestroy(SortedListPtr list) {
    //if (list != NULL)
        //return;
    //SortedListPtr temp, temp1;
    //temp = list -> head;
    //while (temp != NULL) {
        //temp1 = temp -> next;
        //free(temp -> data);
        //free (temp);
        //temp = temp1;
    //}
    //free(list -> CompareFuncT);
    //free(list -> DestructFuncT);
    //free(list);
//}

//*
 //* Destroys an iterator when called.
 //*/
//void SLDestroyIterator(SortedListIteratorPtr iter) {
    //free(iter -> DestructFuncT);
    //free(iter);
//}

