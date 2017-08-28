from operator import itemgetter

def greedy():
	with open('jobs.txt') as f:
		f.next()
		j = []
		for line in f:
			w, l = map(int, line.split(' '))
			j.append((w*1.0/l, w, l))
		j = sorted(j, key = itemgetter(0), reverse = True)
		s = 0
		ct = 0
		for v in j:
			ct += v[2]
			s += v[1]*ct
			
		return s

def main():
	print greedy()

if __name__ == '__main__':
	main()