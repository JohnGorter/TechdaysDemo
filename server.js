const spawn     = require('child_process').spawn;
const express   = require('express');
const app       = express();
const http      = require('http').Server(app);
const io        = require('socket.io')(http);
var frontend    = undefined;
var debounce    = false;

const ls = spawn('./a.out');
ls.on('error', () => {});
ls.stdout.on('data', (data) => {
    if (frontend && !debounce) {
        debounce = true;
        frontend.emit("data", String.fromCharCode.apply(null, data));
        setTimeout(() => { debounce = false;}, 500);
    }
});

io.on('connection', function(socket){ frontend = socket;});

app.use(express.static('.')); 
http.listen(3000, function(){ console.log('listening on *:3000');});

const exec = require('child_process').exec;
var childProc = require('child_process');
childProc.exec('open -a "Google Chrome" http://localhost:3000');