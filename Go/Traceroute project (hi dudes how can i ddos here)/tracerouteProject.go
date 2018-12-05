package main

import (

	"net/http"
	"github.com/mgutz/logxi/v1"
	"fmt"
)

func HomeRouterHandler2(w http.ResponseWriter, r *http.Request) {

	r.ParseForm()
	yourUrl := r.Form["yourl"][0]

	fmt.Fprint(w, yourUrl)

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