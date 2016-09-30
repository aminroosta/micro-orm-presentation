var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database(':memory:');

db.serialize(function() {
    db.run(`create table if not exists user (
                   id integer primary key autoincrement not null,
                   age int,
                   name text,
                   weight real
                );`);
    var stmt = db.prepare(`insert into user (age,name,weight) values (?,?,?);`);

    stmt.run(21,  'joey',     80);
    stmt.run(22,  'chandler', 65);
    stmt.run(23,  'monica',   50);
    stmt.run(24,  'ross',     75);
    stmt.run(25,  'phoebe',   45);
    stmt.run(26,  'rachel',   50);

    stmt.finalize();

    db.each('select * from user', function(err, row) {
        console.log(row.age, row.name, row.weight);
    });
});

db.close();
