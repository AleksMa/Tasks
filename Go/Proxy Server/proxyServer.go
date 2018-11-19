package main

import (

	"net/http"
	"github.com/mgutz/logxi/v1"
	"fmt"
	"io/ioutil"
)

var CurrentUrl string

func serveWebsite(w http.ResponseWriter, url string){

	resp, _ := http.Get(url)

	defer resp.Body.Close()

	body, _ := ioutil.ReadAll(resp.Body)

	outputStream := string(body)

	//re := regexp.MustCompile("href=\"*\"")



	//outputStream = re.ReplaceAllString(outputStream, "href=\"https://vk.com\"")

	//fmt.Print(outputStream)

	fmt.Fprintf(w, outputStream)
}

func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {

	if r.URL.Path == "/" {
		http.ServeFile(w, r, "kek.html")
	} else {
		serveWebsite(w, CurrentUrl+r.URL.Path)
	}

}

func HomeRouterHandler2(w http.ResponseWriter, r *http.Request) {

	r.ParseForm()
	yourUrl := r.Form["yourl"][0]

	CurrentUrl = yourUrl

	serveWebsite(w, yourUrl)

}

func main() {


	http.HandleFunc("/", HomeRouterHandler)
	http.HandleFunc("/process", HomeRouterHandler2)

	err := http.ListenAndServe(":10053", nil)

	if err != nil {

		log.Fatal("ListenAndServe: ", err)

	}

}
