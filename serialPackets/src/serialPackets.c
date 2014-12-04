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

    struct unused_t *result0;
    struct valid_t *result1;
    MALLOC(result0, sizeof(struct unused_t));
    MALLOC(result1, sizeof(struct valid_t));
    TAILQ_INIT(&result0->un_head);
    TAILQ_INIT(&result1->val_head);
    pthread_mutex_init(&result0->mutex, NULL);
    pthread_mutex_init(&result1->mutex, NULL);
    result0->errorcnt=0;
    result0->overruncnt=0;
    result1->errorcnt=0;
    result1->overruncnt=0;
    int i=0;
    result0->max_size = pool_size;
    result0->un_size=pool_size;
    result0->packet_size = item_size;
    result1->max_size = pool_size;
    result1->val_size=pool_size;
    result1->packet_size = item_size;
    for (;i<pool_size;i++) {
        struct Packet *packet;
        MALLOC(packet, sizeof(struct Packet));
        MALLOC(packet->data, item_size);
        bzero(packet->data, item_size);
        TAILQ_INSERT_TAIL(&result0->un_head, packet, entries);
        TAILQ_INSERT_TAIL(&result1->val_head, packet, entries);
    }
    /*struct Result *result;
    result->unused=result0;
    result->valid=result1;*/


    return result0&&result1;
}

int pool_max_size(struct pool_t *pool){
    return pool ? pool_t->[valid_t.max_size]:0;
}
