import numpy as np

def cos(a,b):
	return (sum(a * b)) / (np.sqrt(sum([i**2 for i in a])) * np.sqrt(sum([i**2 for i in b])))
def main():
	sim = {0:1}
	w = np.load("w.npy")
	print('w shape',w.shape)
	i = 1
	for wi in w[1:]:
		sim[i] = cos(w[0], wi)
		i += 1
	d = sorted(sim.items(),key=lambda item:item[1],reverse=True)
	# print(sim[:10])
	idx2token = np.load("idx2token.npy")
	print(idx2token)
	for i in d[:10]:
		print(idx2token[i[0]])
if __name__ == '__main__':
	main()
