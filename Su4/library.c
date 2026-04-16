#include <stdio.h>
#include <stdlib.h>

int **createMatrix(int rows, int cols) {
    int **m = malloc(rows * sizeof(*m));
    for (int i = 0; i < rows; i++)
        m[i] = malloc(cols * sizeof(*m[i]));
    return m;
}

void freeMatrix(int **m, int rows) {
    for (int i = 0; i < rows; i++)
        free(m[i]);
    free(m);
}

void pauseScreen() {
    printf("\nНатиснете Enter за да продължите...");
    getchar();
    getchar();
}

void proveriRedoveIKoloni() {
    int rows, cols;

    printf("\nЗадача 1: Проверка на редове и колони\n");
    printf("Въведете редове и колони: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0) return;

    int **m = createMatrix(rows, cols);

    printf("Въведете матрицата:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &m[i][j]);

    int okRows = 1, okCols = 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            if (m[i][j] >= m[i][j + 1]) {
                okRows = 0;
                break;
            }
        }
        if (!okRows) break;
    }

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows - 1; i++) {
            if (m[i][j] <= m[i + 1][j]) {
                okCols = 0;
                break;
            }
        }
        if (!okCols) break;
    }

    printf("Редове нарастващи: %s\n", okRows ? "ДА" : "НЕ");
    printf("Колони намаляващи: %s\n", okCols ? "ДА" : "НЕ");

    freeMatrix(m, rows);
    pauseScreen();
}

void naiDoburSased() {
    int rows, cols;

    printf("\nЗадача 2: Макс сбор на съседи\n");
    printf("Въведете редове и колони: ");
    scanf("%d %d", &rows, &cols);

    int **m = createMatrix(rows, cols);

    printf("Въведете матрицата:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &m[i][j]);

    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    long long best = -2000000000LL;
    int bi = 0, bj = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            long long sum = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + dr[d], nj = j + dc[d];
                if (ni >= 0 && nj >= 0 && ni < rows && nj < cols)
                    sum += m[ni][nj];
            }
            if (sum > best) {
                best = sum;
                bi = i;
                bj = j;
            }
        }

    printf("Елемент: %d на позиция %d %d със сбор %lld\n", m[bi][bj], bi, bj, best);

    freeMatrix(m, rows);
    pauseScreen();
}

void razmeniRedove() {
    int rows, cols;

    printf("\nЗадача 3: Размяна на редове\n");
    printf("Въведете редове и колони: ");
    scanf("%d %d", &rows, &cols);

    int **m = createMatrix(rows, cols);

    printf("Въведете матрицата:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &m[i][j]);

    int max = m[0][0], min = m[0][0];
    int rmax = 0, rmin = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            if (m[i][j] > max) { max = m[i][j]; rmax = i; }
            if (m[i][j] < min) { min = m[i][j]; rmin = i; }
        }

    int *tmp = m[rmax];
    m[rmax] = m[rmin];
    m[rmin] = tmp;

    printf("Матрицата след размяна:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%4d", m[i][j]);
        printf("\n");
    }

    freeMatrix(m, rows);
    pauseScreen();
}

typedef struct {
    int *friends;
    int count;
} Person;

void priyatelstva() {
    int n, m;

    printf("\nЗадача 4: Приятелства\n");
    printf("Въведете хора и връзки: ");
    scanf("%d %d", &n, &m);

    int *deg = calloc(n + 1, sizeof(int));
    int *u = malloc(m * sizeof(int));
    int *v = malloc(m * sizeof(int));

    printf("Въведете двойки:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u[i], &v[i]);
        deg[u[i]]++;
        deg[v[i]]++;
    }

    Person *g = malloc((n + 1) * sizeof(Person));
    int *idx = calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        g[i].friends = malloc(deg[i] * sizeof(int));
        g[i].count = deg[i];
    }

    for (int i = 0; i < m; i++) {
        int a = u[i], b = v[i];
        g[a].friends[idx[a]++] = b;
        g[b].friends[idx[b]++] = a;
    }

    while (1) {
        int x;
        printf("Човек (0 за край): ");
        scanf("%d", &x);
        if (x == 0) break;

        for (int i = 0; i < g[x].count; i++)
            printf("%d ", g[x].friends[i]);
        printf("\n");
    }

    for (int i = 1; i <= n; i++)
        free(g[i].friends);

    free(g); free(deg); free(idx); free(u); free(v);
    pauseScreen();
}

