let logo = "\n\t    _/_/_/_/        _/_/_/  _/    _/  _/      _/    _/_/_/        _/      _/_/_/    _/_/_/      _/_/    _/      _/    _/_/_/  _/    _/   \n"
            + "\t   _/            _/        _/    _/    _/  _/    _/            _/_/      _/    _/  _/    _/  _/    _/  _/_/    _/  _/        _/    _/    \n"
            + "\t  _/_/_/        _/  _/_/  _/    _/      _/        _/_/          _/      _/_/_/    _/_/_/    _/_/_/_/  _/  _/  _/  _/        _/_/_/_/     \n"
            + "\t       _/      _/    _/  _/    _/      _/            _/        _/      _/    _/  _/    _/  _/    _/  _/    _/_/  _/        _/    _/      \n"
            + "\t_/_/_/          _/_/_/    _/_/        _/      _/_/_/          _/      _/_/_/    _/    _/  _/    _/  _/      _/    _/_/_/  _/    _/ \n";

console.log("\033[2J"); // Clear screen;
console.log("\033[0;0H"); // Move cursor to top left
console.log("\033[36m"); // Change color to blue
console.log(logo);
console.log("\033[31m"); // Change color to red
console.log("\033[37m"); // Change color to white

// ===========================
//    Get the dependencies
// ===========================

// start express application
const app = require("express")();

const bodyParser = require("body-parser");

let server = require('http').Server(app);
let io = require('socket.io')(server);

app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({extended: false}));

// ===========================
//       Socket for app
// ===========================

io.on('connection', function (socket) {

    console.log("App connected");

    socket.on('disconnect', function () {
        io.emit('App disconnected');
        });

    socket.on('message', function () {
        io.emit('Echo response');
        });
});

// ===========================
//          Detection
// ===========================

app.post('/detection', (req, res) => {
    // Test -> curl -X POST -d '{"Test":123}' -H "Content-Type:application/json" http://127.0.0.1:8080/detection

    console.log("Object detected");

    /* Data received in format
    JSON data:
    {
        "frame_id":696, 
        "objects": [ 
            {"class_id":2, "name":"lion", "relative_coordinates":{"center_x":0.493874, "center_y":0.655773, "width":1.137844, "height":0.575388}, "confidence":0.269735}
        ] 
    }

    {"frame_id":696,"objects": [{"class_id":2, "name":"lion", "relative_coordinates":{"center_x":0.493874, "center_y":0.655773, "width":1.137844, "height":0.575388}, "confidence":0.269735}]}
    */

    console.log("Content type -> " + req.get('Content-Type'));
    // console.log(req.body);
    var detection = req.body;

    console.log(detection);

    io.emit('detection', { data: detection });

    res.status(200).send();
});

// Endpoint to test socket connection since it cannot really be sent
app.get('/test', (req, res) => {
    //res.write("Connection established");
    res.status(200).json({
        status : "connected"
    });
});

// ===========================
//           Ports
// ===========================

let port = (process.env.PORT | 8080);

app.listen(port, function () {
    console.log("Server is running on port -> " + port + "\n");
});

let socketPort = 6969;
server.listen(socketPort, function () {
    console.log("App socket listening on port -> " + socketPort + "\n");
});