import rsa

eFileName = "C:/RSA/PythonScripts/files/e.txt"
dFileName = "C:/RSA/PythonScripts/files/d.txt"
nFileName = "C:/RSA/PythonScripts/files/mod.txt"
BlockSize = 256


(pubkey, privkey) = rsa.newkeys(BlockSize * 8)
eFile = open(eFileName, "wb")
eFile.write(privkey.e.to_bytes((privkey.e.bit_length() + 7) // 8, byteorder='little'))
eFile.close()
dFile = open(dFileName, "wb")
dFile.write(privkey.d.to_bytes((privkey.d.bit_length() + 7) // 8, byteorder='little'))
dFile.close()
nFile = open(nFileName, "wb")
nFile.write(privkey.n.to_bytes((privkey.n.bit_length() + 7) // 8, byteorder='little'))
nFile.close()

