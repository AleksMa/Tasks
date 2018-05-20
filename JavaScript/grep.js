'use strict';
var fs = require('fs');
var readline = require('readline');
var key = [], i = 2, M = 1, N = 1, K = 0;
for(;process.argv[i] && process.argv[i][0]=='-'; i++){
  key[i-2]=process.argv[i];
}
var keyI = key.indexOf('-i')+1, keyM = key.indexOf('-m')+1, keyN = key.indexOf('-n')+1, keyE = key.indexOf('-e')+1;
if(keyM)
  M = process.argv[i++];
var word = process.argv[i++], folder = process.env.PWD;
var filename = [];
var j = 0;
if(keyE){
  var length = word.split('/')[1].length
  word = new RegExp(word.split('/')[1], word.split('/')[2]);
}
while(process.argv[i]){
  filename[j++]=process.argv[i++];
  K++;
}
for(j = 0; j<K; j++){
  grep(filename[j]);
}

function grep(filename){
  var lines = fs.readFileSync(filename, 'utf-8').split('\n');
  lines.forEach((line) => {
    if((keyE?line.search(word)+1:line.indexOf(word)+1) && (!keyM || M)){
      var start = (keyE?line.search(word):line.indexOf(word));
      var end = start + (keyE?length:word.length);
      console.log("\x1b[35m%s\x1b[32m%s\x1b[34m%s\x1b[0m%s\x1b[31m%s\x1b[0m%s",
                  (K>1?filename+':':''), (keyN?N:''), (keyN?':':''), line.substring(0, start), line.substring(start, end) ,line.substring(end));
      M--;
    }
    else if(!keyE && keyI && line.toUpperCase().indexOf(word.toUpperCase())+1 && (!keyM || M)){
      var start = line.toUpperCase().indexOf(word.toUpperCase());
      var end = start + word.length;
      console.log("\x1b[35m%s\x1b[32m%s\x1b[34m%s\x1b[0m%s\x1b[31m%s\x1b[0m%s",
                  (K>1?filename+':':''), (keyN?N:''), (keyN?':':''), line.substring(0, start), line.substring(start, end) ,line.substring(end));
      M--;
    }
    N++;
  });
}
if (K == 0){
  var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
  });

  rl.on('line', function (line) {
    if((keyE?line.search(word)+1:line.indexOf(word)+1) && (!keyM || M)){
      var start = (keyE?line.search(word):line.indexOf(word))
      var end = start + (keyE?length:word.length);
      console.log("\x1b[35m%s\x1b[32m%s\x1b[34m%s\x1b[0m%s\x1b[31m%s\x1b[0m%s",
                  (K>1?filename+':':''), (keyN?N:''), (keyN?':':''), line.substring(0, start), line.substring(start, end) ,line.substring(end));
      M--;
    }
    else if(!keyE && keyI && line.toUpperCase().indexOf(word.toUpperCase())+1 && (!keyM || M)){
      var start = line.toUpperCase().indexOf(word.toUpperCase());
      var end = start + word.length;
      console.log("\x1b[35m%s\x1b[32m%s\x1b[34m%s\x1b[0m%s\x1b[31m%s\x1b[0m%s",
                  (K>1?filename+':':''), (keyN?N:''), (keyN?':':''), line.substring(0, start), line.substring(start, end) ,line.substring(end));
      M--;
    }
    N++;
  });
}
















/*
//STDIN
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

rl.on('line', function (cmd) {
  console.log('You just typed: '+cmd);
});
*/
//      -i, --ignore-case
// -m NUM, --max-count=NUM
// -n, --line-number
