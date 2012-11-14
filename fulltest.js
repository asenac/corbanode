var corba = require('./build/Release/corbanode');

// Directory that contains the corbasim plug-ins
// for Example.idl
corba.loadDirectory('./example/build');

var obj = corba.createObject("MyModule::MyInterface", "IOR:...");

// asynchronous call
obj.call("myOperation", {a: 10}, function(err, res){
    if (err)
        throw err;

    console.log(res.b);
});

