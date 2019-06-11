#ifndef snowflake_h
#define snowflake_h

#include <stdint.h>
extern int getNodeIdByUUID(uint64_t uuid);
extern uint64_t uuid(int nodeId);
#endif
