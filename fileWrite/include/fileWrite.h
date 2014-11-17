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
char fw_filewrite_default(const char *pathname, const char *buffer);

/**
 File Writer: write buffer to file, if not exits file or direction then the function create it

 @param pathname path and filename (Where?)
 @param buffer data for write (What?)
 @param nexits 0 if file or direction is not exits and you don't create it; 1 if you want create it
 @param content 0 if you would like re-write file; 1 if you would like to append a new data to the file
 @return return 1 if eweryting is awesome, return 0 if error, return 2 if created new file or direction
*/
char fw_filewrite(const char *pathname, const char *buffer, const char nexits, const char content);
