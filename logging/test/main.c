#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <logging.h>
#include <fileWrite.h>

int test_logging()
{

}

int main(int argc, char **argv)
{
    printf("logging testing started\n");
    int result = test_logging(argc, argv);
    logging_out(3, "hiba_app", "szar");
    printf("logging testing ended\n");
    return result;
}
