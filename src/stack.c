#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/*________________________________________________________________________________________________________________________

    This file contains relative to stacks (as the interpretor must contain one).
    Here are the classic stack-manipulations functions (push, pop, ...), and every action requiering to change
    the stack of the interpretor will only use these functions.
    As the size of the stack will surely change during the execution of the image.ppm, 
    we use dynamic arrays to store the <int> values.
________________________________________________________________________________________________________________________*/


/*
Implementation for stacks. 
'top' indicates the index of the current top. 
Thus the top of an empty stack equals -1 

typedef struct stack {
    int top;
    int size;
    int *tab;
} stack;

*/


/*
@requires : s points to a valid stack
@assigns : *s
@ensures : sets the top to -1, indicating that the stack is empty */
void stack_init (stack *s) {
    s->top = -1;
    // As we want to allocate as little memory as possible, the created stack has a size of 1,
    // and will be recised if needed.
    s->size = 1;
    s->tab = malloc(sizeof(int));
}


/*
@requires : s points to a valid stack
@assigns : *s
@ensures : free the memory used by 's'   */
void stack_free (stack *s) {
    free(s->tab);
    free(s);
}


/*
This is not one of the classic stack manipulation function, but it will be usefull to know the size of the stack
before performing the actions on it, to be sure the stack does contain enough elements.
@requires : s points to a valid stack
@assigns : *s
@ensures : returns the size of the stack   */
int stack_size (stack *s) {
    return (s->top + 1);
}


/*
@requires : nothing
@assigns : dynamically allocates memory for a stack
@ensures : returns a pointer to a new empty stack */
stack* stack_empty () {
    stack *s = malloc(sizeof(stack));
    stack_init(s);
    return s;
}


/*
@requires : nothing
@assigns : nothing
@ensures : tests if *s is empty */
int stack_isEmpty (stack *s) {
    return s->top == -1;
}


/*
As we use dynamic arrays, here is a function to resize the stack if needed when pushing a new element,
or if possible after poping one.
@requires : 's' points to a valid stack, and s->tab has less than 'new_size' elements.
@assigns : frees 's' but allocates other memory for another stack
@ensures : transfers the integers stored in *s in a new stack of size 'new_size'  */

void stack_resize (stack *s, int new_size) {

    // We store the adress of the current array, to be able to copy its elements after 
    // making 's' point to another one
	int *tmp = s->tab;

    // We allocate a new array of size 'new_size'
	s->tab = malloc(new_size * sizeof(int));
    s->size = new_size;

    // We copy the elements of the previous array to the new one
	for(int i = 0; i < s->top + 1; i++){
		s->tab[i] = tmp[i];
	}

	// We can free the previous array
	free(tmp);
}


/*
@requires : s points to a valid stack
@assigns : *s
@ensures : adds 'elem' on the top of *s  */
void stack_push (stack *s, int elem) {
    // if the stack is full,
    if (s->top == s->size - 1) {
        // we double its size
        stack_resize(s, 2 * s->size);
    }
    // we add 'elem' above the previous top
    s->tab[s->top + 1] = elem;
    // we update the index of the top
    s->top++;
}


/*
@requires : s points to a valid stack
@assigns : *s
@ensures : remove from *s its top element and returns it    */
int stack_pop (stack *s) {
    // If only a third of the size is used,
    if (3 * s->top < s->size) {
        // we devise its size by half.
		stack_resize(s, s->size / 2);
	}
    // No need to physically remove the top element, qualifying the "second" one as the top is enough 
    s->top--;
    // We return the previous top, which is now on 'top + 1' position
    return s->tab[s->top + 1];
}


/*
@requires : nothing
@assigns : nothing
@ensures : prints the elements of the stack : [top] - [.] - ... - [bottom]]   */
void stack_print (stack *s) {
    for (int i = s->top; i >= 0; i--) {
        printf("-[%d]", s->tab[i]);
    }
    printf("\n");
}