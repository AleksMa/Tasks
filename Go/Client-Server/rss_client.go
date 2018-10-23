package main

import (

    "net"
    "github.com/RealJK/rss-parser-go"
    "os"

)



func main() {



    servAddr := "lab.posevin.com:10053"

    tcpAddr, err := net.ResolveTCPAddr("tcp", servAddr)

    if err != nil {

        println("ResolveTCPAddr failed:", err.Error())

        os.Exit(1)

    }



    conn, err := net.DialTCP("tcp", nil, tcpAddr)

    if err != nil {

        println("Dial failed:", err.Error())

        os.Exit(1)

    }

    rssObject, err := rss.ParseRSS("https://lenta.ru/rss/news")

    NumberOfItems := len(rssObject.Channel.Items)

    for i := 0; i < NumberOfItems; i++ {
	    item := rssObject.Channel.Items[i]
//	    conn.Write([]byte("Item Number : " + string(i) + "\n"))
	    conn.Write([]byte("Title:          " + item.Title + "\n"))
	    conn.Write([]byte("Description:    " + item.Description + "\n\n"))
/*
	    if err != nil {

		println("Write to server failed:", err.Error())

		os.Exit(1)

	    }

*/

//	    println("write to server = ", strEcho)



//	    reply := make([]byte, 1024)



//	    _, err = conn.Read(reply)

/*	    if err != nil {

		println("Write to server failed:", err.Error())

		os.Exit(1)

	    }
*/


//	    println("reply from server=", string(reply))

	    
    }

   // conn.Write([]byte("#eof"))

    conn.Close()

}

