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

    <title>Help</title>

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
            <a class="blog-nav-item" href="about.do">About</a>
        </nav>
    </div>
</div>

<div class="container">

    <div class="blog-header">
        <h1 class="blog-title">帮助文档</h1>
        <p class="lead blog-description">A*算法玩转八数码问题</p>
    </div>

    <div class="row">

        <div class="col-sm-8 blog-main">

            <div class="blog-post">
                <h2 class="blog-post-title">八数码游戏玩法</h2>
                <p class="blog-post-meta">December 20, 2018 by <a href="#">yangyangu</a></p>

                <p>游戏要求非常低，只需浏览器即可。支持移动端/电脑端，Chrome/IE10/...</p>
                <hr>
                <p>电脑端操作：方向键 or 鼠标按住滑动</p>
                <hr>
                <p>手机or平板： 按住滑动即可</p>
                <hr>
                <p>游戏规则非常简单，给定一个随机的初始状态，移动空白方块可使数字方块移动，直到到达如下状态：</p>
                <div align="center">
                    <th>
                        <tr>1</tr>
                        <tr>2</tr>
                        <tr>3</tr>
                    </th>
                    <br>
                    <th>
                        <tr>8</tr>
                        <tr>0</tr>
                        <tr>4</tr>
                    </th>
                    <br>
                    <th>
                        <tr>7</tr>
                        <tr>6</tr>
                        <tr>5</tr>
                    </th>
                </div>
                <br>
                <p>游戏非常简(bing)单(bu), 评分规则如下：</p>
                <p>给定初始分数100分，每过1分钟减少1分。网站会统计玩家和计算机使用的步数的差值，你的分数会减去这个差值的一半</p>
                <p>最后，再减去你查看下一步做法的次数(哼)</p>
                <hr>
                <h2>寻求A*算法帮助？</h2>
                <p></p>
                <h3>不放弃游戏？</h3>
                <p>只需点一下游戏界面的“下一步”即可</p>
                <h3>放弃游戏？</h3>
                <p>直接点击游戏界面的“查看最终解”</p>
                <p>但是，你的分数会直接清零，或者不计入服务器统计</p>
                <h3>完成游戏后</h3>
                <p>当然，完成游戏后仍然可以查看A*算法给出的最优解</p>
                <hr>
            </div><!-- /.blog-post -->

            <div class="blog-post">
                <h2 class="blog-post-title">A*算法的解析</h2>
                <p class="blog-post-meta">December 23, 2018 by <a href="#">yangyangu</a></p>

                <p>首先，本站给出的初始序列是有解的（针对标准结尾序列而言）</p>
                <br>
                <p>根据排列的相关知识，只要初始序列和目标序列的逆序数的奇偶性相同，那么必然有解</p>
                <hr>
                <p>其次，假设目标节点相异的个数g，每个节点在搜索树的层数为h，则每个节点的代价是f = g + h</p>
                <br>
                <p>搜索算法最初是向四个方向搜索，并计算出每个待拓展的节点的代价f，放入open表中</p>
                <br>
                <p>A*算法要找的是open表中代价最小的节点，优先拓展，最终得到的一定是最优解。</p>
                <br>
                <p>次优解由于代价更大而处在open表的某个位置不被拓展</p>
                <hr>
            </div><!-- /.blog-post -->

            <div class="blog-post">
                <h2 class="blog-post-title">本站A*算法的优化细节</h2>
                <p class="blog-post-meta">December 25, 2018 by <a href="#">yangyangu</a></p>

                <p>关键词：优先队列</p>
                <br>
                <p>前面提到了，A*算法会优先找代价f最小的节点进行拓展，那么算法的进一步优化就可以在这里做文章</p>
                <br>
                <p>一开始作者用的是遍历法找出f最小的节点。时间复杂度：插入为O(1)，查找为O(n)</p>
                <br>
                <p>虽然是线性的时间，但是open表到最后会越来越大，程序会在搜索最小节点上花费大量的时间</p>
                <br>
                <p>考虑用快速排序算法？时间复杂度：插入O(1), 查找O(nlogn)</p>
                <br>
                <p>显然没有变得更好</p>
                <p>说到排序，就想起了堆排序的过程（每次推出最小/最大的元素，再维护堆的性质）</p>
                <br>
                <p>而优先队列正是用了最小/最大堆（也可以用平衡二叉树）时间复杂度：插入为O(logn), 查找为O(1)</p>
                <br>
                <p>经过实践，大大缩短了A*算法在维护open表的时间</p>
            </div><!-- /.blog-post -->

            <nav>
                <ul class="pager">
                    <li><a href="#">Previous</a></li>
                    <li><a href="#">Next</a></li>
                </ul>
            </nav>

        </div><!-- /.blog-main -->

        <div class="col-sm-3 col-sm-offset-1 blog-sidebar">
            <div class="sidebar-module sidebar-module-inset">
                <h4>About</h4>
                <p>yangyangu <br><em>帮助文档</em><br>A*算法及其优化策略简介</p>
            </div>
            <div class="sidebar-module">
                <h4>Archives</h4>
                <ol class="list-unstyled">
                    <li><a href="#">December 20 2018</a></li>
                    <li><a href="#">December 23 2018</a></li>
                    <li><a href="#">December 25 2018</a></li>
                </ol>
            </div>
            <div class="sidebar-module">
                <h4>Elsewhere</h4>
                <ol class="list-unstyled">
                    <li><a href="https://github.com/yangyangu">GitHub</a></li>
                </ol>
            </div>
        </div><!-- /.blog-sidebar -->

    </div><!-- /.row -->

</div><!-- /.container -->

<footer class="blog-footer">
    <p>Creted <a href="#">Help document</a> by <a href="https://github.com/yangyangu">@yangyangu</a>.</p>
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
