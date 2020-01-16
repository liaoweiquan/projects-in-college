
import numpy as np
import re

def get_act(x):
    act_vec = []
    for i in x:
        act_vec.append(1/(1+np.exp(-i)))
    act_vec = np.array(act_vec)
    return act_vec

class LoadNN(object):
    
    def __init__(self,filename):
        args = []
        with open(filename,'r') as f:
            while True:
                line = f.readline()
                if not line:
                    break
                pass
                args.append(line.strip())
        self.inp_num = int(args[0])
        self.hid_num = int(args[1])
        self.out_num = int(args[2])
        self.inp_lrate = float(args[3])
        self.hid_lrate = float(args[4])
        self.cost_time = []

        w_temp = []
        for i in range(5, 5 + self.inp_num):
            s1 = re.split(' ',args[i])
            for j in s1:
                w_temp.append(float(j))
        self.w1 = np.array(w_temp).reshape(self.inp_num, int(len(w_temp)/self.inp_num))
        # print(self.w1.shape)

        w_temp = []
        s1 = re.split(' ', args[5 + self.inp_num])
        for j in s1:
            w_temp.append(float(j))
        self.w2 = np.array(w_temp).reshape(int(len(w_temp)/self.out_num),self.out_num)
        # print(self.w2.shape)

        off_temp = []
        s1 = re.split(' ', args[5 + self.inp_num + 1])
        for j in s1:
            off_temp.append(float(j))
        self.hid_offset = np.array(off_temp)
        # print(self.hid_offset.shape)

        off_temp = []
        s1 = re.split(' ', args[5 + self.inp_num + 2])
        for j in s1:
            off_temp.append(float(j))
        self.out_offset = np.array(off_temp)
        # print(self.out_offset.shape)
    def getrs(self,img):
        img = np.array(img)
        hid_value = np.dot(img,self.w1) + self.hid_offset
        hid_act = get_act(hid_value)
        out_value = np.dot(hid_act,self.w2) + self.out_offset
        out_act = get_act(out_value)
        res = np.argmax(out_act)
        print('predict:',res)
        return res