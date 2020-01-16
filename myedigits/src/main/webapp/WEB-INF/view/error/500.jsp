<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/18
  Time: 18:35
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
    <link rel="icon" href="<%=basePath%>static/img/favorite.ico">
    <title>500Page</title>
    <!-- Bootstrap -->
    <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">
    <link href="<%=basePath%>static/css/edigits.css" rel="stylesheet">
    <style>
        .h1{
            font-size: 80px;
        }
    </style>
</head>
<body>
<div class="middle-box text-center animated fadeInDown">
    <h1 class="h1">500</h1>
    <h3>页面出错！</h3>
    <div>
        <h2>抱歉，貌似出Bug了！攻城狮正在紧张地Debug</h2>
        <button class="button btn btn-primary" onclick="location.href='index.do'">返回首页</button>
    </div>
</div>
<!-- jQuery (Bootstrap 的所有 JavaScript 插件都依赖 jQuery，所以必须放在前边) -->
<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"></script>
<!-- 加载 Bootstrap 的所有 JavaScript 插件。你也可以根据需要只加载单个插件。 -->
<script src="<%=basePath%>static/js/bootstrap.min.js"></script>
<script src="<%=basePath%>static/js/detail.js"></script>
</body>

</html>
