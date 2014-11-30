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

struct sckClient {

};

/**

    @param family protokol család
    @param type pl SOCKET_STREAM
    @param  protocol default a type és a family alapján
    @return -1 hiba vagy file leíró
*/

struct sckClient *sckclInit(int family, int type,int protocol);

/**

    @param fd file leíró
    @param *addr server cím
    @param alen cim mérete
    @return ok 0 hiba -1

*/


int sckConnect(struct sckClient *client, char *host, uint16_t port);

/**

    @param socket file leíró
    @param üzenet
    @param üzenet hossz
    @return number of bytes written to socket
*/

int write(struct sckClient *client, char *buff, int len);

/**

    @param socket file leíró
    @param üzenet
    @param üzenet hossz
    @return number of bytes readed
*/

int read(struct sckClient *client, char *buff, int len);

/**
    @param fd socket file leíró
    @return 0 if error or 1 if ok
*/

int close(struct sckClient *client);
