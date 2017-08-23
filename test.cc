#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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

int main() {
  // set buffer size, SIZE
  // int SIZE = 255;
  //
  // char buffer[SIZE];
  // freopen("/dev/null", "a", stdout);
  // setbuf(stdout, buffer);
  // printf("This will be stored in the buffer");
  // freopen ("/dev/tty", "a", stdout);
  // cout << "BUFFER: " << buffer << endl;

  // string x = "1234";
  // string y = "\x12\x34";
  // std::ostringstream oss;
  // for (int i = 0; i < x.length(); i+=2) {
  //   oss << "\\x" << x[i] << x[i+1];
  // }
  //
  // string f = oss.str();
  // cout << f << endl;
  // cout << (f == y) << endl;



   string s = "1234";
   string h = "\x12\x34";
   const char *o = hexTohex(s).c_str();
   cout << "s " << s << endl;
   cout << "h " << h << endl;
   cout << "o " << o << endl;
   cout << "o == h " << (o == h) << endl;
  //  cout << o, o.size(), (o == h);

  return 0;
}
