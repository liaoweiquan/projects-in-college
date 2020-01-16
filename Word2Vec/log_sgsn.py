import numpy as np
import re
import random
import collections
from string import punctuation
add_punc='，。、【 】 “”：；（）《》‘’{}？！⑦()、%^>℃：.”“^-——=&#@￥'
all_punc=punctuation+add_punc

# 对文本的预处理
class PreProcess(object):
	"""
	1、读取数据
	2、构建词表
	3、提供获取方法
	"""
	def __init__(self,preparams):
		self.sentences = []
		self.word = []
		self.filename = preparams["filename"]
		self.maxWinSize = preparams["maxWinSize"]
		self.negSampNumK = preparams["negSampNumK"]
		self.idx2token = None
		self.token2idx = None
		self.dataset = None
		self.centers = None
		self.contexts = None
		self.negatives = None
		self.tokenNum = 0
		self.read_data()
		self.build_data()
		self.get_center_and_contexts()
		self.get_negative_samples()

	def read_data(self):
		assert self.filename != "", "filename could not be empty!"
		# 读取语料库
		with open(self.filename, 'r', encoding='UTF-8-sig') as f:
			while True:
				line = f.readline()
				if line == None or line == "":
					break
				# 去除换行符、前后空格
				line = line.strip()
				line = re.sub(r"[0-9\s+\.\!\/_,$%^*()?;；:-【】+\"\']+|[+—！，;:。？、~@#￥%……&*（）]+", " ", line)
				if line != "":
					seg = re.split(" ",line)
					if seg[0] != '<':
						res = [s for s in seg if s != "" and s not in all_punc]
						if len(res) >= 3:
							self.sentences.append(res)
	def build_data(self):
		# 计算一个词被丢弃的概率
		def disp(idx):
			return np.random.uniform(0,1) < 1 - np.sqrt(1e-4 / self.counter[self.idx2token[idx]] * self.tokenNum)
		# 从读取的句子中提取词
		self.word = [w for s in self.sentences for w in s]
		# 计算词频
		self.counter = collections.Counter(self.word)
		# 过滤低频词 保留频数>=5的词
		self.counter = dict(filter(
			lambda x:x[1] >= 5, self.counter.items()
			))
		# 构造 索引-词 表
		self.idx2token = [c for c, _ in self.counter.items()]
		# 构造 词-索引 表
		self.token2idx = {c:idx for idx, c in enumerate(self.idx2token)}
		# self.dataset = [[self.token2idx[t] for t in s if t in self.token2idx] for s in self.sentences]
		self.tokenNum = len(self.idx2token)
		# self.subset = [[t for t in s if not disp(t)] for s in self.dataset]
		# 丢弃高频词后的词表
		self.subset = [[self.token2idx[t] for t in s if t in self.token2idx and not disp(self.token2idx[t])] for s in self.sentences]
		# 更新词表大小
		self.tokenNum = sum([len(s) for s in self.subset])

	def get_center_and_contexts(self):
		"""
		获取中心词及对应的上下文
		"""
		self.centers, self.contexts = [],[]
		for s in self.subset:
			if len(s) < 2:
				continue
			self.centers += s
			for idx in range(len(s)):
				winSize = np.random.randint(1, self.maxWinSize)
				idxs = list(range(max(0, idx - winSize), min(len(s), idx + 1 + winSize)))
				idxs.remove(idx)
				self.contexts.append([s[idx] for idx in idxs])
		# for center, context in zip(self.centers, self.contexts):
		# 	print('center', center, 'has contexts', context)
	def get_negative_samples(self):
		"""
		负采样
		根据word2vec论文 每个词采样权重设置为词频的0.75次方
		"""
		self.negatives, neg_tmp = [], []

		weight = [self.counter[w] ** 0.75 for w in self.idx2token]
		i = 0
		p = list(range(len(weight)))
		for context in self.contexts:
			negs = []
			while len(negs) < len(context) * self.negSampNumK:
				if i == len(neg_tmp):
					i = 0
					neg_tmp = random.choices(p, weight, k=int(1e5))
				neg = neg_tmp[i]
				i += 1
				# 负采样的词不可出现在上下文词汇中
				if neg not in set(context):
					negs.append(neg)
			self.negatives.append(negs)
		# print(self.negatives)

	# 提供相应属性的获取方法
	def get_num(self):
		return self.tokenNum
	def get_data(self):
		return self.centers, self.contexts, self.negatives
	def get_idx2token(self):
		return self.idx2token
	def get_token2idx(self):
		return self.token2idx
	def __repr__(self):
		return "PreProcess()"

# 词向量训练
class Word2Vec(object):
	"""
	word2vec的实现
	输入参数 word_size： 词表大小 embdding_size： 词向量维数 eta：学习率（步长）n_iters：迭代次数
	采用梯度上升法
	"""
	def __init__(self, w2vparams):
		self.word_size = w2vparams["word_size"]
		self.embdding_size = w2vparams["embdding_size"]
		self.w = np.random.normal(loc=0,scale=1,size=(self.word_size,self.embdding_size))
		self.theta = np.random.normal(loc=0,scale=1,size=(self.word_size,self.embdding_size))

	def sigmoid(self, x):
		return 1. / (1. + np.exp(-x))

	def fit(self, center, context, negative, eta=0.1, n_iters=10):
		"""
		训练函数
		输入为中心词、上下文词汇、负采样词汇
		"""
		y = np.zeros((len(negative)))
		cur_iter = 0
		while cur_iter < n_iters:
			for i in range(len(context)):
				e = 0
				for j in range(len(negative)):
					y_hat = self.sigmoid(np.dot(self.w[context[i]].reshape(1,-1), self.theta[negative[j]].reshape(-1,1)))
					g = (y[j] - y_hat) * eta
					e += g[0][0] * self.theta[negative[j]]
					self.theta[negative[j]] += g[0][0] * self.w[context[i]]
				# print("e",e)
			# 	break
			self.w[context[i]] += e
			cur_iter += 1
		# print("one fit done.")
	# 获取词向量
	def get_w(self):
		return self.w
	def __repr__(self):
		return "Word2Vec()"

def main():
	
	# 读取文本并构建词典
	preparams = {"filename":"two.txt","maxWinSize":2,"negSampNumK":4}
	preProcess = PreProcess(preparams)
	idx2token = preProcess.get_idx2token()
	# 词向量初始化
	w2vparams = {"word_size":len(idx2token),"embdding_size":100}
	w2v = Word2Vec(w2vparams)
	centers, contexts, negatives = preProcess.get_data()
	
	assert len(contexts) == len(centers) and len(contexts) == len(negatives)

	# 训练
	for i in range(len(centers)):
		w2v.fit(centers[i], contexts[i], negatives[i])
		print(i + 1, '/',len(centers),'done.')
	w2v_w = w2v.get_w()
	# 保存词向量
	np.save('w.npy',w2v_w)
	
	print("w.shape",w2v_w.shape)
	# 保存词表
	np.save('idx2token.npy', idx2token)
	print("done.")
	# print("len idx", len(idx2token))
if __name__ == '__main__':
	main()