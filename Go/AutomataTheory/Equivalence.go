package Automata

import(
"fmt"
)


type Mealy struct{
	n, m, q int
	D [][]int
	F [][]string
}

func (machine *Mealy) initialization(){
	fmt.Scan(&machine.n, &machine.m, &machine.q)
	machine.D = make([][]int, machine.n)
	machine.F = make([][]string, machine.n)

	for i := 0; i < machine.n; i++ {

		machine.D[i] = make([] int, machine.m)
		for j := 0; j < machine.m; j++ {
			fmt.Scan(&machine.D[i][j])
		}
	}

	for i := 0; i < machine.n; i++ {
		machine.F[i] = make([] string, machine.m)
		for j := 0; j < machine.m; j++ {
			fmt.Scan(&machine.F[i][j])
		}
	}
}

func (machine *Mealy) visualization(){

	fmt.Printf("digraph {\n" + "    rankdir = LR\n" + "    dummy [label = \"\", shape = none]\n" + "    dummy -> %d\n", machine.q)

	for i := 0; i < machine.n; i++ {
		fmt.Printf("    %d [shape = circle]\n", i)
		for j := 0; j < machine.m; j++ {
			fmt.Printf("    %d -> %d [label = \"%s(%s)\"]\n",i , machine.D[i][j], string(rune(j + 'a')), machine.F[i][j])
		}
	}
	fmt.Println("}")
}

var k = 0

func (machine *Mealy) DFS(renumeration [] int, q int){
	renumeration[q] = k
	k++
	for _, v := range machine.D[q] {
		if renumeration[v] == -1 {
			machine.DFS(renumeration, v)
		}
	}
}

func (machine *Mealy) canonization(){
	k = 0
	renumeration := make([] int, machine.n)
	oldN := machine.n
	for i := 0; i < oldN; i++ {
		renumeration[i] = -1
	}
	machine.DFS(renumeration, machine.q)
	machine.n = k
	newD := make([][]int, machine.n)
	newF := make([][]string, machine.n)
	for i := 0; i < machine.n; i++ {
		newD[i] = make([] int, machine.m)
		newF[i] = make([] string, machine.m)
	}
	for i := 0; i < oldN; i++ {
		if k := renumeration[i]; k != -1{
			for j := 0; j < machine.m; j++ {
				newD[k][j] = renumeration[machine.D[i][j]]
				newF[k][j] = machine.F[i][j]
			}
		}
	}
	machine.q = 0
	machine.D = newD
	machine.F = newF
}

func (machine *Mealy) split1 (pi []int) (m int){
	m = machine.n
	assoc := make([] DSF, machine.n)
	for i := 0; i < machine.n; i++{
		assoc[i].init(i)
	}
	for i := 0; i < machine.n; i++{
		for j := 0; j < machine.n; j++{
			if assoc[i].find() != assoc[j].find(){
				eq := true
				for k := 0; k < machine.m; k++ {
					if machine.F[i][k] != machine.F[j][k]{
						eq = false
						break
					}
				}
				if eq {
					assoc[i].union(&assoc[j])
					m--
				}
			}
		}
	}
	for i := 0; i < machine.n; i++{
		pi[i] = assoc[i].find().x
	}
	return m
}

func (machine *Mealy) split (pi []int) (m int){
	m = machine.n
	assoc := make([] DSF, machine.n)
	for i := 0; i < machine.n; i++{
		assoc[i].init(i)
	}
	for i := 0; i < machine.n; i++{
		for j := 0; j < machine.n; j++{
			if pi[i] == pi[j] && assoc[i].find() != assoc[j].find(){
				eq := true
				for k := 0; k < machine.m; k++ {
					w1, w2 := machine.D[i][k], machine.D[j][k]
					if pi[w1] != pi[w2] {
						eq = false
						break
					}
				}
				if eq {
					assoc[i].union(&assoc[j])
					m--
				}
			}
		}
	}
	for i := 0; i < machine.n; i++{
		pi[i] = assoc[i].find().x
	}
	return m
}

func (machine *Mealy) AufenkampHohn(){
	pi := make([] int, machine.n)
	m := machine.split1(pi)
	for {
		ml := machine.split(pi)
		if m == ml{
			break
		}
		m = ml
	}
	used := make([] bool, machine.n)
	newD := make([][]int, machine.n)
	newF := make([][]string, machine.n)
	for i := 0; i < machine.n; i++ {
		newD[i] = make([] int, machine.m)
		for j := 0; j < machine.m; j++{
			//newD[i][j] = -1
		}
		newF[i] = make([] string, machine.m)
	}
	for i := 0; i < machine.n; i++ {
		ql := pi[i]
		if !used[ql] {
			used[ql] = true
			for j := 0; j < machine.m; j++ {
				newD[ql][j] = pi[machine.D[i][j]]
				newF[ql][j] = machine.F[i][j]
			}
		}
	}

	for i := 0; i < machine.n; i++ {
		if !used[i]{
			for j := 0; j < machine.m; j++ {
				newD[i][j] = i
			}
		}
	}

	machine.D = newD
	machine.F = newF
}

func (machine *Mealy) minimization(){
	machine.canonization()
	machine.AufenkampHohn()
	machine.canonization()
}

type DSF struct {
	x, depth int
	parent *DSF
}

func (s *DSF) init (x int){
	s.x = x
	s.depth = 0
	s.parent = s
}

func (x *DSF) find () *DSF {
	if x.parent == x {
		return x
	} else {
		return x.parent.find()
	}
}

func (x *DSF) union (y *DSF){
	rootX := x.find()
	rootY := y.find()
	if rootX.depth < rootY.depth {
		rootX.parent = rootY
	} else {
		rootY.parent = rootX
		if rootX.depth == rootY.depth && rootX != rootY {
			rootX.depth++
		}
	}

}

func  main() {

	firstMachine := &Mealy{}
	secondMachine := &Mealy{}

	firstMachine.initialization()
	secondMachine.initialization()

	firstMachine.minimization()
	secondMachine.minimization()

	fl := firstMachine.n == secondMachine.n && firstMachine.m == secondMachine.m

	for i := 0; i < firstMachine.n && fl; i++ {
		for j := 0; j < firstMachine.m && fl; j++ {
			if firstMachine.D[i][j] != secondMachine.D[i][j] || firstMachine.F[i][j] != secondMachine.F[i][j]{
				fl = false
			}
		}
	}

	if fl {
		fmt.Print("EQUAL")
	} else {
		fmt.Print("NOT EQUAL")
	}
}
