/*
 * Copyright (C) Attila Lenkovits, Attila Zsiga
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
FileReader library
*/

/**
 File readable test.

 @param path path and filename of a file
 @return  return 0 if file or direction is not exist, 1 file is readable
*/
int FileIsReadable(const char *path);

/**
 Reading a file to a configurable size and counts buffer.

 @param path path and filename of a file
 @param buffer buffer address where you want to read
 @param size size of a buffer
 @param counts counts of buffers
 @return return -1 if file or direction is not exist, return 0 if buffers is not enugh,return 1 if read is success
*/
char FileReader(const char *path, const char *buffer, int size, int counts);

/**
 Reading a file to a default size and counts buffer.

 @param path path and filename of a file
 @param buffer buffer address where you want to read
 @return return -1 if file or direction is not exist, return 0 if buffers is not enugh,return 1 if read is success
*/
char FileReaderDefault(const char *path, const char *buffer);


/**
 Reading a file to a configurable size and counts buffer. The start line and reading lines are also configurable.

 @param path path and filename of a file
 @param buffer buffer address where you want to read
 @param size size of a buffer
 @param counts counts of buffers
 @param from number of line where start reading
 @param lines number of readnig lines
 @return return -1 if file or direction is not exist, return 0 if buffers is not enugh,return 1 if read is success
*/
char FileLinesReader(const char *path, const char *buffer, int size, int counts, int from, int lines);

/**
 Reading a file to a default size and counts buffer. The start line and reading lines are also configurable.

 @param path path and filename of a file
 @param buffer buffer address where you want to read
 @param from number of line where start reading
 @param lines number of readnig lines
 @return return -1 if file or direction is not exist, return 0 if buffers is not enugh,return 1 if read is success
*/
char FileLinesReaderDefault(const char *path, const char *buffer, int from, int lines);
