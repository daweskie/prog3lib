#ifndef FILEWRITESS_H_INCLUDED
#define FILEWRITESS_H_INCLUDED

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
fwStringStream library

*/

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

struct FWStringStream {
    char *buffer;
    unsigned int nextPosition; //actual buffer length
    unsigned int position; //last char position
    unsigned int maxBufferSize;
};

/**
 Initialise FWStringStream variable

 @param maxBufferSize maximum buffer size
 @return FWStringStream variable
*/
struct FWStringStream *fwssInit(unsigned int maxBufferSize);


/**
 Add date to FWStringStream Buffer

 @param fwss FWStringStream variable
 @param data Data
 @param dataSize data size
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssAddToBuffer(struct FWStringStream *fwss, char *data, unsigned int dataSize);


/**
 Copy data to x position in FWStringStream Buffer

 @param fwss FWStringStream variable
 @param x position in buffer (min = 0, max = nextPosition if not equal maxBufferSize)
 @param data Data
 @param dataSize data size
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssPasteToBuffer(struct FWStringStream *fwss, unsigned int x, char *data, unsigned int dataSize);


/**
 Clear date in FWStringStream Buffer

 @param fwss FWStringStream variable
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssClearBuffer(struct FWStringStream *fwss);


/**
 Remove last n char in FWStringStream Buffer

 @param fwss FWStringStream variable
 @param n number of characters
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssLastRemoveInBuffer(struct FWStringStream *fwss, unsigned int n);


/**
 Remove n char from x in FWStringStream Buffer

 @param fwss FWStringStream variable
 @param x position of characters (begins in 0)
 @param n number of characters (minimum 1)
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssRemoveInBuffer(struct FWStringStream *fwss, unsigned int x, unsigned int n);


/**
 Write date with FWStringStream

 @param fwss FWStringStream variable
 @param pathname path and filename (Where?)
 @param append 0 if you would like re-write file; 1 if you would like to append a new data to the file
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssWriteBuffer(struct FWStringStream *fwss, const char *pathname, int append);

/**
 close FWStringStream variable

 @param fwss FWStringStream variable
 @return return 1 if everything is awesome, return 0 if error
*/
int fwssClose(struct FWStringStream *fwss);


#endif // FILEWRITESS_H_INCLUDED
