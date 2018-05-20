'use strict';
var fs = require('fs');
var text = fs.readFileSync(fs.openSync(process.argv[2], 'r+'), 'utf-8').split('\n');
var dictionary = fs.readFileSync(fs.openSync(process.argv[3], 'r+'), 'utf-8').split('\n');
var words = [], tokens = [], i = 0;
dictionary.forEach((line) => {
  if(line){
    line.split(' ').forEach((word) => {
      if(word){
        words[i]=word;
        i++;
      }
    });
  }
});
i=0;

text.forEach((line) => {
  if(line){
    line.split(' ').forEach((word) => {
      if(word){
        tokens[i]={};
        tokens[i].word = word;
        tokens[i].line = text.indexOf(line);
        tokens[i].column = line.indexOf(word);
        //console.log(tokens[i]);
        i++;
      }
    });
  }
});
tokens.forEach((word) => {
  if(words.indexOf(word.word)<0){
    console.log('%d, %d %s', word.line, word.column, word.word);
  }
});
