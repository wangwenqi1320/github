<%@ page language="java" import="java.util.*" pageEncoding="utf-8" contentType="text/html; charset=utf-8"%>
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
    <title>My JSP '3.jsp' starting page</title>
    <style>

a:link {text-decoration: none;color:red;}

a:visited {color:green；text-decoration:none;}

a:hover  {color:blue;text-decoration:underline;}

a:active {color:orange;text-decoration:blink;}

</style>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

  </head>
  
  <body style="background:url(images/111.jpg);background-repeat:no-repeat">
  <div style="width:100%;height:100%">
  	<% 
  	String id=(String)session.getAttribute("id");
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
	rs=sql.executeQuery("select * from users where id='"+id+"'");
	System.out.println("Connection Successful!");   //如果连接成功 控制台输出Connection Successful! 
	if(rs.next()){
	out.println("<br><h4><font color=\"black\">&nbsp;你好！<font color=\"red\">"+rs.getString(2)+"</font></font></h2>");
	/* out.println("<h5>&nbsp;电子邮箱："+rs.getString(4)+"</h4>"); */
	}
	dbConn.close();
	} catch (Exception e) {  
	e.printStackTrace();  
	}  
	%>
	<div style="position:relative;left:10px;top:25px;">
	<a href="AddNote.html?param=<%=id%>" target="_top"><h5>&nbsp;1.添加新笔记</h5></a>
	</div>
	<div style="position:relative;left:10px;top:16px">
	<a href="Landing.html" target="_top"><h5>&nbsp;2.注销</h5></a>
	</div>
	<div style="position:relative;left:10px;top:8px">
	<a href="newuser.jsp" target="_top"><h5>&nbsp;3.注册新用户</h5></a>
	</div>
	<div style="position:relative;left:10px;top:0px">
	<a href="http://www.cnblogs.com/qimiaoyuan/" target="_top"><h5>&nbsp;4.博客园</h5></a>
	</div>
	</div>
  </body>
</html>
