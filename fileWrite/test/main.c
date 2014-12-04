#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fileWrite.h>

int testStandardNullOrEmpty(const char *path, const char *fullpath){
    assert(fwDelete(NULL)==0);
    assert(fwDelete("")==0);
    assert(fwFoD(NULL)==0);
    assert(fwFoD("")==0);
    assert(fwExists(NULL)==0);
    assert(fwExists("")==0);
    assert(fwReadOnly(NULL)==0);
    assert(fwReadOnly("")==0);
    assert(fwCanWrite(NULL)==0);
    assert(fwCanWrite("")==0);
    assert(fwMkDir(NULL)==0);
    assert(fwMkDir("")==0);
}


int standardTest(const char *path, const char *fullpath){
    //no direction & file
    assert(fwDelete(fullpath)==0);
    assert(fwDelete(path)==0);
    assert(fwFoD(fullpath)==0);
    assert(fwFoD(path)==0);
    assert(fwExists(fullpath)==0);
    assert(fwExists(path)==0);
    assert(fwReadOnly(fullpath)==0);
    assert(fwReadOnly(path)==0);
    assert(fwCanWrite(fullpath)==0);
    assert(fwCanWrite(path)==0);

    //Direction
    assert(fwMkDir(path)!=0);
    assert(fwMkDir(path)==0);
    assert(fwFoD(fullpath)==0);
    assert(fwFoD(path)==2);
    assert(fwExists(fullpath)==0);
    assert(fwExists(path)!=0);
    assert(fwReadOnly(fullpath)==0);
    assert(fwReadOnly(path)==0);
    assert(fwCanWrite(fullpath)==0);
    assert(fwCanWrite(path)!=0);
    assert(fwDelete(fullpath)==0);
    assert(fwDelete(path)!=0);
    assert(fwDelete(path)==0);

    //Direction & File
    assert(fwMkDir(path)!=0);
    //create file
    struct FileWriter *fwTest = fwInit(fullpath, 0, 50);
    assert(fwTest!=NULL);
    //close file
    fwClose(fwTest);
    assert(fwMkDir(path)==0);
    assert(fwFoD(fullpath)==1);
    assert(fwFoD(path)==2);
    assert(fwExists(fullpath)!=0);
    assert(fwExists(path)!=0);
    assert(fwReadOnly(fullpath)==0);
    assert(fwReadOnly(path)==0);
    assert(fwCanWrite(fullpath)!=0);
    assert(fwCanWrite(path)!=0);
    assert(fwDelete(fullpath)!=0);
    assert(fwDelete(fullpath)==0);
    assert(fwDelete(path)!=0);
    assert(fwDelete(path)==0);
}


