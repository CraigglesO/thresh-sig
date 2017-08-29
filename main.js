const { Dealer, Encrypt, VerifyCipherText, DecryptShare, VerifyShare, CombineShares } = require('./build/Release/addon'); // native c/c++

// let x = Convert('416849841944504217544112404058997752252563094476');
// console.log("x", x);

// const dealer = {
//   secret: '226bd47664e8034071b8aae35cc3a84716d36ba4',
//   SKs: [
//    '6c71618d3edbd2c6c0c2f4f7a43ed9aee547114c',
//    '1fb62fb96d579450607a0bdc0db8bbecd7224612',
//    '45cad154cf980844435cef7eb62eae21b8d35283',
//    '75fe9dfa36c7de2d4a07bf5bb7b9f5d75a546c2e',
//    '555fb28565ffccba4333ba7d298fbf008f2bb5a7',
//    '16baf113124699bdebb73f7b20011bf92e6b3e88',
//    '7a9c0100e2911a2eee85cc7bac7b058612b10371',
//    '4f4d4eed6fc20a27e4afff32dd865ad51a26ee03',
//    '70d80cb844aa4ce7556394e2bec7e17d2682d4e8',
//    '49043181de08b4cfb5eb6a5b5900457e1d067bcc',
//   ],
//   VK: '3cf0329dd07dca3e078d1424117262fb74b42300cf709ad4b8838124f832339364ff266b691d75a8e460dcd404718ff96975fd282d954c08a8fd72544590efa99bda5a3e8fbb91618610c3f1db66a120fcbb0085e244760bbff8e455e9925ff16c26ed833758ad86c59adfd88a087822a49b3c7cce44c61d681dacbebd0d0f83',
//   VKs: [
//    '8a00582ae76f084e1574e8ea22377b7280b452828f2d07e055313e44ca0455f08e522c791292441c1dddd2b1627802ff94a41ccc570271e6f6d28e7f92434f3913c8d81369d17893425dfb9aa3d5e480ea03fbec116b7027b17c9bbd8cf0b68501d3b99e9d541f9a86c8634bab877c13e331bc0202e5ba2f95a3102de3e4ae7b',
//    '4b4a3ae6bd11070c67231c12310c1e675a3198515aff9b29f85eca07ecb6e5f753c294e56698cba3b3ac674201f16cb800627949d049441ab93e8bbc2a93452c1da726f96ac21b292ee606e3b948005b8255e6c823ba41a49d0670b481f8ef32b7a4b6093a417257b113ce16637a13cf3923dd603b4f39aa9a8bbca71db5831f',
//    '3ed4b7ef682a1a1684c8560812dbf7c0dd423769fbfa7e05a5a1ea28c1e03eab5328e43c0a8aae0c06fb6e7183150a76a81b691152f77f226756c7f161b0496e0a6fd3d0ca659294b0e54585fcf1eb4c57538c0156ac0d37b422b830091b16ce6065e4f2d20fa3f810ce67c9777670f2bc95f86e3bc8a04d2c9f8dd71907b69b',
//    '3bb92565e7c3685cf766509f938aba45f5fbd34a3ac908b352750d83b173ea5203adb7c7913bbbb4b05e6f866ab975258fdae1d64e7a4014926bd80def74af1994dc799b684d3d35c5a48f5c52196debe672999dbee107491353f9580fa982f9766ae7c7eb3723cfe49636af0d264468e422e4964aecfbe6afbfb4e233f18d6a',
//    '5533dcfc5ef10c1f5e0eb1f68c177a77db0d484fd54aab01c6433cab430cee769eb52e7b12ec9d8fd4a58ea8fcb30317fa88e67c1c0b4343560c9953313b652893b0bbf9d7911bc5c10be0447ca95bff7dbe0bc8cb4b265409ccf595f63c3a8e1361445b527ef6bbf741965bca671a6255e7fe41f20bb6e9bc5c42d9bafe036c',
//    '0a32369bc01ec5cc10fcbd8995ed4f1f9164f02c2dd05615600e57290a2fd4d8fec2b6062e1c60e444d59bd3489109184a14fbf50ce912945418a66e4630f6ae74900524cab8f380c0ebac6c68e22db7bc81606a6135dbc9b86447e089efe1a259a292a0b9cffb4327e0cad058c56177ca6bb2d8182b90a2f61f5ec30672713f',
//    '9e1b2d1250b75151e8a345f982381328ebc6d4226004333eaa77c033a7c0b42b2be3575da891b4ff46fa873cee2cdd43b1add959c6ffea66b46bbf494480bee790ba9cac374e0040607a789020395492d37b9c48b35fe898e2083b28ae9fd4363c7d41ddb2a35833dd396ed26f12852e04daef785531741b569c9b7eb0a6221b',
//    '05cc163097e038dd26234a071837a5cd6574650397cec55d96e6fc7cbd9b7c9dab85e57eb74d1e68ed726e06af944cd52ce788778a60ad150254de17d47de6f0a73758eb49564c493b5cab963e5b18f410a2f996c9962a7998f51993bc646772662b78b81011937668e81e2c01dc091aed63e1eb25d019a75c71b2614aff84bc',
//    '4311e5ca65ab369e5ca2a1f355c27efa1c6cf6d265b6a738cccfce19a4ab8848acc477232a89578f7f87f9480630aef90ce91e2ce7b860ff51c24f8ee76618505712a4c34c438d3a525835d4da67d7f8116d9707f71a1388c5b7f2f6b19461388b1f154f90765a9fc255ce0f3607e60beb3d4612b66ba1943b09242331431fea',
//    '165a391f1d43fdd098f7ecfb5613bec3d42290db1e35a2592e12401cb7623d8fa39453ac318d6fb2bd0ee748ad3fad3108bce537ea651d7e5cf9a4e966e907a189bab53c51e395ce244b8b553499a63c9cc59e1fd1bdb4dee533d90048c165659b7e7b0a982a1d9474ed8d0c30762335cb7127a873b45ade490eefc74afb0c14'
//   ]
// };
const str = "TEST", players = 10, k = 5;
const m = require("crypto").createHash("sha256").update(str).digest().toString("hex");
console.log("m", m);

const dealer = Dealer(players, k);
console.log("dealer", dealer);
const C = Encrypt("TEST", dealer.VK);
console.log("C", C);
const verifyCipherText = VerifyCipherText(C);
console.log("Verify", verifyCipherText);
const shares = dealer.SKs.map((SK) => DecryptShare(C, SK));
console.log("decrypted shares", shares);
const verifiedShares = shares.map((share, i) => VerifyShare(C, share, dealer.VKs[i]));
console.log("verified Shares", verifiedShares);


// As long as you have at least 5 decrypted shares, you can obtain the original message:
const arr = [shares[0], null, null, shares[3], shares[4], null, null, shares[7], null, shares[9]];
console.log("SHARES ARRAY", arr);
const _m = CombineShares(C, arr);
console.log("_m", _m);
// console.log("m === _m", m === _m);


// [x] Dealer
// [x] Encrypt
// [x] Verify Encrypt
// [x] Decrypt Share
// [x] Verify Share
// [x] Combine Shares
