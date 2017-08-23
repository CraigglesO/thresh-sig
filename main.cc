#include <iostream>
#include <nan.h>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/bn.h>
#include "./pbcwrapper/PBC.h"

using namespace std;
using namespace v8;

#include <fstream>

const char *paramFileName = "pairing.param";
FILE *sysParamFile = fopen(paramFileName, "r");
Pairing e(sysParamFile);
Zr ZERO(e, (long int) 0);
Zr ONE(e, (long int) 1);
G1 g1(e, false);

Zr polynomialEvaluation(long int x, long int size, Zr a[]) {
  Zr y = ZERO;
  Zr xx = ONE;
  for (int coeff = 0; coeff < size; coeff++) {
    Zr x_val(e, x);
    y += a[coeff] * xx;
    xx *= x_val;
  }
  return y;
}

string sha256(const string str) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, str.c_str(), str.size());
  SHA256_Final(hash, &sha256);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  return ss.str();
}

static inline unsigned int value(char c) {
  if (c >= '0' && c <= '9') { return c - '0';      }
  if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
  if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
  return -1;
}

string str_xor(string const & s1, string const & s2) {
  assert(s1.length() == s2.length());
  static char const alphabet[] = "0123456789abcdef";
  string result;
  result.reserve(s1.length());
  for (size_t i = 0; i != s1.length(); ++i) {
    unsigned int v = value(s1[i]) ^ value(s2[i]);
    assert(v < sizeof alphabet);
    result.push_back(alphabet[v]);
  }
  return result;
}

char nibble(char c) {
  if (c >= '0' && c <= '9')
   return c - '0';
  return 10 + (c - 'a');
}

string stringToHex(string s) {
  string o;
  for (size_t i=0 ; i<s.size() ; i+=2){
    char c = (nibble(s[i]) << 4) | nibble(s[i+1]);
    o.push_back(c);
  }
  return o;
}

NAN_METHOD(CombineShares) {

}

NAN_METHOD(VerifyShare) {

}

NAN_METHOD(DecryptShare) {

}

NAN_METHOD(VerifyCipherText) {
  // Check correctness of ciphertext
  if (!info[0]->IsString() && !info[1]->IsString() && !info[1]->IsString()) {
    Nan::ThrowTypeError("arguments must be strings!");
    return;
  }
  // grab the parameters:
  String::Utf8Value param0(info[0]->ToString());
  String::Utf8Value param1(info[1]->ToString());
  String::Utf8Value param2(info[2]->ToString());
  // setup U
  G1 U(e, (const unsigned char *)*param0, param0.length(), false, 10);
  // setup V and H
  BIGNUM *bU = BN_new();
  BIGNUM *bV = BN_new();
  BIGNUM *bH = BN_new();
  BN_hex2bn(&bU, U.toHexString(false).c_str());
  BN_hex2bn(&bV, *param1);
  BN_add(bH, bU, bV);
  string sH = stringToHex(BN_bn2hex(bH));
  G2 H(e, (const unsigned char *)sH.c_str(), sH.length());
  // setup W
  G2 W(e, (const unsigned char *)*param2, param2.length());

  if (e(g1, W) == e(U, H))
    info.GetReturnValue().Set(Nan::True());
  else
    info.GetReturnValue().Set(Nan::False());
}

