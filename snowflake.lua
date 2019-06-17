local core = require "snowflake.core"

local function gen62char()
    local map = {}
    for i=0,61 do
        local char
        if 10 <= i and i < 36 then
            char = string.char(65+i-10)
        elseif 36 <= i and i < 62 then
            char = string.char(97+i-36)
        else
            char = tostring(i)
        end
        map[i] = char
        map[char] = i
    end
    return map
end

local snowflake = {
	nodeid = nil,
	nodes = {},
    char62 = gen62char(),
}

function snowflake.init(nodeid,nodes)
	snowflake.nodeid = nodeid
	if nodes then
		for nodename,nodeid in pairs(nodes) do
			snowflake.node(nodename,nodeid)
		end
	end
end

function snowflake.node(nodename,nodeid)
	-- get
	if nodeid == nil then
		return snowflake.nodes[nodename]
	end
	-- register
	assert(snowflake.nodes[nodename] == nil)
	assert(snowflake.nodes[nodeid] == nil)
	snowflake.nodes[nodename] = nodeid
	snowflake.nodes[nodeid] = nodename
end


function snowflake.uuid(nodeid)
	if type(nodeid) == "string" then
		nodeid = snowflake.nodes[nodeid]
	end
	nodeid = nodeid or snowflake.nodeid
	return core.uuid(nodeid)
end

function snowflake._tostring(num,base)
    local list = {}
    while num > 0 do
        local divider = math.floor(num / base)
        local remainder = num % base
        num = divider
        table.insert(list,1,snowflake.char62[remainder])
    end
    return table.concat(list,"")
end

function snowflake.tostring(uuid,base)
    base = base or 10
    assert(base <= 62)
    local timestamp = snowflake.getTimestampByUUID(uuid)
    local nodeid = snowflake.getNodeIdByUUID(uuid)
    local sequence = snowflake.getSequenceByUUID(uuid)
    local list = {snowflake._tostring(timestamp,base),snowflake._tostring(nodeid,base),snowflake._tostring(sequence,base)}
    return table.concat(list,"-")
end

function snowflake._tointeger(str,base)
    local num = 0
    for i=1,#str do
        local b = string.sub(str,i,i)
        num = num * base + snowflake.char62[b]
    end
    return num
end

function snowflake.tointeger(str,base)
    base = base or 10
    assert(base <= 62)
    local timestamp,nodeid,sequence = string.match(str,"([0-9A-Za-z]+)-([0-9A-Za-z]+)-([0-9A-Za-z]+)")
    timestamp = snowflake._tointeger(timestamp,base)
    nodeid = snowflake._tointeger(nodeid,base)
    sequence = snowflake._tointeger(sequence,base)
    return snowflake.composeUUID(timestamp,nodeid,sequence)
end

function snowflake.getTimestampByUUID(uuid)
	return core.getTimestampByUUID(uuid)
end

function snowflake.getNodeIdByUUID(uuid)
	return core.getNodeIdByUUID(uuid)
end

function snowflake.getSequenceByUUID(uuid)
	return core.getSequenceByUUID(uuid)
end

function snowflake.getNodeNameByUUID(uuid)
	return snowflake.node(snowflake.getNodeIdByUUID(uuid))
end

function snowflake.composeUUID(timestamp,nodeid,sequence)
    return core.composeUUID(timestamp,nodeid,sequence)
end

return snowflake
