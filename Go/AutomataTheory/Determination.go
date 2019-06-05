package Automata

import (
	"fmt"
	"sort"
)

func equal(a sort.IntSlice, b sort.IntSlice) bool {
	if len(a) != len(b) {
		return false
	} else {
		for i := 0; i < len(a); i++ {
			if a[i] != b[i] {
				return false
			}
		}
	}
	return true
}

type StringSlice [] string

func (s StringSlice) Len() int { return len(s) }

func (s StringSlice) Less(i, j int) bool { return alphabet[s[i]] < alphabet[s[j]] }

func (s StringSlice) Swap(i, j int) { s[i], s[j] = s[j], s[i] }

type FinalMach struct {
	N, K, M int
	Q       [] sort.IntSlice
	D       [][] StringSlice
	Final   [] bool
	q       sort.IntSlice
}

type Stack struct {
	data     [] int
	cap, top int
}

var (
	alphabet map[string]int
)

func DFS(D [][][] int, q int, C *sort.IntSlice) {
	in := false
	for _, c := range *C {
		if c == q {
			in = true
		}
	}
	if !in {
		*C = append(*C, q)
		if _, b := alphabet["lambda"]; b {
			for _, w := range D[q][alphabet["lambda"]] {
				DFS(D, w, C)
			}
		}
	}
}

func Closure(D [][][] int, z sort.IntSlice) (C sort.IntSlice) {
	C = make([] int, 0)
	for _, q := range z {
		DFS(D, q, &C)
	}
	return C
}

func (machine *FinalMach) Det(D [][][]int, Final []bool, q int, N int) {
	machine.q = Closure(D, append(make(sort.IntSlice, 0), q))
	machine.Q = append(machine.Q, machine.q)
	F := make([]sort.IntSlice, 0)

	machine.D = make([][]StringSlice, 1)
	//for i := 0; i < 10; i++ {
	machine.D[0] = make([]StringSlice, 1)
	//}
	s := &Stack{}
	s.InitStack()
	s.Push(0)
	for !s.Empty() {
		z := s.Pop()
		for _, u := range machine.Q[z] {
			if Final[u] {
				F = append(F, machine.Q[z])
				break
			}
		}
		for a, k := range alphabet {
			if a == "lambda" {
				continue
			}
			arg := make(sort.IntSlice, 0)
			for _, u := range machine.Q[z] {
				temp := D[u][k]
				for _, v := range temp {
					arg = append(arg, v)
				}
			}
			zz := Closure(D, arg)
			in := false
			var zNum int
			for i, c := range machine.Q {
				if equal(c, zz) {
					in = true
					zNum = i
				}
			}
			if !in {
				machine.Q = append(machine.Q, zz)
				machine.D = append(machine.D, make([]StringSlice, len(machine.Q)))
				for i := 0; i < len(machine.Q)-1; i++ {
					for len(machine.D[i]) < len(machine.Q) {
						machine.D[i] = append(machine.D[i], make(StringSlice, 0))
					}
				}
				zNum = len(machine.Q) - 1
				s.Push(zNum)
			}
			machine.D[z][zNum] = append(machine.D[z][zNum], a)
		}
	}

	machine.Final = make([]bool, len(machine.Q))
	for _, f := range F {
		var zNum int
		for i, t := range machine.Q {
			if equal(f, t) {
				zNum = i
			}
		}
		machine.Final[zNum] = true
	}

	for i, _ := range machine.Q {
		sort.Sort(machine.Q[i])
	}
}

//STACK

func (s *Stack) InitStack() {
	s.data = make([] int, 0)
	s.top = 0
}

func (s *Stack) Empty() bool { return s.top == 0 }

func (s *Stack) Push(x int) {
	if len(s.data) == s.top {
		s.data = append(s.data, x)
	} else {
		s.data[s.top] = x
	}
	s.top++
}

func (s *Stack) Pop() int {
	s.top--
	x := s.data[s.top]
	return x
}

func main() {
	var (
		a, b, q int
		c       string
		D       [][][]int
		Final   []bool
		N, M    int
	)
	machine := &FinalMach{}
	alphabet = make(map[string]int)
	input.Scanf("%d %d", &N, &M)
	Final = make([]bool, N)
	D = make([][][]int, N)
	for i := 0; i < N; i++ {
		D[i] = make([][] int, M)
	}
	K := 0
	for i := 0; i < M; i++ {
		input.Scanf("%d %d %s", &a, &b, &c)
		x, fl := alphabet[c]
		if !fl {
			alphabet[c] = K
			x = K
			K++
			for i := 0; i < N; i++ {
				D[i] = append(D[i], make([] int, 0))
			}
		}
		D[a][x] = append(D[a][x], b)
	}

	for i := 0; i < N; i++ {
		input.Scanf("%d", &a)
		Final[i] = a != 0
	}

	input.Scanf("%d", &q)
	machine.Det(D, Final, q, N)

	fmt.Printf("digraph {\n"+"    rankdir = LR\n"+"    dummy [label = \"\", shape = none]\n"+"    dummy -> %d\n", 0)

	for i := 0; i < len(machine.Q); i++ {
		fmt.Printf("    %d [label = \"%d\", shape = ", i, machine.Q[i])
		if machine.Final[i] {
			fmt.Print("doublecircle")
		} else {
			fmt.Print("circle")
		}
		fmt.Printf("]\n")

		for j := 0; j < len(machine.Q); j++ {
			if machine.D[i][j].Len() > 0 {
				sort.Sort(machine.D[i][j])
				fmt.Printf("    %d -> %d [label = \"", i, j)
				for l, t := range machine.D[i][j] {
					if l < machine.D[i][j].Len()-1 {
						fmt.Printf("%s, ", t)
					} else {
						fmt.Printf("%s", t)
					}
				}
				fmt.Print("\"]\n")
			}
		}
	}
	fmt.Println("}")

}
