package main

import (
	"bytes"
	"fmt"
	"golang.org/x/crypto/ssh"
	"os"
	"time"
)

type fullConfig struct {
	config *ssh.ClientConfig
	addr   string
}

func executeCmd(cmd string, config fullConfig) string {
	conn, _ := ssh.Dial("tcp", config.addr, config.config)
	session, _ := conn.NewSession()
	defer session.Close()

	var stdoutBuf bytes.Buffer
	session.Stdout = &stdoutBuf
	session.Run(cmd)

	return config.addr + "# " + cmd + ":\n" + stdoutBuf.String() + "=================\n"
}

func main() {
	cmd := os.Args[1]
	hosts := os.Args[2:]
	results := make(chan string, 3)
	timeout := time.After(5 * time.Second)
	configs := make(map[string]fullConfig)
	configs["lab"] = fullConfig{
		&ssh.ClientConfig{
			User: "lab_53_2018",
			Auth: []ssh.AuthMethod{
				ssh.Password("fdffffdfdy9"),
			},
			HostKeyCallback: ssh.InsecureIgnoreHostKey(),
		},
		"lab.posevin.com:22",
	}
	configs["lab2"] = fullConfig{
		&ssh.ClientConfig{
			User: "lab2_53_2018",
			Auth: []ssh.AuthMethod{
				ssh.Password("fdffffdfdy9"),
			},
			HostKeyCallback: ssh.InsecureIgnoreHostKey(),
		},
		"lab2.posevin.com:22",
	}
	configs["newlab"] = fullConfig{
		&ssh.ClientConfig{
			User: "user",
			Auth: []ssh.AuthMethod{
				ssh.Password("12345678990"),
			},
			HostKeyCallback: ssh.InsecureIgnoreHostKey(),
		},
		"151.248.113.144:443",
	}

	for _, hostname := range hosts {
		go func(hostname string) {
			cnfg := configs[hostname]
			results <- executeCmd(cmd, cnfg)
		}(hostname)
	}

	for i := 0; i < len(hosts); i++ {
		select {
		case res := <-results:
			fmt.Print(res)
		case <-timeout:
			return
		}
	}
}