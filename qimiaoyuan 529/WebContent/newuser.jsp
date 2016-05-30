<%@ page import = "java.sql.*" language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>用户注册</title>
<style> 
input{ font-family:"Arial", "Tahoma", "微软雅黑", "雅黑"; border:1;}
 button { font-family:"Arial", "Tahoma", "微软雅黑", "雅黑"; border:0;
 vertical-align:middle; margin:8px; line-height:18px; font-size:18px } 
.btns { width:143px; height:40px; background:url("css/images/bg11.jpg") no-repeat left top; color:#FFF; border:0; } 
</style> 
<style type="text/css">
    a:link
    {
        color: #000000; 
        text-decoration: none;
        font-size: 12px;
    }
   
    a:visited 
    {
        color:#4F4F4F;
        font-size: 12px;
    }
    a:hover 
    {
        color: red; 
        text-decoration: underline;
        font-size: 12px;
    }
</style>
<script type="text/jscript" >
function show(){
        	var date = new Date();
        	var now = "";
        	now = date.getFullYear()+"年";
        	now = now + (date.getMonth()+1)+"月"
        	now = now + date.getDate()+"日";
        	now = now + date.getHours()+"时";
        	now = now + date.getMinutes()+"分";
        	now = now + date.getSeconds()+"秒";
        	
        	document.getElementById("nowDiv").innerHTML = now;
        	setTimeout("show()",1000);
}
function checkNULL()
{
	  var uid = document.form.uid.value;
	  var uname = document.form.uname.value;
	  var upassword = document.form.upassword.value;
	  var eupassword = document.form.eupassword.value;
	  var reg = /^[a-zA-Z0-9]{3,6}$/;
	  if(uid == "请输入你的登录名" || uname == "请输入你的昵称" ||upassword == "请输入你的密码" || eupassword == "请确认你的密码")
	  {
		  alert("输入不能为空！")
		  return false;
      }
	  else if(!reg1.test(uid))
	  {
		  alert("用户名格式不正确！")
		  return false;
	  }
	  else if(upassword != eupassword)
	  {
		  alert("两次输入的密码不一致！")
		  return false;
	  }
	  else 
		  return true;
}
</script>

</head>
<body onload = show()>
<div style = "width:100%;height:40px;background-color: #F0F0F0;">
<div style = "float:left;width:20%;height:100%;position: relative; left: 70px; top: 10px;">
<a href = "Landing.html" ><font color = green>请登陆</font></a>
<a href = "newuser.jsp">免费注册</a>
<a href = "http://www.cnblogs.com/qimiaoyuan/">关于我们</a>
</div>
<div  style = "float:right;font-size:14px;width:20%;height:100%;position: relative; right: 20px;  top: 13px;" id="nowDiv" ></div>
<div style = "float:right; width:15%;height:100%;position: relative;  top: 10px;" >
<a href = "http://www.cnblogs.com/qimiaoyuan/" ><font color = green>博客园</font></a>
<a href = "newuser.jsp"></a>
<a href = "newuser.jsp">注册需知</a>
</div>
</div>
<div style = "float:left;width:100%;height:80px;position:relative;left:60px;top:10px">
<a href = "http://www.baidu.com" style = "text-decoration:none">
     <font color="#FF0000" size="6+px"><b>奇妙缘</b><font color=#000000 size="4px"><b>&nbsp用户注册</b></font><br></font><font color="#FF0000" size="3px"><b>QiMiaoYuan</b></font></a>
</div>
<div style = "float:left;width:100%;height:40px;position:relative;left:40%;top:0px">
<font size = "5px" color = "#000000"><b>填写账号信息</b></font>
</div>
<hr align = "center" style="width:90%;">
<div style = "float:left;width:100%;height:350px;position:relative;left:35%;top:20px">
<form action="judgeuser.jsp"  method=post name=form onSubmit = "return checkNULL()">
  <br>&nbsp;&nbsp;&nbsp;&nbsp;用户名：
  <input type="text" name="uid" onkeyup="value=value.replace(/[/W]/g,'') " onbeforepaste="clipboardData.setData('text',clipboardData.getData('text').replace(/[^/d]/g,''))" autofocus="autofocus" value="请输入你的登陆名" onFocus="if(value==defaultValue){value='';this.style.color='#000'}" onBlur="if(!value){value=defaultValue;this.style.color='#999'}" style="color:#999999;width:170px;height:20px">
   <br>
   <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;昵称：
  <input type="text" name="uname"  value="请输入你的昵称" onFocus="if(value==defaultValue){value='';this.style.color='#000'}" onBlur="if(!value){value=defaultValue;this.style.color='#999'}" style="color:#999999;width:170px;height:20px">
   <br>
  <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;密码：
  <input type="password" name="upassword" value="请输入你的密码" onFocus="if(value==defaultValue){value='';this.style.color='#000'}" onBlur="if(!value){value=defaultValue;this.style.color='#999'}" style="color:#999999;width:170px;height:20px">
  <br>
  <br>确认密码：
  <input type="password" name="eupassword" value="请确认你的密码" onFocus="if(value==defaultValue){value='';this.style.color='#000'}" onBlur="if(!value){value=defaultValue;this.style.color='#999'}" style="color:#999999;width:170px;height:20px">
  
  <br>
  <br>
  <div style = "float = left;width = 20%;heigth = 30px;position:relative;left:6.6%;top:20px">
  <input type="submit"  class="btns" onmouseover="this.style.backgroundPosition='left -40px'" onmouseout="this.style.backgroundPosition='left top'"  value="注册" name="submit">
  </div>
</form>
</div>
<hr style=" height:2px;align:center;width:90%;border:none;border-top:1px dotted #185598;">
</body>
</html>