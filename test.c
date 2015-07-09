#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int maxof(int, int, int, ...) ;
//void f(void);

main(){
        printf("%d\n",maxof(3, 2, 3, 10, 42, 0));
        exit(EXIT_SUCCESS);
}

int maxof(int b, int c, int n_args, ...){
        register int i;
        int max, a;
        va_list ap;

        va_start(ap, n_args);
        max = va_arg(ap, int);
        for(i = 0; i <= (n_args - 2); i++) {
                if((a = va_arg(ap, int)) > max)
                        max = a;
                printf("%i\n", a);
        }

        va_end(ap);
        return max;
}