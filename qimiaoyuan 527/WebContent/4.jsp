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
    <title>My JSP '4.jsp' starting page</title>
    <style>
	a:link {text-decoration: none;}
	a:visited {color:green；text-decoration:none;}
	a:hover  {color:red;text-decoration:underline;}
	a:active {color:orange;text-decoration:blink;}
	div
	{
	   border:1px solid  #ccc;      
	margin:0px auto;
	padding:0px;
	width:98%;
	height:90px;
	background-color:white;
	}
</style>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
<script type="text/jscript" >
    
</script>
  </head>
  
  <body style="background-color:#e8f3f8">
    <% 
    String id=(String)session.getAttribute("id");
    session.setAttribute("id1", id);
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
	rs=sql.executeQuery("select * from note where id="+id+" order by time desc");
	System.out.println("Connection Successful!");   //如果连接成功 控制台输出Connection Successful! 
	 %><!-- <div style="width:100%;height:8px;"></div> --><%
	while(rs.next()){
		%>
		<div onmouseover="this.style.background='#fbedce'" onmouseout="this.style.background='white'" >
		<%
	out.print("<h4><font color=\"blue\"><a href=\"6.jsp?param="+rs.getString(6)+"\" target=\"_top\">&nbsp;&nbsp"+rs.getString(2)+"</a></font></h4><h5 align=\"right\">编辑时间："+rs.getString(6)+"&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"6.jsp?param="+rs.getString(6)+"\" target=\"_top\">查看</a>&nbsp;&nbsp;&nbsp;<a href=\"7.jsp?param="+rs.getString(6)+"\" target=\"_top\">修改</a>&nbsp;&nbsp;&nbsp;<a href=\"DeleteNote.jsp?param="+rs.getString(6)+"\" target=\"_top\">删除</a></h5>");
	%>
	</div>
	<%
	}
	dbConn.close();
	} catch (Exception e) {  
	e.printStackTrace();  
	}  
	%>
  </body>
</html>
