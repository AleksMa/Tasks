package main

import (
	//"fmt"
	"github.com/gliderlabs/ssh"
	"golang.org/x/crypto/ssh/terminal"
	"log"
	"os/exec"
	"strings"
)
func Handler(sess ssh.Session) {


	term := terminal.NewTerminal(sess, "> ")
	for {
		line, err := term.ReadLine()
		if err != nil {
			break
		}

		cmd := exec.Command(line)

		arr := strings.Split(line, " ")
		if len(arr) > 1 {
			cmd = exec.Command(arr[0], arr[1:]...)
		}

		res, err := cmd.Output()
		if err != nil {
			term.Write([]byte("bad command\n"))
			continue
		} else {
			term.Write(res)
		}
		log.Println(line)
	}

	log.Println("terminal closed")
}


func main() {
	ssh.Handle(Handler)

	log.Println("starting ssh server on port 2222...")
	log.Fatal(ssh.ListenAndServe(":2222", nil))
}