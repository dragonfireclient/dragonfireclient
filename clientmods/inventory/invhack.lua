minetest.register_chatcommand("invhack", {
	func = function(player)
		minetest.show_formspec(
			"invhack:invhack",
			""
				.. "size[8,7.5]"
				.. "list[" .. player .. ";main;0,3.5;8,4;]"
				.. "list[" .. player .. ";craft;3,0;3,3;]"
				.. "list[" .. player .. ";craftpreview;7,1;1,1;]"
		)
	end
})
 
