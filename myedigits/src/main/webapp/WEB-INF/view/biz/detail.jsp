<%@ page import="com.my.edigits.entity.Usr" %>
<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/20
  Time: 21:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="key" uri="http://java.sun.com/jsp/jstl/functions" %>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
    Usr usr = (Usr)request.getAttribute("usr");
    request.setAttribute("usr",usr);
%>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- 上述3个meta标签*必须*放在最前面，任何其他内容都*必须*跟随其后！ -->
    <title>Detail</title>
    <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">
    <link href="<%=basePath%>static/css/solution.css" rel="stylesheet">
    <link rel="icon" href="<%=basePath%>static/img/favorite.ico">
    <link href="<%=basePath%>static/css/help.css" rel="stylesheet">

</head>
<body>
<div class="blog-masthead">
    <div class="container">
        <nav class="blog-nav">
            <a class="blog-nav-item active" href="index.do">Home</a>
            <a class="blog-nav-item" href="game.do">Game</a>
            <a class="blog-nav-item" href="help.do">Help</a>
            <a class="blog-nav-item" href="about.do">About</a>
            <a class="blog-nav-item" href="contact.do">Contact</a>
        </nav>
    </div>
</div>
<div class="page-header">
    <h1>详情页<small>Here is your detail score and our A* solution.</small></h1>
</div>
<div align="center" style="margin-bottom: 5%;margin-left: 5%;margin-right: 5%">
    <input type="hidden" id="score" name="score" value="<%=request.getAttribute("score")%>">
    <div class="alert alert-success" role="alert">祝贺你!通过本关卡</div>
    <div class="alert alert-info" role="alert">一共走了:<%=request.getAttribute("hstep")%>步</div>
    <div class="alert alert-warning" role="alert">查看了:<%=request.getAttribute("ccnt")%>次"下一步"</div>
    <div class="alert alert-danger" role="alert">总分数: <%=request.getAttribute("score")%></div>
    <div>
        <div class="input-group">
            <span class="input-group-addon" id="basic-addon1">@</span>
            <input type="text" class="form-control" id="nickname" name="nickname" placeholder="输入你的昵称?" aria-describedby="basic-addon1">
        </div>
        <button class="btn btn-default" onclick="getName();" id="sub-btn" name="sub-btn">提交</button>
    </div>
    <br>
    <span class="label label-default">下面是 A* 算法给出的最优解</span>
    <input type="hidden" id="urlStr" value="<%=basePath%>">
    <input type="hidden" id="username" name="username" value="<%=usr.getUsername()%>">
</div>
<div class="containerv" id="tablediv" align="center">
    <c:forEach items="${solution}" var="key" varStatus="id">
        <table class="table table-striped">
            <thread>

                <c:if test="${id.index == 0}">初始状态 <br/> 本题从所选状态共<span class="badge"> ${cstep}步</span></c:if>
                <c:if test="${id.index > 0}">第${id.index}步</c:if>
                <tr>
                    <th class="myth">${fn:substring(key, 0, 1)}</th>
                    <th class="myth">${fn:substring(key, 1, 2)}</th>
                    <th class="myth">${fn:substring(key, 2, 3)}</th>
                </tr>
                <tr>
                    <th class="myth">${fn:substring(key, 3, 4)}</th>
                    <th class="myth">${fn:substring(key, 4, 5)}</th>
                    <th class="myth">${fn:substring(key, 5, 6)}</th>
                </tr>
                <tr>
                    <th class="myth">${fn:substring(key, 6, 7)}</th>
                    <th class="myth">${fn:substring(key, 7, 8)}</th>
                    <th class="myth">${fn:substring(key, 8, 9)}</th>
                </tr>
            </thread>
        </table>
        <br/>
        <br/>
    </c:forEach>
</div>


</body>

<!-- jQuery (Bootstrap 的所有 JavaScript 插件都依赖 jQuery，所以必须放在前边) -->
<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"></script>
<!-- 加载 Bootstrap 的所有 JavaScript 插件。你也可以根据需要只加载单个插件。 -->
<script src="<%=basePath%>static/js/bootstrap.min.js"></script>
<script src="<%=basePath%>static/js/detail.js"></script>

</html>
