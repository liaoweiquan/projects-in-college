package com.my.edigits.servlet;

import com.google.gson.Gson;
import com.my.edigits.utils.AStarUtils;
import com.my.edigits.utils.Matutils;
import com.my.edigits.utils.Node;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Date;

@WebServlet("/game.do")
public class GameServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        System.out.println("GET is precessing...");
        // 游戏准备开始
        // 获取可解的初始序列
        Integer[] arr = Matutils.createMatrix();
        String str =  Matutils.getJsonStr(arr);
        System.out.println("Str: " + str);
        req.setAttribute("str",str);
        System.out.println();
        AStarUtils aStarUtils = new AStarUtils(new Node(arr));
        aStarUtils.search();
        ArrayList<String> solution = aStarUtils.getSolution();
        //获取初始解并放入request域
        req.setAttribute("fSolution",solution);
        req.setAttribute("fStep",solution.size());
        req.setAttribute("stime",new Date().getTime());
        // 跳转页面
        req.getRequestDispatcher(req.getContextPath()+"/WEB-INF/view/biz/game.jsp").forward(req,resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("Post is precessing...");
        String str = req.getParameter("curStr");
        System.out.println("curStr: " + str);
        Integer[] curArr = new Integer[9];
        for(int i = 0; i < str.length(); ++ i)
            curArr[i] = Integer.parseInt(str.substring(i,i + 1));

        AStarUtils aStarUtils = new AStarUtils(new Node(curArr));
        aStarUtils.search();
        ArrayList<String> stepList = aStarUtils.getStepList();
        for(int i = 0; i < stepList.size(); ++ i){
            System.out.print(stepList.get(i));
        }
        System.out.println(" ");
        Gson gson = new Gson();
        String json = gson.toJson(stepList);
        resp.setCharacterEncoding("UTF-8");
        resp.setContentType("application/json; charset=utf-8");
        PrintWriter writer = resp.getWriter();
        writer.append(json);
    }
}
