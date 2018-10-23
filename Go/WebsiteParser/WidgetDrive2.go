package main

import (
	"golang.org/x/net/html"
	"github.com/mgutz/logxi/v1"
	"github.com/mgutz/ansi"
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


func parseTextTag(node *html.Node) string {
	acc := ""
	for _, z := range getChildren(node) {
		if isElem(z, "br") {
			acc += "\n"
		} else if isElem(z, "b") || isElem(z, "i") {
			//fmt.Println(z.FirstChild.Data)
			acc += z.FirstChild.Data
		} else if isElem(z, "a") {
			acc += "https://www.drive2.ru"  + getAttr(z, "href")
		} else {
			acc += z.Data
		}
	}
	return acc
}

func parseCBlock(node *html.Node) *Item {
	var item Item

	title := recSearchForNode(node, "c-post-preview__title", "c-article-card__title")
	img := recSearchForNode(node, "c-preview-pic", "c-article-card__pic")
	lead := recSearchForNode(node, "c-post-preview__lead", "c-article-card__lead")

	if isDiv(title, "c-article-card__title") {
		item.Title = strings.TrimSpace(title.FirstChild.Data)
	} else if isDiv(title, "c-post-preview__title") {
		if cs := getChildren(title); len(cs) > 1 && isElem(cs[1], "a") {
			a := cs[1]
			if ttl := a.FirstChild; ttl != nil {
				item.Title = ttl.Data
			}
		}
	}

	if cs := getChildren(img); len(cs) > 1 && isElem(cs[1], "a"){
		a := cs[1]
		item.Ref = "https://drive2.ru" + getAttr(a, "href")
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
		item.Issue = downloadIssues(item.Ref)
		//COLOR
		item.Ref = ansi.Color(item.Ref, "blue")
		item.ImageRef = ansi.Color(item.ImageRef, "yellow")
		return &item
	}

	return nil
}

type Item struct {
	Ref, Title, Preview, ImageRef string
	Issue []*Issue
}

type Issue struct {
	Type, Data string
}

func downloadIssues(link string) []*Issue {
	log.Info("sending request to " + link)
	if response, err := http.Get(link); err != nil {
		log.Error("request to " + link + " failed", "error", err)
	} else {
		defer response.Body.Close()
		status := response.StatusCode
		log.Info("got response from " + link, "status", status)
		if status == http.StatusOK {
			if doc, err := html.Parse(response.Body); err != nil {
				log.Error("invalid HTML from " + link, "error", err)
			} else {
				log.Info("HTML from " + link + " parsed successfully")
				return searchIssues(doc)
			}
		}
	}
	return nil
}

func searchIssues(node *html.Node) []*Issue{

	if isDiv(node, "c-post__body") {
		var items []*Issue
		for c := node.FirstChild.NextSibling.FirstChild; c != nil; c = c.NextSibling {
			if isDiv(c, "c-post__pic") {
				cd := c.FirstChild
				var data string
				if isElem(cd, "a"){
					data = getAttr(cd, "href")
				} else if len(getChildren(cd)) > 1 && isElem(cd.FirstChild.NextSibling, "img"){
					data = getAttr(cd.FirstChild.NextSibling, "src")
				}
				//COLOR
				data = ansi.Color(data, "yellow")
				items = append(items, &Issue{
					Type: "img",
					Data: data,
				})
			} else if (isElem(c, "p") || isElem(c, "i") || isElem(c, "b")) && len(getChildren(c)) != 0 {
				data := parseTextTag(c)
				items = append(items, &Issue{
					Type: "txt",
					Data: data,
				})
			/*} else if isElem(c, "br"){
				items = append(items, &Issue{
					Type: "txt",
					Data: "\n",
				})*/
			} else if len(c.Data) > 5 {
				items = append(items, &Issue{
					Type: "txt",
					Data: c.Data,
				})
			}
		}
		return items
	}


	for c := node.FirstChild; c != nil; c = c.NextSibling {
		if items := searchIssues(c); items != nil {
			return items
		}
	}
	return nil
}

func downloadItems(link string) []*Item {
	log.Info("sending request to " + link)
	if response, err := http.Get(link); err != nil {
		log.Error("request to " + link + " failed", "error", err)
	} else {
		defer response.Body.Close()
		status := response.StatusCode
		log.Info("got response from " + link, "status", status)
		if status == http.StatusOK {
			if doc, err := html.Parse(response.Body); err != nil {
				log.Error("invalid HTML from " + link, "error", err)
			} else {
				log.Info("HTML from " + link + " parsed successfully")
				return searchItems(doc, "l-page-main", "c-block")
			}
		}
	}
	return nil
}

func searchItems(node *html.Node, containerClass string, setClass string) []*Item {

	/*
		searchItems не находил некоторые вершины по имени класса
		Связано с >1 классами некоторых div'ов
		isDiv переработан, теперь проверяет принадлежность элемента к хотя бы одному классу
	*/


	if isDiv(node, containerClass) {
		var items []*Item
		for c := node.FirstChild; c != nil; c = c.NextSibling {
			if isDiv(c, setClass) {
				if item := parseCBlock(c); item != nil {
					items = append(items, item)
				}
			}
		}
		return items
	}


	for c := node.FirstChild; c != nil; c = c.NextSibling {
		if items := searchItems(c, containerClass, setClass); items != nil {
			return items
		}
	}
	return nil
}


func writeSomeIssues(issues []*Issue){
	for _, issue := range issues {
		fmt.Println(issue.Data)
		//log.Info(issue.Data)
	}
}

func writeSomeItems(item *Item, writer func(issues []*Issue)){
	/*
	log.Info(item.Title)
	log.Info(item.Ref)
	log.Info(item.ImageRef)
	log.Info(item.Preview)

	log.Info("")
	*/

	fmt.Println(item.Title)
	fmt.Println(item.Ref)
	fmt.Println(item.ImageRef)
	fmt.Println(item.Preview)
	fmt.Println("=========================================")

	writer(item.Issue)

	fmt.Println()
}


func main() {


	log.Info("Downloader started")

	items := downloadItems("http://drive2.ru")

	for _, item := range items {
		writeSomeItems(item, writeSomeIssues)
	}



}
