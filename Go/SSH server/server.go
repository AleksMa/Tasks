package main

import (
	//"fmt"
	"github.com/gliderlabs/ssh"
	"golang.org/x/crypto/ssh/terminal"
	"log"
	"os/exec"
	"strings"
	"io"
)
func Handler(s ssh.Session) {

	cmd := s.Command()
	log.Println("Command handled: ", cmd)
	if len(cmd) != 0 {
		if out, err := exec.Command(cmd[0], cmd[1:]...).CombinedOutput(); err != nil {
			io.WriteString(s, err.Error())
		} else {
			io.WriteString(s, string(out))
		}
	} else {
		term := terminal.NewTerminal(s, "> ")
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
	}

	log.Println("terminal closed")
}


func main() {
	ssh.Handle(Handler)

	log.Println("starting ssh server on port 2222...")
	log.Fatal(ssh.ListenAndServe(":2222", nil))
}