int test_GoodFileWriter(const char *path, const char *fullpath){
    //no create file
    assert(fwInit(NULL, 0, 50)==NULL);
    assert(fwInit("", 0, 50)==NULL);
    assert(fwInit(fullpath, 0, 0)==NULL);
    assert(fwInit(NULL, 1, 50)==NULL);
    assert(fwInit("", 1, 50)==NULL);
    assert(fwInit(fullpath, 1, 0)==NULL);

    //create file & Dir
    assert(fwMkDir(path)!=0);
    struct FileWriter *fwTest = fwInit(fullpath, 0, 14);
        assert(fwTest!=NULL);

    //No Add To Buffer
    assert(fwAddToBuffer(fwTest, "test", 0) == 0);
    assert(fwAddToBuffer(fwTest, "", 4) == 0);
    assert(fwAddToBuffer(fwTest, NULL, 4) == 0);
    assert(fwAddToBuffer(NULL, "test", 4) == 0);
    assert(fwAddToBuffer(NULL, NULL, 4) == 0);
    assert(fwAddToBuffer(NULL, NULL, 0) == 0);

    //Add To Buffer
    assert(fwAddToBuffer(fwTest, "10", 2) != 0);
    assert(fwAddToBuffer(fwTest, "30", 4) != 0);
    assert(fwAddToBuffer(fwTest, "500", 2) != 0);
    assert(fwEqualWithBuffer(fwTest, NULL) == 0);
    assert(fwEqualWithBuffer(fwTest, "") == 0);
    assert(fwEqualWithBuffer(fwTest, "103050") != 0);

    //No Paste To Buffer
    assert(fwPasteToBuffer(NULL, 0, NULL, 4) == 0);
    assert(fwPasteToBuffer(NULL, 0, "40", 4) == 0);
    assert(fwPasteToBuffer(fwTest, 0, NULL, 4) == 0);
    assert(fwPasteToBuffer(fwTest, 0, "", 4) == 0);
    assert(fwPasteToBuffer(fwTest, 0, "40", 0) == 0);
    assert(fwPasteToBuffer(fwTest, 4, "40", 0) == 0);


    //Paste To Buffer
    assert(fwPasteToBuffer(fwTest, 0, "00", 2) != 0);
    assert(fwPasteToBuffer(fwTest, 4, "20", 6) != 0);
    assert(fwPasteToBuffer(fwTest, 8, "400", 2) != 0);
    assert(fwPasteToBuffer(fwTest, 12, "60000000", 2) != 0);
    assert(fwEqualWithBuffer(fwTest, "00102030405060") != 0);
    assert(fwPasteToBuffer(fwTest, 14, "00", 2) == 0);

    //No remove
    assert(fwLastRemoveInBuffer(NULL, 4) == 0);
    assert(fwLastRemoveInBuffer(fwTest, 0) == 0);

    //remove
    assert(fwLastRemoveInBuffer(fwTest, 2) != 0);
    assert(fwEqualWithBuffer(fwTest, "001020304050") != 0);

    //no remove
    assert(fwRemoveInBuffer(NULL, 0, 4) == 0);
    assert(fwRemoveInBuffer(fwTest, 0, 0) == 0);
    assert(fwRemoveInBuffer(fwTest, 10, 0) == 0);
    assert(fwRemoveInBuffer(fwTest, 10, 3) == 0);

    //remove
    assert(fwRemoveInBuffer(fwTest, 0, 2) != 0);
    assert(fwRemoveInBuffer(fwTest, 2, 4) != 0);
    assert(fwRemoveInBuffer(fwTest, 4, 2) != 0);
    assert(fwEqualWithBuffer(fwTest, "1040") != 0);
    assert(fwPasteToBuffer(fwTest, 2, "test", 4) != 0);
    assert(fwEqualWithBuffer(fwTest, "10test40") != 0);
    assert(fwRemoveInBuffer(fwTest, 2, 4) != 0);
    assert(fwEqualWithBuffer(fwTest, "1040") != 0);

    //Write
    assert(fwWriteBuffer(NULL) == 0);
    assert(fwWriteBuffer(fwTest) != 0);

    //Print
    assert(fwAddToBuffer(fwTest, " OK", 3) != 0);
    assert(fwPrintfBuffer(NULL) == 0);
    assert(fwPrintfBuffer(fwTest) != 0);

    //no clear Buffer
    assert(fwClearBuffer(NULL) == 0);
    //clear Buffer
    assert(fwClearBuffer(fwTest) != 0);
    //no print
    assert(fwPrintfBuffer(fwTest) == 0);
    //empty
    assert(fwEqualWithBuffer(fwTest, "") != 0);

    //Copy to Sting
    assert(fwCopyToString(NULL) == NULL);
    assert(fwCopyToString(fwTest) == NULL);
    assert(fwAddToBuffer(fwTest, "test", 4) != 0);
    assert(fwEqualWithBuffer(fwTest, "test") != 0);
    assert(fwEqualWithBuffer(fwTest, fwCopyToString(fwTest)) != 0);

    //close file
    assert(fwClose(fwTest)!=0);
}