typedef struct {
    int *data;
    int size;
    int cap;
} Bag;

void add(Bag *b, int x) {
    if (b->size == b->cap) {
        b->cap = b->cap ? b->cap * 2 : 4;
        b->data = realloc(b->data, b->cap * sizeof(int));
    }
    int i = b->size;
    while (i > 0 && b->data[i - 1] > x) {
        b->data[i] = b->data[i - 1];
        i--;
    }
    b->data[i] = x;
    b->size++;
}

void removeAll(Bag *b, int x) {
    int j = 0;
    for (int i = 0; i < b->size; i++)
        if (b->data[i] != x)
            b->data[j++] = b->data[i];
    b->size = j;
}

void komandi() {
    printf("\nЗадача 5: Команди\n");
    printf("1 X добавя, 2 X трие, 3 X показва, 0 край\n");

    Bag b = {0};
    int c, x;

    while (1) {
        scanf("%d", &c);
        if (c == 0) break;
        scanf("%d", &x);

        if (c == 1) add(&b, x);
        else if (c == 2) removeAll(&b, x);
        else if (c == 3 && x <= b.size) printf("%d\n", b.data[x - 1]);
    }

    free(b.data);
    pauseScreen();
}

int prime(int x) {
    if (x < 2) return 0;
    if (x % 2 == 0 && x != 2) return 0;
    for (int i = 3; i * i <= x; i += 2)
        if (x % i == 0) return 0;
    return 1;
}

void bezProsti() {
    int n;
    printf("\nЗадача 6\nВъведете брой: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    printf("Числа:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Без прости:\n");
    for (int i = 0; i < n; i++)
        if (!prime(a[i])) printf("%d ", a[i]);

    printf("\nСамо прости:\n");
    for (int i = 0; i < n; i++)
        if (prime(a[i])) printf("%d ", a[i]);

    free(a);
    pauseScreen();
}

void podmatrica() {
    int n, m;
    printf("\nЗадача 7\nВъведете размери: ");
    scanf("%d %d", &n, &m);

    int **a = createMatrix(n, m);

    printf("Матрица:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    long long best = -2000000000LL;
    int r = 0, c = 0;

    for (int i = 0; i <= n - 3; i++)
        for (int j = 0; j <= m - 3; j++) {
            long long s = 0;
            for (int di = 0; di < 3; di++)
                for (int dj = 0; dj < 3; dj++)
                    s += a[i + di][j + dj];

            if (s > best) {
                best = s;
                r = i;
                c = j;
            }
        }

    printf("Подматрица:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%4d", a[r + i][c + j]);
        printf("\n");
    }

    freeMatrix(a, n);
    pauseScreen();
}

void vmakvane() {
    printf("\nЗадача 8\nВъведете 10 числа:\n");

    int cap = 10, size = 10;
    int *a = malloc(cap * sizeof(int));

    for (int i = 0; i < 10; i++)
        scanf("%d", &a[i]);

    printf("Въвеждайте число и индекс (0 за край):\n");

    while (1) {
        int x, pos;
        scanf("%d", &x);
        if (x == 0) break;
        scanf("%d", &pos);

        if (size == cap) {
            cap *= 2;
            a = realloc(a, cap * sizeof(int));
        }

        for (int i = size; i > pos; i--)
            a[i] = a[i - 1];

        a[pos] = x;
        size++;
    }

    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);

    free(a);
    pauseScreen();
}

int main() {
    int izbor;

    do {
        printf("1. Проверка редове и колони\n");
        printf("2. Макс сбор съседи\n");
        printf("3. Размяна редове\n");
        printf("4. Приятелства\n");
        printf("5. Команди\n");
        printf("6. Прости числа\n");
        printf("7. Подматрица\n");
        printf("8. Вмъкване\n");
        printf("0. Изход\n");
        printf("Избор: ");

        scanf("%d", &izbor);

        switch (izbor) {
            case 1: proveriRedoveIKoloni(); break;
            case 2: naiDoburSased(); break;
            case 3: razmeniRedove(); break;
            case 4: priyatelstva(); break;
            case 5: komandi(); break;
            case 6: bezProsti(); break;
            case 7: podmatrica(); break;
            case 8: vmakvane(); break;
        }

    } while (izbor != 0);

    return 0;
}