<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/18
  Time: 18:16
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%--<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>--%>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
    String jsonStr = (String)request.getAttribute("str");
    Long stime = (Long) request.getAttribute("stime");
%>
<html>
    <head>
        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="icon" href="<%=basePath%>static/img/favorite.ico">
        <title>Game</title>
        <!-- Bootstrap -->
        <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">
        <link href="<%=basePath%>static/css/edigits.css" rel="stylesheet">
    </head>

    <body>
    <input type="hidden" id="jsonStr" value="<%=jsonStr%>">
    <input type="hidden" id="urlStr" value="<%=basePath%>">

    <form action="detail.do" id="submit_form" name="submit_form" method="post">
        <input type="hidden" id="hstep" name="hstep">
        <input type="hidden" id="ccnt" name="ccnt">
        <input type="hidden" id="startstr" name="startstr">
        <input type="hidden" id="stime" name="stime" value="<%=stime%>">
    </form>
    <form action="solution.do" id="sub_form" name="sub_form" method="post">
        <input type="hidden" id="nowstr" name="nowstr">
    </form>
        <main>
            <div class="main">
                <div id="gameover">游戏结束了</div>
                <div id="peace">暂停游戏,点击继续</div>
                <div id="final"></div>
                <div class="container" id="container">

                    <div class="item" id="item00"></div>
                    <div class="item" id="item01"></div>
                    <div class="item" id="item02"></div>

                    <div class="item" id="item10"></div>
                    <div class="item" id="item11"></div>
                    <div class="item" id="item12"></div>

                    <div class="item" id="item20"></div>
                    <div class="item" id="item21"></div>
                    <div class="item" id="item22"></div>


                </div>

                    <div style="width:50%;padding:0;margin:0;float:left;box-sizing:border-box;">
                        <button id="btn" onclick="location.href='game.do'">开始游戏</button>
                        <button id="everyS" onclick="if(confirm('确定?'))location.href='input.do'">求任意解</button>
                        <button id="backS" onclick="location.href='index.do'">返回首页</button>

                    </div>


                    <div style="width:50%;padding:0;margin:0;float:right;box-sizing:border-box;">
                        <button id="nextS" onclick="gameMain.getStep(0);">求下一步</button>
                        <button id="allS" onclick="send();">求最终解</button>
                        <button id="helpS" onclick="location.href='help.do'">帮助文档</button>
                    </div>

            </div>
            <%--<p style="text-align: right;color:red" id="score"></p>--%>
        </main>


        <script src="<%=basePath%>static/js/jquery-2.2.4.min.js"></script>
        <!-- 加载 Bootstrap 的所有 JavaScript 插件。你也可以根据需要只加载单个插件。 -->
    <script src="<%=basePath%>static/js/bootstrap.min.js"></script>
        <script src="<%=basePath%>static/js/edights.js"></script>
    </body>

</html>
