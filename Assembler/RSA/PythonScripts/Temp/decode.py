import sys
import os
from shutil import copyfile
from subprocess import call
# func writeEncodedMsg(msg []byte, blockSize int) error {
# 	exec.Command("cmd", "/C", "COPY /B /Y C:\\RSA\\files\\e.txt C:\\RSA\\RSASM\\num2.txt").Run()
# 	exec.Command("cmd", "/C", "COPY /B /Y C:\\RSA\\files\\n.txt C:\\RSA\\RSASM\\mod.txt").Run()
# 	encodedFile, _ := os.OpenFile(dataResult, os.O_WRONLY, 0644)
# 	for index := 0; index < len(msg); index += blockSize {
# 		r := index + blockSize
# 		if r > len(msg) {
# 			r = len(msg)
# 		}
#
# 		ioutil.WriteFile(dataPartFile, msg[index:r], 0644)
# 		exec.Command("cmd", "/C", "C:\\RSA\\RSASM\\RSA.exe").Run()
# 		encoded, _ := ioutil.ReadFile(dataEncodePartFile)
# 		encodedFile.Write(encoded)
# 	}
#
# 	return nil
# }

BlockSize = 256

dec = open('dec.txt', "wb")

copyfile('C:/Users/Fujitsu/PycharmProjects/ASM/RSA/files/d.txt',
         'C:/Users/Fujitsu/PycharmProjects/ASM/RSA/RSASM/power.txt')
copyfile('C:/Users/Fujitsu/PycharmProjects/ASM/RSA/files/n.txt',
         'C:/Users/Fujitsu/PycharmProjects/ASM/RSA/RSASM/mod.txt')


i = 0
block = 1
with open("enc.txt", "rb") as f:
    base = open("RSASM/base.txt", "wb")
    byte = f.read(1)
    while byte or i != 0:
        print(i)
        print(byte)
        i+=1
        if byte:
            base.write(byte)
        else:
            base.write(bytes(1))

        if i == 256:
            base.close()
            call(["RSASM/pow.EXE"])
            with open("RSASM/res.txt", "rb") as res:
                t = res.read(BlockSize)
                print(block)

                dec.write(t)
                res.close()
            base = open("RSASM/base.txt", "wb")
            i = 0
        byte = f.read(1)
    base.close()
    f.close()
dec.close()

