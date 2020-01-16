package com.my.edigits.servlet;

import com.my.edigits.utils.AStarUtils;
import com.my.edigits.utils.Node;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;

@WebServlet("/solution.do")
public class SolutionServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String start = req.getParameter("nowstr");
        req.setAttribute("str",start);
        Integer[] strarr = new Integer[9];
        for(int i = 0; i < start.length(); ++ i){
            strarr[i] = Integer.valueOf(start.charAt(i) - '0');
        }

        AStarUtils aStarUtils = new AStarUtils(new Node(strarr));
        aStarUtils.search();
        ArrayList<String> solution = aStarUtils.getSolution();

        req.setAttribute("solution",solution);
        req.setAttribute("step",solution.size());
        req.getRequestDispatcher(req.getContextPath()+"/WEB-INF/view/biz/solution.jsp").forward(req, resp);

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        doGet(req, resp);
    }
}
