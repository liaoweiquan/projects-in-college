<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/28
  Time: 10:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String path = request.getContextPath();
    String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<html>
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- 上述3个meta标签*必须*放在最前面，任何其他内容都*必须*跟随其后！ -->
    <title>Contact</title>
    <link rel="icon" href="<%=basePath%>static/img/favorite.ico">
    <!-- Bootstrap core CSS -->
    <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">
    <!-- Custom styles for this template -->
    <link href="<%=basePath%>static/css/help.css" rel="stylesheet">
</head>
<body>
<div class="blog-masthead">
    <div class="container">
        <nav class="blog-nav">
            <a class="blog-nav-item active" href="index.do">Home</a>
            <a class="blog-nav-item" href="game.do">Game</a>
            <a class="blog-nav-item" href="about.do">About</a>
            <a class="blog-nav-item" href="contact.do">Contact</a>
        </nav>
    </div>
</div>
<div class="panel panel-primary" style="margin-top: 5%">
    <div class="panel-heading">
        <h3 class="panel-title">
            联系我们
        </h3>
    </div>
        <div class="panel-body">
            Email<a href="mailto:angusxu2009@gmail.com">To: Angus</a>
        </div>
</div>
<div class="panel panel-danger">
    <div class="panel-heading">
        <h3 class="panel-title">
            提交Bug?
        </h3>
    </div>
    <div class="panel-body">
        欢迎提交bug
        <br>
        <a href="https://github.com/yangyangu/myedigits/issues">GitHub</a>
    </div>
</div>
<div class="panel panel-info">
    <div class="panel-heading">
        <h3 class="panel-title">
            喜欢这个项目?
        </h3>
    </div>
    <div class="panel-body">
        不妨点个start吧
        <br>
        <a href="https://github.com/yangyangu/myedigits">GitHub</a>
    </div>
</div>
<footer class="blog-footer">
    <p>About page by <a href="https://github.com/yangyangu">@yangyangu></a>.</p>
    <p>
        <a href="#">Back to top</a>
    </p>
</footer>

<!-- Bootstrap core JavaScript
================================================== -->
<!-- Placed at the end of the document so the pages load faster -->
<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"></script>
<script>window.jQuery || document.write('<script src="<%=basePath%>static/js/jquery.min.js"><\/script>')</script>
<script src="<%=basePath%>static/js/bootstrap.min.js"></script>
<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
<script src="<%=basePath%>static/js/ie10-viewport-bug-workaround.js"></script>
</body>
</html>
