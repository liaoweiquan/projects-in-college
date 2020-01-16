package com.my.edigits.servlet;

import com.my.edigits.dao.UsrDao;
import com.my.edigits.entity.Usr;
import com.my.edigits.utils.AStarUtils;
import com.my.edigits.utils.Node;
import com.my.edigits.utils.SqlSessionFactoryUtils;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;

@WebServlet("/detail.do")
public class DetailServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {

        String nickname = req.getParameter("nickname");
        String username = req.getParameter("username");

        System.out.println("nickname: " + nickname);
        System.out.println("username:" + username);
        SqlSessionFactoryUtils.initSqlSessionFactory();
        UsrDao usrDao = new UsrDao();
        Usr usr = usrDao.findUsr(username);
        System.out.println(usr.toString());
        usr.setNickname(nickname);
        usr = usrDao.changeUsr(usr);
        req.setAttribute("usr",usr);
        SqlSessionFactoryUtils.close();

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        Integer hstep = Integer.valueOf(req.getParameter("hstep"));
        Integer ccnt = Integer.valueOf(req.getParameter("ccnt"));
        String stimestr = req.getParameter("stime");
        Long stime = Long.valueOf(stimestr);
        Long etime = new Date().getTime();
        Double t = etime.doubleValue() - stime.doubleValue();
        System.out.println("用时t:" + t);
        Integer[] start = new Integer[9];
        String str = req.getParameter("startstr");
        System.out.println("hstep:"+hstep);
        System.out.println("ccnt:"+ccnt);
        System.out.println("str:"+ str);
        String[] strs = str.split(",");
        String startStr = "";
        for(int i = 0; i < strs.length; ++ i){
            start[i] = Integer.valueOf(strs[i]);
            startStr += strs[i];
        }

        AStarUtils aStarUtils = new AStarUtils(new Node(start));
        aStarUtils.search();
        ArrayList<String> solution = aStarUtils.getSolution();
        Integer cstep = solution.size();

        req.setAttribute("hstep",hstep);
        req.setAttribute("ccnt",ccnt);
        req.setAttribute("cstep",cstep - 1);
        req.setAttribute("solution",solution);
        Double score = 100 - (hstep < cstep ? cstep - hstep : hstep - cstep) * 0.5 - ccnt - t / 60000;
        req.setAttribute("score",String.format("%.3f",score));
        // 分数写入服务器
        SqlSessionFactoryUtils.initSqlSessionFactory();
        Usr usr = new Usr(String.valueOf(stime),startStr,hstep,cstep,ccnt,score,new Date());
        UsrDao usrDao = new UsrDao();
        usr = usrDao.addUsr(usr);
        req.setAttribute("usr",usr);
        SqlSessionFactoryUtils.close();
        req.getRequestDispatcher("/WEB-INF/view/biz/detail.jsp").forward(req,resp);
    }
}
