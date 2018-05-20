'use strict';
var fs = require('fs');
var readline = require('readline');
var key = [], i = 2;
var answer = '', filename = [];
for(;process.argv[i] && process.argv[i][0]=='-'; i++){
  key[i-2]=process.argv[i];
}
var keyC = key.indexOf('-c')+1, keyM = key.indexOf('-m')+1, keyW = key.indexOf('-w')+1, keyL = key.indexOf('-l')+1, keyAll;
keyAll = (!keyC && !keyW && !keyM && !keyL? 1 : 0);
var C=0, M=0, W=0, L=0;
var c=0, m=0, w=0, l=0;
var j = 0;
while(process.argv[i]){
  filename[j++]=process.argv[i++];
}
if(j){
  filename.forEach((filename) => {
    wc(filename);
    console.log('%s%s%s%s%s', (keyL || keyAll?l+' ':''), (keyW || keyAll?w+' ':''), (keyM?--m+" ":'') , (keyC || keyAll?c+' ':''), filename);
    C+=c, M+=m, W+=w, L+=l;
    c=0, m=0, w=0, l=0;
  });
  if(j>1)
    console.log('%s%s%s%s%s', (keyL || keyAll?L+' ':''), (keyW || keyAll?W+' ':''), (keyM?--M+" ":'') , (keyC || keyAll?C+' ':''), 'итого');
}
else{
  filename = 'temp.txt';
  const stdin = process.openStdin();
  let answer = '';
  stdin.addListener('data', d => {
    answer += d.toString();
  });
  stdin.addListener('end', () => {
    fs.writeSync(fs.openSync('temp.txt', "w+"), answer);
    wc('temp.txt');
    console.log('%s%s%s%s', (keyL || keyAll?l+' ':''), (keyW || keyAll?w+' ':''), (keyM?--m+" ":'') , (keyC || keyAll?c+' ':''));
    fs.unlinkSync('temp.txt');
  });
}

function wc(filename){
  var data = fs.readFileSync(fs.openSync(filename, 'r+'), 'utf-8').split('\n');
  l = data.length-1;
  c = fs.statSync(filename).size;
  data.forEach((line) => {
    m+=line.length+1;
    line.split(' ').forEach((word) => {
      if(word)
        w++;
    });
  });
}
