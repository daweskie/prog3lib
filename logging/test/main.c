#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int test_logging()
{
}

int main(int argc, char **argv)
{
    printf("logging testing started\n");
    int result = test_logging(argc, argv);
    printf("logging testing ended\n");
    return result;
}
