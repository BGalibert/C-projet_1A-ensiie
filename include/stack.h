#ifndef STACK_H 
#define STACK_H


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
Thus the top of an empty stack equals -1 */
typedef struct stack {
    int top;
    int size;
    int *tab;
} stack;

/*
@requires : s points to a valid stack
@assigns : *s
@ensures : sets the top to -1, indicating that the stack is empty */
void stack_init (stack *s);

/*
@requires : s points to a valid stack
@assigns : *s
@ensures : free the memory used by 's'   */
void stack_free (stack *s);

/*
This is not one of the classic stack manipulation function, but it will be usefull to know the size of the stack
before performing the actions on it, to be sure the stack does contain enough elements.
@requires : s points to a valid stack
@assigns : *s
@ensures : returns the size of the stack   */
int stack_size (stack *s);

/*
@requires : nothing
@assigns : dynamically allocates memory for a stack
@ensures : returns a pointer to a new empty stack */
stack* stack_empty(void);

/*
@requires : s points to a valid stack
@assigns : nothing
@ensures : tests if *s is empty */
int stack_isEmpty (stack *s);

/*
As we use dynamic arrays, here is a function to resize the stack if needed when pushing a new element,
or if possible after poping one     
@requires : 's' points to a valid stack, and s->tab has less than 'new_size' elements.
@assigns : frees 's' but allocates other memory for another stack
@ensures : transfers the integers stored in *s in a new stack of size 'new_size'  */
void stack_resize(stack *s, int new_size);

/*
@requires : s points to a valid stack
@assigns : *s
@ensures : adds 'elem' on the top of *s  */
void stack_push (stack *s, int elem);

/*
@requires : s points to a valid stack
@assigns : *s
@ensures : remove from *s its top element and returns it    */
int stack_pop (stack *s);

/*
@requires : nothing
@assigns : nothing
@ensures : prints the elements of the stack : [top] - [.] - ... - [bottom]   */
void stack_print (stack *s);




#endif
