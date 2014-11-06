#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int test_serial_driver()
{
}

int main(int argc, char **argv)
{
    printf("serial_driver testing started\n");
    int result = test_serial_driver(argc, argv);
    printf("serial_driver testing ended\n");
    return result;
}