NAN_METHOD(Encrypt) {
  if (!info[0]->IsString() && !info[1]->IsString()) {
    Nan::ThrowTypeError("arguments must be strings!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // get the message and primary verification key
  String::Utf8Value param0(info[0]->ToString());
  String::Utf8Value param1(info[1]->ToString());
  string m = sha256((string) *param0);
  // setup random value
  Zr r(e, true);
  // U
  G1 U(e);
  U = G1(g1^r);
  // V (param1 is VK)
  string hashG = sha256(*param1);
  string Vxor = str_xor(m, hashG);
  // Create big Numbers for U, V, and W for special computation
  BIGNUM *bU = BN_new();
  BIGNUM *bV = BN_new();
  BIGNUM *bW = BN_new();
  BN_hex2bn(&bU, U.toHexString(false).c_str());
  BN_hex2bn(&bV, Vxor.c_str());
  BN_add(bW, bU, bV);   // W = U + V
  string sV = BN_bn2hex(bV);
  string sW = stringToHex(BN_bn2hex(bW));
  // Finally get the proper W groups:
  G2 W(e, (const unsigned char *)sW.c_str(), sW.length());
  // W must be raised to r:
  W ^= r;
  // Prepare an object and send the ciphertext
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "U"),
    String::NewFromUtf8(isolate, U.toString(false).c_str()));
  obj->Set(String::NewFromUtf8(isolate, "V"),
    String::NewFromUtf8(isolate, sV.c_str()));
  obj->Set(String::NewFromUtf8(isolate, "W"),
    String::NewFromUtf8(isolate, W.toHexString(false).c_str()));
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(Dealer) {
  if (!info[0]->IsNumber() && !info[1]->IsNumber()) {
    Nan::ThrowTypeError("arguments must be numbers!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // grab player count and # of shards needed to successfully decrypt (k)
  int players = (int) info[0]->NumberValue();
  int k = (int) info[1]->NumberValue();

  FILE * pFile;
  pFile = fopen ("ZrLog.txt" , "w");
  // prepare all polynomial secrets. Master ksecret is secrets[0]
  Zr secrets[k];
  for (int i = 0; i < k; i++) {
    Zr r(e,true);
    r.dump(pFile, "random number set", 10);
    secrets[i] = r;
  }
  // get all shared secrets of master key (secrets[0])
  Zr SKs[players];
  Local<Array> lSKs = Array::New(isolate);
  for (long int i = 0; i < players; i++) {
    SKs[i] = polynomialEvaluation(i + 1, k, secrets);
    lSKs->Set(i, String::NewFromUtf8(isolate, SKs[i].toHexString().c_str()));
    SKs[i].dump(pFile, "SKs set", 10);
  }
  // Create verifications keys:
  G1 VK(e);
  // G1 VK(e, (const unsigned char *)"[4264083391895955901265257040028479149400169025615345260303986214726423231173928285256791041998919055277112394516001733341992693480052725918957267301183325, 2116426609166886503385333553365957364401816544109920990955286798122869276384003469957105697651246200288946800075692216092350705727159751274607530017817646]", 312, false, 10);
  // Zr Secret(e,(const unsigned char *)"145811360758041481562956711359142699218402722188", 48, 10);
  VK = g1^secrets[0];
  G1 VKs[players];
  Local<Array> lVKs = Array::New(isolate);
  for (int i = 0; i < players; i++) {
    VKs[i] = g1^SKs[i];
    lVKs->Set(i, String::NewFromUtf8(isolate, VKs[i].toHexString(false).c_str()));
    VKs[i].dump(pFile, "VKs", 10);
  }
  VK.dump(pFile, "VK", 10);

  // Let's create the v8 object and pass it over to node
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "G1"),
    String::NewFromUtf8(isolate, g1.toHexString(false).c_str()));
  obj->Set(String::NewFromUtf8(isolate, "secret"),
    String::NewFromUtf8(isolate, secrets[0].toHexString().c_str()));
  obj->Set(String::NewFromUtf8(isolate, "SKs"),
    lSKs);
  obj->Set(String::NewFromUtf8(isolate, "VK"),
    String::NewFromUtf8(isolate, VK.toHexString(false).c_str()));
  obj->Set(String::NewFromUtf8(isolate, "VKs"),
    lVKs);

  info.GetReturnValue().Set(obj);
}

NAN_MODULE_INIT(Initialize) {
  NAN_EXPORT(target, Dealer);
  NAN_EXPORT(target, Encrypt);
  NAN_EXPORT(target, VerifyCipherText);
}

NODE_MODULE(addon, Initialize);
