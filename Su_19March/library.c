#include <stdio.h>

void clearBuffer() {
    while (getchar() != '\n');
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

void task1() {
    printf("Вход цели числа, като след като сте написали числата завършвате с 0\n");

    int num;

    scanf("%d", &num);

    if (num == 0) {
        printf("Въведете начално число по-голямо от 0\n");
        return;
    }

    int largest = num;
    int smallest = num;

    while (1) {
        scanf("%d", &num);

        if (num == 0) break;

        if (num > largest) largest = num;
        if (num < smallest) smallest = num;
    }

    printf("Най-голямо число %d\n", largest);
    printf("Най-малко число %d\n", smallest);
}

void task2() {
    printf("Вход час и минути\n");

    int h, m;
    scanf("%d %d", &h, &m);

    m += 15;
    if (m >= 60) { h++; m -= 60; }
    if (h >= 24) h = 0;

    printf("Резултат %d:%02d\n", h, m);
}

void task3() {
    printf("Вход 3 цели числа\n");

    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);

    printf((a==b && b==c)?"yes\n":"no\n");
}

void task4() {
    printf("Вход цяло число\n");

    int n;
    scanf("%d",&n);

    double bonus;

    if(n<=100) bonus=5;
    else if(n<=1000) bonus=n*0.2;
    else bonus=n*0.1;

    if(n%2==0) bonus+=1;
    if(n%10==5) bonus+=2;

    printf("Бонус %.1f\nОбщо" " %.1f\n",bonus,n+bonus);
}

void task5() {
    printf("Вход 3 времена в секунди\n");

    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);

    int sum=a+b+c;
    printf("%d:%02d\n",sum/60,sum%60);
}

void task6() {
    printf("Вход x1 y1 x2 y2 x y\n");

    double x1,y1,x2,y2,x,y;
    scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x,&y);

    if(x>=x1 && x<=x2 && y>=y1 && y<=y2)
        printf("Inside\n");
    else
        printf("Outside\n");
}

void task7() {
    printf("Вход km и време D или N\n");

    int n;
    char t;

    scanf("%d",&n);
    scanf(" %c",&t);

    double taxi=0.70+(t=='D'?0.79:0.90)*n;
    double bus=(n>=20)?0.09*n:1e9;
    double train=(n>=100)?0.06*n:1e9;

    double min=taxi;
    if(bus<min)min=bus;
    if(train<min)min=train;

    printf("Цена %.2f\n",min);
}

void task8() {
    printf("Вход V p1 p2 N\n");

    int V,p1,p2,N;
    scanf("%d %d %d %d",&V,&p1,&p2,&N);

    int total=(p1+p2)*N;

    if(total<=V)
        printf("Пълен %.2f%%\n",total*100.0/V);
    else
        printf("Прелял с %d литра\n",total-V);
}

void task9() {
    printf("Вход" " X Y Z и работници\n");

    int X,Y,Z,w;
    scanf("%d %d %d %d",&X,&Y,&Z,&w);

    double wine=(X*0.4*Y)/2.5;

    if(wine>=Z){
        printf("Достатъчно %.0f\n",wine);
        printf("На човек %.0f\n",(wine-Z)/w);
    } else {
        printf("Недостиг %.0f\n",Z-wine);
    }
}

void task10() {
    printf("Вход n числа\n");

    int n,num;
    int p1=0,p2=0,p3=0,p4=0,p5=0;

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%d",&num);

        if(num<200)p1++;
        else if(num<400)p2++;
        else if(num<600)p3++;
        else if(num<800)p4++;
        else p5++;
    }

    printf("%.2f%%\n",p1*100.0/n);
    printf("%.2f%%\n",p2*100.0/n);
    printf("%.2f%%\n",p3*100.0/n);
    printf("%.2f%%\n",p4*100.0/n);
    printf("%.2f%%\n",p5*100.0/n);
}

void task11() {
    printf("Вход n цяло число\n");

    int n;
    scanf("%d",&n);

    int mid = n/2;

    printf("/");
    for(int i=0;i<mid;i++) printf("^");
    printf("\\");
    for(int i=0;i<n-2*mid-2;i++) printf("_");
    printf("/");
    for(int i=0;i<mid;i++) printf("^");
    printf("\\\n");

    for(int i=0;i<n-2;i++){
        printf("|");
        for(int j=0;j<2*n-2;j++) printf(" ");
        printf("|\n");
    }

    printf("\\");
    for(int i=0;i<mid;i++) printf("_");
    printf("/");
    for(int i=0;i<n-2*mid-2;i++) printf(" ");
    printf("\\");
    for(int i=0;i<mid;i++) printf("_");
    printf("/\n");
}

void task12() {
    printf("Вход: n цяло число\n");

    int n;
    scanf("%d",&n);

    int width = 2*n-1;

    for(int i=0;i<n-2;i++){
        for(int j=0;j<n-1;j++) printf(i%2==0?"*":"-");
        printf("\\ /");
        for(int j=0;j<n-1;j++) printf(i%2==0?"*":"-");
        printf("\n");
    }

    for(int i=0;i<width/2;i++) printf(" ");
    printf("@\n");

    for(int i=0;i<n-2;i++){
        for(int j=0;j<n-1;j++) printf(i%2==0?"*":"-");
        printf("/ \\");
        for(int j=0;j<n-1;j++) printf(i%2==0?"*":"-");
        printf("\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n=========== МЕНЮ ===========\n");
        printf("1. Най-голямо/най-малко\n");
        printf("2. Час +15 мин\n");
        printf("3. Равни числа\n");
        printf("4. Бонус точки\n");
        printf("5. Състезатели време\n");
        printf("6. Точка в правоъгълник\n");
        printf("7. Транспорт\n");
        printf("8. Басейн\n");
        printf("9. Вино\n");
        printf("10. Проценти\n");
        printf("11. Крепост\n");
        printf("12. Пеперуда\n");
        printf("0. Изход\n");
        printf("============================\n");
        printf("Избор ");

        if(scanf("%d",&choice)!=1){
            clearBuffer();
            continue;
        }

        switch(choice){
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 4: task4(); break;
            case 5: task5(); break;
            case 6: task6(); break;
            case 7: task7(); break;
            case 8: task8(); break;
            case 9: task9(); break;
            case 10: task10(); break;
            case 11: task11(); break;
            case 12: task12(); break;
            case 0: printf("Изход\n"); break;
            default: printf("Невалиден избор\n");
        }

    } while(choice != 0);

    return 0;
}