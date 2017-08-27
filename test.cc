#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include "openssl/objects.h"
#include "openssl/sha.h"

using namespace std;

// ------------------------------------------------------------------
/*!
    Convert a block of data to a hex string
*/
void toHex(
    void *const data,                   //!< Data to convert
    const size_t dataLength,            //!< Length of the data to convert
    std::string &dest                   //!< Destination string
    )
{
    unsigned char     *byteData = reinterpret_cast<unsigned char*>(data);
    std::stringstream hexStringStream;

    hexStringStream << std::hex << std::setfill('0');
    for(size_t index = 0; index < dataLength; ++index)
        hexStringStream << std::setw(2) << static_cast<int>(byteData[index]);
    dest = hexStringStream.str();
}

char nibble(char c) {
  if (c >= '0' && c <= '9')
   return c - '0';
  return 10 + (c - 'a');
}

string hexTohex(string s) {
  string o;
  for (size_t i=0 ; i<s.size() ; i+=2){
    char c = (nibble(s[i]) << 4) | nibble(s[i+1]);
    o.push_back(c);
  }
  return o;
}

int hash_to_bytes(uint8_t *input_buf, int input_len, uint8_t *output_buf, int hash_len, uint8_t hash_prefix)
{
	SHA256_CTX sha2;
	int i, new_input_len = input_len + 2; // extra byte for prefix
	uint8_t first_block = 0;
	uint8_t new_input[new_input_len+1];

	memset(new_input, 0, new_input_len+1);
	new_input[0] = first_block; // block number (always 0 by default)
	new_input[1] = hash_prefix; // set hash prefix
	memcpy((uint8_t *)(new_input+2), input_buf, input_len); // copy input bytes

	// prepare output buf
	memset(output_buf, 0, hash_len);

	if (hash_len <= SHA256_DIGEST_LENGTH) {
		SHA256_Init(&sha2);
		SHA256_Update(&sha2, new_input, new_input_len);
		uint8_t md[SHA256_DIGEST_LENGTH+1];
		SHA256_Final(md, &sha2);
		memcpy(output_buf, md, hash_len);
	}
	else {
		// apply variable-size hash technique to get desired size
		// determine block count.
		int blocks = (int) ceil(((double) hash_len) / SHA256_DIGEST_LENGTH);
		uint8_t md[SHA256_DIGEST_LENGTH+1];
		uint8_t md2[(blocks * SHA256_DIGEST_LENGTH)+1];
		uint8_t *target_buf = md2;
		for(i = 0; i < blocks; i++) {
			/* compute digest = SHA-2( i || prefix || input_buf ) || ... || SHA-2( n-1 || prefix || input_buf ) */
			target_buf += (i * SHA256_DIGEST_LENGTH);
			new_input[0] = (uint8_t) i;
			SHA256_Init(&sha2);
			SHA256_Update(&sha2, new_input, new_input_len);
			SHA256_Final(md, &sha2);
			memcpy(target_buf, md, hash_len);
			memset(md, 0, SHA256_DIGEST_LENGTH);
		}
		// copy back to caller
		memcpy(output_buf, md2, hash_len);
	}

	OPENSSL_cleanse(&sha2,sizeof(sha2));
	return 1;
}

int main() {
  int hash_len = 64;
  uint8_t hash_buf[hash_len+1];

  string str = "test";
  int result = hash_to_bytes((uint8_t *) &str, str.length(), hash_buf, hash_len, 2);

  cout << "result " << result << endl;
  cout << "data " << hash_buf << endl;

  return 0;
}
