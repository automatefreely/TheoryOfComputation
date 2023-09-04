// Author: Swaroop Dora (Automate Freely)
// Github: https://github.com/automatefreely |
// Email: automatefreely@gmail.com / iit2022052@iiita.ac.in

// Description: This program takes an DFA and minimizes it.
//              The DFA is represented as a table with states as rows and symbols as columns.
//              The user is asked to enter the number of states and symbols.
//              Then the user is asked to enter the number of transitions from each state on each symbol.
//              Then the user is asked to enter the final states.
//              then the program prints the minimized DFA table.

// To test: 7 2 1 2 5 4 6 4 0 4 4 4 5 5 6 6 2 5 6

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

    int dfa[nstates][nsymbols];

    printf("enter the dfa table:\n");
    for (int i = 0; i < nstates; i++)
    {
        for (int j = 0; j < nsymbols; j++)
        {
            printf("enter the transition from state %d on symbol %d: ", i, j);
            scanf("%d", &dfa[i][j]);
        }
    }

    int nfinal;
    printf("enter number of final states: ");
    scanf("%d", &nfinal);

    int final[nfinal];
    printf("enter the final states: ");
    for (int i = 0; i < nfinal; i++)
    {
        scanf("%d", &final[i]);
    }

    // print dfa
    printf("dfa table:\n");
    for (int i = 0; i < nstates; i++)
    {
        for (int j = 0; j < nsymbols; j++)
        {
            printf("%d ", dfa[i][j]);
        }
        printf("\n");
    }

    // we will remove all the unreachable states from the dfa
    // we will do this by traversing the dfa from the initial state and pushing all the reachable states into a vector
    // then we will remove all the states that are not in the vector

    // make a vector to store the reachable states
    vector reachable_states;
    reachable_states.size = 0;

    // push the initial state into the vector
    push(&reachable_states, 0);

    // traverse the dfa from the initial state and push all the reachable states into the vector
    for (int i = 0; i < reachable_states.size; i++)
    {
        int state = reachable_states.arr[i];
        for (int j = 0; j < nsymbols; j++)
        {
            int next_state = dfa[state][j];
            int is_in_reachable_states = 0;
            for (int k = 0; k < reachable_states.size; k++)
            {
                if (next_state == reachable_states.arr[k])
                {
                    is_in_reachable_states = 1;
                    break;
                }
            }
            if (is_in_reachable_states == 0)
            {
                push(&reachable_states, next_state);
            }
        }
    }

    // print the reachable states
    printf("reachable states: ");
    for (int i = 0; i < reachable_states.size; i++)
    {
        printf("%d ", reachable_states.arr[i]);
    }
    printf("\n");

    // remove all the states that are not in the reachable states vector
    for (int i = 0; i < nstates; i++)
    {
        int is_in_reachable_states = 0;
        for (int j = 0; j < reachable_states.size; j++)
        {
            if (i == reachable_states.arr[j])
            {
                is_in_reachable_states = 1;
                break;
            }
        }
        if (is_in_reachable_states == 0)
        {
            for (int j = 0; j < nsymbols; j++)
            {
                dfa[i][j] = -1;
            }
        }
    }

    // state 0 is the initial start state

    // partistioning the states into final and non-final states and pushing them into vector 1 and vector 2 respectively
    // foe each state in the vector 1 and vector 2, we will check if they are distinguishable or not and if they are distinguishable, we will partition them into two vectors
    // we will keep doing this until next partitioning does not change the partitioning
    // we will beigin with initial partitioning of final and non-final states and then keep partitioning the states until we get the partitioning that matches the previous partitioning

    vector partition[nstates];
    int partition_size = 0;

    // make the partition_size = 2
    partition_size = 2;
    // fill partition 0 with non-final state and partition 1 with final states
    partition[0].size = 0;
    partition[1].size = 0;
    for (int i = 0; i < nstates; i++)
    {
        int is_final_state = 0;
        for (int j = 0; j < nfinal; j++)
        {
            if (i == final[j])
            {
                is_final_state = 1;
                break;
            }
        }
        if (is_final_state == 1)
        {
            push(&partition[1], i);
        }
        else
        {
            push(&partition[0], i);
        }
    }

    // print the initial partitioning
    printf("initial partitioning:\n");
    for (int i = 0; i < partition_size; i++)
    {
        printf("partition %d: ", i);
        for (int j = 0; j < partition[i].size; j++)
        {
            printf("%d ", partition[i].arr[j]);
        }
        printf("\n");
    }

    int flag = 1;
    while (flag == 1)
    {
        vector new_partition[nstates];
        int new_partition_size = 0;
        for (int i = 0; i < partition_size; i++)
        {
            for (int j = 0; j < partition[i].size; j++)
            {
                int state = partition[i].arr[j];
                int is_in_new_partition = 0;
                for (int k = 0; k < new_partition_size; k++)
                {
                    for (int l = 0; l < new_partition[k].size; l++)
                    {
                        if (state == new_partition[k].arr[l])
                        {
                            is_in_new_partition = 1;
                            break;
                        }
                    }
                    if (is_in_new_partition == 1)
                    {
                        break;
                    }
                }
                if (is_in_new_partition == 1)
                {
                    continue;
                }
                new_partition[new_partition_size].size = 0;
                push(&new_partition[new_partition_size], state);
                for (int k = j + 1; k < partition[i].size; k++)
                {
                    int next_state = partition[i].arr[k];
                    int is_distinguishable = 0;
                    for (int symbol = 0; symbol < nsymbols; symbol++)
                    {
                        int next_state1 = dfa[state][symbol];
                        int next_state2 = dfa[next_state][symbol];
                        int is_in_same_partition = 0;
                        for (int l = 0; l < partition_size; l++)
                        {
                            for (int m = 0; m < partition[l].size; m++)
                            {
                                if (next_state1 == partition[l].arr[m])
                                {
                                    for (int n = 0; n < partition[l].size; n++)
                                    {
                                        if (next_state2 == partition[l].arr[n])
                                        {
                                            is_in_same_partition = 1;
                                            break;
                                        }
                                    }
                                }
                                if (is_in_same_partition == 1)
                                {
                                    break;
                                }
                            }
                            if (is_in_same_partition == 1)
                            {
                                break;
                            }
                        }
                        if (is_in_same_partition == 0)
                        {
                            is_distinguishable = 1;
                            break;
                        }
                    }
                    if (is_distinguishable == 0)
                    {
                        push(&new_partition[new_partition_size], next_state);
                    }
                }
                new_partition_size++;
            }
        }
        if (new_partition_size == partition_size)
        {
            flag = 0;
            // print the partitioning
            printf("final partitioning:\n");
            for (int i = 0; i < partition_size; i++)
            {
                printf("partition %d: ", i);
                for (int j = 0; j < partition[i].size; j++)
                {
                    printf("%d ", partition[i].arr[j]);
                }
                printf("\n");
            }
        }
        else
        {
            partition_size = new_partition_size;
            for (int i = 0; i < partition_size; i++)
            {
                partition[i].size = 0;
                for (int j = 0; j < new_partition[i].size; j++)
                {
                    push(&partition[i], new_partition[i].arr[j]);
                }
            }
            // print the partitioning
            printf("partitioning:\n");
            for (int i = 0; i < partition_size; i++)
            {
                printf("partition %d: ", i);
                for (int j = 0; j < partition[i].size; j++)
                {
                    printf("%d ", partition[i].arr[j]);
                }
                printf("\n");
            }
        }
    }

    // make the minimized dfa table
    int minimized_dfa[partition_size][nsymbols];
    for (int i = 0; i < partition_size; i++)
    {
        for (int j = 0; j < nsymbols; j++)
        {
            minimized_dfa[i][j] = -1;
        }
    }

    for (int i = 0; i < partition_size; i++)
    {
        for (int j = 0; j < nsymbols; j++)
        {
            int state = partition[i].arr[0];
            int next_state = dfa[state][j];
            for (int k = 0; k < partition_size; k++)
            {
                for (int l = 0; l < partition[k].size; l++)
                {
                    if (next_state == partition[k].arr[l])
                    {
                        minimized_dfa[i][j] = k;
                        break;
                    }
                }
                if (minimized_dfa[i][j] != -1)
                {
                    break;
                }
            }
        }
    }

    // print the minimized dfa table
    printf("minimized dfa table:\n");
    // print the symbols and the state with minimize dfa table
    printf("   ");
    for (int i = 0; i < nsymbols; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
    for (int i = 0; i < partition_size; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < nsymbols; j++)
        {
            if (minimized_dfa[i][j] == -1)
            {
                printf("  ");
            }
            else
            {
                printf("%d ", minimized_dfa[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}