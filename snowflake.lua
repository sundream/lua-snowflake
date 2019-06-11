local core = require "snowflake.core"

local snowflake = {
	nodeid = nil,
	nodes = {},
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

function snowflake.getNodeIdByUUID(uuid)
	return core.getNodeIdByUUID(uuid)
end

function snowflake.getNodeNameByUUID(uuid)
	return snowflake.node(snowflake.getNodeIdByUUID(uuid))
end

return snowflake
