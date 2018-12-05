package main

import (
	"fmt"
	"os"

	"golang.org/x/crypto/ssh"
	"bytes"

)


func executeCmd(cmd, hostname string, port string, config *ssh.ClientConfig) {
	conn, _ := ssh.Dial("tcp", hostname+":" + port, config)
	session, _ := conn.NewSession()
	defer session.Close()

	var stdoutBuf bytes.Buffer
	session.Stdout = &stdoutBuf
	session.Run(cmd)

	fmt.Println(stdoutBuf.String())
}



func main() {
	cmd := os.Args[1]
	hostname := "localhost"
	port := "2222"

	config := &ssh.ClientConfig{
		User: "lab2_53_2018",
		Auth: []ssh.AuthMethod{
			ssh.Password("fdffffdfdy9"),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	executeCmd(cmd, hostname, port, config)

}