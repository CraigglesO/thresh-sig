const { Dealer, Encrypt, VerifyCipherText } = require('./build/Release/addon'); // native c++
// const isPrime = require('./isPrime'); // js
//
// const number = 654188429; // thirty-fifth million first prime number (see https://primes.utm.edu/lists/small/millions/)
// const NATIVE = 'native';
// const JS = 'js';
//
// console.time(NATIVE);
// console.log(`${NATIVE}: checking whether ${number} is prime... ${PCB()}`);
// console.timeEnd(NATIVE);
// console.log('');
// console.time(JS);
// console.log(`${JS}: checking whether ${number} is prime... ${isPrime(number)}`);
// console.timeEnd(JS);
let dealer = Dealer(10, 5);
console.log("dealer", dealer);
let C = Encrypt("message", dealer.VK);
console.log("C", C);
let verifyCipherText = VerifyCipherText(C.U, C.V, C.W);
console.log("Verify", verifyCipherText);
