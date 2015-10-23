/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

enum states {
    undetermined,			//The begining of a token
    malformed,
    isAlphaNumeric, //Once a letter is found, it will be a word no matter what.
    done,
} curr_State, temp_State;

char err;
char* pc;
int onlySpaces = 0;

struct TokenizerT_ {
    int i;   			//Index number used later for creating tokens
    int stringSize;		//String size for getnexttoken function
    char *myString;		//input string
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    char copy[strlen(ts)]; 					//copy of string ts
    strcpy(copy,ts);
    
    TokenizerT *ptr = (TokenizerT*) malloc (sizeof(struct TokenizerT_));   //Allocation of size for TokenizerT_
    ptr -> i = 0;
    ptr -> stringSize = strlen(copy);
    ptr -> myString = strdup(copy);
    
    pc = (ptr -> myString);
    
    return ptr;           /*returning the pointer*/
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk);
}


/*beginning of all states and function calls for states. Each function checks for the
 * current state and current char and makes a decision based on that.
 * It may change states or figure out that the current token is in a finished
 * state. Each function is called upon based on the previous state the FSM
 * was in. */

/*set the global char to the malform char of token*/
int malChar(char ptr) {
    err = ptr;
    return 0;
}

/* this will check whether or not the first character of token is a valid char of
 * (1-9), (this will be int or float), '0' (which will be float, hex, oct or zero state) or a letter (word)
 * or one of the many C operators or a malformed character. */
int isZeroLetterOrNot(char x) {
    if ((x >= 'a' && x <= 'z')||(x >= 'A' && x <= 'Z')) {
        curr_State = isAlphaNumeric;
    }
    else {
        curr_State = malformed;
        temp_State = malformed;
        malChar(x);
    }
    
    return 0;
}

/*This function will check if the next character after the
 * first character in a word token is valid, if it is not
 * state becomes undetermined again*/
int isAlphaNumericOrNot(char x) {
    if (isalnum(x)) {
    }
    else {
        temp_State = curr_State;
        curr_State = done;
    }
    return 0;
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    if (*pc == '\0') {
        TKDestroy(tk);
        exit (0);
    }
    
    char* token = (char*) malloc (((tk -> stringSize)+2)*sizeof(char));
    char* tempToken = (char*) malloc(sizeof(char*));
    tempToken = token;
    
    while (isspace(*pc)) {
        pc++;
    }
    
    if (*pc == '\0' && onlySpaces == 0) {
        printf("Only whitespace entered\n");
        TKDestroy (tk);
        exit (0);
    }
    else if (*pc == '\0') {
        TKDestroy (tk);
        exit(0);
    }
    
    onlySpaces++;			//only if a nonspace is found;
    
    curr_State = undetermined;
    
    while (*pc != '\0') {
        if ((curr_State != done)&&(curr_State != undetermined)) {
            *token = *pc;
            pc++;
            token++;
        }
        switch(curr_State) {
            case (malformed): {     /*temporary*/
                *token = '\0';
                return tempToken;
            }
            case (undetermined): {
                isZeroLetterOrNot(*pc);
                break;
            }
            case (isAlphaNumeric): {
                isAlphaNumericOrNot(*pc);
                break;
            }
            case (done): {
                *token = '\0';
                return tempToken;
            }
            default:
                break;
        }
    }
    *token = '\0';
    return tempToken;
}

/* Returns the type of token for print to terminal*/
char* TKGetState(char* token) {
    switch (temp_State) {
        case(malformed): {
            return "ERROR";
            break;
        }
        case (isAlphaNumeric): {
            if (isJavaKeyword(token) == 1){
                return "C KEYWORD";
                break;
            }
            else {
                return "WORD";
                break;
            }
        }
        default:
            break;
    }
    return 0;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
    if (argc == 1 || argv[1][0] == '\0') {									//in case no arguments are given
        fprintf(stdout,"No arguments given!\n");
        return 0;
    }
    
    TokenizerT *tokenizer = TKCreate (argv[1]);        //creation of tokenizerT	
    curr_State = undetermined;	
    char* token;
    
    while (*tokenizer->myString != '\0') {
        token = TKGetNextToken(tokenizer);
        if (temp_State != isMultiComment && temp_State != isSingleComment && temp_State !=isEOC) { 
            char* status = TKGetState(token);
            fprintf(stdout,"%s: %s ",status,token);
            if (temp_State == malformed) {
                fprintf(stdout,"Error caused by: [0x%x]",err);
            }
            printf("\n");
        }
    }
    TKDestroy(tokenizer);
    return 0;
}
