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

/**
 Default File Writer: write buffer to file, if not exits file or direction then the function create it

 @param pathname path and filename (Where?)
 @param buffer data for write (What?)
 @return return 1 if eweryting is awesome, return 0 if error, return 2 if created new file or direction
*/
char fw_fileWriteDefault(const char *pathname, const char *buffer);


/**
 File Writer: write buffer to file, if not exits file or direction then the function create it

 @param pathname path and filename (Where?)
 @param buffer data for write (What?)
 @param nexists 0 if file or direction is not exits and you don't create it; 1 if you want create it
 @param content 0 if you would like re-write file; 1 if you would like to append a new data to the file
 @return return 1 if everything is awesome, return 0 if error, return 2 if created new file or direction
*/
char fw_fileWrite(const char *pathname, const char *buffer, const char nexists, const char content);


/**
 Create file and write to TEMP/fw_{date}/{time}.txt

 @param pathname filename
 @param buffer data for write (What?)
 @return return 1 if eweryting is awesome, return 0 if error
*/
char fw_fileWriteTempDefault(const char *buffer);


/**
 File Writer in TEMP: write buffer to file in temp, if not exits file or direction then the function create it

 @param pathname filename
 @param buffer data for write (What?)
 @return return 1 if eweryting is awesome, return 0 if error, return 2 if created new file or direction
*/
char fw_fileWriteTemp(const char *filename, const char *buffer);


/**
 File Exists info - Question: be or not be?

 @param pathname path and filename
 @return return 1 if file is exits or 0 if not exits
*/
char fw_exists(const char *pathname);


/**
 File or Direction info

 @param pathname path and filename
 @return return 1 if it is file, 2 if it is direction, 0 if not exists
*/
char fw_fod(const char *pathname);


/**
 Delete File or Direction

 @param pathname path and filename
 @return return 1 if delete file, 2 if delete direction, 0 if error
*/
char fw_delete(const char *pathname);


/**
 Read Only info

 @param pathname path and filename
 @return return 1 if read only or 0 if not exists
*/
char fw_readonly(const char *pathname);


/**
 Can write info

 @param pathname path and filename
 @return return 1 if can write, 0 if read only or not exists
*/
char fw_canwrite(const char *pathname);


/**
 Create Direction

 @param pathname path and filename
 @return return 1 if everything is awesome, 0 error
*/
char fw_mkdir(const char *pathname);
