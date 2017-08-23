cmd_Release/obj.target/addon/main.o := c++ '-DNODE_GYP_MODULE_NAME=addon' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_DARWIN_USE_64_BIT_INODE=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/Users/craigoconnor/.node-gyp/8.1.2/include/node -I/Users/craigoconnor/.node-gyp/8.1.2/src -I/Users/craigoconnor/.node-gyp/8.1.2/deps/uv/include -I/Users/craigoconnor/.node-gyp/8.1.2/deps/v8/include -I../node_modules/nan -I../pbcwrapper -I../pbc-0.5.14  -Os -gdwarf-2 -mmacosx-version-min=10.7 -arch x86_64 -Wall -Wendif-labels -W -Wno-unused-parameter -std=gnu++0x -stdlib=libc++ -fno-rtti -fno-threadsafe-statics -fno-strict-aliasing -MMD -MF ./Release/.deps/Release/obj.target/addon/main.o.d.raw -I/usr/local/opt/openssl/include/ -I/usr/local/include -I/usr/local/opt/expat/include  -c -o Release/obj.target/addon/main.o ../main.cc
Release/obj.target/addon/main.o: ../main.cc ../node_modules/nan/nan.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/node_version.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-errno.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-version.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-unix.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-threadpool.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-darwin.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/pthread-barrier.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/node.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/v8.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/v8-version.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/v8config.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/node_buffer.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/node_object_wrap.h \
  ../node_modules/nan/nan_callbacks.h \
  ../node_modules/nan/nan_callbacks_12_inl.h \
  ../node_modules/nan/nan_maybe_43_inl.h \
  ../node_modules/nan/nan_converters.h \
  ../node_modules/nan/nan_converters_43_inl.h \
  ../node_modules/nan/nan_new.h \
  ../node_modules/nan/nan_implementation_12_inl.h \
  ../node_modules/nan/nan_persistent_12_inl.h \
  ../node_modules/nan/nan_weak.h ../node_modules/nan/nan_object_wrap.h \
  ../node_modules/nan/nan_private.h \
  ../node_modules/nan/nan_typedarray_contents.h \
  ../node_modules/nan/nan_json.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/sha.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/e_os2.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/opensslconf.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/./archs/darwin64-x86_64-cc/opensslconf.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/bn.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/ossl_typ.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/crypto.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/stack.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/safestack.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/opensslv.h \
  /Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/symhacks.h \
  .././pbcwrapper/PBC.h ../pbcwrapper/G1.h ../pbcwrapper/G.h \
  ../pbcwrapper/Pairing.h ../pbcwrapper/Zr.h ../pbcwrapper/G2.h \
  ../pbcwrapper/GT.h ../pbcwrapper/PBCExceptions.h \
  ../pbcwrapper/PPPairing.h
../main.cc:
../node_modules/nan/nan.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/node_version.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-errno.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-version.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-unix.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-threadpool.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/uv-darwin.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/pthread-barrier.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/node.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/v8.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/v8-version.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/v8config.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/node_buffer.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/node_object_wrap.h:
../node_modules/nan/nan_callbacks.h:
../node_modules/nan/nan_callbacks_12_inl.h:
../node_modules/nan/nan_maybe_43_inl.h:
../node_modules/nan/nan_converters.h:
../node_modules/nan/nan_converters_43_inl.h:
../node_modules/nan/nan_new.h:
../node_modules/nan/nan_implementation_12_inl.h:
../node_modules/nan/nan_persistent_12_inl.h:
../node_modules/nan/nan_weak.h:
../node_modules/nan/nan_object_wrap.h:
../node_modules/nan/nan_private.h:
../node_modules/nan/nan_typedarray_contents.h:
../node_modules/nan/nan_json.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/sha.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/e_os2.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/opensslconf.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/./archs/darwin64-x86_64-cc/opensslconf.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/bn.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/ossl_typ.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/crypto.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/stack.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/safestack.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/opensslv.h:
/Users/craigoconnor/.node-gyp/8.1.2/include/node/openssl/symhacks.h:
.././pbcwrapper/PBC.h:
../pbcwrapper/G1.h:
../pbcwrapper/G.h:
../pbcwrapper/Pairing.h:
../pbcwrapper/Zr.h:
../pbcwrapper/G2.h:
../pbcwrapper/GT.h:
../pbcwrapper/PBCExceptions.h:
../pbcwrapper/PPPairing.h:
