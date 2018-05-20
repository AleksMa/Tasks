function fib(n){
  if (n == 0 || n == 1)
    return n;
  else
    return fib(n-1) + fib(n-2);
};
function ackermann(m, n){
  if(m == 0){
    return n+1;
  }
  else if(m > 0 && n == 0){
    return ackermann(m-1, 1);
  }
  else
    return ackermann(m-1, ackermann(m, n-1));
}
console.log(fib(40));
console.log(ackermann(3, 10));
