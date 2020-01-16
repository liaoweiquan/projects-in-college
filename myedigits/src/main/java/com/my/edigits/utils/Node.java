package com.my.edigits.utils;

/**
 * List Node
 * 链表节点
 * @author yangyangu
 */


public class Node {
    public Integer[][] mat;
    public int x, y;
    public int f, g, h;
    public int flag; // Last move direction
    public Node prev;

    public Node(){
        mat = new Integer[3][3];
        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                mat[i][j] = 0;
            }
        }
        prev = null;
    }
    public Node(Integer[] arr){
        mat = new Integer[3][3];
        prev = null;
        int k = 0;
        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                mat[i][j] = arr[k ++];
            }
        }
    }
    public int getF(){
        return f;
    }
}
