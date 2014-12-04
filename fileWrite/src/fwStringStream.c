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
* fwStringStream
*/
#include <fwStringStream.h>

int fwssNullOrEmpty(const char *str){
    if (!(str && *str))
        return 1;

    return 0;
}


int notInitFWStringStream(struct FWStringStream *fwss){
    if(!(fwss && fwss->buffer))
        return 1;

    return 0;
}


struct FWStringStream *fwssInit(unsigned int maxBufferSize){
    if(!maxBufferSize)
        return NULL;

    struct FWStringStream *retVal = malloc(sizeof(struct FWStringStream));
    if (!retVal)
        return NULL;

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


int fwssAddToBuffer(struct FWStringStream *fwss, char *data, unsigned int dataSize){
    if(fwssNullOrEmpty(data) || !dataSize || notInitFWStringStream(fwss))
        return 0;

    if(dataSize > fwss->maxBufferSize - fwss->nextPosition)
        return 0;

    unsigned int i;
    for(i=0; dataSize && *(data+i); dataSize--, i++, fwss->nextPosition++){
        *(fwss->buffer+fwss->nextPosition) = *(data+i);
    }

    fwss->position = fwss->nextPosition - 1;

    *(fwss->buffer+fwss->nextPosition) = '\0';

    return 1;
}


int fwssClearBuffer(struct FWStringStream *fwss){
    if(notInitFWStringStream(fwss))
        return 0;

    fwss->nextPosition = 0;
    fwss->position = 0;
    *(fwss->buffer) = '\0';

    return 1;
}


int fwssLastRemoveInBuffer(struct FWStringStream *fwss, unsigned int n){
    if(notInitFWStringStream(fwss))
        return 0;

    if(fwss->nextPosition < n)
        return 0;

    if(fwss->nextPosition == n)
        return fwssClearBuffer(fwss);

    fwss->nextPosition -= n;
    fwss->position -= n;
    *(fwss->buffer+fwss->nextPosition) = '\0';

    return 1;
}


int fwssRemoveInBuffer(struct FWStringStream *fwss, unsigned int x, unsigned int n){
    if(notInitFWStringStream(fwss) || n == 0)
        return 0;

    if(fwss->nextPosition < x+n)
        return 0;

    /* handled function
    if(fwss->nextPosition == n)
        return fwClearBuffer(fwss);*/

    //initial removal position
    fwss->position = x;
    //safety work if no add new char
    *(fwss->buffer+fwss->position) = '\0';

    unsigned int i;
    //copy final not removed char
    for(i=0; *(fwss->buffer+fwss->position+n+i); i++)
        *(fwss->buffer+fwss->position+i) = *(fwss->buffer+fwss->position+n+i);

    //final work
    fwss->nextPosition = x+i;
    fwss->position = (x+i-1 == -1) ? 0 : x+i-1 ;
    *(fwss->buffer+fwss->position+1) = '\0';


    return 1;
}


int fwssPasteToBuffer(struct FWStringStream *fwss, unsigned int x, char *data, unsigned int dataSize){
    if(fwssNullOrEmpty(data) || !dataSize || notInitFWStringStream(fwss))
        return 0;

    if(dataSize > fwss->maxBufferSize - fwss->nextPosition)
        return 0;

    if(x > fwss->nextPosition)
        return 0;

    int copyed = 0;
    char *copy;
    unsigned int i = 0;
    //copy if found last date under position
    if(fwss->nextPosition-x != 0){
        copy = malloc(fwss->nextPosition-x+1);
        if(!copy)
            return 0;

        copyed = 1;

        for(; *(fwss->buffer+x+i); i++){
            *(copy+i) = *(fwss->buffer+x+i);
        }

        if(!fwssLastRemoveInBuffer(fwss, i))
            return 0;
    }


    if(!fwssAddToBuffer(fwss, data, dataSize))
        return 0;

    if(copyed){
        if(!fwssAddToBuffer(fwss, copy, i))
            return 0;

        free(copy);
        copy = NULL;
    }

    return 1;
}


int fwssWriteBuffer(struct FWStringStream *fwss, const char *pathname, int append){
    if(notInitFWStringStream(fwss))
        return 0;

    if(fwssNullOrEmpty(pathname))
        return 0;

    FILE * file;

    if(!append)
        file = fopen(pathname, "w");
    else
        file = fopen(pathname, "a");

    if(!file)
        return 0;

    int result = fputs(fwss->buffer, file) < 0 ? 0 : 1;

    fclose(file);

    return result;
}


int fwssClose(struct FWStringStream *fwss){
    if (!fwss)
        return 0;

    free (fwss->buffer);
    free (fwss);
    fwss = NULL;

    return 1;
}
