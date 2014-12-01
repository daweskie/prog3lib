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

int nullOrEmpty(const char *str){
    if (!(str && *str))
        return 1;

    return 0;
}


int fwFoD(const char *pathname){
    if(nullOrEmpty(pathname))
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
    if(nullOrEmpty(pathname))
        return 0;

    if(fwFoD(pathname) == 1 || fwFoD(pathname) == 2)
        return 1;

    return 0;
}


int fwMkDir(const char *pathname){
    if(nullOrEmpty(pathname))
        return 0;

    struct stat st;
    if (stat(pathname, &st) == -1)
        if(mkdir(pathname, 0777) != -1)
            return 1;

    return 0;
}


int fwReadOnly(const char *pathname){
    if(nullOrEmpty(pathname))
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
    if(nullOrEmpty(pathname))
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
    if(nullOrEmpty(pathname))
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


int fwInit(struct FileWriter *fWriter, const char *pathname, int append, unsigned int maxBufferSize){
    if(nullOrEmpty(pathname))
        return 0;

    int available = 0;
    if(fwFoD(pathname)==1)
        available = 1;

    fWriter->buffer = (char*) malloc(maxBufferSize+1);
    if(fWriter->buffer==NULL)
        return 0;
    *(fWriter->buffer) = '\0';

    fWriter->position = 0;

    if(append == 1)
        fWriter->file = fopen(pathname, "a");
    else
        fWriter->file = fopen(pathname, "w");

    return 1;
}


int fwAddtoBuffer(struct FileWriter *fWriter, char *data, unsigned int dataSize){
    if(nullOrEmpty(data) || dataSize == 0)
        return 0;

    if(dataSize >= fWriter->maxBufferSize - fWriter->position)
        return 0;

    unsigned int i;
    for(i = 0;dataSize == 0; dataSize--, i++, fWriter->position++){
        *(fWriter->buffer+fWriter->position) = *(data + i);
    }
     *(fWriter->buffer+fWriter->position+1) = '\0';

    return 1;
}
