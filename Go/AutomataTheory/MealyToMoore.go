package Automata

import "fmt"

type pair struct {
	q int
	y string
}

type Mealy struct{
	N, K, M, q int
	In, Out [] string
	D [][]int
	F [][]string
}

func main() {
	machine := &Mealy{}

	fmt.Scan(&machine.M)
	machine.In = make([]string, machine.M)
	for i := 0; i < machine.M; i++ {
		fmt.Scan(&machine.In[i])
	}
	fmt.Scan(&machine.K)
	machine.Out = make([]string, machine.K)
	for i := 0; i < machine.K; i++ {
		fmt.Scan(&machine.Out[i])
	}
	fmt.Scan(&machine.N)

	machine.D = make([][]int, machine.N)
	machine.F = make([][]string, machine.N)

	for i := 0; i < machine.N; i++ {

		machine.D[i] = make([] int, machine.M)
		for j := 0; j < machine.M; j++ {
			fmt.Scan(&machine.D[i][j])
		}
	}
	for i := 0; i < machine.N; i++ {
		machine.F[i] = make([] string, machine.M)
		for j := 0; j < machine.M; j++ {
			fmt.Scan(&machine.F[i][j])
		}
	}

	assoc := make(map[pair]pair, machine.M*machine.N)

	fmt.Printf("digraph {\n" + "    rankdir = LR\n")

	k := 0
	for i2 := 0; i2 < machine.N; i2++ {
		for j2, _ := range machine.In {
			i, j := machine.D[i2][j2], machine.F[i2][j2]
			if _, fl := assoc[pair{i, j}]; !fl{
				fmt.Printf("    %d [label = \"(%d,%s)\"]\n", k, i, j)
				assoc[pair{i, j}] = pair{k, "yes'n"}
				k++
			}
		}
	}
	for i := 0; i < machine.N; i++ {
		for _, j := range machine.Out {
			if msg, _ := assoc[pair{i, j}]; msg.y == "yes'n" {
				for m, l := range machine.In {
					fmt.Printf("    %d -> %d [label = \"%s\"]\n", assoc[pair{i, j}].q, assoc[pair{machine.D[i][m], machine.F[i][m]}].q, l)
				}
				assoc[pair{i, j}] = pair{assoc[pair{i, j}].q, "yep"}
			}
		}
	}
	fmt.Println("}")

}