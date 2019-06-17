#include <lua.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdint.h>
#include "snowflake.h"

/**
 * 根据UUID获得其包含的时间戳
 * @function snowflake.getTimestampByUUID
 * @param uuid int64 分布式唯一ID
 * @return timestamp int 节点ID
 */
static int
lgetTimestampByUUID(lua_State *L) {
    uint64_t i = luaL_checkinteger(L,1);
    uint64_t timestamp = getTimestampByUUID(i);
    lua_pushinteger(L,timestamp);
    return 1;
}

/**
 * 根据UUID获得其包含的节点ID
 * @function snowflake.getNodeIdByUUID
 * @param uuid int64 分布式唯一ID
 * @return nodeId int 节点ID
 */
static int
lgetNodeIdByUUID(lua_State *L) {
    uint64_t i = luaL_checkinteger(L,1);
    int nodeId = getNodeIdByUUID(i);
    lua_pushinteger(L,nodeId);
    return 1;
}

/**
 * 根据UUID获得其包含的序号ID
 * @function snowflake.getSequenceByUUID
 * @param uuid int64 分布式唯一ID
 * @return sequence int 节点ID
 */
static int
lgetSequenceByUUID(lua_State *L) {
    uint64_t i = luaL_checkinteger(L,1);
    int sequence = getSequenceByUUID(i);
    lua_pushinteger(L,sequence);
    return 1;
}

/**
 * 由时间戳,节点ID,序号构成uuid
 * @function snowflake.composeUUID
 * @param timestamp int 时间戳(范围:[0,2^41))
 * @param nodeid int 节点ID(范围:[0,2^10))
 * @param sequence int 序号(范围:[0,2^12))
 * @return uuid uint64 分布式唯一ID
 */
static int
lcomposeUUID(lua_State *L) {
    uint64_t timestamp = luaL_checkinteger(L,1);
    int nodeid = luaL_checkinteger(L,2);
    int sequence = luaL_checkinteger(L,3);
    uint64_t id = composeUUID(timestamp,nodeid,sequence);
	lua_pushinteger(L, id);
    return 1;
}


/**
 * 传递节点ID,生成分布式唯一ID
 * @function snowflake.uuid
 * @param nodeId int 节点ID
 * @return uuid uint64 分布式唯一ID
 */
static int
luuid(lua_State *L) {
    int nodeId = luaL_checkinteger(L,1);
    uint64_t id = uuid(nodeId);
	lua_pushinteger(L, id);
    return 1;
}


LUAMOD_API int
luaopen_snowflake_core(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg l[] = {
        {"getTimestampByUUID",lgetTimestampByUUID},
        {"getNodeIdByUUID",lgetNodeIdByUUID},
        {"getSequenceByUUID",lgetSequenceByUUID},
        {"composeUUID",lcomposeUUID},
        {"uuid",luuid},
        {NULL,NULL},
    };

    luaL_newlib(L,l);
    return 1;
}
