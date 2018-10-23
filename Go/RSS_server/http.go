package main

/*
import (

	"fmt" // пакет для форматированного ввода вывода

	"net/http" // пакет для поддержки HTTP протокола

	"strings" // пакет для работы с  UTF-8 строками

	"log" // пакет для логирования

	"github.com/RealJK/rss-parser-go"
)

func RSSParser(w http.ResponseWriter, url string){
	var URLData string
	if(url == "/"){
		URLData = "https://lenta.ru/rss/news"
	}  else {
		URLData = "https://" + url[1:]
	}
	//fmt.Fprintf(w, "%s", URLData)
	rssObject, err := rss.ParseRSS(URLData)
	if err != nil {

		fmt.Fprintf(w, "<html>")
		fmt.Fprintf(w, "<body>")
		fmt.Printf("Title           : %s\n", rssObject.Channel.Title)
		fmt.Printf("Generator       : %s\n", rssObject.Channel.Generator)
		fmt.Printf("PubDate         : %s\n", rssObject.Channel.PubDate)
		fmt.Printf("LastBuildDate   : %s\n", rssObject.Channel.LastBuildDate)
		fmt.Printf("Description     : %s\n", rssObject.Channel.Description)

		fmt.Printf("Number of Items : %d\n", len(rssObject.Channel.Items))

		for v := range rssObject.Channel.Items {
			item := rssObject.Channel.Items[v]
			//	fmt.Println()
			fmt.Printf("Item Number : %d\n", v)
			fmt.Printf("Title       : %s\n", item.Title)
			fmt.Printf("Link        : %s\n", item.Link)
			fmt.Printf("Description : %s\n", item.Description)
			fmt.Printf("Guid        : %s\n", item.Guid.Value)

			fmt.Fprintf(w, "<b align=center>%s</b><br>", item.Title)


			fmt.Fprintf(w, "%s<br><br>", item.Description)
		}
		fmt.Fprintf(w, "</body>")
		fmt.Fprintf(w, "</html>")
	}
}



func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {

	r.ParseForm() //анализ аргументов,

	fmt.Println(r.Form)  // ввод информации о форме на стороне сервера

	fmt.Println("path", r.URL.Path)

	fmt.Println("scheme", r.URL.Scheme)

	fmt.Println(r.Form["url_long"])

	for k, v := range r.Form {

		fmt.Println("key:", k)

		fmt.Println("val:", strings.Join(v, ""))

	}

	RSSParser(w, r.URL.Path);

	//fmt.Fprintf(w, "Hello!") // отправляем данные на клиентскую сторону

}



func main() {

	http.HandleFunc("/", HomeRouterHandler) // установим роутер

	err := http.ListenAndServe(":10053", nil) // задаем слушать порт

	if err != nil {

		log.Fatal("ListenAndServe: ", err)

	}

}


*/