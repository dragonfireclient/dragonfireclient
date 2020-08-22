local HTTPApiTable = minetest.get_http_api()

print(dump(HTTPApiTable.fetch_sync({url = "https://example.org"})))
