local snowflake = require "snowflake"

function test()
	local nodeid = 100
	local nodename = "node100"
	snowflake.init(nodeid,{
		[nodename] = nodeid,
	})
	--[[
	snowflake.init(nodeid)
	snowflake.node(nodename,nodeid)
	]]
	local cnt = 4096
	for i=1,cnt do
		local uuid = snowflake.uuid()
		print("uuid:",uuid)
		local got_nodeid = snowflake.getNodeIdByUUID(uuid)
		assert(nodeid == got_nodeid)
		local got_nodename = snowflake.getNodeNameByUUID(uuid)
		assert(nodename == got_nodename)
	end
    local uuid = snowflake.uuid()
    local timestamp = snowflake.getTimestampByUUID(uuid)
    local nodeid = snowflake.getNodeIdByUUID(uuid)
    local sequence = snowflake.getSequenceByUUID(uuid)
    local uuid2 = snowflake.composeUUID(timestamp,nodeid,sequence)
    assert(uuid == uuid2)
    for base=2,62 do
        local s = snowflake.tostring(uuid,base)
        print(string.format("base=%s,uuid=%s,s=%s",base,uuid,s))
        uuid2 = snowflake.tointeger(s,base)
        assert(uuid == uuid2)
    end
end

test()
