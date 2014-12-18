#ifndef SERIALPACKETS_H_INCLUDED
#define SERIALPACKETS_H_INCLUDED

#include <stdint.h>
#include <sys/queue.h>
#include <pthread.h>
/**  -----Structures------ */
struct unused_t {
    /** Tail queue un_head. */
    struct un_tailhead *headp;

    /** TAILQ declaration */
    TAILQ_HEAD(un_tailhead, Packet) un_head;

    /**  Mutex for multithread using  */
    pthread_mutex_t mutex;

    /** Current size of pool */
    int un_size;

    /** Max number of element in the pool */
    int max_size;

    /** Size of a pool item */
    int packet_size;

    /** number of underflow for statistics. Means of underflow is try to get an element from an empty pool*/
    int errorcnt;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int overruncnt;
};

struct valid_t {
    /** Tail queue val_head. */
    struct val_tailhead *headp;

    /** TAILQ declaration */
    TAILQ_HEAD(val_tailhead, Packet) val_head;

    /**  Mutex for multithread using */
    pthread_mutex_t mutex;

    /** Current size of pool */
    int val_size;
    /** Max number of element in the pool */
    int max_size;

    /** Size of a pool item */
    int packet_size;

    /** number of underflow for statistics. Means of underflow is try to get an element from an empty pool*/
    int errorcnt;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int overruncnt;
};

struct pool_t {
    struct unused_t unused;
    struct valid_t valid;
};

/**	Structure of Packets
  address: the destination of the Packet
  data: what the Packet contains
  n: the size of data */

struct Packet {
    TAILQ_ENTRY(Packet) entries;
    char *address;
    void *data;
    int n;
};

/*struct Result {
    int *unused;
    int *valid;
};*/

/** --------------------Actual beadando--------------------- */


/** Initialize pools
    @param max number of packets
    @param packet size
    @return the pools or NULL if max_size or packet_size is >= 0
*/

struct pool_t *pool_init(int max_size, int packet_size);


/** Closes serialPackets
    @param the pools
    @return 0 if failed, else if successful
*/

int spClose(struct pool_t *pool);


/** returns Maximum Transfer size
    @param the pool
    @return the maximum size of a Packet
*/

uint16_t spGetMaxUnitSize(struct pool_t *pool);


/** Maximum number of packets
    @param the pool
    @return the maximum size or 0 if pool is NULL
*/

int spMaxPackets(struct pool_t *pool);


/** Gets packet to Unused
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty
*/

struct Packet *unused_get(struct pool_t *pool);


/** Put back packet to Unused
    @param the pool.  It can be NULL
    @param the item to put back. It can be NULL.
    @return the packet to put back
*/

void unused_give(struct pool_t *pool, struct Packet *packet);


/**Checks the pool for available packet
    @param  the pool
    @return 0 if pool is out of valid packets, or anything else for available packets*/

int spIsValidPackets(struct pool_t *pool);


/** Gets packet to Valid
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty
*/

struct Packet *valid_get(struct pool_t *pool);


/** Gives packet from Unused
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty
*/

void valid_give(struct pool_t *pool, struct Packet *packet);


/** return number of packets in pool
    @param the pool
    @return number of packets (all of them)
*/

uint16_t spPacketCounts(struct pool_t *pool);
https://developer.android.com/sdk/installing/index.html?pkg=tools

/** returns number of all errors
    @param the pool
    @return number of all errors
*/

long spPacketErrors(struct pool_t *pool);

/**Number of overruns, when a packet needed to put back to an already full pool
    @param the pool
    @return number of overruns
*/
long spGetOverrunCounts(struct pool_t *pool);

/**Increment the global error counter
    @param the pool
    @return 1 for ok, 0 for error

*/
void spIncErrorCounts(struct pool_t *pool);

/**Increment the overrun counter
    @param the pool
    @return 1 for ok, 0 for error

*/
void spIncOverrunCounts(struct pool_t *pool);



#endif // SERIALPACKETS_H_INCLUDED











/*------------------Help from above--------------------
struct PacketFifo *spInit(unsigned int maxPackets, u_int16_t mtu);          pipa
int spClose(struct PacketFifo *fifo);                                       pipa
u_int16_t spGetMtu(struct PacketFifo *fifo);                                pipa
int spGetMaxPackets(struct PacketFifo *fifo);                               pipa
struct Packet *spGetPacketFromPool(struct PacketFifo *fifo);                pipa
void spRecycle(struct PacketFifo *fifo, struct Packet *packet);             pipa
bool spIsValidPackets(struct PacketFifo *fifo);                             pipa
struct Packet *spGetPacket(struct PacketFifo *fifo);                        pipa
int spPutPacket(struct PacketFifo *fifo, struct Packet *packet);            pipa
long spGetAllPacketCounts(struct PacketFifo *fifo);                         pipa
long spGetErrorPacketCounts(struct PacketFifo *fifo);                       pipa
long spGetOverrunCounts(struct PacketFifo *fifo);                           pipa
void spIncErrorCounts(struct PacketFifo *fifo);                             pipa
void spIncOverrunCounts(struct PacketFifo *fifo);                           pipa
*/
