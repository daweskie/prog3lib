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
serialPackets
*/

#include <serialPackets.h>
#include <macros.h>

struct pool_t *pool_init(int pool_size, int item_size) {
    if (pool_size<=0 || item_size<=0)
        return NULL;

    struct pool_t *result;

    MALLOC(result, sizeof(struct pool_t));
    bzero(result, sizeof(struct pool_t));

 //   MALLOC(result, sizeof(struct unused_t));
 //   MALLOC(result, sizeof(struct valid_t));



    TAILQ_INIT(&result->unused.un_head);
    TAILQ_INIT(&result->valid.val_head);
    pthread_mutex_init(&result->unused.mutex, NULL);
    pthread_mutex_init(&result->valid.mutex, NULL);

//    result.unused.errorcnt=0;
//    result.unused.overruncnt=0;
//    result1->errorcnt=0;
//    result1->overruncnt=0;
    int i=0;
    result->unused.max_size = pool_size;
    result->unused.un_size=pool_size;
    result->valid.packet_size = item_size;
    result->valid.max_size = pool_size;
    result->unused.un_size=pool_size;
    result->valid.val_size=pool_size;


    for (;i<pool_size;i++) {
        struct Packet *packet;
        MALLOC(packet, sizeof(struct Packet));
        MALLOC(packet->data, item_size);
        bzero(packet->data, item_size);
        TAILQ_INSERT_TAIL(&result->unused.un_head, packet, entries);
    }
    /*struct Result *result;
    result->unused=result0;
    result->valid=result1;*/
    return result;
}

int spMaxPackets(struct pool_t *pool){
    return pool ? pool->valid.max_size:0;
}

uint16_t spGetMaxUnitSize(struct pool_t *pool){
    return pool ? pool->valid.packet_size:0;
}

uint16_t spPacketCounts(struct pool_t *pool){
    uint8_t packet_count=0;
    packet_count =(pool->valid.val_size) + (pool->unused.un_size);
    return packet_count;
}
