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

 @param fileName
 @param createIfNotExists is 1 means create if not exists
 @return 0 if file isn't exist, 1 if exist
*/
int cfgInit(char *fileName, int createIfNotExists);


int cfgClose();

/**
 *
@param *key is the keys
@param *addr adddress of value
@return value of string or 0 if the key isn't exist
 */
int cfgGetString(const char *key, char *addr);

/**
 *
@param *key is the keys
@param *def default value if key is not exist
@return value of string or default value
 */
char cfgGetStringDef(const char *key, char def);

/**
 *
@param *key is the keys
@param *addr adddress of value
@return value of key or 0 if the key isn't exist
 */
int cfgGetLong(long *key, long *addr);

/**
 *
@param *key is the keys
@param *def default value if key is not exist
@return value of key or default value
 */
long cfgGetLongDef(long *key, long def);

int cfgGetInt(long *key, int *addr);

int cfgGetIntDef(long *key, int def);

int cfgGetShort(long *key, short *addr);

int cfgGetShortDef(long *key, short def);

int cfgGetFloat(long *key, float *addr);

int cfgGetFloatDef(long *key, float def);

int cfgGetDouble(long *key, double *addr);

int cfgGetDoubleDef(long *key, double def);

int cfgGetBool(long *key, int *addr);

int cfgGetBoolDef(long *key, int def);



/**
    @param *key is the keys
    @param *value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/

int cfgSetString(const char *key, const char *value);

/**
    @param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetChar(const char *key, const char value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
short cfgSetShort(const char *key, const short value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetInt(const char *key, const int value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetLong(const char *key, const long value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetFloat(const char *key, const float value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetDouble(const char *key, const double value);

/**
	@param *key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetBool(const char *key, const int value);
