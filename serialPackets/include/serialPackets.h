#ifndef SERIALPACKETS_H_INCLUDED
#define SERIALPACKETS_H_INCLUDED

/**  -----Structures------ */



/**Structure of Unused */

struct Unused{
    /** Tail queue un_head. */
    struct un_tailhead *un_headp;

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
    int un_underflow;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int un_overflow;
};

/**Structure of Unused */

struct Valid{
    /** Tail queue val_head. */
    struct val_tailhead *val_headp;

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
    int val_underflow;

    /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
    int val_overflow;
};


/**  ------Initializes and sizes------- */


/** Initialize an "unused pool" */
//struct Unused *un_pool_init(int un_size, int packet_size);

/** Initialize an "valid pool" */
//struct Valid *val_pool_init(int val_size, int packet_size);

/** Current size of Unused */
//int un_size(struct Unused *unused);

/** Current size of Valid */
//int val_size(struct Valid *valid);

/** Max size of pools */
//int pool_max_size(struct Unused *unused);
//int pool_max_size(struct Valid *valid);



/**  -----Errors------ */

/** Unused is empty (part of underflow check)*/
int un_is_empty(struct Unused *unused);

/** Valid is empty (part of underflow check)*/
int val_is_empty(struct Valid *valid);

/** Underflow in Unused */
int un_underflow(struct Unused *unused);

/** Underflow in Valid */
int val_underflow(struct Valid *valid);

/** Overflow in Unused */
int un_overflow(struct Unused *unused);

/** Overflow in Valid */
int val_overflow(struct Valid *valid);


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

/*          WTF???????????????----------------------
    u_int16_t spGetMtu(struct PacketFifo *fifo);
*/

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

/**Put back packet to Unused
    @param the pool.  It can be NULL
    @param the item to put back. It can be NULL.

*/
void unused_give(struct pool_t *pool, struct Packet *packet);

/** Gets packet to Valid
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty

*/
struct Packet *valid_get(struct pool_t *pool);

/**Gives packet from Unused
    @param the pool.  It can be NULL
    @return the element or NULL if pool is NULL or pool is empty
*/
void valid_give(struct pool_t *pool, struct Packet *packet);

/**Checks the pool for available packet
    @param  the pool
    @return 0 if pool is out of valid packets, or anything else for available packets

*/
int spIsValidPackets(struct PacketFifo *fifo);

/**Number of overruns, when a packet needed to put back to an already full pool
    @param the pool
    @return number of overruns
*/
long spGetOverrunCounts(struct PacketFifo *fifo);

/**Increment the global error counter
    @param the pool
    @return 1 for ok, 0 for error

*/
void spIncErrorCounts(struct PacketFifo *fifo);

/**Increment the overrun counter
    @param the pool
    @return 1 for ok, 0 for error

*/
void spIncOverrunCounts(struct PacketFifo *fifo);


#endif // SERIALPACKETS_H_INCLUDED




//struct pool_t *pool_init(int pool_size, int item_size);




/*
struct PacketFifo *spInit(unsigned int maxPackets, u_int16_t mtu);
int spClose(struct PacketFifo *fifo);
uint16_t spGetMtu(struct PacketFifo *fifo);
int spGetMaxPackets(struct PacketFifo *fifo);
struct Packet *spGetPacketFromPool(struct PacketFifo *fifo);
void spRecycle(struct PacketFifo *fifo, struct Packet *packet);
bool spIsValidPackets(struct PacketFifo *fifo);
struct Packet *spGetPacket(struct PacketFifo *fifo);
int spPutPacket(struct PacketFifo *fifo, struct Packet *packet);
long spGetAllPacketCounts(struct PacketFifo *fifo);
long spGetErrorPacketCounts(struct PacketFifo *fifo);
long spGetOverrunCounts(struct PacketFifo *fifo);
void spIncErrorCounts(struct PacketFifo *fifo);
void spIncOverrunCounts(struct PacketFifo *fifo);

/**	Structure of Packets
  address: the destination of the Packet
  data: what the Packet contains
  n: the size of data */

struct Packet{
char *address;
char *data;
int n;
}

struct pool_t *spPool_init(int pool_size, int packet_size);

struct pool_t{
    struct unused_t{
        /** Tail queue un_head. */
        struct un_tailhead *un_headp;

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
        int un_underflow;

        /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
        int un_overflow;
    };

/**Structure of Unused */

    struct valid_t{
        /** Tail queue val_head. */
        struct val_tailhead *val_headp;

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
        int val_underflow;

        /** number of overflow for statistics. Means of overflow is try to put back an element to a full pool */
        int val_overflow;
    };
};
