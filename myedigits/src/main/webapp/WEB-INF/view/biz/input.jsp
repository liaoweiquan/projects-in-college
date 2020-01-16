<%--
  Created by IntelliJ IDEA.
  User: AngusXu
  Date: 2018/12/24
  Time: 15:47
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
    <title>Input</title>
    <link rel="icon" href="<%=basePath%>static/img/favorite.ico">
    <!-- Bootstrap core CSS -->
    <link href="<%=basePath%>static/css/bootstrap.min.css" rel="stylesheet">
    <style type="text/css">
        .td{width:50px;overflow:hidden}
    </style>
</head>
<body>
<div align="center"><h2>Input the Start state.</h2></div>
<br>
<div class="start" id="start" align="center">
    <tr>
        <td class="td"><input id="ips01"></td>
        <td class="td"><input id="ips02"></td>
        <td class="td"><input id="ips03"></td>
    </tr>
    <br/>
    <tr>
        <td class="td"><input id="ips11"></td>
        <td class="td"><input id="ips12"></td>
        <td class="td"><input id="ips13"></td>
    </tr>
    <br/>
    <tr>
        <td class="td"><input id="ips21"></td>
        <td class="td"><input id="ips22"></td>
        <td class="td"><input id="ips23"></td>
    </tr>
    <br/>
</div>
<br/>
<div align="center"><h2>Input the End state.</h2></div>
<br>
<div class="end" id="end" align="center">
    <tr>
        <td class="td"><input id="ipe01"></td>
        <td class="td"><input id="ipe02"></td>
        <td class="td"><input id="ipe03"></td>
    </tr>
    <br/>
    <tr>
        <td class="td"><input id="ipe11"></td>
        <td class="td"><input id="ipe12"></td>
        <td class="td"><input id="ipe13"></td>
    </tr>
    <br/>
    <tr>
        <td class="td"><input id="ipe21"></td>
        <td class="td"><input id="ipe22"></td>
        <td class="td"><input id="ipe23"></td>
    </tr>
    <br/>
</div>
<br/>
    <div align="center"><button class="btn btn-default" id="inp-submit" onclick="isVaild();" >提交</button></div>
</body>
<form action="every.do" name="arr-submit" id="arr-submit">
    <input type="hidden" id="startarr" name="startarr">
    <input type="hidden" id="endarr" name="endarr">
</form>
<script src="<%=basePath%>static/js/jquery-1.12.4.min.js"></script>
<script src="<%=basePath%>static/js/input.js"></script>
<script src="<%=basePath%>static/js/bootstrap.min.js"></script>
</html>
