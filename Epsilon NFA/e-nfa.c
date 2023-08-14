// Author: Swaroop Dora 
// Github: https://github.com/automatefreely
// Email: automatefreely@gmail.com / iit2022052@iiita.ac.in
// Description: This program takes an e-nfa as input and a string and checks if the string is accepted by the e-nfa or not.
//              The e-nfa is represented as a table with states as rows and symbols as columns. The first column is epsilon.
//              The user is asked to enter the number of states and symbols. Then the user is asked to enter the number of
//              transitions from each state on each symbol. Then the user is asked to enter the final states. Then the user
//              is asked to enter a string. The program then prints the e-closure of each state. Then for each symbol in the
//              string, the program takes the e-closure of the current state, then takes the transition on the symbol and
//              then takes the e-closure of the resulting states. The program then prints the final states. If any of the
//              final states belong to the set of final states, the string is accepted, else it is rejected.

#include <stdio.h>
#include <stdlib.h>

// implement a vector
typedef struct
{
    int *arr;
    int size;
} vector;

// to push element to vector
void push(vector *v, int element)
{
    if (v->size == 0)
        v->arr = (int *)malloc(sizeof(int));
    else
        v->arr = (int *)realloc(v->arr, sizeof(int) * (v->size + 1));
    v->arr[v->size] = element;
    v->size++;
}

// to pop element from vector
int pop(vector *v)
{
    if (v->size == 0)
    {
        printf("vector empty\n");
        return -1;
    }
    int element = v->arr[v->size - 1];
    v->size--;
    v->arr = realloc(v->arr, (v->size * sizeof(int)));
    return element;
}

int main()
{
    int nstates;
    printf("enter number of states: ");
    scanf("%d", &nstates);
    int nsymbols;
    printf("enter number of symbols: ");
    scanf("%d", &nsymbols);
    vector e_nfa[nstates][nsymbols];
    vector should_be_final;
    should_be_final.size = 0;

    // take input of e-nfa table
    for (int state = 0; state < nstates; state++)
        // 0 symbol is epsilon
        for (int symbol = 0; symbol < nsymbols; symbol++)
        {
            e_nfa[state][symbol].size = 0;
            printf("enter number of transitions from state %d on symbol %d: ", state, symbol);
            int ntransitions;
            scanf("%d", &ntransitions);

            for (int transition = 0; transition < ntransitions; transition++)
            {
                printf("enter transition %d: ", transition);
                int next_state;
                scanf("%d", &next_state);
                push(&e_nfa[state][symbol], next_state);
            }
        }

    // take input of final states
    printf("enter number of final states: ");
    int nfinal_states;
    scanf("%d", &nfinal_states);
    printf("enter final states: ");
    for (int i = 0; i < nfinal_states; i++)
    {
        int final_state;
        scanf("%d", &final_state);
        push(&should_be_final, final_state);
    }

    printf("e-nfa table:\n");
    for (int state = 0; state < nstates; state++)
        for (int symbol = 0; symbol < nsymbols; symbol++)
        {
            printf("state %d on symbol %d: ", state, symbol);
            for (int transition = 0; transition < e_nfa[state][symbol].size; transition++)
                printf("%d ", e_nfa[state][symbol].arr[transition]);
            printf("\n");
        }

    printf("epsilon closure of this nfa: \n");
    vector e_nfa_closure[nstates];
    for (int state = 0; state < nstates; state++)
    {
        e_nfa_closure[state].size = 0;
        push(&e_nfa_closure[state], state);
        for (int transition = 0; transition < e_nfa[state][0].size; transition++)
            push(&e_nfa_closure[state], e_nfa[state][0].arr[transition]);
    }
    for (int state = 0; state < nstates; state++)
    {
        printf("state %d: ", state);
        for (int transition = 0; transition < e_nfa_closure[state].size; transition++)
            printf("%d ", e_nfa_closure[state].arr[transition]);
        printf("\n");
    }


    // take input of string untill user enter nothing
    while(1){
        char str[100];
        printf("enter a string: ");
        scanf("%s", str);
        // if string is empty, break
        if(str[0] == '\0')
            break;

        int current_state = 0;
        vector *final_states = malloc(sizeof(vector));
        (*final_states).size = 0;
        push(final_states, 0);

        // for each symbol in string taking e-closure and transitionand e-closure
        for (int i = 0; str[i] != '\0'; i++)
        {
            int symbol = str[i] - 'a' + 1;
            // take e-closure of final_states
            vector *temp = malloc(sizeof(vector));
            temp->size = 0;
            for (int i = 0; i < final_states->size; ++i)
            {
                int state = final_states->arr[i];
                for (int j = 0; j < e_nfa_closure[state].size; j++)
                    push(temp, e_nfa_closure[state].arr[j]);
            }
            // check if it has transition on the symbol
            vector *temp2 = malloc(sizeof(vector));
            temp2->size = 0;
            for (int i = 0; i < temp->size; ++i)
            {
                int state = temp->arr[i];
                for (int j = 0; j < e_nfa[state][symbol].size; j++)
                    push(temp2, e_nfa[state][symbol].arr[j]);
            }
            // take e-closure of temp2
            vector *temp3 = malloc(sizeof(vector));
            temp3->size = 0;
            for (int i = 0; i < temp2->size; ++i)
            {
                int state = temp2->arr[i];
                for (int j = 0; j < e_nfa_closure[state].size; j++)
                    push(temp3, e_nfa_closure[state].arr[j]);
            }
            // set final state to temp3;
            final_states = temp3;
        }

        // print the final state
        printf("final states returned: ");
        for (int state = 0; state < final_states->size; state++)
            printf("%d ", final_states->arr[state]);
        printf("\n");

        // check if any element of final_state belong to should_be_final
        int flag = 0;
        for (int i = 0; i < final_states->size; i++)
        {
            for (int j = 0; j < should_be_final.size; j++)
                if (final_states->arr[i] == should_be_final.arr[j])
                {
                    flag = 1;
                    break;
                }
            if (flag == 1) break; 
        }
        if (flag) printf("string accepted\n"); 
        else printf("string rejected\n"); 
    }

    

    return 0;
}