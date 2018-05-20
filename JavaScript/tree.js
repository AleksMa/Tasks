'use strict';
var fs = require('fs');
var path = require('path');
var key = [], i = 2;
for(;process.argv[i] && process.argv[i][0]=='-'; i++){
  key[i-2]=process.argv[i];
}
if(process.argv[i-1]=='-o'){
  var output = process.argv[i++];
  var answer = '';
}
var folder = (process.argv[i]?process.argv[i]:process.env.PWD);
var keyD = key.indexOf('-d')+1, keyO = key.indexOf('-o')+1;
if(keyO)
  answer+='.\n';
else
  console.log('\x1b[0m%s', '.');
var directory = 0, files = 0;
function tree(path, shift){
  try{
    var dirarr = fs.readdirSync(path);
  }
  catch(err){
    console.error(err);
    return;
  }
  for(var i = 0; i < dirarr.length; i++){
    var file = dirarr[i];
    try{
      var stat = fs.statSync(path+'/'+file);
    }
    catch(err){
      console.error(err);
      return;
    }
    //var stat = fs.statSync(path+'/'+file);
    if(i<dirarr.length-1){
      if(stat.isFile() && !keyD){
        if(keyO){
          answer+=shift+'├── '+file+'\n';
        }
        else {
          console.log('%s%s%s', shift, '├── ', file);
        }
        files++;
      }
      else if(stat.isDirectory()){
        if(keyO){
          answer+=shift+'├── '+file+'\n';
        }
        else {
          console.log('%s%s\x1b[36m%s\x1b[0m', shift, '├── ', file);
        }
        directory++;
        tree(path+'/'+file, shift+'│   ');
      }
    }
    else{
      if(stat.isFile() && !keyD){
        if(keyO){
          answer+=shift+'└── '+file+'\n';
        }
        else {
          console.log('%s%s%s', shift, '└── ', file);
        }
        files++;
      }
      else if(stat.isDirectory()){
        if(keyO){
          answer+=shift+'└── '+file+'\n';
        }
        else {
          console.log('%s%s\x1b[36m%s\x1b[0m', shift, '└── ', file);
        }
        directory++;
        tree(path+'/'+file, shift+'    ');
      }
    }
  }
}
tree(folder, '');
var dir = (directory==1?' directory ':' directories ');
var fl = (files==1?' file ':' files ');
if(keyO){
  answer+=directory+dir+(!keyD?files+fl:'');
  fs.writeSync(fs.openSync(output, "w+"), answer);
}
else{
  console.log(directory+dir+(!keyD?files+fl:''));
}
