// Author: Swaroop Dora | Anand Raj
// Github: https://github.com/automatefreely |
// Email: automatefreely@gmail.com / iit2022052@iiita.ac.in / iit2022047@iiita.ac.in

// Description: This program takes an e-nfa as input and return nfa as output.
//              The e-nfa is represented as a table with states as rows and symbols as columns. The first column is epsilon.
//              The user is asked to enter the number of states and symbols. Then the user is asked to enter the number of
//              transitions from each state on each symbol. Then the user is asked to enter the final states.
//              then the program prints the nfa table.

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



    // convert e-nfa to nfa
    vector nfa[nstates][nsymbols];

    for (int state = 0; state < nstates; state++)
        for (int symbol = 1; symbol < nsymbols; symbol++)
        {
            nfa[state][symbol].size = 0;
            // for each state in epsilon closure of this state
            // take all transitions on this symbol
            // and then take epsilon closure of all those states
            // and add them to the nfa table
            for (int transition = 0; transition < e_nfa_closure[state].size; transition++)
                for (int transition2 = 0; transition2 < e_nfa[e_nfa_closure[state].arr[transition]][symbol].size; transition2++)
                    for (int transition3 = 0; transition3 < e_nfa_closure[e_nfa[e_nfa_closure[state].arr[transition]][symbol].arr[transition2]].size; transition3++)
                        push(&nfa[state][symbol], e_nfa_closure[e_nfa[e_nfa_closure[state].arr[transition]][symbol].arr[transition2]].arr[transition3]);
        }

    printf("nfa table:\n");
    for (int state = 0; state < nstates; state++)
        for (int symbol = 1; symbol < nsymbols; symbol++)
        {
            printf("state %d on symbol %d: ", state, symbol);
            for (int transition = 0; transition < nfa[state][symbol].size; transition++)
                printf("%d ", nfa[state][symbol].arr[transition]);
            printf("\n");
        }
    return 0;
    }
