package com.my.edigits.servlet;

import com.my.edigits.utils.AStarUtils;
import com.my.edigits.utils.Matutils;
import com.my.edigits.utils.Node;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;

@WebServlet("/every.do")
public class EveryServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        String startarr = req.getParameter("startarr");
        String endarr = req.getParameter("endarr");
        System.out.println(startarr);
        System.out.println(endarr);
        Integer[] start = new Integer[9];
        Integer[] end = new Integer[9];
        //在这里判断一下是否有解！！没解或者非法输入说明用户修改了js文件
        String[] s_strs = startarr.split(",");
        String[] e_strs = endarr.split(",");
        Integer[] test1 = {0,0,0,0,0,0,0,0,0};
        Integer[] test2 = {0,0,0,0,0,0,0,0,0};
        for(int i = 0; i < 9; ++ i){
            start[i] = Integer.valueOf(s_strs[i]);
            end[i] = Integer.valueOf(e_strs[i]);
            ++ test1[start[i]];
            ++ test2[end[i]];
        }
        boolean isVaild = true;
        for(int i = 0; i < 9; ++ i){
            if(test1[i] != 1 || test2[i] != 1){
                isVaild = false;
                break;
            }
        }
        boolean hasSolution = Matutils.haveSolution(start,end);
        if(!isVaild || !hasSolution){
            req.getRequestDispatcher("/WEB-INF/view/error/404.jsp").forward(req,resp);
            return;
        }
        AStarUtils aStarUtils = new AStarUtils(new Node(start),new Node(end));
        aStarUtils.search();
        ArrayList<String> solution = aStarUtils.getSolution();

        req.setAttribute("solution",solution);
        req.setAttribute("step",solution.size() - 1);
        req.getRequestDispatcher("/WEB-INF/view/biz/solution.jsp").forward(req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
