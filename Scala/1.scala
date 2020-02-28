val partitionHelper: (List[Int], Int => Boolean) => List[Int]  = {
	case (Nil, p) => Nil
	case (x :: xs, p) if p(x) => x :: partitionHelper(xs, p)
	case (x :: xs, p) => partitionHelper(xs, p)
}


val partition: (List[Int], Int => Boolean) => (List[Int], List[Int]) = 
	(as, p) => (partitionHelper(as, p), partitionHelper(as, !p(_)))


