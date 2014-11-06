#ifndef POOL_H_INCLUDED
#define POOL_H_INCLUDED

/*
 * Copyright (C)  2014 Zoltan Zidarics (Zamek)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/** \file pool.h
    \brief Presenting pool idea

    The continuos memory allocation and dispose cause memory fragmentation.
    Solving the problem:
    1. Use preallocated memory fragments for the data
    2. Hold these fragments in a pool
    3. If a client needs memory request from the pool
    4. After using the clients give back the unnecessary memory to the pool

    The pool doesn't known the type of an element it only needs a pointer and size of an item
    This realization of pool is thread safe
*/

#include <stdint.h>
#include <sys/queue.h>
#include <pthread.h>

/**
    Item type of pool.

*/
struct pool_item_t {
    /** pool use a TAILQ. This is for TAILQ entry */
    TAILQ_ENTRY(pool_item_t) entries;
    /** pool item data */
    void *data;
};

/**
    Pool structure.
*/
struct pool_t{
    /** Tail queue head. */
    struct tailhead *headp;
    /** TAILQ declaration */
    TAILQ_HEAD(tailhead, pool_item_t) head;
    /** Mutex for multithread using */
    pthread_mutex_t mutex;
    /** Size of pool */
    int size;
    /** Max number of element in the pool */
    int max_size;
    /** Size of a pool item */
    int item_size;
    /** number of underflow for statistics. Means of underflow is try to get an element from an empty pool*/
    int underflow;
    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int overflow;
};

/**
    Initialize a new pool with a given size an itemsize
    \param pool_size elements in the pool
    \param size of an element in pool
    \return the initialized pool or NULL if pool_size or item_size less or equal than 0
*/
struct pool_t *pool_init(int pool_size, int item_size);

/**
    the current size of pool
    \param pool the pool. It can be NULL
    \return the current size of the pool or 0 if pool is NULL
*/
int pool_size(struct pool_t *pool);

/**
    the maximum size of pool
    \param pool the pool. It can be NULL
    \return the maximum size of the pool or 0 if pool is NULL
*/
int pool_max_size(struct pool_t *pool);

/**
    Getting an element from the pool or NULL if pool is empty
    \param the pool.  It can be NULL
    \return the element or NULL if pool is NULL or pool is empty
*/
struct pool_item_t *pool_get(struct pool_t *pool);

/**
    Put back an element into the pool
    \param the pool.  It can be NULL
    \param the item to put back. It can be NULL.
*/
void pool_back(struct pool_t *pool, struct pool_item_t *item);

/**
    return true if pool is empty
    \param the pool.  It can be NULL
    \return 0 if pool is not empty or 1 if pool is NULL or empty
*/
int pool_is_empty(struct pool_t *pool);

/**
    return the number of underflows for statistics. Means of underflow is try to get an element from an empty pool
    \param the pool.  It can be NULL
    \return number of underflows or 0 if pool is empty
*/
int pool_underflow(struct pool_t *pool);

/**
    return the number of overflows for statistics. Means of overflow is try to put back an element to a full pool
    \param the pool.  It can be NULL
    \return number of overflows or 0 if pool is empty
*/
int pool_overflow(struct pool_t *pool);

#endif // POOL_H_INCLUDED
