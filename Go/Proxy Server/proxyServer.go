package main

import (

	"net/http"
	"github.com/mgutz/logxi/v1"
	"fmt"
	"io/ioutil"
	"regexp"
	"strings"
)

var CurrentUrl string

func serveWebsite(w http.ResponseWriter, url string){

	resp, _ := http.Get(url)

	defer resp.Body.Close()

	body, _ := ioutil.ReadAll(resp.Body)

	outputStream := string(body)



	re := regexp.MustCompile("href=\"(?P<proto>http.?)://(?P<url>.*?)\"")

	outputStream = re.ReplaceAllString(outputStream, "href=\"/${proto}/${url}\"")


/*
	re := regexp.MustCompile("href=\"(?P<proto>http.?)://(?P<url>.*?)\"")

	outputStream = re.ReplaceAllString(outputStream, "href=\"/${proto}://${url}\"")
*/

	/*
	re := regexp.MustCompile("href=\"(?P<proto>https://.*?)\"")

	outputStream = re.ReplaceAllString(outputStream, "href=\"/${proto}\"")
	*/
	//fmt.Print(outputStream)

	fmt.Fprintf(w, outputStream)
}

func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {

	//fmt.Println(r.URL.Path[1:5])
	if r.URL.Path == "/" {
		http.ServeFile(w, r, "kek.html")
	} else if strings.HasPrefix(r.URL.Path, "/https/") {
		fmt.Println("/https")
		path := r.URL.Path[7:]
		fmt.Println(path)
		//fmt.Fprintf(w, r.URL.Path[7:])
		serveWebsite(w, "https://"+path)
		ending := strings.Index(path, "/")
		if ending > 0 {
			CurrentUrl = "https://" + path[0:strings.Index(path, "/")]
		} else {
			CurrentUrl = "https://" + path[0:]
		}
		fmt.Println(CurrentUrl)
	} else if strings.HasPrefix(r.URL.Path, "/http/") {
		fmt.Println("/http")
		path := r.URL.Path[6:]
		fmt.Println(path)
		//fmt.Fprintf(w, r.URL.Path[6:])
		serveWebsite(w, "http://"+path)
		ending := strings.Index(path, "/")
		if ending > 0 {
			CurrentUrl = "https://" + path[0:strings.Index(path, "/")]
		} else {
			CurrentUrl = "https://" + path[0:]
		}
		fmt.Println(CurrentUrl)
	} else {
		fmt.Println(CurrentUrl)
		serveWebsite(w, CurrentUrl+r.URL.Path)
	}

}

func HomeRouterHandler2(w http.ResponseWriter, r *http.Request) {

	r.ParseForm()
	yourUrl := r.Form["yourl"][0]

	if !strings.HasPrefix(yourUrl, "http"){
		CurrentUrl = yourUrl
		yourUrl = "http://" + yourUrl
	} else {
		t := strings.Index(yourUrl, "//")
		ts := yourUrl[t + 2:]
		ending := strings.Index(ts, "/")
		if ending > 0 {
			CurrentUrl = yourUrl[0:t] + "//" + ts[0:ending]
		} else {
			CurrentUrl = yourUrl[0:t] + "//" + ts[0:]
		}
	}



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
