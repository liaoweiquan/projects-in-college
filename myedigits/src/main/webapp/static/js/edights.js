/*
	author:sgyp 18/4/22
*/

var gameMain = {
    start: function() {
        this.data = new Array();
        this.end = new Array();
        this.hstep = 0;
        this.ccnt = 0;

        var str = $("#jsonStr").val();
        var arr = eval(str);
        this.startstr = arr;
        document.getElementById('allS').style.display = 'block';
        document.getElementById('nextS').style.display = 'block';
        var k = 0;
        for (var i = 0; i < this.row; i++) {
            this.data[i] = [];
            for (var j = 0; j < this.col; this.data[i][j] = parseInt(arr[k]), j++, k++){
                if(parseInt(arr[k]) == 0){
                    this.x = i;
                    this.y = j;
                }
            }
            console.log("X:"+this.x + " Y:" + this.y);

        } //将data做一个3*3矩阵数组

        this.resetFlex();
        //先运行一次resetflex，渲染页面，再绑定事件

        document.addEventListener('mousedown', this.Logic, false); //鼠标滑动效果监听
        document.getElementById('container').addEventListener('touchstart', function(event) {
            event.preventDefault(); //阻止滚动

            startX = event.touches[0].pageX;
            startY = event.touches[0].pageY;

            //获取起始值
        });
        document.getElementById('container').addEventListener('touchend', function(event) {
            event.preventDefault();
            moveEndX = event.changedTouches[0].pageX;
            moveEndY = event.changedTouches[0].pageY;
            X = moveEndX - startX;
            Y = moveEndY - startY;

            if (Math.abs(X) > Math.abs(Y) && X > 0) {
                gameMain.goRight();
            }
            else if (Math.abs(X) > Math.abs(Y) && X < 0) {
                gameMain.goLeft();
            }
            else if (Math.abs(Y) > Math.abs(X) && Y > 0) {
                gameMain.goBottom();
            }
            else if (Math.abs(Y) > Math.abs(X) && Y < 0) {
                gameMain.goTop();
            }
            else {　　　　　　 //暂停游戏
                alert('暂停游戏')
                document.getElementById('container').style.display = "none";
                document.getElementById('peace').style.display = "block";
                document.getElementById('peace').addEventListener('click', function() {
                    document.getElementById('container').style.display = "flex";
                    document.getElementById('peace').style.display = "none";
                })
            }
        });
    },
    getCurMat: function(){
        var str = "";
        for(var i = 0; i < 3; i++){
            for(var j = 0; j < 3;j ++){
                str += this.data[i][j];
            }
        }
        console.log("cur str in js:" + str);
        return (str);
    },
    getStep: function(flag){
        var urlStr = $("#urlStr").val();
        this.ccnt ++;
        $.ajax({
            type:"post",
            url:urlStr + "/game.do",
            data:{"curStr":this.getCurMat()},
            success:function (data) {
                console.log(data);

                if(flag == 0){
                    // alert(data[0]);
                     // return data;
                    if(data[0] == 'U'){
                        gameMain.goTop();
                    }else if(data[0] == 'L'){
                        gameMain.goLeft();
                    }else if(data[0] == 'R'){
                        gameMain.goRight();
                    }else if(data[0] == 'D'){
                        gameMain.goBottom();
                    }
                    //Give step <= 3
                }else if(flag == 1){
                    alert(data);
                }

            }
        });
    },

    //move->移动模块
    sendData:function(){
        var o_hstep = document.getElementById('hstep');
        o_hstep.value = this.hstep;
        var o_ccnt = document.getElementById('ccnt');
        o_ccnt.value = this.ccnt;
        var o_str = document.getElementById('startstr');
        o_str.value = this.startstr;
        var submit_form = document.getElementById('submit_form');
        submit_form.submit();
        // location.href=("/detail.do");
    },
    sendData2:function(){
        if(confirm("你确定放弃本次游戏查看最终解?")){
            var o_str = document.getElementById('nowstr');
            o_str.value = this.getCurMat();
            var sub_form = document.getElementById('sub_form');
            sub_form.submit();
        }
    },
    move: function(callback) {
        var move1 = String(this.data); //把数组字符串化，进行操作
        callback(); //进行一次回调函数，用arrow function，this指向最近的对象,匿名函数回调指向window对象
        var move2 = String(this.data);
        if (move1 != move2) {

            if (this.gameOver()) { //判断游戏是否结束
                this.state = 0;
                this.resetFlex();
                if(confirm("游戏结束，跳转到详情页查看分数？")){
                    this.sendData();
                }
            }
            this.resetFlex();
        }
    },

    //resetFlex->重新更新视图模块
    resetFlex: function() {
        for (var i = 0; i < this.row; i++) {
            for (var j = 0; j < this.col; j++) {
                var oDiv = document.getElementById("item" + i + j);
                // console.log(this.data[i][j])
                if (this.data[i][j] != 0) {
                    oDiv.innerHTML = this.data[i][j];
                    oDiv.className = "item n" + this.data[i][j]
                } else { //否则
                    oDiv.innerHTML = "";
                    oDiv.className = "item n0";
                }
            }
        }
        //找到id为score的元素，设置其内容为score属性
        //document.getElementById("score").innerHTML = "分数：" + this.score;
        //如果游戏状态为结束
        if (this.state == 0) {
            document.getElementById("gameover").style.display = "block";
            document.getElementById("final").innerHTML = '最终得分：' + this.score;
            document.getElementById('container').style.display = "none";
        } else {
            document.getElementById("gameover").style.display = "none";

        }
    },
    //Logic->鼠标滑动模块
    Logic: function(event) {
        var e = event || window.event;
        var scrollX = document.documentElement.scrollLeft || document.body.scrollLeft;
        var scrollY = document.documentElement.scrollTop || document.body.scrollTop;
        var x = e.pageX || e.clientX + scrollX;
        var y = e.pageY || e.clientY + scrollY;
        document.onmouseup = function(event) {
            var e = event || window.event;
            var scrollX = document.documentElement.scrollLeft || document.body.scrollLeft;
            var scrollY = document.documentElement.scrollTop || document.body.scrollTop;
            var x1 = e.pageX || e.clientX + scrollX;
            var y1 = e.pageY || e.clientY + scrollY;
            if (Math.abs(x - x1) > Math.abs(y - y1) && (x - x1) < 0) {
                gameMain.goRight();
                //以上右滑
            } else if (Math.abs(x - x1) > Math.abs(y - y1) && (x - x1) > 0) {
                gameMain.goLeft();
            } else if (Math.abs(x - x1) < Math.abs(y - y1) && (y - y1) < 0) {
                gameMain.goBottom();
            } else if (Math.abs(x - x1) < Math.abs(y - y1) && (y - y1) > 0) {
                gameMain.goTop();
            }
        };
    },
    //gameOver->判断游戏结束模块
    gameOver: function() {
        return this.data[0][0] == 1 && this.data[0][1] == 2 && this.data[0][2] == 3 && this.data[1][0] == 8 && this.data[1][1] == 0 && this.data[1][2] == 4
            && this.data[2][0] == 7 && this.data[2][1] == 6 && this.data[2][2] == 5;
    },

    //向左
    goLeft: function() {
        this.move(() => {
            if(this.y > 0){
            this.data[this.x][this.y] = this.data[this.x][this.y - 1];
            this.data[this.x][this.y - 1] = 0;
            this.y --;
            this.hstep ++;
            this.resetFlex();
        }
        });
    },

    goRight: function() {
        this.move(() => {
            if(this.y < 2){
            this.data[this.x][this.y] = this.data[this.x][this.y + 1];
            this.data[this.x][this.y + 1] = 0;
            this.y ++;
            this.hstep ++;
            this.resetFlex();
        }
        });
    },

    goBottom: function() {
        this.move(() => {
            if(this.x < 2){
            this.data[this.x][this.y] = this.data[this.x + 1][this.y];
            this.data[this.x + 1][this.y] = 0;
            this.x ++;
            this.hstep ++;
            this.resetFlex();
        }
        });
    },
    goTop: function() {
        this.move(() => {
            if(this.x > 0){
            this.data[this.x][this.y] = this.data[this.x - 1][this.y];
            this.data[this.x - 1][this.y] = 0;
            this.x --;
            this.hstep ++;
            this.resetFlex();
        }
        });
    },
    row: 3, //横
    col: 3, //竖
    data: null, //用于存取格子数组
    score: 0, //得分
    state: 1, //状态值 0为游戏结束，1为游戏开始
    switchGame: true, //游戏暂停
    x: 0,
    y: 0
}
gameMain.start();
document.onkeydown=function (ev) {
    var e = event || window.event || arguments.callee.caller.arguments[0];
    if(e){
        switch (e.keyCode) {
            case 37:
                gameMain.goLeft();
                break;
            case 38:
                gameMain.goTop();
                break;
            case 39:
                gameMain.goRight();
                break;
            case 40:
                gameMain.goBottom();
                break;
        }
    }
}
document.getElementById('btn').addEventListener('click', function() {
    gameMain.row=3;
    gameMain.col=3;
    gameMain.score=0;
    gameMain.state=1;
    gameMain.data=null;
    gameMain.hstep = 0;
    gameMain.ccnt = 0;
    document.getElementById("gameover").style.display = "none";
    document.getElementById("final").style.display='none'
    document.getElementById('container').style.display = "flex";

    gameMain.start();
});

function send() {
    gameMain.sendData2();
}