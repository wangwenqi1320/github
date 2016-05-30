<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<%@ page import="java.sql.*" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <title>My JSP '6.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
<style type="text/css" align="center">
div
{
/* border:1px solid black; */
}
#apDiv1 {
	width: 500px;
	margin:0 auto;
	height: 48px;
	text-align:center;
	color:white;
	position:relative;
	top:15px;
}
#apDiv2 {
	width: 800px;
	margin:0 auto;
	height: auto;
	text-align:center;
}
 .btns { width:100px; height:30px; color:#000;background-color:#00ccff; 1px solid black; } 
a:link {text-decoration: none;color:red;}

a:visited {color:green；text-decoration:none;}

a:hover  {color:blue;text-decoration:underline;}

a:active {color:orange;text-decoration:blink;}
</style>
  </head>
  
  <body style="background-image:url(images/body_bg2.jpg);">  
    <% request.setCharacterEncoding("utf-8");%>
  <%String time=new String(request.getParameter("param").getBytes("ISO-8859-1"),"utf-8");
  String id=(String)session.getAttribute("id1");
  	Statement sql;
	ResultSet rs;
	String driverName = "com.microsoft.sqlserver.jdbc.SQLServerDriver";   //加载JDBC驱动  
	String dbURL = "jdbc:sqlserver://localhost:1433; DatabaseName=qimiaoyuan";   //连接服务器和数据库 
	String userName = "sa";   //默认用户名  
	String userPwd = "sa";   //密码  
	Connection dbConn;
	try {  
	Class.forName(driverName);  
	dbConn = DriverManager.getConnection(dbURL, userName, userPwd); 
	sql=dbConn.createStatement();
	rs=sql.executeQuery("select * from note where time='"+time+"' and id='"+id+"'");
	System.out.println("Connection Successful!");   //如果连接成功 控制台输出Connection Successful! 
	rs.next();
		%>
		
		<div id="apDiv1"><h2><%out.print(rs.getString(2)); %></h2></div>
		<hr style="width: 800px; height:10px;border:none;border-top:10px groove skyblue;" align="center" />
		<div id="apDiv2" align="left">
		<textarea rows="18" cols="65" style="background-color:#e8f3f8;font-size:20px;text-align:left;" disabled="disabled"><%=rs.getString(3)%>
		<%
		dbConn.close();
		} catch (Exception e) {  
		e.printStackTrace();  
		}  
	  %>
	  
	 
	  </textarea>
	  </div>
	  <div style="float:left;position:relative;left:20%;top:10px">
	  
	  <button class="btns" onClick="window.location.href='try.jsp'" onmouseover="this.style.background='#0099ff'" onmouseout="this.style.background='#00ccff'" >返回</button>
	  </div>
	  <!-- 页脚区域 -->
	  <div style="width:100%;position:relative;top:33px;height:20px;">
	<hr style=" height:2px;align:left;width:100%;border:none;border-top:1px dotted white;">
	</div>
    <div style="float:left;position:relative;left:33%;top:45px;height:50px;">
    <p style="margin:0px auto;color:#fff;line-height:25px;text-align:center;">&lt;奇妙缘云笔记，随时随地记录一切&gt;</p>
    <p style="margin:0px auto;color:#fff;line-height:25px;text-align:center;">版权所有&copy;奇妙缘</p>
    </div>
  </body>
</html>
