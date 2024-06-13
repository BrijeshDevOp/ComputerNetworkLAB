// Character Stuffing :
#include <stdio.h>
#include <stdlib.h>
void charc(void);
void main()
{
    int choice;
    while (1)
    {
        printf("\n1.Character Stuffing: ");
        printf("\n2.Exit");
        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);
        if (choice > 2)
            printf("\n\n Invalid Option");
        switch (choice)
        {
        case 1:
            charc();
            break;
        case 2:
            exit(0);
        }
    }
}
void charc(void)
{
    char c[50], d[50], t[50];
    int i, m, j;
    printf("Enter nor of Characters: \n");
    scanf("%d", &m);
    printf("\nEnter Characters: \n");
    for (i = 0; i < m + 1; i++)
    {
        scanf("%c", &c[i]);
    }
    printf("\nActual Data\n");
    for (i = 0; i < m + 1; i++)
        printf("%c", c[i]);
    d[0] = 'd';
    d[1] = 'l';
    d[2] = 'e';
    d[3] = 's';
    d[4] = 't';
    d[5] = 'x';
    for (i = 0, j = 6; i < m + 1; i++, j++)
    {
        if ((c[i] == 'd' && c[i + 1] == 'l' && c[i + 2] == 'e'))
        {
            d[j] = 'd';
            j++;
            d[j] = 'l';
            j++;
            d[j] = 'e';
            j++;
            m = m + 3;
        }
        d[j] = c[i];
    }
    m = m + 6;
    m++;
    d[m] = 'd';
    m++;
    d[m] = 'l';
    m++;
    d[m] = 'e';
    m++;
    d[m] = 's';
    m++;
    d[m] = 't';
    m++;
    d[m] = 'x';
    m++;
    printf("\n\nTransmitted Data: \n");
    for (i = 0; i < m; i++)
    {
        printf("%c", d[i]);
    }
    for (i = 6, j = 0; i < m - 6; i++, j++)
    {
        if (d[i] == 'd' && d[i + 1] == 'l' && d[i + 2] == 'e' && d[i + 3] == 'd' && d[i + 4] == 'l' && d[i + 5] == 'e')
            i = i + 3;
        t[j] = d[i];
    }
    printf("\n\nReceived Data:");
    for (i = 0; i < j; i++)
    {
        printf("%c", t[i]);
    }
}

// input abcdle