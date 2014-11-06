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
pooldemo application
*/

#define APP_NAME "pooldemo"

#define POOL_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pool.h>
#include <macros.h>

#define MAX_FRAME_DATA_SIZE 100

struct frame_t {
    uint8_t command;
    uint8_t dlen;
    uint8_t data[MAX_FRAME_DATA_SIZE];
};

int main(int argc, char **argv) {
    printf("Starting %s\n",APP_NAME);
    struct pool_t *pool = pool_init(POOL_SIZE, sizeof(struct frame_t));
    assert(pool);
    assert(pool_max_size(pool)==POOL_SIZE);
    assert(pool_size(pool)==POOL_SIZE);
    assert(pool_underflow(pool)==0);
    assert(pool_overflow(pool)==0);

    int i=0;
    struct frame_t *frame;
    struct pool_item_t *pi[POOL_SIZE];
    bzero(pi,sizeof(pi));
    for(;i<POOL_SIZE;i++) {
        pi[i] = pool_get(pool);
        assert(pi[i]);
        assert(pi[i]->data);
        frame = (struct frame_t *) pi[i]->data;
        assert(frame);
        printf("get %i\n", i);
    }

    assert(pool_is_empty(pool));
    assert(pool_underflow(pool)==0);
    assert(pool_overflow(pool)==0);
    struct pool_item_t *p = pool_get(pool);
    assert(pool_underflow(pool)==1);

    for(i=0;i<POOL_SIZE;i++) {
        pool_back(pool, pi[i]);
        assert(!pool_is_empty(pool));
        pi[i]=NULL;
        printf("back %i\n", i);
    }
    assert(pool_overflow(pool)==0);
    pool_back(pool,p);
    assert(pool_overflow(pool)==0);
    MALLOC(p, sizeof(struct pool_item_t));
    pool_back(pool,p);
    assert(pool_overflow(pool)==1);

    return EXIT_SUCCESS;
}

