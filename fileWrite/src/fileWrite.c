/*
 * Copyright (C) 2014 Gergely Molnar & Kalman Szabadi
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
* fileWrite
*/
#include <fileWrite.h>

int fwNullOrEmpty(const char *str){
    if (!(str && *str))
        return 1;

    return 0;
}


int fwFoD(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IFMT){
        case S_IFDIR:
            return 2; //directory
        break;

        case S_IFREG:
            return 1; //file
        break;

        default:
            return 0; //unkown
        break;
    }
}


int fwExists(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    if(fwFoD(pathname) == 1 || fwFoD(pathname) == 2)
        return 1;

    return 0;
}


int fwMkDir(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        if(mkdir(pathname, 0777) != -1)
            return 1;

    return 0;
}


int fwReadOnly(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IRWXU){
        case S_IRUSR: //read only
            return 1;
        break;

        default:
            return 0;
        break;
    }
}


int fwCanWrite(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        return 0;

    switch(st.st_mode & S_IWUSR){
        case S_IWUSR: //can write
            return 1;
        break;

        default:
            return 0;
        break;
    }
}


int fwDelete(const char *pathname){
    if(fwNullOrEmpty(pathname))
        return 0;

    switch(fwFoD(pathname)){
        case 1:
            if(unlink(pathname)!= -1)
                return 1;
        break;

        case 2:
            if(rmdir(pathname)!= -1)
                return 2;
        break;
    }

    return 0;
}


int notInitFileWriter(struct FileWriter *fWriter){
    if(!(fWriter && fWriter->file && fWriter->buffer))
        return 1;

    return 0;
}


struct FileWriter *fwInit(const char *pathname, int append, unsigned int maxBufferSize){
    if(fwNullOrEmpty(pathname))
        return NULL;

    if(!maxBufferSize)
        return NULL;

    struct FileWriter *retVal = malloc(sizeof(struct FileWriter));
    if (!retVal)
        return NULL;

    if(!append)
        retVal->file = fopen(pathname, "w");
    else
        retVal->file = fopen(pathname, "a");

    if(!retVal->file){
        free(retVal);
        return NULL;
    }

    retVal->buffer = malloc(maxBufferSize+1);
    if (!retVal->buffer) {
        free (retVal);
        return NULL;
    }
    retVal->maxBufferSize = maxBufferSize;

    *(retVal->buffer) = '\0';

    retVal->nextPosition = 0;
    retVal->position = 0;

    return retVal;
}


int fwAddToBuffer(struct FileWriter *fWriter, char *data, unsigned int dataSize){
    if(fwNullOrEmpty(data) || !dataSize || notInitFileWriter(fWriter))
        return 0;

    if(dataSize > fWriter->maxBufferSize - fWriter->nextPosition)
        return 0;

    unsigned int i;
    for(i=0; dataSize && *(data+i); dataSize--, i++, fWriter->nextPosition++){
        *(fWriter->buffer+fWriter->nextPosition) = *(data+i);
    }

    fWriter->position = fWriter->nextPosition - 1;

    *(fWriter->buffer+fWriter->nextPosition) = '\0';

    return 1;
}


int fwClearBuffer(struct FileWriter *fWriter){
    if(notInitFileWriter(fWriter))
        return 0;

    fWriter->nextPosition = 0;
    fWriter->position = 0;
    *(fWriter->buffer) = '\0';

    return 1;
}


int fwLastRemoveInBuffer(struct FileWriter *fWriter, unsigned int n){
    if(notInitFileWriter(fWriter))
        return 0;

    if(fWriter->nextPosition < n)
        return 0;

    if(fWriter->nextPosition == n)
        return fwClearBuffer(fWriter);

    fWriter->nextPosition -= n;
    fWriter->position -= n;
    *(fWriter->buffer+fWriter->nextPosition) = '\0';

    return 1;
}


int fwRemoveInBuffer(struct FileWriter *fWriter, unsigned int x, unsigned int n){
    if(notInitFileWriter(fWriter) || n == 0)
        return 0;

    if(fWriter->nextPosition < x+n)
        return 0;

    /* handled function
    if(fWriter->nextPosition == n)
        return fwClearBuffer(fWriter);*/

    //initial removal position
    fWriter->position = x;
    //safety work if no add new char
    *(fWriter->buffer+fWriter->position) = '\0';

    unsigned int i;
    //copy final not removed char
    for(i=0; *(fWriter->buffer+fWriter->position+n+i); i++)
        *(fWriter->buffer+fWriter->position+i) = *(fWriter->buffer+fWriter->position+n+i);

    //final work
    fWriter->nextPosition = x+i;
    fWriter->position = (x+i-1 == -1) ? 0 : x+i-1 ;
    *(fWriter->buffer+fWriter->position+1) = '\0';


    return 1;
}


int fwPasteToBuffer(struct FileWriter *fWriter, unsigned int x, char *data, unsigned int dataSize){
    if(fwNullOrEmpty(data) || !dataSize || notInitFileWriter(fWriter))
        return 0;

    if(dataSize > fWriter->maxBufferSize - fWriter->nextPosition)
        return 0;

    if(x > fWriter->nextPosition)
        return 0;

    int copyed = 0;
    char *copy;
    unsigned int i = 0;
    //copy if found last date under position
    if(fWriter->nextPosition-x != 0){
        copy = malloc(fWriter->nextPosition-x+1);
        if(!copy)
            return 0;

        copyed = 1;

        for(; *(fWriter->buffer+x+i); i++){
            *(copy+i) = *(fWriter->buffer+x+i);
        }

        if(!fwLastRemoveInBuffer(fWriter, i))
            return 0;
    }


    if(!fwAddToBuffer(fWriter, data, dataSize))
        return 0;

    if(copyed){
        if(!fwAddToBuffer(fWriter, copy, i))
            return 0;

        free(copy);
        copy = NULL;
    }

    return 1;
}


int fwWriteBuffer(struct FileWriter *fWriter){
    if(notInitFileWriter(fWriter))
        return 0;

    return fputs(fWriter->buffer,fWriter->file) < 0 ? 0 : 1;
}


int fwClose(struct FileWriter *fWriter){
    if (!fWriter)
        return 0;

    free (fWriter->buffer);
    fclose(fWriter->file);
    free (fWriter);
    fWriter = NULL;

    return 1;
}
