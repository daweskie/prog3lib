/*
 * Copyright (C) Zsolt Lovonyák, Tamás Manolakis
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
ConfigModule library

*/

/**
Open the config file. Read the keys and values.Close file.

 @param *fileName 
 @return 0 if file isn't exist, 1 if exist
*/
int confInit(char *fileName);

/**
 * 
@param *key is the keys
@param *addr adddress of value
@return value of string or 0 if the key isn't exist
 */
char *getString(const char *key, char *addr);

/**
 * 
@param *key is the keys
@param *def default value if key is not exist
@return value of string or default value
 */
char *getStringDef(const char *key, char *def);

/**
 * 
@param *key is the keys
@param *addr adddress of value
@return value of char or 0 if the key isn't exist
 */
char *getString(const char *key, int *addr);

/**
 * 
@param *key is the keys
@param *def default value if key is not exist
@return value of char or default value
 */
char *getStringDef(const char *key, int *def);

/**
 * 
@param *key is the keys
@param *addr adddress of value
@return value of key or 0 if the key isn't exist
 */
int *getString(int *key, int *addr);

/**
 * 
@param *key is the keys
@param *def default value if key is not exist
@return value of key or default value
 */
int *getStringDef(int *key, int *def);

/**
 * 
@param *key is the keys
@param *addr adddress of value
@return value of key or 0 if the key isn't exist
 */
long *getLong(long *key, int *addr);

/**
 * 
@param *key is the keys
@param *def default value if key is not exist
@return value of key or default value
 */
long *getLongDef(long *key, int *def);


/**
    @param *key is the keys
    @param *value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int setString(const char *key, const char *value);

/**
    @param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int setChar(const char *key, const char value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
short setShort(const char *key, const short value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int setInt(const char *key, const int value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
long setLong(const char *key, const long value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
float setFloat(const char *key, const float value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
double setDouble(const char *key, const double value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int setBool(const char *key, const int value);
