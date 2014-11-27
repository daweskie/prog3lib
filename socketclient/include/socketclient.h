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




struct sockaddr {
    short int sin_family;  /* address family: AF_INET */
    unsigned short int sin_port;  /* port */
    struct in_addr sin_addr;  /* internet address */
    unsigned char sin_zero[8];
};

struct in_addr{
        unsigned long s_addr;  /* address in network byte order */

};
/**

    @param family protokol család
    @param type pl SOCKET_STREAM
    @param  protocol default a type és a family alapján
    @return -1 hiba vagy file leíró
*/

int socket(int family, int type,int protocol){
};
/**

    @param fd file leíró
    @param *addr server cím
    @param alen cim mérete
    @return ok 0 hiba -1

*/


int connect(int fd, struct sockaddr *addr, int alen){
};

/**

    @param socket file leíró
    @param üzenet
    @param üzenet hossz
    @return Ok 0 hiba -1
*/

int write(int fd, char *buff, int len){
};
/**

    @param socket file leíró
    @param üzenet
    @param üzenet hossz
    @return Ok 0 hiba -1
*/

int read(int fd, char *buff, int len){
};

/**
    @param fd socket file leíró
    @return Ok 0 hiba -1
*/

int close(int fd){
};
