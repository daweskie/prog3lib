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
 @param createIfNotExists
 @param createIfNotExists is 1 means create if not exists
 @return 0 if file isn't exist, 1 if exist
*/
int cfgInit(char *fileName, int createIfNotExists);



/**
If modified the key value pair save it to file.

@return 0 if can't save the file, 1 if can save the file.
*/
int cfgClose();

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetString(const char *key, char *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetStringDef(const char *key, char def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetChar(const char *key, char *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetCharDef(const char *key, char def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetLong(const char *key, long *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetLongDef(const char *key, long def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetInt(const char *key, int *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetIntDef(const char *key, int def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetShort(const char *key, short *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetShortDef(const char *key, short def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetFloat(const char *key, float *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetFloatDef(const char *key, float def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetDouble(const char *key, double *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetDoubleDef(const char *key, double def);

/**
 *
@param key is the keys
@param addr adddress of value
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetBool(const char *key, int *addr);

/**
 *
@param key is the keys
@param def default value if key is not exist
@return 1 if the key exist or 0 if the key isn't exist
 */
int cfgGetBoolDef(const char *key, int def);



/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetString(const char *key, const char *value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetChar(const char *key, const char value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
short cfgSetShort(const char *key, const short value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetInt(const char *key, const int value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetLong(const char *key, const long value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetFloat(const char *key, const float value);

/**
	@param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetDouble(const char *key, const double value);

/**
    @param key is the keys
    @param value the new value of the key
    @return 1 if value set was successful or 0 if error occured

*/
int cfgSetBool(const char *key, const int value);
