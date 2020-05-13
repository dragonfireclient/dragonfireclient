const fs = require("fs");
const util = require("util");
const http = require("http");

function baseAnalysis(){
	let text = fs.readFileSync("spoof.txt", "utf8");
	let messages = text.split("\n");
	let analyzed = [];
	
	messages.forEach(msg => {
		if(msg.startsWith("<")){
			let player = msg.replace("<", "").split(">")[0];
			let message = msg.replace("<" + player + "> ", "");
			analyzed.push({
				type: "chat",
				player: player,
				message: message,
			});
		}
		else if(msg.startsWith("PM")){
			let player = msg.replace("PM from ", "").split(":")[0];
			let message = msg.replace("PM from " + player + ": ", "");
			analyzed.push({
				type: "PM",
				player: player,
				message: message,
			});
		}
		else if(msg.startsWith("***")){
			let player = msg.replace("*** ", "").split(" ")[0];
			let rawaction = msg.replace("*** " + player + " ", "");
			let type = undefined;
			let timeout = undefined;
			if(rawaction.split(".")[0] == "joined the game")
				type = "join";
			else if(rawaction.split(".")[0] == "left the game"){
				type = "leave";
				timeout = (rawaction.split(".")[1] == " (timed out)");
			}
			analyzed.push({
				type: type,
				player: player,
				timeout: timeout,
			});
		}
		else{
			analyzed.push({
				type: "unknown",
				content: msg 
			})
		}
	});
	
	return analyzed;
}

const server = http.createServer((request, response) => {
	response.statusCode = 200;
	response.setHeader('Content-Type', 'application/json');
	response.end(JSON.stringify(baseAnalysis()));
});

server.listen(3000);
