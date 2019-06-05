package Automata

import "fmt"

var k = 0;

func DFS(D [][] int, renumeration [] int, q int){
	renumeration[q] = k;
	k++;
	for _, v := range D[q] {
		if renumeration[v] == -1 {
			DFS(D, renumeration, v);
		}
	}
}

func  main() {

	var n, m, q int;

	fmt.Scan(&n, &m, &q);

	var D = make([][] int, n);
	var F = make([][] string, n);
	var renumeration = make([] int, n);
	var reRenumeration = make([] int, n);

	for i := 0; i < n; i++ {

		renumeration[i] = -1;

		D[i] = make([] int, m);
		for j := 0; j < m; j++ {
			fmt.Scan(&D[i][j]);
		}
	}

	for i := 0; i < n; i++ {
		F[i] = make([] string, m);
		for j := 0; j < m; j++ {
			fmt.Scan(&F[i][j]);
		}
	}

	DFS(D, renumeration, q);

	for i, x := range renumeration {
		if x != -1{
			reRenumeration[x] = i
		} else {
			n--;
		}
	}

	fmt.Printf("%d\n%d\n%d\n", n, m, 0);

	for i := 0; i < n; i++ {

		//fmt.Printf("%d ", reRenumeration[i]);
		k := reRenumeration[i];

		for j := 0; j < m; j++ {
			fmt.Printf("%d ", renumeration[D[k][j]]);
		}
		fmt.Println();

	}

	for i := 0; i < n; i++ {

		//fmt.Printf("%d ", reRenumeration[i]);
		k := reRenumeration[i];
		for j := 0; j < m; j++ {
			fmt.Printf("%s ", F[k][j]);
		}
		fmt.Println();

	}
}