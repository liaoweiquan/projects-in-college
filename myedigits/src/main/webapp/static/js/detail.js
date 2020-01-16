function getName() {

    var nickname = $("#nickname").val();
    var username = $("#username").val();
    var urlStr = $("#urlStr").val();
    $.ajax({
        type:"get",
        url:urlStr + "/detail.do",
        data:{"nickname":nickname,
            "username": username
        },
        success:function () {
            document.getElementById("sub-btn").disabled=true;
            alert("Submit Success!");
        }
    });
}
