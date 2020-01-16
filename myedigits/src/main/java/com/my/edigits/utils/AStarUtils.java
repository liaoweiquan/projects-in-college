package com.my.edigits.utils;

import java.util.*;

/**
 *
 *  AStar Algorithm Core
 *  A* 算法核心
 * @author yangyangu
 */
public class AStarUtils {

    private Node start;                         //初始序列
    private Node end;                           //结束序列
    private ArrayList<String> solution;         //解法数组
    private Queue<Pos> queue;                   //解法移动的数组
    private Queue<Node> openQueue;              //open表（优先队列实现）

    /**
     * 无初始和结尾的构造函数
     */
    public AStarUtils(){
        this.start = new Node();
        Integer[] arr = {1,2,3,8,0,4,7,6,5};
        this.end = new Node(arr);
        this.start.g = 0;
    }
    /**
     * 有初始状态的构造函数
     */
    public AStarUtils(Node start){
        this.start = start;
        Integer[] arr = {1,2,3,8,0,4,7,6,5};
        end = new Node(arr);
        this.start.g = 0;
        this.start.h = get_h(this.start);
        this.start.f = this.start.g + this.start.h;

        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                if(this.start.mat[i][j] == 0){
                    this.start.x = i;
                    this.start.y = j;
                }
                if(this.end.mat[i][j] == 0){
                    this.end.x = i;
                    this.end.y = j;
                }
            }
        }
        this.start.flag = 0;
        this.queue = new LinkedList<Pos>();
        this.openQueue = new PriorityQueue<Node>(1000,nodeComparator);
        this.solution = new ArrayList<String>();
    }

    /**
     * 有初始和结束状态的构造函数
     */
    public AStarUtils(Node start, Node end){
        this.start = start;
        this.end = end;
        this.start.g = 0;
        this.start.h = get_h(this.start);
        this.start.f = this.start.g + this.start.h;

        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                if(this.start.mat[i][j] == 0){
                    this.start.x = i;
                    this.start.y = j;
                }
                if(this.end.mat[i][j] == 0){
                    this.end.x = i;
                    this.end.y = j;
                }
            }
        }
        this.start.flag = 0;
        this.queue = new LinkedList<Pos>();
        this.openQueue = new PriorityQueue<Node>(1000,nodeComparator);
        this.solution = new ArrayList<String>();
    }

    /**
     * 优先队列用到的比较函数
     */
    public static Comparator<Node> nodeComparator = new Comparator<Node>() {
        @Override
        public int compare(Node o1, Node o2) {
            return (int)(o1.f - o2.f);
        }
    };

    /**
     * 获取绝对值
     * @param n
     * @return
     */
    private int get_abs(int n){
        return n >= 0 ? n : -n;
    }

    /**
     * 获取相异点的个数
     * @param node
     * @return
     */
    private int get_h(Node node){
        int h = 0;
        int old_x = 0, old_y = 0, end_x = 0, end_y = 0;
        for(int k = 1; k < 9; ++ k){
            for(int i = 0; i < 3; ++ i){
                for(int j = 0; j < 3; ++ j){
                    if(node.mat[i][j] == k){
                        old_x = i;
                        old_y = j;
                    }
                    //target x and y
                    if(end.mat[i][j] == k){
                        end_x = i;
                        end_y = j;
                    }
                }
            }
            h += get_abs(old_x - end_x) + get_abs(old_y - end_y);
        }
        return h;
    }

    /**
     * 判断是否到达终态
     * @param node
     * @return
     */
    private boolean isEnd(Node node){
        if(node ==  null)
            System.out.println("Node is null!!!");
        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                if(!Objects.equals(node.mat[i][j],end.mat[i][j]))
                    return false;
            }
        }
        return true;
    }

    /**
     * 搜索算法移动函数
     * 先构造新节点，将原有节点的矩阵复制到新节点中，再计算移动后的矩阵、h值，f值
     * @param flag
     * @param node
     */
    private void move(int flag, Node node){
        if(flag == 1 && node.x > 0){
            Node n = new Node();
            for(int i = 0; i < 3; ++ i){
                for(int j = 0; j < 3; ++ j){
                    n.mat[i][j] = node.mat[i][j];
                }
            }
            n.mat[node.x][node.y] = node.mat[node. x - 1][node.y];
            n.mat[node.x - 1][node.y] = 0;
            n.x = node.x - 1;
            n.y = node.y;
            n.flag = 3;
            n.prev = node;
            n.g = node.g + 1;
            n.h = get_h(n);
            n.f = n.g + n.h;
            openQueue.add(n);

        }else if(flag == 2 && node.y < 2){
            // go up
            Node n = new Node();
            for(int i = 0; i < 3; ++ i){
                for(int j = 0; j < 3; ++ j){
                    n.mat[i][j] = node.mat[i][j];
                }
            }
            // Swap value
            n.mat[node.x][node.y] = node.mat[node.x][node.y + 1];
            n.mat[node.x][node.y + 1] = 0;
            n.x = node.x;
            n.y = node.y + 1;
            n.flag = 4;
            n.prev = node;
            n.g = node.g + 1;
            n.h = get_h(n);
            n.f = n.g + n.h;
            openQueue.add(n);
        }else if(flag == 3 && node.x < 2){
            // turn right
            Node n = new Node();
            for(int i = 0; i < 3; ++ i){
                for(int j = 0; j < 3; ++ j){
                    n.mat[i][j] = node.mat[i][j];
                }
            }
            n.mat[node.x][node.y] = node.mat[node.x + 1][node.y];
            n.mat[node.x + 1][node.y] = 0;
            n.x = node.x + 1;
            n.y = node.y;
            n.flag = 1;
            n.prev = node;
            n.g = node.g + 1;
            n.h = get_h(n);
            n.f = n.g + n.h;
            openQueue.add(n);

        }else if(flag == 4 && node.y > 0){
            // go down
            Node n = new Node();

            for(int i = 0; i < 3; ++ i){
                for(int j = 0; j < 3; ++ j){
                    n.mat[i][j] = node.mat[i][j];
                }
            }
            n.mat[node.x][node.y] = node.mat[node.x][node.y - 1];
            n.mat[node.x][node.y - 1] = 0;
            n.x = node.x;
            n.y = node.y - 1;
            n.flag = 2;
            n.prev = node;
            n.g = node.g + 1;
            n.h = get_h(n);
            n.f = n.g + n.h;
            openQueue.add(n);
        }
    }

    /**
     * 节点拓展函数
     * @param node
     */
    private void expand(Node node){
        for(int i = 1; i < 5; ++ i){
            if(node.flag != i){
                move(i, node);
            }
        }
    }

    /**
     * 打印解 存储解法
     * @param node
     * @return
     */
    public int show(Node node){

        if(node == this.start){
            String str = "";
            for(int i = 0; i < 3; ++ i){
                for(int j = 0;j < 3; ++ j){
                    str += String.valueOf(node.mat[i][j]);
                    if(node.mat[i][j] == 0){
                        this.queue.offer(new Pos(i, j));
                    }
                }
            }
            solution.add(str);
            return 1;
        }
        else show(node.prev);
        String str = "";
        for(int i = 0; i < 3; ++ i){
            for(int j = 0; j < 3; ++ j){
                str += String.valueOf(node.mat[i][j]);
                if(node.mat[i][j] == 0){
                    this.queue.offer(new Pos(i,j));
                }
            }
        }

        solution.add(str);
        return 0;
    }

    /**
     * 启动搜索算法
     */
    public void search(){

        openQueue.add(start);

        while(true){
            Node firstNode = openQueue.poll();
            if(isEnd(firstNode)){
                show(firstNode);
                break;
            }
            expand(firstNode);
        }
    }

    /**
     * 获取解法
     * @return
     */
    public ArrayList<String> getSolution(){
        return solution;
    }

    /**
     * 获取解法数组
     * @return
     */
    public ArrayList<String> getStepList(){
        ArrayList<String> stepList = new ArrayList<String>();
        if(this.queue != null){
            Pos p = this.queue.poll();
            int preX = p.getX(), preY = p.getY();
            for(Pos pos: this.queue){
                int nowX = pos.getX();
                int nowY = pos.getY();
                if(nowX == preX){
                    // left or right
                    if(nowY == preY + 1){
                        //right
                        stepList.add("R");
                    }else if(nowY == preY - 1){
                        //left
                        stepList.add("L");
                    }

                }else if(nowY == preY){
                    //Up or Down
                    if(nowX == preX + 1){
                        //Down
                        stepList.add("D");
                    }else if(nowX == preX - 1){
                        //Up
                        stepList.add("U");
                    }
                }
                preX = nowX;
                preY = nowY;
            }
        }
        return stepList;
    }
}
