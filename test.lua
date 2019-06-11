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
end

test()
