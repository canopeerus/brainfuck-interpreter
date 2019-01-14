#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>

#define BF_TAPE_SIZE 9999

int run_brainfuck(FILE* f)
{
    char *bf_tape = NULL,*buf = NULL;
    int i = 0,j = 0,cc = 0,err;

    bf_tape = (char*) malloc( (BUFSIZ+1) * sizeof(char));
    assert(bf_tape);

    buf = (char*) malloc( (BUFSIZ+1) * sizeof(char));
    assert(buf);

    err = fread(buf,sizeof(char),BUFSIZ,f);
    assert(err != 0);

    for(i = 0;*(buf + i) != '\0';i++)
    {
        if ( *(buf + i) == '[' )
            ++cc;
        else if ( *(buf + i) == ']' )
            --cc;
    }

    if ( cc )
        return -1;

    for(i = 0;*(buf+i) != '\0';i++)
    {
        char c = *(buf + i);
        switch(c)
        {
            case '+':
                ++*(bf_tape + j);
                break;
            case '-':
                --*(bf_tape + j);
                break;
            case '>':
                ++j;
                break;
            case '<':
                --j;
                break;
            case '.':
                printf("%c",*(bf_tape + j));
                break;
            case ',':
                *(bf_tape + j) = getchar();
                break;
            case '[':
                if ( ! *(bf_tape + j) )
                {
                    int bc = 1;
                    while ( bc )
                    {
                        c = *(buf + ++i);
                        if ( c == ']' )
                            --bc;
                        else if ( c == '[' )
                            ++bc;
                    }
                }
                break;
            case ']':
                if ( *(bf_tape + j) )
                {
                    int bc = 1;
                    while ( bc > 0 )
                    {
                        c = *(buf + --i);
                        if ( c == '[' )
                            --bc;
                        else if ( c == ']' )
                            ++bc;
                    }
                }
                break;
        }
    }

    free(buf);
    free(bf_tape);
    return 0;
}

int main(int argc,char *argv[])
{
    FILE *f = NULL;
    int err;

    if ( argc == 1 )
    {
        /* read from stdin if no args */
        err = run_brainfuck(stdin);
        if ( err != 0 )
        {
            fprintf(stderr,"Syntax error\n");
            return EXIT_FAILURE;
        }
    }
    else
    {
        /* read file from argv[1] */
        f = fopen(argv[1],"r");
        assert(f);

        err = run_brainfuck(f);

        if ( err != 0 )
        {
            fprintf(stderr,"Syntax error\n");
            return EXIT_FAILURE;
        }
        fclose(f);
    }
    return EXIT_SUCCESS;
}
