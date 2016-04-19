/*
 Yuya Oguchi
 COEN12L Lab2
 sorted.c
 1/26/15
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "set.h"

#include <stdio.h>

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
    assert(sp!= NULL);// check to see if there is actually sp
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

//O(logn)
int findElement(SET *sp, char *elt, bool *found)
{
    	int mid;
        int lo = 0;
        int hi = sp->count-1;

        *found = false;// found is false until found
        if (sp->count == 0)
        	return 0;
        while (lo <= hi) {// do it while lo doesnt go over high
                mid = (lo + hi) / 2; // declare mid
                int result = strcmp(sp->elts[mid], elt);
                if (result < 0) // number is in lower half
                    hi = mid - 1; // make high to middle
                else if (result > 0) // number is in higher half
                    lo = mid + 1; // make low to middle
                else{
                    *found = true; // if elt is at the right spot, return the val
                    return mid;
                  }
        }
        return lo; // if nothing found, return lo, but found is false

}
//O(n)
bool hasElement(SET *sp, char *elt)
{
	bool found;
    int i = findElement(sp, elt, &found);//pointer found is changed when findelement is run
    return found;// return the result

}
//O(n)
bool addElement(SET *sp, char *elt)
{
	bool found;
    int i = findElement(sp, elt, &found);// check for duplicate and location of the elt
    int j;
    if (found == false)// check to make sure there is no duplicate
    {
    	for(j = sp->count; i < j;j--)// swap all the elts in locations from elt to end
    	{sp->elts[j] = sp->elts[j-1];
    	}
        sp->elts[i] = strdup(elt); // add new elt to the newly opened spot
        sp->count++;//increment overall count
        return true;
    }
    return false;

}
//O(n)
bool removeElement(SET* sp, char *elt)
{
	bool found;
    int i = findElement(sp, elt, &found);// check for duplicate and location of the elt
    int j;
    if(found == true)// if there is elt, then remove it
    {
        free(sp->elts[i]);// free the location
        sp->count--;
        for(j = i; sp->count > j;j++)//move all the loc from elt to end to front by one
    	{sp->elts[j] = sp->elts[j+1];
    	}
        return true;
    }

    return false;// no elt matched elts in set.
}