int test_GoodStringStream(const char *path, const char *fullpath){
    //no init
    assert(fwssInit(0)==NULL);

    //init
    struct FWStringStream *fwssTest = fwssInit(14);
        assert(fwssTest!=NULL);

    //No Add To Buffer
    assert(fwssAddToBuffer(fwssTest, "test", 0) == 0);
    assert(fwssAddToBuffer(fwssTest, "", 4) == 0);
    assert(fwssAddToBuffer(fwssTest, NULL, 4) == 0);
    assert(fwssAddToBuffer(NULL, "test", 4) == 0);
    assert(fwssAddToBuffer(NULL, NULL, 4) == 0);
    assert(fwssAddToBuffer(NULL, NULL, 0) == 0);

    //Add To Buffer
    assert(fwssAddToBuffer(fwssTest, "10", 2) != 0);
    assert(fwssAddToBuffer(fwssTest, "30", 4) != 0);
    assert(fwssAddToBuffer(fwssTest, "500", 2) != 0);
    assert(fwssEqualWithBuffer(fwssTest, NULL) == 0);
    assert(fwssEqualWithBuffer(fwssTest, "") == 0);
    assert(fwssEqualWithBuffer(fwssTest, "103050") != 0);

    //No Paste To Buffer
    assert(fwssPasteToBuffer(NULL, 0, NULL, 4) == 0);
    assert(fwssPasteToBuffer(NULL, 0, "40", 4) == 0);
    assert(fwssPasteToBuffer(fwssTest, 0, NULL, 4) == 0);
    assert(fwssPasteToBuffer(fwssTest, 0, "", 4) == 0);
    assert(fwssPasteToBuffer(fwssTest, 0, "40", 0) == 0);
    assert(fwssPasteToBuffer(fwssTest, 4, "40", 0) == 0);


    //Paste To Buffer
    assert(fwssPasteToBuffer(fwssTest, 0, "00", 2) != 0);
    assert(fwssPasteToBuffer(fwssTest, 4, "20", 6) != 0);
    assert(fwssPasteToBuffer(fwssTest, 8, "400", 2) != 0);
    assert(fwssPasteToBuffer(fwssTest, 12, "60000000", 2) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "00102030405060") != 0);
    assert(fwssPasteToBuffer(fwssTest, 14, "00", 2) == 0);

    //No remove
    assert(fwssLastRemoveInBuffer(NULL, 4) == 0);
    assert(fwssLastRemoveInBuffer(fwssTest, 0) == 0);

    //remove
    assert(fwssLastRemoveInBuffer(fwssTest, 2) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "001020304050") != 0);

    //no remove
    assert(fwssRemoveInBuffer(NULL, 0, 4) == 0);
    assert(fwssRemoveInBuffer(fwssTest, 0, 0) == 0);
    assert(fwssRemoveInBuffer(fwssTest, 10, 0) == 0);
    assert(fwssRemoveInBuffer(fwssTest, 10, 3) == 0);

    //remove
    assert(fwssRemoveInBuffer(fwssTest, 0, 2) != 0);
    assert(fwssRemoveInBuffer(fwssTest, 2, 4) != 0);
    assert(fwssRemoveInBuffer(fwssTest, 4, 2) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "1040") != 0);
    assert(fwssPasteToBuffer(fwssTest, 2, "test", 4) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "10test40") != 0);
    assert(fwssRemoveInBuffer(fwssTest, 2, 4) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "1040") != 0);

    //no write
    assert(fwMkDir(path)!=0);
    assert(fwssWriteBuffer(fwssTest, NULL, 0)==0);
    assert(fwssWriteBuffer(fwssTest, "", 0)==0);
    assert(fwssWriteBuffer(NULL, fullpath, 0)==0);
    assert(fwssWriteBuffer(fwssTest, NULL, 1)==0);
    assert(fwssWriteBuffer(fwssTest, "", 1)==0);
    assert(fwssWriteBuffer(NULL, fullpath, 1)==0);
    //write
    assert(fwssWriteBuffer(fwssTest, fullpath, 1)!=0);
    assert(fwssWriteBuffer(fwssTest, fullpath, 0)!=0);
    assert(fwssWriteBuffer(fwssTest, fullpath, 1)!=0);

    //Print
    assert(fwssAddToBuffer(fwssTest, " OK", 3) != 0);
    assert(fwssPrintfBuffer(NULL) == 0);
    assert(fwssPrintfBuffer(fwssTest) != 0);

    //no clear Buffer
    assert(fwssClearBuffer(NULL) == 0);
    //clear Buffer
    assert(fwssClearBuffer(fwssTest) != 0);
    //no print
    assert(fwssPrintfBuffer(fwssTest) == 0);
    //empty
    assert(fwssEqualWithBuffer(fwssTest, "") != 0);

    //Copy to Sting
    assert(fwssCopyToString(NULL) == NULL);
    assert(fwssCopyToString(fwssTest) == NULL);
    assert(fwssAddToBuffer(fwssTest, "test", 4) != 0);
    assert(fwssEqualWithBuffer(fwssTest, "test") != 0);
    assert(fwssEqualWithBuffer(fwssTest, fwssCopyToString(fwssTest)) != 0);

    //close file
    assert(fwssClose(fwssTest)!=0);
}


int test_fileWrite(const int argc, const char *argv[]){
    char path[127];
    strcpy(path, "/tmp/"); //work in TEMP
    strcat(path, argv[1]);
    char fullpath[255];
    strcpy(fullpath, path);
    strcat(fullpath, "/");
    strcat(fullpath, argv[2]);

    //cleaning
    fwDelete(fullpath);
    fwDelete(path);

    testStandardNullOrEmpty(path, fullpath);
    standardTest(path, fullpath);
    test_GoodFileWriter(path, fullpath);

    //cleaning
    fwDelete(fullpath);
    fwDelete(path);
    test_GoodStringStream(path, fullpath);
}


int main(int argc, char *argv[]){
    if (argc != 3) {
        printf("Usage: %s <path> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("fileWrite testing started\n");
    int result = test_fileWrite(argc, argv);
    printf("fileWrite testing ended\n");
    return result;
}
