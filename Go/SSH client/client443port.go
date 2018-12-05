package main

import (
	"fmt"
	"os"
	"bytes"
	"golang.org/x/crypto/ssh"
)

func executeCmd(cmd, hostname string, port string, config *ssh.ClientConfig) {
	conn, _ := ssh.Dial("tcp", hostname+":"+port, config)
	session, _ := conn.NewSession()
	defer session.Close()

	var stdoutBuf bytes.Buffer
	session.Stdout = &stdoutBuf
	session.Run(cmd)

	fmt.Println(stdoutBuf.String())
}

func main() {
	cmd := os.Args[1]
	hostname := "151.248.113.144"
	port := "443"

	config := &ssh.ClientConfig{
		User: "user",
		Auth: []ssh.AuthMethod{
			ssh.Password("12345678990"),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	executeCmd(cmd, hostname, port, config)

}
