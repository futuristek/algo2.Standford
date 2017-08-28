def prim_simple():
	with open('test_edges.txt') as f:
		nodes = {}
		fl = f.next()
		nn, ne = map(int, fl.split(' '))
		for line in f:
			v1, v2, c = map(int, line.split(' '))
			if v1 in nodes:
				nodes[v1].append((v2, c))
			else:
				nodes[v1] = [(v2, c)]
			if v2 in nodes:
				nodes[v2].append((v1, c))
			else:
				nodes[v2] = [(v1, c)]
		n_mark = {}
		for k in nodes.keys():
			n_mark[k] = 0
		mst = list(nodes.keys()[0])
		n_mark[nodes.keys()[0]] = 1
		mst_cost = 0
		while len(mst) < nn:
			for node in mst:
				neighbors = nodes[node]
				min_c = neighbors[0][1]
				min_n = neighbors[0][0]
				for tup in neighbors:
					if tup[1] < min_c and n_mark[tup[0]] != 1:
						min_c = tup[1]
						min_n = tup[0]
				n_mark[min_n] = 1
				n = min_n
				mst_cost += min_
		return mst_cost


def main():
	print prim_simple()

if __name__ == '__main__':
	main()