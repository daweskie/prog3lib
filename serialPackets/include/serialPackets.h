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

#include <pthread.h>
#include <sys/queue.h>


struct PoolUnUsed {
    int value;
    TAILQ_ENTRY(PoolUnUsed) entries;
};

struct FifoUnUsed {
    struct TailHead *headp;
    TAILQ_HEAD(TailHead, PoolUnUsed) head;
    pthread_mutex_t mutex;
};


struct Unused {
    char *name;
    pthread_t thread;
    struct FifoUnUsed *values;
    struct FifoUnUsed *pool;
    };

struct PoolUsed {
    int value;
    TAILQ_ENTRY(PoolUsed) entries;
};

struct FifoUsed {
    struct TailHead *headp;
    TAILQ_HEAD(TailHead, PoolUsed) head;
    pthread_mutex_t mutex;
};


struct Unused {
    char *name;
    pthread_t thread;
    struct FifoUsed *values;
    struct FifoUsed *pool;
    };
/*
serialPackets library

*/

