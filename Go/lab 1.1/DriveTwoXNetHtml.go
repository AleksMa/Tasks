package main

import (
	"golang.org/x/net/html"
	"github.com/mgutz/logxi/v1"
	"net/http"
	"strings"
	"fmt"
)

func getChildren(node *html.Node) []*html.Node {
	var children []*html.Node
	for c := node.FirstChild; c != nil; c = c.NextSibling {
		children = append(children, c)
	}
	return children
}

func getAttr(node *html.Node, key string) string {
	for _, attr := range node.Attr {
		if attr.Key == key {
			return attr.Val
		}
	}
	return ""
}

func isText(node *html.Node) bool {
	return node != nil && node.Type == html.TextNode
}

func isElem(node *html.Node, tag string) bool {
	return node != nil && node.Type == html.ElementNode && node.Data == tag
}

func stringInSlice(a string, list []string) bool {
	for _, b := range list {
		if b == a {
			return true
		}
	}
	return false
}

func isDiv(node *html.Node, class string) bool {
	return isElem(node, "div") && stringInSlice(class, strings.Split(getAttr(node, "class"), " "))
}



/*
func readItem(item *html.Node) *Item {
	if a := item.FirstChild; isElem(a, "a") {
		if cs := getChildren(a); len(cs) == 2 && isElem(cs[0], "time") && isText(cs[1]) {
			return &Item{
				Ref:   getAttr(a, "href"),
				Time:  getAttr(cs[0], "title"),
				Title: cs[1].Data,
			}
		}
	}
	return nil
}*/

func recSearchForNode(node *html.Node, firstClass string, secondClass string) *html.Node {

	if isDiv(node, firstClass) || isDiv(node, secondClass) {
		return node
	}

	for c := node.FirstChild; c != nil; c = c.NextSibling {
		if node := recSearchForNode(c, firstClass, secondClass); node != nil {
			return node
		}
	}
	return nil
}

func parseCBlock(node *html.Node) *Item {
	var item Item

	//card := getChildren(getChildren(getChildren(item)[1])[3])[1]
	//fmt.Println(item.Attr)
	title := recSearchForNode(node, "c-article-card__title", "c-post-preview__title")
	img := recSearchForNode(node, "c-preview-pic", "c-article-card__pic")
	lead := recSearchForNode(node, "c-post-preview__lead", "c-article-card__lead")

	if isDiv(title, "c-article-card__title") {
		item.Title = strings.TrimSpace(title.FirstChild.Data)
	} else if isDiv(title, "c-post-preview__title") {
		if cs := getChildren(title); len(cs) > 1 && isElem(cs[1], "a") {
			a := cs[1]
			//item.Ref = "drive2.ru" + getAttr(a, "href")
			if ttl := a.FirstChild; ttl != nil {
				item.Title = ttl.Data
			}
		}
	}

	if cs := getChildren(img); len(cs) > 1 && isElem(cs[1], "a"){
		a := cs[1]
		item.Ref = "https://drive2.ru" + getAttr(a, "href")
		//fmt.Println(item.Ref)
		if im := a.FirstChild; im != nil && isDiv(im, "o-img") {
			if cs := getChildren(im); len(cs) >= 2 {
				if imgLink := cs[1]; isElem(imgLink, "img"){
					item.ImageRef = getAttr(imgLink, "src")
				}
			}
		}
	}

	item.Preview = strings.TrimSpace(lead.FirstChild.Data)


	if title != nil && lead != nil && img != nil {
		return &item
	}

	//var ref, title, preview, image *html.Node

	//for title == nil {}



	/*
	for !isDiv(card, "c-article-card") {
		card = getChildren(card)[1]
	}
	fmt.Println(card)
	//var ref, title, preview, image *html.Node
	var title *html.Node
	for c := card.FirstChild; c != nil; c = c.NextSibling {
		if isDiv(c, "c-preview-pics"){
			//image = c
		} else if isDiv(c, "c-post-preview__title"){
			title = c
			//ref = c
		} else if isDiv(c, "c-post-preview__lead"){
			//preview = c
		}
	}
	fmt.Println(title.FirstChild.Data)
	*/
	return nil
}

type Item struct {
	Ref, Title, Preview, ImageRef string
	//Issue *Issue
}

type Issue struct {
	Text, Image string
}


func downloadNews() []*Item {
	log.Info("sending request to drive2.ru")
	if response, err := http.Get("http://drive2.ru"); err != nil {
		log.Error("request to drive2.ru failed", "error", err)
	} else {
		defer response.Body.Close()
		status := response.StatusCode
		log.Info("got response from drive2.ru", "status", status)
		if status == http.StatusOK {
			if doc, err := html.Parse(response.Body); err != nil {
				log.Error("invalid HTML from drive2.ru", "error", err)
			} else {
				log.Info("HTML from drive2.ru parsed successfully")
				return search(doc)
			}
		}
	}
	return nil
}

func search(node *html.Node) []*Item {
	//var itemx []*Item

	/*
	if isDiv(node, "c-block"){

		if set := getChildren(getChildren(node)[1]); len(set) > 0 {
			for _, c := range set {
				//fmt.Println(getAttr(c, "class"))
				if isDiv(c, "c-block") {
					fmt.Println(c.Attr)

					if item := parseCBlock(c); item != nil {
						//log.Info(item.Title)
						itemx = append(itemx, item)
					}
				}
			}
			return itemx
		}

		fmt.Println("lol")
	} */

	/*
		search не заходит в некоторые вершины (чередуется заходит/не заходит)
		Нумерация "реальных" дочерних - нечетные числа

		l-page - 3-й дочерний l-container
		l-page-main - 1-й дочерний l-page-columns
		getChildren(getChildren(node)[1]) - множество (массив?) всех статей
	 */





	/*
	if isDiv(node, "l-page-columns"){
		//fmt.Println(getChildren(node)[0].NextSibling.FirstChild.NextSibling.Attr)

		fmt.Println(len(getChildren(getChildren(node)[1])))
		//return nil
	}*/

	if isDiv(node, "l-page-main") {
		var items []*Item
		for c := node.FirstChild; c != nil; c = c.NextSibling {
			if isDiv(c, "c-block") {
				if item := parseCBlock(c); item != nil {
					items = append(items, item)
				}
			}
		}
		return items
	}


	for c := node.FirstChild; c != nil; c = c.NextSibling {
		if items := search(c); items != nil {
			return items
		}
	}
	return nil
}





//===================================================================================================


func writeSomeItems(item *Item){
	log.Info(item.Title)
	log.Info(item.Ref)
	log.Info(item.ImageRef)
	log.Info(item.Preview)

	log.Info("")

	fmt.Println(item.Title)
	fmt.Println(item.Ref)
	fmt.Println(item.ImageRef)
	fmt.Println(item.Preview)

	fmt.Println()
}


func main() {


	log.Info("Downloader started")
	//var items []*Item

	//downloadNews()

	items := downloadNews()

	for _, item := range items {
		writeSomeItems(item)
	}


}
