#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct Stack {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    if (g->alst[src] == NULL) {
        g->alst[src] = nn;
    } else {
        NODE *last = g->alst[src];
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = nn;
    }

    nn = create_node(src);
    if (g->alst[dest] == NULL) {
        g->alst[dest] = nn;
    } else {
        NODE *last = g->alst[dest];
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = nn;
    }
}


GPH *create_g(int v) {
    int i;
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;

    g->vis[v_nr] = 1;
    printf("%d ", v_nr);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);

    for (i = 0; i < edg_nr; i++) {
        do {
            printf("Introduceti muchia %d (src dest): ", i + 1);
            scanf("%d %d", &src, &dest);
        } while (src < 1 || src > nrv || dest < 1 || dest > nrv);

        add_edge(g, src - 1, dest - 1);
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(5, sizeof(int));

    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, i);

        for (int j = 0; j < nrv && !canbe[j]; j++) {
            for (int k = 0; k < nrv && !canbe[j]; k++) {
                if (s1->arr[i] == k && s2->arr[j] == i) {
                    canbe[0] = 1;
                }
            }
        }
    }
}

int main() {
    int nrv;
    int edg_nr;
    int src, dest;
    int i;
    int vortex_1;
    int virtex_2;
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    printf("Parcurgere DFS:\n");
    scanf("%d", &vortex_1);
    DFS(g, s1, vortex_1 - 1);

    return 0;
}
