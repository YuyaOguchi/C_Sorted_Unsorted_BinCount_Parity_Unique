/*
 Yuya Oguchi
 COEN12L Lab2
 unsorted.c
 1/26/15
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "set.h"

struct set
{
    int count; //current number of elts(words)
    int length; // max length
    char **elts; // pointer to word
};
//O(1)
SET *createSet(int maxElts)
{
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL); //check to see if sp already exist
    sp -> count = 0; // store 0 as count of elts
    sp -> length = maxElts; // set the max length as max elts
    sp -> elts = malloc(maxElts*sizeof(char*)); // create space for each elt
    assert(sp-> elts != NULL); // check to make sure the space is created
    return sp; // return the set
}
//O(n)
void destroySet(SET *sp)
{
    assert(sp!= NULL);//check to see if sp exist
    int i;
    for (i = 0; sp -> count<i; i++)
    {
        free(sp->elts[i]);// free each elts in the set
    }
    free(sp->elts);//free pointer of elts
    free(sp);// free elts

}
//O(1)
int numElements(SET *sp)//use the count number stored in the set
{
    return sp->count;//access count
}
//O(n)
int findElement(SET *sp, char *elt) // find if there is elts already in sp
{
    int i;
    for (i=0; sp->count>i; i++)// check for all elts in sp
    {
        if (strcmp(elt, sp->elts[i]) == 0)
        {
            return i; //if elt exist in elts in sp, then return that val
        }
    }
    return -1; // if not duplicate, return -1
}

//O(n)
bool hasElement(SET *sp, char *elt)
{
    int i = findElement(sp, elt); // check for duplicate
    if (i == -1)// if val is not found in sp yet, return false, else return true
    {return false;}
    else
    {return true;}

}

//O(n)
bool addElement(SET *sp, char *elt)
{
    int i = findElement(sp, elt);// find element for duplicate

    if (i == -1)
    {
        sp->elts[sp->count++] = strdup(elt); // add new element to set at the end
        return true;
    }
    return false;//if there is duplicate, do not add

}
//O(n)
bool removeElement(SET* sp, char *elt)
{
    int i = findElement(sp, elt);// find element for duplicate
    if(i != -1)// if there is elt, then remove it
    {
    	free(sp->elts[i]);
        sp->elts[i] = sp->elts[sp->count-1];
        sp->count--;
        return true;
    }

    return false;// no elt matched elts in set.
}
