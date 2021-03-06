var express = require('express');
var app = express();
var port = 8000;

var moment = require('moment');
require('moment-timezone');
moment.tz.setDefault("Asia/Seoul");

var mysql = require('mysql');
var connection = mysql.createConnection({
    host: 'localhost',
    user: 'me',
    password: '1234',
    database: 'skin'
});
connection.connect();

function insertTemp(id, time, leftTemp, rightTemp) {
    obj = {};
    obj.id = id;
    obj.time = time;
    obj.leftTemp = leftTemp;
    obj.rightTemp = rightTemp;

    var query = connection.query('insert into skinTemp set ?', obj, function(err, rows, cols) {
        if (err)
            throw err;
        console.log("database insertion ok = %j", obj);
    });
}

app.get('/input', function (req, res) {
    var time = moment().format('YYYY-MM-DD HH:mm:ss');
    var r = req.query;

    console.log("GET %j", r);
    insertTemp(r.id, time, r.leftTemp, r.rightTemp);

    res.set('Content-Type', 'application/json');
    res.json({"device_id": r.id, "status": "ok", "time": time});
});

app.get('/dump', function (req, res) {
    var r = req.query;
    var qstr = 'select * from skinTemp ';

    if (Object.keys(r.id).length != 0)
        qstr += 'where id=' + r.id;

    connection.query(qstr, function(err, rows, cols) {
        if (err) {
            throw err;
            res.send('query error: ' + qstr);
            return;
        }

        console.log('Got ' + rows.length + ' records');
       
	    var jsonList = new Array();
	    for (var i = 0; i < rows.length; i++) {
	    	var data = new Object();
		    data.id = rows[i]['id'];
            data.time = rows[i]['time'];
            data.leftTemp = rows[i]['leftTemp'];
            data.rightTemp = rows[i]['rightTemp'];
		    jsonList.push(data);
        }
        
	    res.set('Content-Type', 'application/json');
	    res.json(jsonList);
    });
});

var server = app.listen(port, function() {
    var host = server.address().address;
    var port = server.address().port;
    console.log('listening at http://%s:%s', host, port);
});
