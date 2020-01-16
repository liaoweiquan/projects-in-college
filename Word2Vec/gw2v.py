from gensim.models import word2vec
from string import punctuation
import re
def main():
	
	add_punc='，。、【 】 “”：；（）《》‘’{}？！⑦()、%^>℃：.”“^-——=&#@￥'
	all_punc=punctuation+add_punc
	lines = []
	with open("two.txt",'r',encoding='UTF-8-sig') as f:
	    while True:
	        line = f.readline()
	        if line == None or line == "":
	            break
	        line = re.sub(r'[{}]+'.format(all_punc),' ',line)
	        lines.append(line)
	with open("two.cut.txt",'w',encoding='UTF-8-sig') as f:
	    for line in lines:
	        f.write(line)
	


if __name__ == '__main__':
	main()