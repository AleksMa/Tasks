module.exports.memo = function(func) {
  var memoized = {};
  return function () {
    var key = [];
    for (var i = 0; i < arguments.length; i++) {
      key[i] = arguments[i];
    }
    return (memoized[key]?memoized[key]:(memoized[key] = func.apply(func, arguments)));
   }
}
