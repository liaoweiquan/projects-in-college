import pickle
import numpy as np
import cv2 as cv
import bp

def rgb2gray(rgb):
    return np.dot(rgb[...,:3], [0.299, 0.587, 0.114])

def img2class(imgFile): 

    img = cv.imread(imgFile, cv.IMREAD_GRAYSCALE)
    img = cv.resize(img,(20,20),interpolation=cv.INTER_CUBIC)
    img = img.reshape(400,-1)
    img = [i / 256 for i in img]
    img = np.array(img,dtype='float')
    img = img.reshape(1,-1)
    network = bp.LoadNN("MyNetWork_mini_bath_100node_1.txt")
    bp_res = network.getrs(img)
    return bp_res