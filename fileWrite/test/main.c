#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fileWrite.h>

int test_exists(const char *path, const char *fullpath){
    assert(fwExists(path)!=0);
    //assert(fw_exists(fullpath)!=0);
}
int test_n_exists(const char *path, const char *fullpath){
    assert(fwExists(path)==0);
    assert(fwExists(fullpath)==0);
}


int test_fod(const char *path, const char *fullpath){
    assert(fwFoD(path)==2);
    //assert(fw_efod(fullpath)==1);
}
int test_n_fod(const char *path, const char *fullpath){
    assert(fwFoD(path)==0);
    assert(fwFoD(fullpath)==0);
}


int test_mkdir(const char *path){
    assert(fwMkDir(path)==1);
}
int test_n_mkdir(const char *path){
    assert(fwMkDir(path)==0);
}


int test_delete(const char *path, const char *fullpath){
    //assert(fw_delete(fullpath)!=0);
    assert(fwDelete(path)!=0);
}
int test_n_delete(const char *path, const char *fullpath){
    assert(fwDelete(fullpath)==0);
    assert(fwDelete(path)==0);
}


int test_readOnly(const char *path, const char *fullpath){
    assert(fwReadOnly(path)==0);
    assert(fwReadOnly(fullpath)==0);
}


int test_canWrite(const char *path, const char *fullpath){
    assert(fwCanWrite(path)!=0);
    //assert(fw_canWrite(fullpath)!=0);
}


int clean(const char *path, const char *fullpath){
    fwDelete(fullpath);
    fwDelete(path);
}


int test_fileWrite(const int argc, const char *argv[]){

    char path[127];
    strcpy(path, "/tmp/"); //work in TEMP
    strcat(path, argv[1]);
    char fullpath[255];
    strcat(fullpath, path);
    strcat(fullpath, argv[1]);

    clean(path, fullpath);

    //begin test
    test_mkdir(path);
    test_n_mkdir(path);
    test_fod(path, fullpath);
    test_exists(path, fullpath);
    test_readOnly(path, fullpath);
    test_canWrite(path, fullpath);
    test_delete(path, fullpath);
    test_n_delete(path, fullpath);
    test_n_fod(path, fullpath);
    test_n_exists(path, fullpath);
}


int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Usage: %s <path> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /*
    struct FileWriter *proba;
    fwInit(proba, "proba.txt", 0, 512);
    char *szoveg = "sajt";
    fwAddtoBuffer(proba, szoveg, 4);
    printf("Proba: %d\n", proba->position);*/

    printf("fileWrite testing started\n");
    int result = test_fileWrite(argc, argv);
    printf("fileWrite testing ended\n");
    return result;
}
