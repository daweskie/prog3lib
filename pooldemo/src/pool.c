/*
 * Copyright (C)  2014 Zoltan Zidarics (Zamek)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/** \file
    \brief
*/


#include <pool.h>
#include <macros.h>

struct pool_t *pool_init(int pool_size, int item_size) {
    if (pool_size<=0 || item_size<=0)
        return NULL;

    struct pool_t *result;
    MALLOC(result, sizeof(struct pool_t));
    TAILQ_INIT(&result->head);
    pthread_mutex_init(&result->mutex, NULL);
    result->underflow=0;
    result->overflow=0;
    int i=0;
    result->max_size = pool_size;
    result->size=pool_size;
    result->item_size = item_size;
    for (;i<pool_size;i++) {
        struct pool_item_t *item;
        MALLOC(item, sizeof(struct pool_item_t));
        MALLOC(item->data, item_size);
        bzero(item->data, item_size);
        TAILQ_INSERT_TAIL(&result->head, item, entries);
    }
    return result;
}

int pool_max_size(struct pool_t *pool){
    return pool ? pool->max_size:0;
}

int pool_size(struct pool_t *pool) {
    return pool ? pool->size : 0;
}

struct pool_item_t *pool_get(struct pool_t *pool) {
    if (!pool)
        return NULL;

    if(TAILQ_EMPTY(&pool->head)) {
        ++pool->underflow;
        pool->size=0;
        return NULL;
    }

    pthread_mutex_lock(&pool->mutex);
    --pool->size;
    struct pool_item_t *element = pool->head.tqh_first;
    TAILQ_REMOVE(&pool->head, pool->head.tqh_first, entries);
    pthread_mutex_unlock(&pool->mutex);

    return element;
}

void pool_back(struct pool_t *pool, struct pool_item_t *item) {
    if (!(pool&&item))
        return;

    if (pool->size>=pool->max_size) {
        ++pool->overflow;
        return;
    }

    pthread_mutex_lock(&pool->mutex);
    ++pool->size;
    TAILQ_INSERT_TAIL(&pool->head, item, entries);
    pthread_mutex_unlock(&pool->mutex);
}

int pool_is_empty(struct pool_t *pool) {
    return pool ? TAILQ_EMPTY(&pool->head) : 1;
}

int pool_underflow(struct pool_t *pool) {
    return pool ? pool->underflow:0;
}

int pool_overflow(struct pool_t *pool) {
    return pool ? pool->overflow:0;
}

