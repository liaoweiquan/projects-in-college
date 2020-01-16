<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/19
  Time: 23:16
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- 上述3个meta标签*必须*放在最前面，任何其他内容都*必须*跟随其后！ -->
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="<%=basePath%>static/img/favorite.ico">

    <title>About</title>

    <!-- Bootstrap core CSS -->
    <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <link href="<%=basePath%>static/css/ie10-viewport-bug-workaround.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="<%=basePath%>static/css/help.css" rel="stylesheet">

    <!-- Just for debugging purposes. Don't actually copy these 2 lines! -->
    <!--[if lt IE 9]><script src="<%=basePath%>static/js/ie8-responsive-file-warning.js"></script><![endif]-->
    <script src="<%=basePath%>static/js/ie-emulation-modes-warning.js"></script>

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
    <script src="https://cdn.bootcss.com/html5shiv/3.7.3/html5shiv.min.js"></script>
    <script src="https://cdn.bootcss.com/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->
</head>

<body>

<div class="blog-masthead">
    <div class="container">
        <nav class="blog-nav">
            <a class="blog-nav-item active" href="index.do">Home</a>
            <a class="blog-nav-item" href="game.do">Game</a>
            <a class="blog-nav-item" href="help.do">Help</a>
            <a class="blog-nav-item" href="contact.do">Contact</a>
        </nav>
    </div>
</div>

<div class="container">

    <div class="blog-header">
        <h1 class="blog-title">关于</h1>
        <p class="lead blog-description">本站简介</p>
    </div>

    <div class="row">

        <div class="col-sm-8 blog-main">

            <div class="blog-post">
                <h2 class="blog-post-title">技术栈</h2>
                <p><h3>前端: </h3>
                    <img src="https://img.shields.io/badge/jsp-html-brightgreen.svg">
                    <img src="https://img.shields.io/badge/CSS-style-yellowgreen.svg">
                    <img src="https://img.shields.io/badge/JavaScipt-font--end-yellow.svg">
                    <img src="https://img.shields.io/badge/Bootstrap-v3.3.7-8a2be2.svg">
                    <img src="https://img.shields.io/badge/jQuery-1.12.4-blue.svg">
                    <img src="https://img.shields.io/badge/Ajax-I%2FO-orange.svg">
                </p>
                <br>
                <p><h3>后端: </h3>
                    <img src="https://img.shields.io/badge/Java-back--end-orange.svg">
                    <img src="https://img.shields.io/badge/apache-2.4.34-red.svg">
                    <img src="https://img.shields.io/badge/tomcat-8.0-lightgrey.svg">
                    <img src="https://img.shields.io/badge/MySQL-lamp-green.svg">
                    <img src="https://img.shields.io/badge/MyBatis-3.4.6-yellow.svg">
                </p>
                <hr>
                <h2 class="blog-post-title">开发日志</h2>
                <p class="text-muted">2018/12/18 A*算法模块设计、编码 A*算法单元测试</p>
                <p class="text-primary">2018/12/19 八数码游戏界面设计、编码</p>
                <p class="text-success">2018/12/20 优化A*算法 完善后端API</p>
                <p class="text-info">2018/12/21 完成前后端交互逻辑</p>
                <p class="text-warning">2018/12/22 项目部署至服务器</p>
                <p class="text-muted">2018/12/23 加入MyBatis持久化框架 Mysql数据库查询单元测试</p>
                <p class="text-info">2018/12/24 增加计分系统 分数传入数据库</p>
                <p class="text-primary">2018/12/25 优化页面逻辑和游戏</p>
                <p class="text-success">2018/12/26 增加任意状态的八数码解法</p>
                <p class="text-danger">2018/12/28 增加帮助文档页面和关于页面</p>
                <hr>
            </div><!-- /.blog-post -->

        </div><!-- /.blog-main -->

        </div><!-- /.blog-sidebar -->

    </div><!-- /.row -->

</div><!-- /.container -->

<footer class="blog-footer">
    <p>About page by <a href="https://github.com/yangyangu">@yangyangu</a>.</p>
    <p>
        <a href="#">Back to top</a>
    </p>
</footer>

<!-- Bootstrap core JavaScript
================================================== -->
<!-- Placed at the end of the document so the pages load faster -->
<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"></script>
<script>window.jQuery || document.write('<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"><\/script>')</script>
<script src="<%=basePath%>static/js/bootstrap.min.js"></script>
<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<script src="<%=basePath%>static/js/ie10-viewport-bug-workaround.js"></script>
</body>
</html>
