#include <iostream>
#include <nan.h>
#include <sstream>
#include <iomanip>
#include "openssl/objects.h"
#include <openssl/sha.h>
#include "./pbcwrapper/PBC.h"

using namespace std;
using namespace v8;

#include <fstream>

const char *paramFileName = "pairing.param";
FILE *sysParamFile = fopen(paramFileName, "r");
Pairing e(sysParamFile);

Zr polynomialEvaluation(long int x, long int size, Zr a[]) {
  Zr y(e, (long int) 0);
  Zr xx(e, (long int) 1);
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
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  OPENSSL_cleanse(&sha256,sizeof(sha256));
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

NAN_METHOD(Convert) {
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // setup value
  String::Utf8Value input(info[0]->ToString());
  // Zr c(e, (const unsigned char *)*input, input.length(), 10);
  G1 c(e, (const unsigned char *)*input, input.length(), false, 10);

  info.GetReturnValue().Set(String::NewFromUtf8(isolate, c.toHexString(false).c_str()));
}

NAN_METHOD(CombineShares) {

}

NAN_METHOD(VerifyShare) {
  if (!info[0]->IsObject() && !info[1]->IsString() && !info[2]->IsString()) {
    Nan::ThrowTypeError("first argument must be an object, second must be a string!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // grab the parameters:
  Local<Object> c(info[0]->ToObject());
  String::Utf8Value paramU(c->Get(String::NewFromUtf8(isolate,"U")));
  String::Utf8Value paramUi(info[1]->ToString());
  String::Utf8Value paramVKsi(info[2]->ToString());

  // G2
  G2 g2(e, false);
  // U
  string sU = stringToHex(*paramU);
  G1 U(e, (const unsigned char *)sU.c_str(), sU.length());
  // Ui
  string sUi = stringToHex(*paramUi);
  G1 Ui(e, (const unsigned char *)sUi.c_str(), sUi.length());
  // VKsi
  string sVKsi = stringToHex(*paramUi);
  G2 VKsi(e, (const unsigned char *)sVKsi.c_str(), sVKsi.length());

  // if (e(Ui, g2) == e(U, VKsi))
  //   info.GetReturnValue().Set(Nan::True());
  // else
  //   info.GetReturnValue().Set(Nan::False());
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "e1"),
    String::NewFromUtf8(isolate, e(Ui, g2).toHexString().c_str()));
  obj->Set(String::NewFromUtf8(isolate, "e2"),
    String::NewFromUtf8(isolate, e(U, VKsi).toHexString().c_str()));
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(DecryptShare) {
  // Check correctness of ciphertext
  if (!info[0]->IsObject() && !info[1]->IsString()) {
    Nan::ThrowTypeError("first argument must be an object, second must be a string!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // grab the parameters:
  Local<Object> c(info[0]->ToObject());
  String::Utf8Value paramU(c->Get(String::NewFromUtf8(isolate,"U")));
  String::Utf8Value paramSK(info[1]->ToString());

  // setup U
  string sU = stringToHex(*paramU);
  G1 U(e, (const unsigned char *)sU.c_str(), sU.length());
  // setup SK
  string sSK = stringToHex(*paramSK);
  Zr SK(e, (const unsigned char *)sSK.c_str(), sSK.length());
  G1 Ui = U^SK;

  info.GetReturnValue().Set(String::NewFromUtf8(isolate, Ui.toHexString(false).c_str()));
}

NAN_METHOD(VerifyCipherText) {
  // Check correctness of ciphertext
  if (!info[0]->IsObject()) {
    Nan::ThrowTypeError("arguments must be strings!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // grab the parameters:
  Local<Object> c(info[0]->ToObject());
  String::Utf8Value paramU(c->Get(String::NewFromUtf8(isolate,"U")));
  String::Utf8Value paramV(c->Get(String::NewFromUtf8(isolate,"V")));
  String::Utf8Value paramW(c->Get(String::NewFromUtf8(isolate,"W")));

  // setup U
  string sU = stringToHex(*paramU);
  G1 U(e, (const unsigned char *)sU.c_str(), sU.length());
  // setup V
  string UV = U.toHexString(true) + (string)*paramV;
  string sH = stringToHex(UV);
  G2 H(e, sH, sH.length());
  // setup W
  // string sW = stringToHex(*paramW);
  string sW = stringToHex("6d3b620751309b776a8f54200ca611af7c73bb523a55407dfbd096b5935ce6d825cb4a7ae0ddb2e8e50c793649dc1c1ade5b5c2da6957b1b89708a773f28c1535642bdef7a69c0195c93527e7ded83b7b75d5d77ea60d2478eb9bbe2f345fcda024382b3eb84618a103e13db641730a48c7763b7e2f3dfc427e33d9b9e0e47bc");
  G2 W(e, (const unsigned char *)sW.c_str(), sW.length());
  // setup random G along group 1
  G1 g1(e, false);

  // if (e(g1, W) == e(U, H))
  //   info.GetReturnValue().Set(Nan::True());
  // else
  //   info.GetReturnValue().Set(Nan::False());
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "e1"),
    String::NewFromUtf8(isolate, e(g1, W).toHexString().c_str()));
  obj->Set(String::NewFromUtf8(isolate, "e2"),
    String::NewFromUtf8(isolate, e(U, H).toHexString().c_str()));
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(Encrypt) {
  if (!info[0]->IsString() && !info[1]->IsString()) {
    Nan::ThrowTypeError("arguments must be strings!");
    return;
  }
  // Prepare isolate
  Isolate* isolate = info.GetIsolate();
  // get the message and primary verification key
  String::Utf8Value paramM(info[0]->ToString());
  String::Utf8Value paramVK(info[1]->ToString());
  string m = sha256((string) *paramM);

  // setup random values
  // Zr r(e, true);
  Zr r(e, (const unsigned char *)"668446078456621862688939921260498432629873090649", 48, 10);
  // G1 g1(e, false);
  G1 g1(e, (const unsigned char *)"[4264083391895955901265257040028479149400169025615345260303986214726423231173928285256791041998919055277112394516001733341992693480052725918957267301183325, 2116426609166886503385333553365957364401816544109920990955286798122869276384003469957105697651246200288946800075692216092350705727159751274607530017817646]", 312, false, 10);
  // U
  G1 U(e);
  U = G1(g1^r);
  // V
  string sVK = stringToHex(*paramVK);
  G1 VK(e, (const unsigned char *)sVK.c_str(), sVK.length());
  VK ^= r;
  string hashG = sha256(stringToHex(VK.toHexString(true)));
  string V = str_xor(m, hashG);
  // Join U (compressed) and V to create W
  string sU = U.toHexString(true);
  // string sW = stringToHex(sU + V);
  string sW = stringToHex("6d3b620751309b776a8f54200ca611af7c73bb523a55407dfbd096b5935ce6d825cb4a7ae0ddb2e8e50c793649dc1c1ade5b5c2da6957b1b89708a773f28c1535642bdef7a69c0195c93527e7ded83b7b75d5d77ea60d2478eb9bbe2f345fcda024382b3eb84618a103e13db641730a48c7763b7e2f3dfc427e33d9b9e0e47bc");
  G2 W(e, (const unsigned char *)sW.c_str(), sW.length());
  // W must be raised to r:
  // W ^= r;

  // Prepare an object and send the ciphertext
  Local<Object> obj = Object::New(isolate);
  obj->Set(String::NewFromUtf8(isolate, "U"),
    String::NewFromUtf8(isolate, U.toHexString(false).c_str()));
  obj->Set(String::NewFromUtf8(isolate, "V"),
    String::NewFromUtf8(isolate, V.c_str()));
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
  // setup random number along group G1
  G1 g1(e, false);
  // Create verifications keys:
  G1 VK(e);
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
  NAN_EXPORT(target, DecryptShare);
  NAN_EXPORT(target, VerifyShare);
  NAN_EXPORT(target, Convert);
}

NODE_MODULE(addon, Initialize);
