/*
 * Copyright (C) 2014 Gonzcol Peter and Gulyas Daniel
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
logging library

*/

/**
 Export log info with FileWriter; Output format: Date|type|app name|text; Default folder: /var/log/mylog

 @param type 1 - info, 2 - warning, 3 - error
 @param app_name Your app/function name
 @param value text
 @return 1 OK, 0 not work
*/
int logging_out(char type, char * app_name, char * value);












