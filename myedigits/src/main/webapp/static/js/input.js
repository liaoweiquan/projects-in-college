function hasSolution(start, end) {
    var s_r = getRenum(start);
    var e_r = getRenum(end);
    console.log("s_r:" + s_r);
    console.log("e_r:" + e_r);
    return s_r % 2 == e_r % 2;
}
function getRenum(arr) {
    var sum = 0;
    for(var i = 0;i < 9; i ++){
        if(arr[i] != 0){
            for(var j = 0; j < i; j ++){
                if(arr[j] > arr[i]){
                    sum ++;
                }
            }
        }
    }
    return sum;
}

function isSingleVaild(arr) {
    var count = [0,0,0,0,0,0,0,0,0];
    for(var i = 0; i < 9; i++){
        count[arr[i]] ++;
    }
    for(var i = 0; i < 9; i++){
        if(count[i] != 1)
            return false;
    }
    return true;
}

function isVaild() {
    var start = [0,0,0,0,0,0,0,0,0];
    var end = [0,0,0,0,0,0,0,0,0];
    start[0] = document.getElementById('ips01').value;
    start[1] = document.getElementById('ips02').value;
    start[2] = document.getElementById('ips03').value;
    start[3] = document.getElementById('ips11').value;
    start[4] = document.getElementById('ips12').value;
    start[5] = document.getElementById('ips13').value;
    start[6] = document.getElementById('ips21').value;
    start[7] = document.getElementById('ips22').value;
    start[8] = document.getElementById('ips23').value;

    end[0] = document.getElementById('ipe01').value;
    end[1] = document.getElementById('ipe02').value;
    end[2] = document.getElementById('ipe03').value;
    end[3] = document.getElementById('ipe11').value;
    end[4] = document.getElementById('ipe12').value;
    end[5] = document.getElementById('ipe13').value;
    end[6] = document.getElementById('ipe21').value;
    end[7] = document.getElementById('ipe22').value;
    end[8] = document.getElementById('ipe23').value;

    console.log("input start:"+ start);
    console.log("input end:"+ end);
    if(isSingleVaild(start) && isSingleVaild(end)){
        if(hasSolution(start, end)){
            alert("有解");
            var o_start = document.getElementById('startarr');
            var o_end = document.getElementById('endarr');
            o_start.value = start;
            o_end.value = end;
            var o_form = document.getElementById('arr-submit');
            o_form.submit();
        }else{
            alert("无解");
        }
    }
    else{
        alert("输入不合法");
    }


}

