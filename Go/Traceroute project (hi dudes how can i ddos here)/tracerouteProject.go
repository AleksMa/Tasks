package main

import (

	"net/http"
	"github.com/mgutz/logxi/v1"
	"golang.org/x/crypto/ssh"
	"bytes"
	"time"
	"fmt"
	"strings"
	"html/template"
)

type fullConfig struct {
	config *ssh.ClientConfig
	addr   string
}

type tracerouteList struct {
	ServerName string
	Nodes      []string
}

type resultStruct struct {
	Url string
	Tll []tracerouteList
}

func runSSH(url string) []tracerouteList{
	cmd := "traceroute " + url
	results := make(chan tracerouteList, 4)
	timeout := time.After(5 * time.Second)
	var resultList []tracerouteList


	configs := []fullConfig{
		{
			&ssh.ClientConfig{
				User: "lab_53_2018",
				Auth: []ssh.AuthMethod{
					ssh.Password("fdffffdfdy9"),
				},
				HostKeyCallback: ssh.InsecureIgnoreHostKey(),
			},
			"lab.posevin.com:22",
		},
		{
			&ssh.ClientConfig{
				User: "lab2_53_2018",
				Auth: []ssh.AuthMethod{
					ssh.Password("fdffffdfdy9"),
				},
				HostKeyCallback: ssh.InsecureIgnoreHostKey(),
			},
			"lab2.posevin.com:22",
		},
		{
			&ssh.ClientConfig{
				User: "user",
				Auth: []ssh.AuthMethod{
					ssh.Password("12345678990"),
				},
				HostKeyCallback: ssh.InsecureIgnoreHostKey(),
			},
			"151.248.113.144:443",
		},
		{
			&ssh.ClientConfig{
				User: "user",
				Auth: []ssh.AuthMethod{
					ssh.Password("12345678990"),
				},
				HostKeyCallback: ssh.InsecureIgnoreHostKey(),
			},
			"127.0.0.1:2222",
		},
	}

	for _, config := range configs {
		go func(cnfg fullConfig) {
			results <- executeCmd(cmd, cnfg)
		}(config)
	}

	for i := 0; i < len(configs); i++ {
		select {
		case res := <-results:
			resultList = append(resultList, res)
			/*fmt.Println(res.ServerName)
			for _, node := range  res.Nodes{
				fmt.Println(node)
			}
			fmt.Println()*/
		case <-timeout:
			fmt.Println("Time limit!")
			return resultList
		}
	}
	return resultList
}

func executeCmd(cmd string, config fullConfig) tracerouteList {
	conn, _ := ssh.Dial("tcp", config.addr, config.config)
	session, _ := conn.NewSession()
	defer session.Close()

	var stdoutBuf bytes.Buffer
	var tList tracerouteList
	tList.ServerName = config.addr
	session.Stdout = &stdoutBuf
	session.Run(cmd)
	tList.Nodes = strings.Split(stdoutBuf.String(), "\n")
	return tList
}



func HomeRouterHandler2(w http.ResponseWriter, r *http.Request) {

	r.ParseForm()
	argUrl := r.Form["yourl"][0]

	//fmt.Fprint(w, argUrl)

	var result resultStruct
	result.Url = argUrl
	result.Tll = runSSH(argUrl)

	tmpl, _ := template.ParseFiles("trace_table.html")
	tmpl.Execute(w, result)

	fmt.Println(result)

}

func HomeRouterHandlerStart(w http.ResponseWriter, r *http.Request) {

	if r.URL.Path == "/" {
		http.ServeFile(w, r, "index.html")
	}

}


func main() {

	http.HandleFunc("/", HomeRouterHandlerStart)
	http.HandleFunc("/process", HomeRouterHandler2)

	err := http.ListenAndServe(":10053", nil)

	if err != nil {

		log.Fatal("ListenAndServe: ", err)

	}

}