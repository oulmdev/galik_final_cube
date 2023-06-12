# include <stdio.h>
# include <stdlib.h>
# include <string.h>
// char *dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));


int main()
{
    char **tab;

    tab = malloc(sizeof(char *) * 5);
    tab[0] = strdup("abcdef");
    tab[1] = strdup("ghijkl");
    tab[2] = strdup("mnopqr");
    tab[3] = strdup("stuvwx");
    tab[4] = NULL;

    char *str_tab = malloc(sizeof(char) * 25);
    int i = 0;
    int j = 0;
    int k = 0;
    while (tab[i])
    {
        while (tab[i][j])
        {
            str_tab[k] = tab[i][j];
            j++;
            k++;
        }
        j = 0;
        i++;
    }
    str_tab[k] = '\0';
    printf("%s", str_tab);
    printf("f = %c", str_tab [(1 * 6 + 1 * 1)]);
    
}