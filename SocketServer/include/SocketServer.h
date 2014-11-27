/*
 * Copyright (C)
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
SocketServer library

*/

int scksrvCallbackConnect();

int scksrvCallbackError(int code);

struct SocketServer {

};

/* Reads the configuration file, and separates it's rows. */

struct SocketServer *scksrvInit(uint16_t port, uint16_t maxConnects,
                                int (*scksrvCallbackConnect)(),
                                int (*scksrvCallbackError)(int code)  );

int scksrvClose(struct SocketServer *sckServer);



//char config_reader ();

/* Chooses the proper task to excecute if it exists, returns zero if it isn't */

//char command_execution (char config_reader(), char requested_command);
