var express = require('express');
var app = express();
var server = require('http').createServer(app);
var io = require('socket.io')(server);
var path = require('path');

var turret = require('../addon');

app.use(express.static(__dirname + '/public'));
app.use('/socket.io.js', function(req, res) {
  res.sendFile(path.join(__dirname, '../node_modules/socket.io-client/socket.io.js'));
});

io.on('connection', function(socket){
  socket.emit('data', { base64: turret.getFrame() });
});

server.listen(3000);

setInterval(function() {
  io.emit('data', { base64: turret.getFrame() });
});
