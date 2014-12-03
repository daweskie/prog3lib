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
fileWrite library

*/

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


struct FileWriter {
    FILE *file;
    char *buffer;
    unsigned int nextPosition; //actual buffer length
    unsigned int position; //last char position
    unsigned int maxBufferSize;
};

/**
 Initialise FileWriter variable

 @param pathname path and filename (Where?)
 @param append 0 if you would like re-write file; 1 if you would like to append a new data to the file
 @param maxBufferSize maximum buffer size
 @return FileWriter variable
*/
struct FileWriter *fwInit(const char *pathname, int append, unsigned int maxBufferSize);


/**
 Add date to FileWriter Buffer

 @param fWriter FileWriter variable
 @param data Data
 @param dataSize data size
 @return return 1 if everything is awesome, return 0 if error
*/
int fwAddToBuffer(struct FileWriter *fWriter, char *data, unsigned int dataSize);


/**
 Copy data to x position in FileWriter Buffer

 @param fWriter FileWriter variable
 @param x position in buffer (min = 0, max = nextPosition if not equal maxBufferSize)
 @param data Data
 @param dataSize data size
 @return return 1 if everything is awesome, return 0 if error
*/
int fwPasteToBuffer(struct FileWriter *fWriter, unsigned int x, char *data, unsigned int dataSize);


/**
 Clear date in FileWriter Buffer

 @param fWriter FileWriter variable
 @return return 1 if everything is awesome, return 0 if error
*/
int fwClearBuffer(struct FileWriter *fWriter);


/**
 Remove last n char in FileWriter Buffer

 @param fWriter FileWriter variable
 @param n number of characters
 @return return 1 if everything is awesome, return 0 if error
*/
int fwLastRemoveInBuffer(struct FileWriter *fWriter, unsigned int n);


/**
 Remove n char from x in FileWriter Buffer

 @param fWriter FileWriter variable
 @param x position of characters (begins in 0)
 @param n number of characters (minimum 1)
 @return return 1 if everything is awesome, return 0 if error
*/
int fwRemoveInBuffer(struct FileWriter *fWriter, unsigned int x, unsigned int n);


/**
 Write date with FileWriter

 @param fWriter FileWriter variable
 @return return 1 if everything is awesome, return 0 if error
*/
int fwWriteBuffer(struct FileWriter *fWriter);

/**
 close FileWriter variable

 @param fWriter FileWriter variable
 @return return 1 if everything is awesome, return 0 if error
*/
int fwClose(struct FileWriter *fWriter);


/**
 Exists info - Question: be or not be?

 @param pathname path and filename
 @return return 1 if file or direction is exits or 0 if not exits
*/
int fwExists(const char *pathname);


/**
 File or Direction info

 @param pathname path and filename
 @return return 1 if it is file, 2 if it is direction, 0 if not exists
*/
int fwFoD(const char *pathname);


/**
 Delete File or Direction

 @param pathname path and filename
 @return return 1 if delete file, 2 if delete direction, 0 if error
*/
int fwDelete(const char *pathname);


/**
 Read Only

 @param pathname path and filename
 @return return 1 if read only or 0 if not
*/
int fwReadOnly(const char *pathname);


/**
 Can write

 @param pathname path and filename
 @return return 1 if can write, 0 if not
*/
int fwCanWrite(const char *pathname);


/**
 Create Direction

 @param pathname path and filename
 @return return 1 if everything is awesome, 0 error
*/
int fwMkDir(const char *pathname);
