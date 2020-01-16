package com.my.edigits.utils;

import com.alibaba.fastjson.JSON;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Random;

/**
 * Create matrix and judge the existence of solution
 * 生成矩阵
 * 判断是否存在解
 * @author yangyangu
 */
public class Matutils {

    /**
     * Create a matrix
     * @return
     */
    public static Integer[] createMatrix(){
        Integer[] arr = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        ArrayList<Integer> res = new ArrayList<Integer>();
        boolean flag = false;
        while(!flag){
            shuffle(arr);
            if(haveSolution(arr))
                flag = true;
        }
        return arr;
    }

    public static String getString(Integer[] arr){
        String str = "";
        for(int i = 0; i < arr.length; ++ i){
            str += arr[i];
        }
        return  str;
    }

    public static String getJsonStr(Integer[] arr){
        return JSON.toJSONString(arr);
    }

    /**
     * Shuffle the array
     * 随机打乱数组
     * @param arr
     */
    public static void shuffle(Integer[] arr){
        Random random = new Random();
        int length = arr.length;
        for(int i = length; i > 0; -- i){
            int randInd = random.nextInt(i);
            swap(arr, randInd, i - 1);
        }
    }

    /**
     * 自定义数组交换函数
     * @param arr
     * @param a
     * @param b
     */
    public static void swap(Integer[] arr, int a, int b){
        int t = arr[a];
        arr[a] = arr[b];
        arr[b] = t;
    }

    /**
     * 检测序列是否存在解
     * @param arr
     * @return
     */
    public static boolean haveSolution(Integer[] arr){
        Integer[] end = {1, 2, 3, 8, 0, 4, 7, 6, 5};
        int arr_ver = getreVersNum(arr);
        int end_ver = getreVersNum(end);
        if(arr_ver % 2 == end_ver % 2){
            System.out.println("arr_ver: " + arr_ver);
            System.out.println("end_ver: " + end_ver);
        }
        return  arr_ver % 2 == end_ver % 2;
    }

    /**
     * 给定初始和结尾，检测序列是否存在解
     * @param start
     * @param end
     * @return
     */
    public static boolean haveSolution(Integer[] start, Integer[] end){
        int start_ver = getreVersNum(start);
        int end_ver = getreVersNum(end);
        if(start_ver % 2 == end_ver % 2){
            System.out.println("arr_ver: " + start_ver);
            System.out.println("end_ver: " + end_ver);
        }
        return  start_ver % 2 == end_ver % 2;
    }

    /**
     * 获取序列的逆序数
     * @param arr
     * @return
     */
    public static int getreVersNum(Integer[] arr){
        int sum = 0;
        for(int i = 0; i < arr.length; ++i){
            if(arr[i] == 0) continue;
            else{
                for(int j = 0; j < i; ++ j){
                    if(arr[j] > arr[i]){
                        ++ sum;
                    }
                }
            }
        }
        return sum;
    }

    /**
     * 单元测试
     */
    @Test
    public void test(){
       System.out.println("Unit Test");
       Integer[] arr = createMatrix();
       String jsonstr = getJsonStr(arr);
       System.out.println(jsonstr);
    }
}
