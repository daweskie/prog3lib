/*
 * Copyright (C) Bálint Dávid, Gerber Olivér
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
socketclient library

*/
#include <sys/socket.h>



struct sckClient {



};

/**

    @param family address family
    @param type  SOCKET_STREAM
    @param  protocol default a type
    @return 0 if error or socket number
*/

struct sckClient *sckclInit(int family, int type,int protocol);

/**

    @param data structure
    @param *host server address
    @param uint16_t
    @return 0  if error or 1 if ok

*/


int sckConnect(struct sckClient *client, char *host, uint16_t port);

/**

    @param data structure
    @param *buff  pointer data
    @param len *buff data size
    @return number of bytes written to socket
*/

int write(struct sckClient *client, char *buff, int len);

/**

    @param  data structure
    @param *buff pointer size
    @param buff date size
    @return number of bytes readed
*/

int read(struct sckClient *client, char *buff, int len);

/**
    @param data structure
    @return 0 if error or 1 if ok
*/

int close(struct sckClient *client);
