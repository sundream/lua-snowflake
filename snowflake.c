/*
 * 64位分布式id生成,由snowflake算法实现,构成如下
 *1bit  41bit     10bit     12bit
 *+--+---------+---------+--------+
 *|0 |timestamp|nodeId   |sequence|
 *+--+---------+---------+--------+
 */

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include "snowflake.h"

#define TIMESTAMP_BIT (41)
#define NODEID_BIT (10)
#define SEQUENCE_BIT (12)
#define NODEID_MASK ((1<<NODEID_BIT)-1)

static uint64_t genTimestamp() {
    struct timeval tv;
    gettimeofday(&tv, 0);

    return (uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000;
}

static uint64_t genNodeId(nodeId) {
    return (uint64_t) (nodeId % (1 << NODEID_BIT));
}

static uint64_t genIncrement() {
    static uint64_t i = 0;
    i = (i + 1) & ~(1 << SEQUENCE_BIT);
    return i;
}

int getNodeIdByUUID(uint64_t uuid) {
    return (uuid >> SEQUENCE_BIT) & NODEID_MASK;
}

uint64_t uuid(int nodeId) {
    uint64_t a = genTimestamp();
    uint64_t b = genNodeId(nodeId);
    uint64_t c = genIncrement();
    return (a << (NODEID_BIT + SEQUENCE_BIT))
         | (b << SEQUENCE_BIT)
         | c;
}
